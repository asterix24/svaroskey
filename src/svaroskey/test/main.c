#include <SDL.h>

#include "keymap.h"
#include "stdio.h"

int printEvent(UsbKbdEvent * event) {
    if (!event)
        return 1;
    printf("%d%d%d%d%d%d%d%d ",
        1 & (event->mods >> 7),
        1 & (event->mods >> 6),
        1 & (event->mods >> 5),
        1 & (event->mods >> 4),
        1 & (event->mods >> 3),
        1 & (event->mods >> 2),
        1 & (event->mods >> 1),
        1 & (event->mods >> 0));

    int counter = 0;
    for (int i = 0; i < 6; ++i) {
        printf("[%d]", event->codes[i]);
        if (i == 0 && event->codes[i] == 4) ++counter;
        if (i == 1 && event->codes[i] == 22) ++counter;
        if (i == 2 && event->codes[i] == 7) ++counter;
    }
    printf("\n");

    if (counter == 3)
        return 1;
    return 0;
}

int init() {
    //Initialize all SDL subsystems
    if( SDL_Init( SDL_INIT_VIDEO ) == -1 )
        return -1;

    //Set up the screen
    SDL_Window *win = SDL_CreateWindow("Hello World!", 100, 100, 640, 480, SDL_WINDOW_SHOWN);
    if (win == NULL) {
        SDL_Quit();
        return -1;
    }
    return 0;
}

int main(void)
{
    UsbKbdEvent *event;

    if (init())
        return -1;

    /* Periodically scan the keyboard */
    for (int i = 0; i < 10000; ++i)
    {
        SDL_PumpEvents();
        keymap_scan();

        if ((event = keymap_get_next_code()) != NULL)
            if (printEvent(event))
                break;

        SDL_Delay(100);
    }

    SDL_Quit();

    return 0;
}
