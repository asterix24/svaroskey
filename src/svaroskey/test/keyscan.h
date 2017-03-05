#ifndef SVAROSKEY_KEYSCAN_H
#define SVAROSKEY_KEYSCAN_H

#include "stdint.h"

/**
 * USB keyboard event descriptor.
 */
typedef struct UsbKbdEvent
{
	uint8_t mods;
	uint8_t codes[6];
} UsbKbdEvent;

int  keyscan_changed(void);
void keyscan_scan(void);
void keyscan_init(void);

#endif
