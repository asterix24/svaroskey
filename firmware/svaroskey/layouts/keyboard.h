/**
 * \file
 * <!--
 * Copyright 2018 Daniele Basile <asterix24@gmail.com>
 * All Rights Reserved.
 * -->
 *
 * \brief 
 *
 * \author Daniele Basile <asterix24@gmail.com>
 */


#ifndef LAYOUT_KEYBOARD_H
#define LAYOUT_KEYBOARD_H

#include "cfg/cfg_keymap.h"

#include <cpu/types.h>

#define KEY_PORTA 0
#define KEY_PORTB 1
#define KEY_PORTC 2

typedef struct {
	uint8_t col;
	uint8_t col_port_idx;
	uint8_t row;
	uint8_t row_port_idx;
} KeyMap;

/*
 * Define column and rows for matrix keys.
 * Column should be place to power supply, and row to ground.
 */

#if CFG_KEYBOARD_LAYOUT == KEYBOARD_PETROSKEY_LAYOUT
	#include "hw/petroskey.h"
#else
	#error No layout defined
#endif


size_t hw_keymap_scan(uint8_t *keys, size_t len);
int kw_keymap_read(uint8_t index);

void hw_keymap_init(void);

extern KeyMap keyboard_layout[KEYBOARD_LAYOUT_NUM_KEYS];

#endif /* LAYOUT_KEYBOARD_H */

