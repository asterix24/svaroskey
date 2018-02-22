#ifndef SVAROSKEY_PHYSICAL_KEY_H
#define SVAROSKEY_PHYSICAL_KEY_H

#include "typedefs.h"

struct PressedPhysicalKeys;
const struct PressedPhysicalKeys* get_physical_keys(void);
uint8_t get_num_keys(const struct PressedPhysicalKeys* pkeys);
key_id_t get_key_id(uint8_t key, const struct PressedPhysicalKeys* pkeys);
#endif
