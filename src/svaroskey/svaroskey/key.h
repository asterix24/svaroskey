#ifndef SVAROSKEY_KEY_H
#define SVAROSKEY_KEY_H

#include "keycodes.h"

typedef void (*key_callback_t)(void);

/* Forward decl */
struct Cell;

struct Key {
	struct Cell	*cell;
	scancode_t	scancode;
	key_callback_t	cb;
};

#endif /* SVAROSKEY_KEY_H */
