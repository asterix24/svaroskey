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

#include "usbbootloader.h"
#include <drv/usbkbd.h>

#define TRIM_START           45
#define USBL_RESET           0x17
#define USBL_WRITE           0x13
#define USBL_NOP             0x15

struct CustomData
{
	KFile *fd;
};

int usbbootloader_write(void *buff, size_t len, struct CustomData *data);
int usbbootloader_writeReply(void *buff, size_t len, struct CustomData *data);
int usbbootloader_nop(void *buff, size_t len, struct CustomData *data);
int usbbootloader_reset(void *buff, size_t len, struct CustomData *data);
void usbbootloader_init(void);

#endif /* USBBOOTLOADER_H */
