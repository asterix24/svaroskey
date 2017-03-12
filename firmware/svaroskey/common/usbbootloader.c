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

#include "usbbootloader.h"

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

static KFile *local_fd;
static UsbBootCtx usb_boot_ctx;
static UsbBootReply usb_boot_reply;
static UsbBootPayload usb_boot_payload;
static uint32_t crc;

int usbbootloader_write(void *buff, size_t len, struct CustomData *data)
{
	ASSERT(buff);
	ASSERT(local_fd);

	(void)data;
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

static uint8_t echo_buff[64];

int usbbootloader_echo(void *buff, size_t len, struct CustomData *data)
{
	ASSERT(buff);
	ASSERT(local_fd);

	(void)data;
	uint8_t *_buf = (uint8_t *)buff;

	// Leave 2 byte for report id and command id
	size_t echo_len = MIN(len, sizeof(echo_buff)-2);
	LOG_INFO("ECHO..Recv len[%u], cpy len[%u]\n", len, echo_len);

	// Prepare already reply buffer with command and report id
	memset(echo_buff, 0, sizeof(echo_buff));
	memcpy(echo_buff, _buf, echo_len);
	usbkbd_registerCallbackReply(USBL_ECHO);
	return 0;
}

int usbbootloader_echoReply(void *buff, size_t len, struct CustomData *data)
{
	ASSERT(buff);
	ASSERT(local_fd);

	(void)data;
	uint8_t *_buf = (uint8_t *)buff;
	memcpy(_buf, echo_buff, len);
	LOG_INFO("ECHO Reply..ret[%u]\n", len);

	return len;
}

int usbbootloader_initBoot(void *buff, size_t len, struct CustomData *data)
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

int usbbootloader_reply(void *buff, size_t len, struct CustomData *data)
{
	ASSERT(buff);
	ASSERT(local_fd);

	(void)data;
	(void)len;
	uint8_t *_buf = (uint8_t *)buff;
	memcpy(_buf, &usb_boot_reply, sizeof(usb_boot_reply));

	memset(&usb_boot_reply, 0, sizeof(usb_boot_reply));
	LOG_INFO("Reply..\n");
	return sizeof(usb_boot_reply);
}

int usbbootloader_reset(void *buff, size_t len, struct CustomData *data)
{
	ASSERT(buff);
	ASSERT(local_fd);

	(void)buff;
	(void)len;
	(void)data;

	LOG_INFO("Reset board..\n");

	#define SCB_AIRCR ((reg32_t *)(SCB_BASE + 0xC))
	#define SCB_AIRCR_VECTKEY   0x05FA0000
	#define SCB_AIRCR_RESET     BV(2)

	*SCB_AIRCR = SCB_AIRCR_VECTKEY | (*SCB_AIRCR & 0xffff) | SCB_AIRCR_RESET;

	return 0;
}

void usbbootloader_init(KFile *fd)
{
	ASSERT(fd);

	local_fd = fd;
	memset(&usb_boot_ctx, 0, sizeof(usb_boot_ctx));
}

