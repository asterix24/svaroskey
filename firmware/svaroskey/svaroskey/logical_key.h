#ifndef SVAROSKEY_LOGICAL_KEY_H
#define SVAROSKEY_LOGICAL_KEY_H

#include "keycodes.h"
#include "typedefs.h"

typedef struct
{
	scancode_t scancode;
	uint8_t modifiers;
} LogicalKey;

static LogicalKey noop_lk = {
	.scancode = KEY_NOOP,
	.modifiers = 0
};

const LogicalKey* get_logical_key(size_t layer, key_id_t key_id);
bool is_modifier(const LogicalKey* lk);
bool is_custom(const LogicalKey* lk);

#endif
