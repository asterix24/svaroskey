#ifndef SVAROSKEY_MAPPINGS_H
#define SVAROSKEY_MAPPINGS_H

#include "keymap.h"

extern key_id_t pressed_key_ids[];

const PhysicalKey* get_physical_key(key_id_t key_id);

#endif /* SVAROSKEY_LAYOUTS_H */
