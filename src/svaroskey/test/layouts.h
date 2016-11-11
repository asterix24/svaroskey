#ifndef SVAROSKEY_LAYOUTS_H
#define SVAROSKEY_LAYOUTS_H

#include "keymap.h"

#define LAYOUT_SIZE 106

extern KeyBinding keymap_layout[LAYOUT_SIZE];

KeyBinding * layout_get_key(int id);

#endif /* SVAROSKEY_LAYOUTS_H */
