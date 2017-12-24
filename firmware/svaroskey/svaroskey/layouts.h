#ifndef SVAROSKEY_LAYOUTS_H
#define SVAROSKEY_LAYOUTS_H

#include "keymap.h"

typedef struct
{
	scancode_t scancode;
	uint8_t modifiers;
} LogicalKey;

const LogicalKey* get_logical_key(int layer, key_id_t key_id);
bool is_modifier(const LogicalKey* lk);
bool is_custom(const LogicalKey* lk);

#endif /* SVAROSKEY_LAYOUTS_H */
