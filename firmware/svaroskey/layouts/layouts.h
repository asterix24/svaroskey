#ifndef SVAROSKEY_LAYOUTS_H
#define SVAROSKEY_LAYOUTS_H

#include "layout.h"

#include "cfg/cfg_keymap.h"

extern KeyBinding keymap_layout[LAYOUT_SIZE];
extern KeyBinding keymap_alternate_layout[LAYOUT_SIZE];

KeyBinding * layout_get_key(int id);

#endif /* SVAROSKEY_LAYOUTS_H */
