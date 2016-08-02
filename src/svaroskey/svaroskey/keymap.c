#include "cfg/cfg_keymap.h"
#include "hw/hw_keymap.h"

#include "keymap.h"
#include "layouts.h"
#include "mappings.h"

#include <cfg/debug.h>

typedef enum
{
	KEY_RELEASED = 0,
	KEY_PRESSED,
} KeyState;

static KeyState current_state[LAYOUT_SIZE] = { KEY_RELEASED };
static KeyState previous_state[LAYOUT_SIZE] = { KEY_RELEASED };

static scancode_t code;
static bool valid = false;

scancode_t * keymap_get_next_code(void)
{
	if (valid) {
		valid = false;
		return &code;
	}
	return NULL;
}

static void keymap_update_key(int i)
{
	// Get key from layout
	KeyBinding * key = &keymap_layout[i];
	KeyMapping * kmap = &keymap_mapping[key->mapping_id];

	// Save current state
	previous_state[i] = current_state[i];

	// Update state
	current_state[i] = (KEYMAP_READ(kmap)) ? KEY_PRESSED : KEY_RELEASED;

	if (current_state[i] != previous_state[i])
	{
		code = 0x00FF & ((current_state[i] == KEY_RELEASED) ? 0 : key->code);
		valid = true;
	}
}

void keymap_scan(void)
{
	int i;

	// Scan all the configured keys
	for (i = 0; i < LAYOUT_SIZE; ++i)
		keymap_update_key(i);
}

void keymap_init(void)
{
	// Low-level hardware initialization
	KEYMAP_INIT();

	// TODO: initialize layout from EEPROM
}
