#ifndef SVAROSKEY_USB_H
#define SVAROSKEY_USB_H

/** @file */

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

/**
 * @brief Global variable holding a USB key/mod buffer.
 */
extern UsbKbdEvent usb_event;

/**
 * @addtogroup free_functions Free Functions
 * @{
 *
 * @name USB Functions
 * @{
 */

/**
 * @brief Resets the usb_event buffer to zero.
 */
void usb_reset(void);

/**
 * @brief Adds the input keycode to the usb_event buffer.
 */
void usb_add_key(keycode_t code);

/// @}
/// @}

#endif /* SVAROSKEY_USB_H */
