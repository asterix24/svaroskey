#ifndef SVAROSKEY_PHYSICAL_KEY_H
#define SVAROSKEY_PHYSICAL_KEY_H

#include "typedefs.h"

typedef struct
{
	uint8_t row_port;
	uint8_t row_pin;
	uint8_t col_port;
	uint8_t col_pin;
} PhysicalKey;

const PhysicalKey* get_physical_key(key_id_t key_id);
#endif
