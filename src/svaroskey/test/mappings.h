#ifndef SVAROSKEY_MAPPINGS_H
#define SVAROSKEY_MAPPINGS_H

#include "stdint.h"

typedef struct
{
	uint8_t row_port;
	uint8_t row_pin;
	uint8_t col_port;
	uint8_t col_pin;
} KeyMapping;

extern KeyMapping keymap_mapping[];

KeyMapping * mapping_get_key(int id);

#endif /* SVAROSKEY_LAYOUTS_H */
