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
#include <io/stm32.h>


//static Sipo sipo;
//static Eeprom eep;
//static I2c i2c;
//static uint8_t leds_off[3]  = {0x00, 0x00, 0x00};

static void hw_init(void)
{
	reg32_t *AFIO;

	/* Disable JTAG function on PB3 and use it as GPIO */
	RCC->APB2ENR |= RCC_APB2_AFIO;
	AFIO = (reg32_t *)(AFIO_BASE + 4);
	*AFIO &= ~(0x07000000);
	*AFIO |=  (0x04000000);
}

#define EINK_BASE ((struct stm32_gpio *)GPIOA_BASE)
#define EINK_BUSY_PIN  BV(0)  // PA0
#define EINK_RST_PIN   BV(1)  // PA1
#define EINK_DC_PIN    BV(4)  // PA4
#define EINK_CS_PIN    BV(5)  // PA5
#define EINK_D0_PIN    BV(6)  // PA6 SCLK
#define EINK_D1_PIN    BV(7)  // PA7 SDIN

#define EINK_SCK_ACTIVE()   do { stm32_gpioPinWrite(EINK_BASE, EINK_D0_PIN, true);  } while(0)
#define EINK_SCK_INACTIVE() do { stm32_gpioPinWrite(EINK_BASE, EINK_D0_PIN, false); } while(0)

#define EINK_MOSI_HIGH()    do { stm32_gpioPinWrite(EINK_BASE, EINK_D1_PIN, true);  } while(0)
#define EINK_MOSI_LOW()     do { stm32_gpioPinWrite(EINK_BASE, EINK_D1_PIN, false); } while(0)

#define EINK_CS_ACTIVE()    do { stm32_gpioPinWrite(EINK_BASE, EINK_CS_PIN, false);  } while(0)
#define EINK_CS_INACTIVE()  do { stm32_gpioPinWrite(EINK_BASE, EINK_CS_PIN, true); } while(0)

#define EINK_DC_ACTIVE()    do { stm32_gpioPinWrite(EINK_BASE, EINK_DC_PIN, false);  } while(0)
#define EINK_DC_INACTIVE()  do { stm32_gpioPinWrite(EINK_BASE, EINK_DC_PIN, true); } while(0)

#define EINK_IS_BUSY()      (stm32_gpioPinRead(EINK_BASE, EINK_BUSY_PIN))


static void eink_send(uint8_t data, bool cmd)
{
	uint8_t shift = 0x80; // MSB (LSB = 1)
	//uint8_t shift = 1; // LSB
	ATOMIC(
		for (int i = 0; i < 8; i++)
		{
		/* Shift the i-th bit to MOSI */
		if (data & shift)
			EINK_MOSI_HIGH();
		else
			EINK_MOSI_LOW();

			/* Assert clock */
			EINK_SCK_ACTIVE();
			timer_udelay(2);
			/* De-assert clock */
			EINK_SCK_INACTIVE();
			timer_udelay(2);

			shift >>= 1; // MSB (LSB <<)
			//shift <<= 1; // LSB
		}
	);
}

static void eink_write(uint8_t cmd, uint8_t *data, size_t len)
{
	EINK_CS_ACTIVE();
	timer_udelay(1);
	EINK_DC_ACTIVE();
	eink_send(cmd, true);
	EINK_DC_INACTIVE();
	timer_udelay(1);


	if (len > 0)
		while (len--)
			eink_send(*data++, false);

	EINK_CS_INACTIVE();

	timer_udelay(2);

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
//	proc_init();

	/* Initialize SIPO */
	//sipo_init(&sipo, 0, SIPO_DATAORDER_LSB);
	//kfile_write(&sipo.fd, leds_off, sizeof(leds_off));


	RCC->APB2ENR |= RCC_APB2_GPIOA;
	stm32_gpioPinConfig(EINK_BASE, EINK_BUSY_PIN, GPIO_MODE_IPU, GPIO_SPEED_50MHZ);
	stm32_gpioPinConfig(EINK_BASE, EINK_DC_PIN | EINK_CS_PIN | EINK_D0_PIN | \
			EINK_D1_PIN | EINK_RST_PIN, GPIO_MODE_OUT_PP, GPIO_SPEED_50MHZ);

	stm32_gpioPinWrite(EINK_BASE, EINK_DC_PIN | EINK_D0_PIN | \
			EINK_D1_PIN, false);
	stm32_gpioPinWrite(EINK_BASE, EINK_RST_PIN | EINK_CS_PIN, false);

	kprintf("start up seq\n");
	timer_delay(50);
	stm32_gpioPinWrite(EINK_BASE, EINK_RST_PIN, true);
	kprintf("start up seq\n");
	timer_delay(1);
	stm32_gpioPinWrite(EINK_BASE, EINK_CS_PIN, true);
	kprintf("start up seq\n");
}


struct Cmd {
	uint8_t cmd;
	uint8_t data[3];
	size_t len;
};

static struct Cmd init_cmd[] = {
	{  0x1,  {0xcf, 0x00, 0x00}, 2},
	{  0xf,  {0x00, 0x00, 0x00}, 1},
	{  0x11, {0x03, 0x00, 0x00}, 1},
	{  0x44, {0x00, 0x0d, 0x00}, 2},
	{  0x45, {0x00, 0xcf, 0x00}, 2},
	{  0x4E, {0x00, 0x00, 0x00}, 1},
	{  0x4F, {0x00, 0x00, 0x00}, 1},


	{  0,    {0x00, 0x00, 0x00}, 0}
};

static struct Cmd update_cmd[] = {
	{  0x3c, {0x80, 0x00, 0x00}, 1},
	{  0x03, {0x10, 0x0a, 0x00}, 2},
	{  0x05, {0x00, 0x00, 0x00}, 1},
	{  0x75, {0x00, 0x00, 0x00}, 3},

	{  0x1A, {0x19, 0x00, 0x00}, 2},
	{  0x22, {0xf7, 0x00, 0x00}, 1},
	{  0x20, {0x00, 0x00, 0x00}, 0},

	{  0,    {0x00, 0x00, 0x00}, 0}
};

static uint8_t buff[2912];

int main(void)
{
	/* Hardware initialization */
	init();

	bool flag = true;
	while (1) {
		if (flag)
			memset(buff, 0xFF, sizeof(buff));
		else
			memset(buff, 0x00, sizeof(buff));

		flag = !flag;

		kprintf("Wait display\n");
		while(EINK_IS_BUSY())
			cpu_relax();

		kprintf("init\n");
		// init
		for (size_t i = 0; ; i++)
		{
			if (init_cmd[i].cmd == 0 && init_cmd[i].len == 0)
				break;

			eink_write(init_cmd[i].cmd, init_cmd[i].data, init_cmd[i].len);
		}

		// Data
		eink_write(0x24, buff, sizeof(buff));

		while(EINK_IS_BUSY())
			cpu_relax();


		// update
		for (size_t i = 0; ; i++)
		{
			if (update_cmd[i].cmd == 0 && update_cmd[i].len == 0)
				break;

			eink_write(update_cmd[i].cmd, update_cmd[i].data, update_cmd[i].len);
		}

		kprintf("update\n");

		timer_delay(5000);
	}
}
