#ifndef SVAROSKEY_GLOBALS_H
#define SVAROSKEY_GLOBALS_H

#include "keyhash.h"
#include "logical_key.h"
#include "typedefs.h"

extern key_id_t std_pressed_key_ids[];
extern key_id_t custom_pressed_key_ids[];
extern LogicalKey* substituted_keys[];
extern KeyHash pressed_keys_hash;

/* The reason the `substituted_keys` array is an array of LogicalKey pointers
 * rather than an array of key ids is that a key id identifies a single
 * physical key on the keyboard, while substituted keys might not have an
 * associated physical key.
 *
 * As a simple example (and the raison d'être of this feature) let us say that
 * a keyboard has a physical key that is assigned to LAYER1, and a different
 * physical key assigned to LAYER2. It might be useful to substitute the
 * combination LAYER1 + LAYER2 with LAYER3, but LAYER3 does not exist on the
 * keyboard itself and thus we cannot place the key id for LAYER3 anywhere,
 * because LAYER3 does not have a key id.
 */

#endif
