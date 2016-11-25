#ifndef SVAROSKEY_LAYOUT_H
#define SVAROSKEY_LAYOUT_H

#include "cfg/cfg_keyboard.h"

/* Forward decl */
struct Key;

struct Layout {
	struct	Key	*keys;
	int		num_keys;
};

#endif /* SVAROSKEY_LAYOUT_H */
