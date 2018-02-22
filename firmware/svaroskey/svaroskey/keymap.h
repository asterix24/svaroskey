#ifndef SVAROSKEY_KEYMAP_H
#define SVAROSKEY_KEYMAP_H

#include "physical_key.h"
#include <drv/usbkbd.h>

UsbKbdEvent* calculate_usb_report(const struct PressedPhysicalKeys* pkeys);
void keymap_init(void);

#endif
