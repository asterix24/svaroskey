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

#include "keyboard.h"
#include "layouts.h"

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

#include <struct/list.h>

#include <kern/proc.h>
#include <kern/msg.h>
#include <kern/signal.h>

#include <mware/event.h>

#define MAX_BRIGHTNESS 100
#define NUM_LED_ROWS   8
#define NUM_LED_COLS   8
#define NUM_LEDS       (NUM_LED_COLS * NUM_LED_ROWS)

static Sipo sipo;
static Eeprom eep;
static I2c i2c;
static Flash internal_flash;
static KFileBlock flash;

static PressedKeyEvent pressed_keys[5];
static MsgPort key_event_port;
static List free_event;


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


	hw_keymap_init();

	/* Initialize system timer */
	timer_init();

	/* Kernel initialization */
	proc_init();

	/* Initialize SIPO */
	sipo_init(&sipo, 0, SIPO_DATAORDER_LSB);
	kfile_write(&sipo.fd, leds_off, sizeof(leds_off));

	flash_init(&internal_flash, FLASH_WRITE_ONCE);
	// trim flash to avoid problems with kfile_block
	LOG_INFO("Trim start: %d, blocks: %ld\n", TRIM_START, internal_flash.blk.blk_cnt - TRIM_START);
	kblock_trim(&internal_flash.blk, TRIM_START, internal_flash.blk.blk_cnt - TRIM_START);
	kfileblock_init(&flash, &internal_flash.blk);

	/* init usb feature to run custom cmd. */
	usbfeature_init(&usb_feature_ctx, &usb_feature_msg, &flash.fd);
	usbfeature_setStatus(&usb_feature_ctx, FEAT_ST_APP);

	///* Initialize the USB keyboard device */
	usbkbd_eventRegister(); // For custom feature
	usbkbd_init(0);

	/* Initialize keymap */
	hw_keymap_init();

	/* Initialize EEPROM */
	i2c_init(&i2c, I2C_BITBANG0, CONFIG_I2C_FREQ);
	eeprom_init(&eep, &i2c, EEPROM_24XX128, 0x00, false);

	layout_init();

}

static void NORETURN feature_proc(void)
{
	/* Wait feature command from usb */
	while (1)
	{
		usbfeature_poll(&usb_feature_ctx);
	}
}

static void dump(PressedKeyEvent *ev)
{
	kputs("Pressed: [");
	for (size_t i = 0; i < ev->len; i++)
		kprintf("%d ", ev->key_index[i]);

	kputs("]\n");
}

static void NORETURN scan_proc(void)
{
	/* Periodically scan the keyboard */
	while (1)
	{
		if (LIST_EMPTY(&free_event))
		{
			LOG_WARN("No enough slot for events\n");
			continue;
		}

		PressedKeyEvent *ev = NODE_TO_KEYEV(list_remTail(&free_event));
		ev->len = hw_keymap_scan(ev->key_index, MAX_PRESSED_KEY);

		if (ev->len == 0)
		{
			memset(ev->key_index, 0, MAX_PRESSED_KEY);
			ev->len = 0;

			ADDHEAD(&free_event, KEYEV_TO_NODE(ev));
			continue;
		}

		msg_put(&key_event_port, &ev->msg);
		timer_delay(150);
	}
}

int main(void)
{
	/* Hardware initialization */
	init();

	/* Sample process */
	proc_new(scan_proc, NULL, KERN_MINSTACKSIZE, NULL);
	proc_new(feature_proc, NULL, 0x400, NULL);

	msg_initPort(&key_event_port, event_createSignal(proc_current(), SIG_USER0));

	LIST_INIT(&free_event);
	for (size_t i = 0; i < countof(pressed_keys); i++) {
		Node *n = KEYEV_TO_NODE(&pressed_keys[i]);
		ADDTAIL(&free_event, n);
	}

	while (1)
	{
		Node *key_node_item;
		sig_wait(SIG_USER0);
		PressedKeyEvent *m = containerof(msg_get(&key_event_port), PressedKeyEvent, msg);
		//dump(m);

		UsbKbdEvent event;
		memset(&event, 0x0, sizeof(UsbKbdEvent));

		if (layout_usbEvent(&event, m) < 0)
		{
			LOG_ERR("Layout event error\n");
			goto free_node;
		}

		// send and release pressed key.
		usbkbd_sendEvent(&event);
		memset(&event, 0x0, sizeof(UsbKbdEvent));
		usbkbd_sendEvent(&event);

free_node:
		key_node_item = KEYEV_TO_NODE(m);
		if (key_node_item )
			ADDHEAD(&free_event, key_node_item);
	}

}

