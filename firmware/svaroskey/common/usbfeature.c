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
#include "crc32.h"

#include "hw/hw_boot.h"

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

typedef struct UsbFeatureTable
{
	uint16_t id;
	FeatureReport_t call;
} UsbFeatureTable;

INLINE void make_reply(UsbFeatureMsg *msg, \
		uint8_t st_code, const char *text, size_t len)
{
	ASSERT(msg);
	msg->data[0] = st_code;
	memcpy(&msg->data[1], text, len);
	msg->len = 1 + len;
}

static int usbfeature_none(UsbFeatureCtx *ctx)
{
	ASSERT(ctx);
	ASSERT(ctx->msg);
	(void) *ctx;

	ctx->flag = FEAT_ST_LOCK_SAFE;
	make_reply(ctx->msg, FEAT_REPLY_OK, "ok!", sizeof("ok!"));

	LOG_INFO("NONE[%d].. len[%ld]\n", ctx->msg->cmd, ctx->msg->len);
	return 0;
}

static int usbfeature_echo(UsbFeatureCtx *ctx)
{
	ASSERT(ctx);
	LOG_INFO("ECHO[%d].. len[%ld]\n", ctx->msg->cmd, ctx->msg->len);
	return 0;
}

static int usbfeature_status(UsbFeatureCtx *ctx)
{
	ASSERT(ctx);
	memset(ctx->msg->data, 0x0, USB_FEATURE_MSGLEN);
	make_reply(ctx->msg, ctx->status, "Status", sizeof("Status"));

	LOG_INFO("STATUS reply[%d]..len[%ld]\n", ctx->status, ctx->msg->len);

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

static int usbfeature_write(UsbFeatureCtx *ctx)
{
	ASSERT(ctx);
	size_t len = kfile_write(ctx->fd, ctx->msg->data, ctx->msg->len);
	memset(ctx->msg->data, 0x0, USB_FEATURE_MSGLEN);

	// Read written block to compute crc
	kfile_seek(ctx->fd, -len, KSM_SEEK_CUR);
	kfile_read(ctx->fd, ctx->msg->data, len);
	ctx->crc = crc32(ctx->msg->data, len, ctx->crc);

	if (len > 0)
	{
		make_reply(ctx->msg, FEAT_REPLY_OK, "Write ok.", sizeof("Write ok."));
	}
	else
	{
		make_reply(ctx->msg, FEAT_REPLY_WR_ERR, "Write Error.", sizeof("Write Error."));
		LOG_ERR("Error while write block\n");
	}

	LOG_INFO("WRITE[%d].. len[%ld] wrote[%u]\n", ctx->msg->cmd, ctx->msg->len, len);
	return 0;
}

struct WrCheck
{
	uint32_t crc;
	uint32_t fw_index;
	uint32_t fw_lenght;
};

static int usbfeature_checkWrite(UsbFeatureCtx *ctx)
{
	LOG_INFO("CHECK WRITE[%d].. len[%ld]\n", ctx->msg->cmd, ctx->msg->len);

	struct WrCheck wr_check;
	memcpy(&wr_check, ctx->msg->data, ctx->msg->len);

	if (wr_check.crc != ctx->crc)
	{
		make_reply(ctx->msg, FEAT_REPLY_CRC_ERR, \
				"CRC missmatch!", sizeof("CRC missmatch!"));

		LOG_ERR("CRC missmatch.. fw [%ld] != computed [%ld]\n", wr_check.crc, ctx->crc);

		goto exit;
	}

	BootMBR boot_mbr;
	boot_mbr.crc = wr_check.crc;
	boot_mbr.len = wr_check.fw_lenght;
	boot_mbr.mode = BOOT_APPMODE;
	boot_mbr.key = BOOTKEY;

	kfile_off_t mbr_offest = 0;
	if (ctx->status == FEAT_ST_APP)
		mbr_offest = FLASH_BOOT_SIZE;

	kfile_seek(ctx->fd, mbr_offest, KSM_SEEK_SET);
	size_t len = kfile_write(ctx->fd, &boot_mbr, sizeof(BootMBR));
	kfile_flush(ctx->fd);

	if (!len)
	{
		make_reply(ctx->msg, FEAT_REPLY_MBR_ERR, \
				"Unable to update MBR.", sizeof("Unable to update MBR."));

		LOG_ERR("Unable to update MBR.\n");

		goto exit;
	}

	make_reply(ctx->msg, FEAT_REPLY_OK, \
			"Ok, fw updated.", sizeof("Ok, fw updated"));
	LOG_INFO("Fw write correctly, MBR updated..\n");

exit:
	ctx->crc = 0;
	return 0;
}

static const UsbFeatureTable feature_cmd_table[] = {
	{ FEAT_STATUS,    usbfeature_status     },
	{ FEAT_NONE,      usbfeature_none       },
	{ FEAT_ECHO,      usbfeature_echo       },
	{ FEAT_WRITE,     usbfeature_write      },
	{ FEAT_CHK_WRITE, usbfeature_checkWrite },
	{ FEAT_RESET,     usbfeature_reset      },
	{ 0,              NULL                  }
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

void usbfeature_poll(UsbFeatureCtx *ctx)
{
	memset(ctx->msg, 0x0, sizeof(UsbFeatureMsg));
	ssize_t len = usbkbd_featureRead(ctx->msg, sizeof(UsbFeatureMsg), -1);
	if (len > 0)
	{
		FeatureReport_t call = usbfeature_searchCallback(ctx->msg->cmd);

		if (call)
		{
			int ret = 0;
			if ((ret = call(ctx)) < 0)
			{
				make_reply(ctx->msg, FEAT_REPLY_ERR, "Cmd Fail!", sizeof("Cmd Fail!"));
				LOG_ERR("Feature Callback, fail! [%d]\n", ret);
			}

			usbkbd_featureWrite(ctx->msg, sizeof(UsbFeatureMsg), 250);
			LOG_INFO("Feature Write cmd[%d] len[%u] {%s}\n", \
					ctx->msg->cmd, sizeof(UsbFeatureMsg), ctx->msg->data);
		}
	}
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

