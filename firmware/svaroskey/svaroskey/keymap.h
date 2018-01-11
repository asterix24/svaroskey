#ifndef SVAROSKEY_KEYMAP_H
#define SVAROSKEY_KEYMAP_H

#include <drv/usbkbd.h>

UsbKbdEvent* get_usb_report(void);
void keymap_scan(void);
void keymap_init(void);

#endif
