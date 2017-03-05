#ifndef SVAROSKEY_LAYOUTS_H
#define SVAROSKEY_LAYOUTS_H

#include "stdint.h"

#define LAYOUT_SIZE 106

typedef uint16_t scancode_t;

typedef struct
{
	uint16_t mapping_id;
	scancode_t code;
} KeyBinding;

extern KeyBinding keymap_layout[LAYOUT_SIZE];

KeyBinding * layout_get_key(int id);

#endif /* SVAROSKEY_LAYOUTS_H */
