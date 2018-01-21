#ifndef SVAROSKEY_KEYMAP_H
#define SVAROSKEY_KEYMAP_H

#include <drv/usbkbd.h>

typedef struct
{
	size_t n_std_keys;
	size_t n_cus_keys;
} KeymapScanResult;

UsbKbdEvent* get_usb_report(void);
void generate_usb_report(size_t layer, size_t n_std_keys);
size_t keyfetch_algo(size_t n_cus_keys);
KeymapScanResult keymap_scan(void);
void keymap_init(void);

#endif
