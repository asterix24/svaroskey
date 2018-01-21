#include "globals.h"

#include "definitions.h"

key_id_t std_pressed_key_ids[LAYOUT_SIZE] = {0};
key_id_t custom_pressed_key_ids[MAX_CUSTOM_KEYPRESSES] = {0};
KeyHash pressed_keys_hash;

// gcc-only initialization
LogicalKey* substituted_keys[] = {[0 ... MAX_CUSTOM_KEYPRESSES] = &noop_lk};
