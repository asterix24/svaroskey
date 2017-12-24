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

#include "keymap.h"
#include "hw/hw_keymap.h"
#include "hw/hw_boot.h"


#include <cfg/debug.h>
#define LOG_LEVEL  2
#define LOG_FORMAT 0

#include <cfg/log.h>

#include <common/usbfeature.h>

#include <cpu/irq.h>
#include <cpu/power.h>

#include <drv/sipo.h>
#include <drv/timer.h>
#include <drv/usbkbd.h>
#include <drv/usbser.h>
#include <drv/eeprom.h>
#include <drv/flash.h>

#include <io/kfile_block.h>

#include <kern/proc.h>

#define MAX_BRIGHTNESS 100
#define NUM_LED_ROWS   8
#define NUM_LED_COLS   8
#define NUM_LEDS       (NUM_LED_COLS * NUM_LED_ROWS)

static Sipo sipo;
static Eeprom eep;
static I2c i2c;
static Flash internal_flash;
static KFileBlock flash;

static UsbFeatureCtx usb_feature_ctx;
static UsbFeatureMsg usb_feature_msg;

static uint8_t leds_off[3]  = {0x00, 0x00, 0x00};

static void hw_init(void)
{
	reg32_t *AFIO;

	/* Disable JTAG function on PB3 and use it as GPIO */
	RCC->APB2ENR |= RCC_APB2_AFIO;
	AFIO = (reg32_t *)(AFIO_BASE + 4);
	*AFIO &= ~(0x07000000);
	*AFIO |=  (0x04000000);
}

static void init(void)
{
	/* Initialize low-level platform */
	hw_init();

	/* Enable all the interrupts */
	IRQ_ENABLE;

	/* Initialize debugging module (allow kprintf(), etc.) */
	kdbg_init();

	kprintf("\n\n==== Main HID App ====\n");

	/* Initialize system timer */
	timer_init();

	/* Kernel initialization */
	proc_init();

	/* Initialize SIPO */
	sipo_init(&sipo, 0, SIPO_DATAORDER_LSB);
	kfile_write(&sipo.fd, leds_off, sizeof(leds_off));

	flash_init(&internal_flash, FLASH_WRITE_ONCE);
	// trim flash to avoid problems with kfile_block
	kprintf("Trim start: %d, blocks: %ld\n", TRIM_START, internal_flash.blk.blk_cnt - TRIM_START);
	kblock_trim(&internal_flash.blk, TRIM_START, internal_flash.blk.blk_cnt - TRIM_START);
	kfileblock_init(&flash, &internal_flash.blk);

	/* init usb feature to run custom cmd. */
	usbfeature_init(&usb_feature_ctx, &usb_feature_msg, &flash.fd);
	usbfeature_setStatus(&usb_feature_ctx, FEAT_ST_APP);

	/* Initialize the USB keyboard device */
	usbkbd_eventRegister(); // For custom feature
	usbkbd_init(0);

	/* Initialize keymap */
	keymap_init();

	/* Initialize EEPROM */
	i2c_init(&i2c, I2C_BITBANG0, CONFIG_I2C_FREQ);
	eeprom_init(&eep, &i2c, EEPROM_24XX128, 0x00, false);

}

static void NORETURN feature_proc(void)
{
	/* Wait feature command from usb */
	while (1)
	{
		usbfeature_poll(&usb_feature_ctx);
	}
}

static void NORETURN scan_proc(void)
{
	UsbKbdEvent *event;

	/* Periodically scan the keyboard */
	while (1)
	{
		keymap_scan();

		if ((event = get_usb_report()) != NULL)
			usbkbd_sendEvent(event);

		timer_delay(1);
	}
}

int main(void)
{
	/* Hardware initialization */
	init();

	/* Sample process */
	proc_new(scan_proc, NULL, KERN_MINSTACKSIZE, NULL);
	proc_new(feature_proc, NULL, 0x400, NULL);

	while (1) {
		timer_delay(5000);
	}
}
