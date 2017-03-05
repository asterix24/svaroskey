#ifndef SVAROSKEY_USB_H
#define SVAROSKEY_USB_H

#include "stdint.h"

#include "keycodes.h"

#define USB_CODE_MAX 6

/**
 * @brief USB keyboard event descriptor.
 *
 * This will probably need to be defined somewhere else.
 */
typedef struct UsbKbdEvent
{
	uint8_t mods;
	uint8_t codes[USB_CODE_MAX];
} UsbKbdEvent;

extern UsbKbdEvent usb_event;

void usb_reset(void);
void usb_add_key(keycode_t code);

#endif /* SVAROSKEY_USB_H */
