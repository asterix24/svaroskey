#ifndef SVAROSKEY_KEYHASH_H
#define SVAROSKEY_KEYHASH_H

/* The purpose of this compact "hashmap" is to detect whether a key identified
 * by its id is pressed or not in O(1) time.
 *
 * This information is used when computing key substitutions.
 *
 * Of course, this is not a general-purpose hasmap implementation, in fact
 * it is nothing more than a bunch of bitfields, and it only works because each
 * key id is an unique integer starting from 0.
 *
 * It works by providing 4 buckets of 32 bits each. Each of the bits represent
 * if the corresponding key id is pressed (1) or not (0).
 *
 * 4 buckets of 32 bit provide 128 bits, which enables us to handle keyboards
 * with up to 128 physical keys. Standard full-size keyboards have around 104
 * keys, so this should provide enough room for extended custom keyboards.
 * In case we need more, we can always throw more buckets at the problem.
 */

#include "definitions.h"
#include "typedefs.h"

typedef struct KeyHash KeyHash;

KeyHash* fetch_key_hash(void);
void clear_key_hash(KeyHash* kh);
void set_pressed(KeyHash* kh, key_id_t k_id);
void set_released(KeyHash* kh, key_id_t k_id);
bool is_pressed(KeyHash* kh, key_id_t k_id);

#endif
