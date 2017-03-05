#include <SDL.h>

#include "keyscan.h"
#include "stdio.h"
#include "config.h"
#include "layouts.h"

// This goes into whatever configs do.
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

int printEvent() {
    int i = 0;

    unsigned char mods = 0;
    for (i = 0; i < eeprom->pressed_keys_num; ++i) {
        // Get key from layout (needed for SDL, see below)
        KeyBinding * key = &keymap_layout[eeprom->pressed_keys[i]];

        if (isMod(key->code))
            mods |= 1 << modShift(key->code);
    }
    printf("%d%d%d%d%d%d%d%d ",
        1 & (mods >> 7),
        1 & (mods >> 6),
        1 & (mods >> 5),
        1 & (mods >> 4),
        1 & (mods >> 3),
        1 & (mods >> 2),
        1 & (mods >> 1),
        1 & (mods >> 0));

    int counter = 0;
    for (i = 0; i < eeprom->pressed_keys_num; ++i) {
        // Get key from layout (needed for SDL, see below)
        KeyBinding * key = &keymap_layout[eeprom->pressed_keys[i]];

        if (!isMod(key->code)) {
            printf("[%d(%d)]", key->code, eeprom->pressed_keys[i]);
            if (key->code == 4) ++counter;
            else if (key->code == 22) ++counter;
            else if (key->code == 7) ++counter;
        }
    }
    printf("\n");

    if (counter == 3)
        return 1;
    return 0;
}

int init() {
    { // SDL STUFF, only needed for test
        // Initialize all SDL subsystems
        if( SDL_Init( SDL_INIT_VIDEO ) == -1 )
            return -1;

        // Set up the screen (needed or it won't work).
        SDL_Window *win = SDL_CreateWindow("Hello World!", 100, 100, 640, 480, SDL_WINDOW_SHOWN);
        if (win == NULL) {
            SDL_Quit();
            return -1;
        }
    }

    // Init the keyboard reading system.
    keyscan_init();

    return 0;
}

int main(void)
{
    if (init())
        return -1;

    /* Periodically scan the keyboard */
    for (int i = 0; i < 10000; ++i)
    {
        SDL_PumpEvents();
        keyscan_scan();
        // We only print if something changed.
        // if (keyscan_changed() && processCallbacks() && printEvent())
        if (keyscan_changed() && printEvent())
            break;

        SDL_Delay(100);
    }

    SDL_Quit();

    return 0;
}
