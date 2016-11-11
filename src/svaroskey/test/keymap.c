#include "keymap.h"
#include "layouts.h"
#include "mappings.h"

#include <stdbool.h>
#include <stdlib.h>

#include <SDL.h>

static uint8_t previous_mods = 0;

static int previous_codes_num = 0;
static int codes_num = 0;

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

static int isMod(scancode_t code) {
	if (code == SDL_SCANCODE_LCTRL  ||
        code == SDL_SCANCODE_LSHIFT ||
        code == SDL_SCANCODE_LALT   ||
        code == SDL_SCANCODE_LGUI   ||
        code == SDL_SCANCODE_RCTRL  ||
        code == SDL_SCANCODE_RSHIFT ||
        code == SDL_SCANCODE_RALT   ||
        code == SDL_SCANCODE_RGUI )
    return 1;

    return 0;
}

static int modShift(scancode_t code) {
    switch (code) {
        case SDL_SCANCODE_LCTRL :
            return 7;
        case SDL_SCANCODE_LSHIFT:
            return 6;
        case SDL_SCANCODE_LGUI  :
            return 5;
        case SDL_SCANCODE_LALT  :
            return 4;
        case SDL_SCANCODE_RALT  :
            return 3;
        case SDL_SCANCODE_RGUI  :
            return 2;
        case SDL_SCANCODE_RCTRL :
            return 0;
        case SDL_SCANCODE_RSHIFT:
            return 1;
    }
    return 10;
}

static void keymap_update_key(int i)
{
	// Get key from layout
	KeyBinding * key = &keymap_layout[i];

	// For non-modifiers we only track 6 at most.
	if (!isMod(key->code) && codes_num == 6)
		return;

    const Uint8 *state = SDL_GetKeyboardState(NULL);
	// We only care about pressed keys
	if (!state[key->code])
		return;

	// Check if the key is a modifier key
    if (isMod(key->code))
		event.mods |= 1 << modShift(key->code);
	// Otherwise see if it is different from before
	else if (event.codes[codes_num++] != key->code) {
		valid = true;
		event.codes[codes_num - 1] = (0xff & key->code);
	}
}

void keymap_scan(void)
{
	int i;

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
}
