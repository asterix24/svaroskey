#ifndef HW_KEYMAP_H
#define HW_KEYMAP_H

#include "physical_key.h"

bool is_key_down(const PhysicalKey* pk);
void keyboard_init(void);

#endif /* HW_KEYMAP_H */

