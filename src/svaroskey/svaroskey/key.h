#ifndef SVAROSKEY_KEY_H
#define SVAROSKEY_KEY_H

#include "keycodes.h"

#include "cfg/cfg_keyboard.h"

typedef void (*key_callback_t)(void);

/* Forward decl */
struct Cell;

struct Key {
	struct Cell	*cell;
	scancode_t	scancodes[CONFIG_HW_FUNCTION_NUM + 1];
	key_callback_t	funcs[CONFIG_HW_FUNCTION_NUM + 1];
};

#endif /* SVAROSKEY_KEY_H */
