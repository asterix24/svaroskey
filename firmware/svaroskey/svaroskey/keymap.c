#include "cfg/cfg_keymap.h"
#include "hw/hw_keymap.h"

#include "keymap.h"
#include "layouts.h"
#include "mappings.h"

#include <cfg/debug.h>
#define LOG_LEVEL  2
#define LOG_FORMAT 0

#include <cfg/log.h>

static uint8_t previous_mods = 0;

static int previous_codes_num = 0;
static int codes_num = 0;
static bool alternate_layout = false;

static UsbKbdEvent event = { 0, { 0 } };

static bool valid = false;

UsbKbdEvent * keymap_get_next_code()
{
	if (valid) {
		valid = false;
		return &event;
	}
	return NULL;
}

static void keymap_update_key(int i)
{
	// Get key from layout
	KeyBinding * key;

	key = &keymap_layout[i];
	if (alternate_layout)
		key = &keymap_alternate_layout[i];

	KeyMapping * kmap = &keymap_mapping[key->mapping_id];

	// For non-modifiers we only track 6 at most.
	if (key->code <= 0xff && codes_num == 6)
		return;

	// We only care about pressed keys
	if (!(KEYMAP_READ(kmap)))
		return;

	alternate_layout = false;
	if (i == 55)
		alternate_layout = true;

	// Check if the key is a modifier key
	if (key->code > 0xff)
	{
		if (i != 55)
			event.mods |= (key->code >> 8);
	}
	// Otherwise see if it is different from before
	else if (event.codes[codes_num++] != key->code)
	{
		valid = true;
		event.codes[codes_num - 1] = (0xff & key->code);
	}
}

void keymap_scan(void)
{
	int i;
	//LOG_INFO("info\n");
	//LOG_ERR("err\n");

	// Reset keycodes
	event.mods = 0;
	codes_num = 0;

	// Scan all the configured keys
	for (i = 0; i < LAYOUT_SIZE; ++i)
		keymap_update_key(i);

	// If mods changed or number of keys pressed changed, we update
	if (previous_mods != event.mods || previous_codes_num != codes_num)
		valid = true;

	if (valid) {
		previous_mods = event.mods;
		previous_codes_num = codes_num;

		// Clean the rest of the keys
		for (i = codes_num; i < 6; ++i)
			event.codes[i] = 0;
	}
}

void keymap_init(void)
{
	// Low-level hardware initialization
	KEYMAP_INIT();

	// TODO: initialize layout from EEPROM
}
