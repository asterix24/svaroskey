#include "keymap.h"

#include "cfg/cfg_keymap.h"
#include "hw/hw_keymap.h"

#include <cfg/debug.h>

typedef enum
{
	KEY_RELEASED = 0,
	KEY_PRESSED,
} state_t;

typedef struct
{
	char code;
	uint16_t row, col;
	state_t curr, prev;
} keybtn_t;

typedef struct
{
	keybtn_t keys[CONFIG_KEYMAP_BTNNUM];
} keymap_t;

static keymap_t keymap =
{
	.keys =
	{
		{ .code = 0x08, .row = 8, .col = 0, .curr = KEY_RELEASED, .prev = KEY_RELEASED }
	}
};

static keystate_t state;
static bool valid = false;

keystate_t * keymap_get_next(void)
{
	if (valid) {
		valid = false;
		return &state;
	}
	return NULL;
}

static void keymap_upd_key(keybtn_t *key)
{
	// Save current state
	key->prev = key->curr;

	// Update state
	key->curr = (KEYMAP_READ(key->row, key->col)) ? KEY_PRESSED : KEY_RELEASED;

	if (key->prev != key->curr)
	{
		state.mod = 0;
		state.scan = (key->curr == KEY_RELEASED) ? 0 : key->code;
		valid = true;
	}
}

void keymap_scan(void)
{
	int i;

	// Scan all the configured keys
	// TODO: fix the iteration number after the mapping is in place
	for (i = 0; i < 1; ++i)
		keymap_upd_key(&keymap.keys[i]);
}

void keymap_init(void)
{
	// Low-level hardware initialization
	KEYMAP_INIT();

	// TODO: initialize keymap from EEPROM
}
