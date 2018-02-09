#ifndef SVAROSKEY_LOGICAL_KEY_H
#define SVAROSKEY_LOGICAL_KEY_H

#include "keycodes.h"
#include "typedefs.h"

typedef struct
{
	usage_code_t usage_code;
	uint8_t modifiers;
} LogicalKey;

extern LogicalKey noop_lk;

const LogicalKey* get_logical_key(size_t layer, key_id_t key_id);
bool is_modifier(const LogicalKey* lk);
bool is_custom(const LogicalKey* lk);

#endif
