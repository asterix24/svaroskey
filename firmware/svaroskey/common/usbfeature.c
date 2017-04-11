/**
 * \file
 * <!--
 * This file is part of BeRTOS.
 *
 * Bertos is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA  02110-1301  USA
 *
 * As a special exception, you may use this file as part of a free software
 * library without restriction.  Specifically, if other files instantiate
 * templates or use macros or inline functions from this file, or you compile
 * this file and link it with other files to produce an executable, this
 * file does not by itself cause the resulting executable to be covered by
 * the GNU General Public License.  This exception does not however
 * invalidate any other reasons why the executable file might be covered by
 * the GNU General Public License.
 *
 * Copyright 2010 Develer S.r.l. (http://www.develer.com/)
 *
 * -->
 *
 * \author Daniele Basile <asterix@develer.com>
 *
 * \brief report hid usb bootloader.
 */

#include "usbfeature.h"

#include <cfg/debug.h>
#define LOG_LEVEL  3
#define LOG_FORMAT 0

#include <cfg/log.h>

#include <cpu/power.h>
#include <cpu/types.h>

#include <drv/usbkbd.h>
#include <drv/flash.h>

#include <io/kfile_block.h>
#include <io/stm32.h>

#include <string.h>
#include <stdio.h>

#if 0
int usbfeature_write(UsbBootCtx *ctx, void *buff, size_t len)
{
	ASSERT(buff);
	ASSERT(local_fd);

	uint8_t *_buf = (uint8_t *)buff;
	memcpy(&usb_boot_payload, _buf, sizeof(UsbBootPayload));
	size_t ret = kfile_write(local_fd, usb_boot_payload.data, usb_boot_payload.len);

	usb_boot_reply.cmd = USBL_WRITE;
	usb_boot_reply.report_id = 0x1;

	if (ret != usb_boot_payload.len)
	{
		usb_boot_reply.status = BOOT_REPLY_ERR;
		usb_boot_reply.index = usb_boot_ctx.index;
	}
	else
	{
		usb_boot_reply.status = BOOT_REPLY_OK;
		usb_boot_reply.index = usb_boot_ctx.index++;
	}

	usbkbd_registerCallbackReply(USBL_REPLY);

	LOG_INFO("Write Flash..len[%u] ret[%u], reply registered\n", len, ret);
	return 0;
}

int usbfeature_initBoot(UsbBootCtx *ctx, void *buff, size_t len)
{
	ASSERT(buff);
	ASSERT(local_fd);

	(void)data;
	(void)len;
	uint8_t *_buf = (uint8_t *)buff;
	memcpy(&usb_boot_payload, _buf, sizeof(UsbBootPayload));

	usb_boot_reply.cmd = USBL_INITBOOT;
	usb_boot_reply.report_id = 0x1;
	usb_boot_reply.index = 0;
	usb_boot_reply.status = BOOT_REPLY_OK;

	usbkbd_registerCallbackReply(USBL_REPLY);
	LOG_INFO("Init Boot..\n");
	return 0;
}

#endif

typedef struct UsbFeatureTable {
	uint16_t id;
	FeatureReport_t call;
} UsbFeatureTable;

static int usbfeature_none(UsbFeatureCtx *ctx)
{
	ASSERT(ctx);
	ASSERT(ctx->msg);
	(void) *ctx;

	memset(ctx->msg->data, 0x0, sizeof(ctx->msg->data));
	sprintf((char *)ctx->msg->data, "Cmd Ok!");
	ctx->msg->len = sizeof("Cmd Ok!");

	LOG_INFO("NONE[%d].. len[%ld]\n", ctx->msg->cmd, ctx->msg->len);

	return 0;
}

static int usbfeature_echo(UsbFeatureCtx *ctx)
{
	ASSERT(ctx);
	LOG_INFO("ECHO[%d].. len[%ld]\n", ctx->msg->cmd, ctx->msg->len);
	return 0;
}


static int usbfeature_reset(UsbFeatureCtx *ctx)
{
	(void)ctx;

	LOG_INFO("Reset board..\n");

	#define SCB_AIRCR ((reg32_t *)(SCB_BASE + 0xC))
	#define SCB_AIRCR_VECTKEY   0x05FA0000
	#define SCB_AIRCR_RESET     BV(2)

	*SCB_AIRCR = SCB_AIRCR_VECTKEY | (*SCB_AIRCR & 0xffff) | SCB_AIRCR_RESET;

	return 0;
}

static const UsbFeatureTable feature_cmd_table[] =
{
	{ FEAT_NONE,    usbfeature_none  },
	{ FEAT_ECHO,    usbfeature_echo  },
	{ FEAT_RESET,   usbfeature_reset },
	{ 0,            NULL             }
};

FeatureReport_t usbfeature_searchCallback(uint8_t id)
{
	LOG_INFO("Search cmd[%x]\n", id);
	for (int i = 0;; i++)
	{
		if (feature_cmd_table[i].id == 0 && feature_cmd_table[i].call == NULL)
			return NULL;

		if (id == feature_cmd_table[i].id)
			return feature_cmd_table[i].call;
	}
	return NULL;
}

void usbfeature_init(UsbFeatureCtx *ctx, UsbFeatureMsg *msg, KFile *fd)
{
	ASSERT(fd);
	ASSERT(ctx);
	ASSERT(msg);

	memset(ctx, 0, sizeof(UsbFeatureCtx));
	memset(msg, 0, sizeof(UsbFeatureMsg));

	ctx->msg = msg;
	ctx->fd = fd;
}

