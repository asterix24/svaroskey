/**
 * \file
 * <!--
 * Copyright 2018 Daniele Basile <asterix24@gmail.com>
 * All Rights Reserved.
 * -->
 *
 * \brief Keyboard maps
 *
 * \author Daniele Basile <asterix24@gmail.com>
 */

#include "keyboard_map.h"
#include "hw_keymap.h"
#include "cfg/cfg_keymap.h"
#include <cfg/macros.h>

#include <drv/timer.h>

#include <io/stm32.h>
#include <drv/gpio_stm32.h>
#include <drv/clock_stm32.h>



static struct stm32_gpio * const port_mappings[] = {
	((struct stm32_gpio *)GPIOA_BASE),
	((struct stm32_gpio *)GPIOB_BASE),
	((struct stm32_gpio *)GPIOC_BASE),
};

int kw_keymap_read(uint8_t index)
{
	struct stm32_gpio *col_port = port_mappings[keyboard_layout[index].col_port_idx];
	struct stm32_gpio *row_port = port_mappings[keyboard_layout[index].row_port_idx];

	uint8_t row_id = keyboard_layout[index].row;
	uint8_t col_id = keyboard_layout[index].col;

	stm32_gpioPinConfig(row_port, BV(row_id), GPIO_MODE_IPD, GPIO_SPEED_50MHZ);

	/* Select Column */
	stm32_gpioPinWrite(col_port, BV(col_id), 1);

	timer_udelay(2);

	/* Read column */
	bool ret = stm32_gpioPinRead(row_port, BV(row_id));

	// TODO: generalize pin mask for each port
	/* Shutdown all Column */
	stm32_gpioPinWrite(col_port, KEYMAP_COL_MASK, 0);

	/* Put as input selected row, and other rows leave low */
	stm32_gpioPinConfig(row_port, KEYMAP_ROW_MASK, GPIO_MODE_OUT_PP, GPIO_SPEED_50MHZ);
	stm32_gpioPinWrite(row_port, KEYMAP_ROW_MASK, 0);

	return ret;
}

size_t hw_keymap_scan(uint8_t *keys, size_t len)
{
	ASSERT(keys);

	size_t count = 0;
	for (int i = 0; i < KEYBOARD_LAYOUT_NUM_KEYS; i++)
	{
		if (kw_keymap_read(i))
		{
			if (count >= len)
				return count;

			keys[count] = i;
			count++;
		}
	}

	return count;
}

void hw_keymap_init(void)
{
	KEYBOARD_INIT_ROWS();
	KEYBOARD_INIT_COLUMNS();
}

