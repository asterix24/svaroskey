#ifndef SVAROSKEY_CALLBACKS_H
#define SVAROSKEY_CALLBACKS_H

#include "stdint.h"

/**
 * @brief USB keyboard event descriptor.
 */
typedef struct UsbKbdEvent
{
	uint8_t mods;
	uint8_t codes[6];
} UsbKbdEvent;

void processCallbacks(void);

#endif /* SVAROSKEY_CALLBACKS_H */
