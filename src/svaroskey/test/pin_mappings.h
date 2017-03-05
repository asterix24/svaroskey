#ifndef SVAROSKEY_MAPPINGS_H
#define SVAROSKEY_MAPPINGS_H

#include "stdint.h"

typedef struct
{
	uint8_t row_port;
	uint8_t row_pin;
	uint8_t col_port;
	uint8_t col_pin;
} PinMapping;

extern PinMapping pin_mapping[];

#endif /* SVAROSKEY_LAYOUTS_H */
