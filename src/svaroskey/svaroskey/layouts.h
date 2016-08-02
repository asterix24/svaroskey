#ifndef SVAROSKEY_LAYOUTS_H
#define SVAROSKEY_LAYOUTS_H

#include "keymap.h"

#if (CONFIG_LAYOUT_REVISION == 0)
#define LAYOUT_SIZE 104
#endif

extern KeyBinding keymap_layout[LAYOUT_SIZE];

KeyBinding * layout_get_key(int id);

#endif /* SVAROSKEY_LAYOUTS_H */
