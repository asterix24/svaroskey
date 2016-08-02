#ifndef SVAROSKEY_KEYMAP_H
#define SVAROSKEY_KEYMAP_H

#include <cpu/types.h>

typedef uint16_t scancode_t;

typedef struct
{
	uint16_t mapping_id;
	scancode_t code;
} KeyBinding;

typedef struct
{
	uint8_t row_port;
	uint8_t row_pin;
	uint8_t col_port;
	uint8_t col_pin;
} KeyMapping;

scancode_t * keymap_get_next_code(void);
void keymap_scan(void);
void keymap_init(void);

#endif
