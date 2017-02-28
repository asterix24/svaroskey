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


int usbbootloader_write(void *buff, size_t len, struct CustomData *data)
{
	uint8_t *_buf = (uint8_t *)buff;
	kprintf("Write blk[%p", data->fd);
	size_t ret = kfile_write(data->fd, _buf, len);
	kprintf("%d]\n", ret);
	usbkbd_registerCallbackReply(0x17);
	return 0;
}

int usbbootloader_writeReply(void *buff, size_t len, struct CustomData *data)
{
	uint8_t *_buf = (uint8_t *)buff;
	kfile_read(data->fd, _buf, len);
	_buf[0] = 0x01;
	_buf[1] = 0x17;
	kprintf("Call Get: %d\n", len);

	return len;
}

int usbbootloader_nop(void *buff, size_t len, struct CustomData *data)
{
	(void)data;
	uint8_t *_buf = (uint8_t *)buff;
	kprintf("Nop[");
	for (size_t i = 0; i < len; i++)
		kprintf("%d", _buf[i]);
	kprintf("]\n");

	return 0;
}

int usbbootloader_reset(void *buff, size_t len, struct CustomData *data)
{
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

void usbbootloader_init(void)
{
}
