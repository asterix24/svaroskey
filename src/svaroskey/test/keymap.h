#ifndef SVAROSKEY_KEYMAP_H
#define SVAROSKEY_KEYMAP_H

#include "stdint.h"

/**
 * USB keyboard event descriptor.
 */
typedef struct UsbKbdEvent
{
	uint8_t mods;
	uint8_t codes[6];
} UsbKbdEvent;

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

UsbKbdEvent * keymap_get_next_code();
void keymap_scan(void);
void keymap_init(void);

#endif
