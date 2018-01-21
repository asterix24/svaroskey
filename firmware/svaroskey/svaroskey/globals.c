#include "globals.h"

#include "definitions.h"

key_id_t std_pressed_key_ids[LAYOUT_SIZE] = {0};
key_id_t custom_pressed_key_ids[MAX_CUSTOM_KEYPRESSES] = {0};
LogicalKey* substituted_keys[MAX_CUSTOM_KEYPRESSES] = {&noop_lk};
KeyHash pressed_keys_hash;
