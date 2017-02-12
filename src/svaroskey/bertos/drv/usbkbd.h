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
 * \author Andrea Righi <arighi@develer.com>
 *
 * \brief Generic USB keyboard device driver.
 *
 * This module allows to create virtual keyboards.
 *
 * \attention The API is work in progress and may change in future versions.
 *
 * $WIZ$ module_name = "usbkbd"
 * $WIZ$ module_configuration = "bertos/cfg/cfg_usbkbd.h"
 * $WIZ$ module_depends = "usb"
 */

#ifndef USBKBD_H
#define USBKBD_H

#include <io/kfile.h>

/**
 * USB keyboard event descriptor.
 */
typedef struct UsbKbdEvent
{
	uint8_t mods;
	uint8_t codes[6];
} UsbKbdEvent;

typedef struct CustomData
{
	KFile *fd;
	size_t len;
} CustomData;

typedef int (*FeatureReport_t)(void *buff, size_t len, void *data);

void usbkbd_sendEvent(UsbKbdEvent *event);
void usbkbd_registerCallback(FeatureReport_t call, uint8_t id, void *data);
void usbkbd_registerCallbackReply(uint8_t id);
int usbkbd_init(int unit);

#endif /* USBKBD_H */
