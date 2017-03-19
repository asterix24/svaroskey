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
 * \brief report hid usb bootloader interface.
 */

#ifndef USBBOOTLOADER_H
#define USBBOOTLOADER_H

#include <drv/usbkbd.h>
#include <io/kfile.h>

#define USBL_NONE            0xFF
#define USBL_ECHO            0x0
#define USBL_REPLY           0x2
#define USBL_INITBOOT        0x3
#define USBL_WRITE           0x4
#define USBL_RESET           0x17

#define BOOTKEY              0x1317
#define BOOT_SAFEMODE        0x1

#define BOOT_REPLY_OK        1
#define BOOT_REPLY_ERR       2

#define USB_BOOT_MSGLEN     (64 - (sizeof(uint32_t) + \
                                 2*sizeof(uint8_t) + \
                                 1*sizeof(uint16_t)))

typedef struct UsbBootMsg
{
	uint8_t report_id;
	uint8_t cmd;
	uint16_t crc;
	uint32_t len;
	uint8_t data[USB_BOOT_MSGLEN];
} UsbBootMsg;

typedef struct UsbBootCtx
{
	KFile *fd;
	uint16_t flag;
	uint16_t fw_index;
	uint32_t fw_lenght;
	UsbBootMsg *msg;
} UsbBootCtx;

//int usbbootloader_initBoot(UsbBootCtx *ctx, void *buff, size_t len);
//int usbbootloader_write(UsbBootCtx *ctx, void *buff, size_t len);
int usbbootloader_reset(UsbBootCtx *ctx, void *buff, size_t len);
int usbbootloader_echo(UsbBootCtx *ctx, void *buff, size_t len);
int usbbootloader_reply(UsbBootCtx *ctx, void *buff, size_t len);
void usbbootloader_init(UsbBootCtx *ctx, UsbBootMsg *msg, KFile *fd);

#endif /* USBBOOTLOADER_H */

