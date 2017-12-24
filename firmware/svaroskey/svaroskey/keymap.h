#ifndef SVAROSKEY_KEYMAP_H
#define SVAROSKEY_KEYMAP_H

#include <cpu/types.h>
#include <drv/usbkbd.h>

typedef uint16_t scancode_t;
typedef uint8_t key_id_t;

typedef struct
{
	uint8_t row_port;
	uint8_t row_pin;
	uint8_t col_port;
	uint8_t col_pin;
} PhysicalKey;

UsbKbdEvent* get_usb_report(void);
void keymap_scan(void);
void keymap_init(void);

#endif
