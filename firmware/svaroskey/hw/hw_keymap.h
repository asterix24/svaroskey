#ifndef HW_KEYMAP_H
#define HW_KEYMAP_H

#include <cpu/types.h>

#define KEY_PORTA 0
#define KEY_PORTB 1
#define KEY_PORTC 2

typedef struct {
	uint8_t col;
	uint8_t col_port_idx;
	uint8_t row;
	uint8_t row_port_idx;
} KeyMap;

size_t hw_keymap_scan(uint8_t *keys, size_t len);
int kw_keymap_read(uint8_t index);

void hw_keymap_init(void);

#endif /* HW_KEYMAP_H */

