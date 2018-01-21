#ifndef SVAROSKEY_KEYMAP_H
#define SVAROSKEY_KEYMAP_H

#include <drv/usbkbd.h>

typedef struct
{
	size_t num_std_keys_pressed;
	size_t num_custom_keys_pressed;
} KeymapScanResult;

UsbKbdEvent* get_usb_report(void);
void generate_usb_report(size_t layer, size_t num_std_pressed);
size_t keyfetch_algo(size_t num_custom_keys);
KeymapScanResult keymap_scan(void);
void keymap_init(void);

#endif
