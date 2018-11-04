/**
 * \file
 * <!--
 * Copyright 2018 Daniele Basile <asterix24@gmail.com>
 * All Rights Reserved.
 * -->
 *
 * \brief Keyboard Map
 *
 * \author Daniele Basile <asterix24@gmail.com>
 */

#include "keyboard.h"

#include "cfg/cfg_keymap.h"

#include <cfg/macros.h>

#include <io/stm32.h>
#include <drv/timer.h>
#include <drv/gpio_stm32.h>
#include <drv/clock_stm32.h>

#include <struct/list.h>

static struct stm32_gpio * const port_mappings[] = {
	((struct stm32_gpio *)GPIOA_BASE),
	((struct stm32_gpio *)GPIOB_BASE),
	((struct stm32_gpio *)GPIOC_BASE),
};

#if CFG_KEYBOARD_LAYOUT == KEYBOARD_PETROSKEY_LAYOUT
#include "hw/petroskey.c"
#else
#error No layout defined
#endif

bool hw_keymap_read(uint8_t index)
{
	struct stm32_gpio *col_port = port_mappings[keyboard_layout[index].col_port_idx];
	struct stm32_gpio *row_port = port_mappings[keyboard_layout[index].row_port_idx];

	uint8_t row_id = keyboard_layout[index].row;
	uint8_t col_id = keyboard_layout[index].col;

	stm32_gpioPinConfig(row_port, BV(row_id), GPIO_MODE_IPD, GPIO_SPEED_50MHZ);

	/* Select Column */
	stm32_gpioPinWrite(col_port, BV(col_id), 1);

	timer_udelay(5);

	/* Read column */
	bool ret = stm32_gpioPinRead(row_port, BV(row_id));

	KEYBOARD_DISABLE_COL();
	KEYBOARD_DISABLE_ROW();

	return ret;
}

static uint16_t key_bounce[KEYBOARD_LAYOUT_NUM_KEYS];
static uint8_t key_status[KEYBOARD_LAYOUT_NUM_KEYS];

#define KEY_RELEASE_BOUNCE  3
#define KEY_PRESS_BOUNCE    2


void hw_keymap_pushKey(KeyScanCtx *ctx, uint8_t index, uint8_t status)
{
	size_t  free_index = 0;
	for (int i = MAX_KEY_STATUS - 1; i >= 0; i--)
	{
		if (!(ctx->status[i] & KEY_CHANGED))
			free_index = i;

		if (index == ctx->index[i])
		{
			ctx->status[i] = status | KEY_CHANGED;
			ctx->index[i] = index;
			return;
		}
	}

	ctx->index[free_index] = index;
	ctx->status[free_index] = status | KEY_CHANGED;
}

void hw_keymap_scan(KeyScanCtx *ctx)
{
	for (int i = 0; i < KEYBOARD_LAYOUT_NUM_KEYS; i++)
	{
		// Check key status, and keys where not elapse bounce
		if (key_bounce[i] != 0)
		{
			//kprintf("dec[%d] %d\n", i, key_bounce[i]);
			key_bounce[i]--;
			continue;
		}

		// For pressed key that bounce time was elapsed
		if (key_status[i] == KEY_PRESSED && !hw_keymap_read(i))
		{
			// good key, put in a message
			key_status[i] = KEY_RELEASE;
			key_bounce[i] = KEY_RELEASE_BOUNCE;

			// update key status map
			//kprintf("release[%d]\n", i);
			hw_keymap_pushKey(ctx, i, key_status[i]);
		}

		// No pressed already, new key found
		if (key_status[i] == KEY_RELEASE && hw_keymap_read(i))
		{
			key_status[i] = KEY_PRESSED;
			key_bounce[i] = KEY_PRESS_BOUNCE;

			// update key status map
			//kprintf("pressed[%d]\n", i);
			hw_keymap_pushKey(ctx, i, key_status[i]);
		}
	}
}

void hw_keymap_init(void)
{
	KEYBOARD_INIT_ROWS();
	KEYBOARD_INIT_COLUMNS();
}

