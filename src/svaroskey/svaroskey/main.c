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
 * \brief BeRTOS virtual keyboard.
 *
 * This project implements a HID USB device using the Olimex STM32-P103
 * evaluation board. The virtual keyboard can be connected to the USB port of a
 * normal PC.
 *
 * The WAKE_UP button on the board can be pressed to send to the host the
 * keyboard scancodes that simulate the typing of http://www.bertos.org.
 *
 * NOTE: this only works if the keyboard layout on the host PC is set to "US"
 * (QWERTY).
 *
 * Example (keyboard detection on Linux):
 *
 * \verbatim
 * [24388.400573] usb 1-8.1.3: new full speed USB device using ehci_hcd and address 32
 * [24388.623957] usb 1-8.1.3: configuration #1 chosen from 1 choice
 * [24388.685827] input: BeRTOS USB Keyboard as /devices/pci0000:00/0000:00:1d.7/usb1/1-8/1-8.1/1-8.1.3/1-8.1.3:1.0/input/input18
 * [24388.688953] generic-usb 0003:FFFF:0000.0007: input,hidraw3: USB HID v1.10 Keyboard [BeRTOS USB Keyboard] on usb-0000:00:1d.7-8.1.3/input0
 * \endverbatim
 *
 */

#include "hw/hw_led.h"
#include "hw/hw_keymap.h"

#include <cfg/debug.h>

#include <cpu/irq.h>
#include <cpu/power.h>

#include <drv/kbd.h>
#include <drv/timer.h>
#include <drv/usbkbd.h>
#include <keymap.h>

#include <kern/proc.h>

static void init(void)
{
	/* Enable all the interrupts */
	IRQ_ENABLE;

	/* Initialize debugging module (allow kprintf(), etc.) */
	kdbg_init();

	/* Initialize system timer */
	timer_init();

	/* Initialize LED driver */
	LED_INIT();

	/* Kernel initialization */
	proc_init();

	/* Enable the WAKE_UP button on the board */
	kbd_init();

	/* Initialize the USB keyboard device */
	usbkbd_init(0);

	/* Initialize keymap */
	keymap_init();
}

/* Send scan code */
static void usb_send_key(scancode_t code)
{
	usbkbd_sendEvent((code & 0xff00) >> 8, code & 0x00ff);
}

static void NORETURN scan_proc(void)
{
	scancode_t * code;

	/* Periodically scan the keyboard */
	while (1)
	{
		keymap_scan();

		while ((code = keymap_get_next_code()) != NULL) {
			usb_send_key(*code);
			LED_OFF();
		}

		timer_delay(1);
	}
}

int main(void)
{
	/* Hardware initialization */
	init();

	/* Sample process */
	proc_new(scan_proc, NULL, KERN_MINSTACKSIZE, NULL);

	while (1)
		cpu_relax();
}
