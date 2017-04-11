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
 * Copyright 2017 Develer S.r.l. (http://www.develer.com/)
 *
 * -->
 *
 * \author Daniele Basile <asterix@develer.com>
 *
 * \brief report hid usb feature interface.
 */

#ifndef USBFEATURE_H
#define USBFEATURE_H

#include <drv/usbkbd.h>
#include <io/kfile.h>

#define FEAT_ERR             0xFF
#define FEAT_NONE            0x0
#define FEAT_ECHO            0x1
#define FEAT_INITBOOT        0x2
#define FEAT_WRITE           0x3
#define FEAT_RESET           0x17

#define BOOTKEY              0x1317
#define BOOT_SAFEMODE        0x1

#define BOOT_REPLY_OK        1
#define BOOT_REPLY_ERR       2

#define USB_FEATURE_MSGLEN     (64 - (sizeof(uint32_t) + \
                                 2*sizeof(uint16_t)))

typedef struct UsbFeatureMsg
{
	uint16_t cmd;
	uint16_t crc;
	uint32_t len;
	uint8_t data[USB_FEATURE_MSGLEN];
} UsbFeatureMsg;

typedef struct UsbFeatureCtx
{
	KFile *fd;
	uint16_t flag;
	uint16_t fw_index;
	uint32_t fw_lenght;
	UsbFeatureMsg *msg;
} UsbFeatureCtx;


typedef int (*FeatureReport_t)(UsbFeatureCtx *ctx);

/* Commands */
void usbfeature_init(UsbFeatureCtx *ctx, UsbFeatureMsg *msg, KFile *fd);
FeatureReport_t usbfeature_searchCallback(uint8_t id);

#endif /* USBFEATURE_H */

