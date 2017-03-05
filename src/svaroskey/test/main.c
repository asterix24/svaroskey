#include <SDL.h>

#include "keyscan.h"
#include "stdio.h"
#include "config.h"
#include "layouts.h"
#include "usb.h"

int printEvent() {
    usb_reset();
    int i = 0;

    for (i = 0; i < eeprom->pressed_keys_num; ++i) {
        unsigned char key = eeprom->pressed_keys[i];
        // Get key from layout (needed for SDL);
        scancode_t code = tmp_sdl_conversion(key);

        usb_add_key(code);
    }

    printf("%d%d%d%d%d%d%d%d ",
        1 & (usb_event.mods >> 7),
        1 & (usb_event.mods >> 6),
        1 & (usb_event.mods >> 5),
        1 & (usb_event.mods >> 4),
        1 & (usb_event.mods >> 3),
        1 & (usb_event.mods >> 2),
        1 & (usb_event.mods >> 1),
        1 & (usb_event.mods >> 0));

    int counter = 0;
    for (i = 0; i < USB_CODE_MAX; ++i) {
        uint8_t code = usb_event.codes[i];
        printf("[%d]", code);
        if      (code == 4) ++counter;
        else if (code == 22) ++counter;
        else if (code == 7) ++counter;
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
