#include "keymap.h"
#include "layouts.h"
#include "mappings.h"

#include <stdbool.h>
#include <stdlib.h>

#include <SDL.h>

static int valid = 0;

int keymap_changed(void) {
    return valid;
}

static int is_key_pressed(int i)
{
    // Get key from layout (needed for SDL, see below)
    KeyBinding * key = &keymap_layout[i];

    // For SDL the key codes are needed otherwise we can't read them.
    // The actual keyboard will just need numbers in the [0, KEYS_NUM) range.
    const Uint8 *state = SDL_GetKeyboardState(NULL);
    // We only care about pressed keys
    return state[key->code];
}

void keymap_scan(void)
{
    unsigned i = 0, pressed_keys_num = 0;
    // Invalidate new reading, put old readings in old array.
    valid = false;
    {
        unsigned char * tmp = eeprom->pressed_keys_old;
        eeprom->pressed_keys_old = eeprom->pressed_keys;
        eeprom->pressed_keys = tmp;
    }
    eeprom->pressed_keys_old_num = eeprom->pressed_keys_num;

    // Scan all the physical keys and keep the pressed ones.
    for (i = 0; i < LAYOUT_SIZE; ++i) {
        if (is_key_pressed(i)) {
            eeprom->pressed_keys[pressed_keys_num++] = i;
            if (pressed_keys_num == eeprom->max_pressed_keys)
                break;
        }
    }
    eeprom->pressed_keys_num = pressed_keys_num;
    if (eeprom->pressed_keys_num != eeprom->pressed_keys_old_num) {
        valid = true;
    } else {
        for (i = 0; i < eeprom->pressed_keys_num; ++i) {
            if (eeprom->pressed_keys[i] != eeprom->pressed_keys_old[i]) {
                valid = true;
                break;
            }
        }
    }
}

void keymap_init(void)
{
}
