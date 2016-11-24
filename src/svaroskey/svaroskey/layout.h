#ifndef SVAROSKEY_LAYOUT_H
#define SVAROSKEY_LAYOUT_H

#include "key.h"

#include "cfg/cfg_keyboard.h"

struct Layout {
	struct	Key	keys[CONFIG_LAYOUT_SIZE];
};

#endif /* SVAROSKEY_LAYOUT_H */
