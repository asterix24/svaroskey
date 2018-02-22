#ifndef HW_KEYMAP_H
#define HW_KEYMAP_H

#include "physical_key.h"

bool is_key_down(uint8_t r_port, uint8_t r_pin, uint8_t c_port, uint8_t c_pin);
void keyboard_init(void);

#endif /* HW_KEYMAP_H */

