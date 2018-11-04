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


#define MAX_KEY_STATUS 10

typedef struct {
	uint8_t index[MAX_KEY_STATUS];
	uint8_t status[MAX_KEY_STATUS];
} KeyScanCtx;

/*
 * Define column and rows for matrix keys.
 * Column should be place to power supply, and row to ground.
 */

#if CFG_KEYBOARD_LAYOUT == KEYBOARD_PETROSKEY_LAYOUT
	#include "hw/petroskey.h"
#else
	#error No layout defined
#endif

#define KEY_RELEASE       0
#define KEY_PRESSED       BV(0)
#define KEY_CHANGED       BV(7)


extern KeyMap keyboard_layout[KEYBOARD_LAYOUT_NUM_KEYS];

bool hw_keymap_read(uint8_t index);
void hw_keymap_scan(KeyScanCtx *ctx);
int hw_keymap_popKey(KeyScanCtx *ctx, uint8_t index);
void hw_keymap_pushKey(KeyScanCtx *ctx, uint8_t index, uint8_t status);

void hw_keymap_init(void);

#endif /* LAYOUT_KEYBOARD_H */

