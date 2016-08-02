#ifndef SVAROSKEY_KEYMAP_H
#define SVAROSKEY_KEYMAP_H

#include <cpu/types.h>

typedef uint16_t scancode_t;

typedef struct
{
	char mod, scan;
} keystate_t;

typedef struct
{
	uint16_t id;
	scancode_t code;
} keybinding_t;

typedef struct
{
	uint8_t row_port;
	uint8_t row_pin;
	uint8_t col_port;
	uint8_t col_pin;
} keymapping_t;

keystate_t * keymap_get_next(void);
void keymap_scan(void);
void keymap_init(void);

#endif
