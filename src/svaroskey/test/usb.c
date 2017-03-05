#include "usb.h"

#include "keycodes.h"

UsbKbdEvent usb_event = { 0, { 0 } };
static unsigned current_code_num = 0;

// This goes into whatever configs do.
static int isMod(scancode_t code) {
    if (code == KEY_LEFTCONTROL     ||
        code == KEY_LEFTSHIFT       ||
        code == KEY_LEFTALT         ||
        code == KEY_LEFTGUI         ||
        code == KEY_RIGHTCONTROL    ||
        code == KEY_RIGHTSHIFT      ||
        code == KEY_RIGHTALT        ||
        code == KEY_RIGHTGUI )
    return 1;

    return 0;
}

static int modShift(scancode_t code) {
    switch (code) {
        case KEY_LEFTCONTROL:
            return 7;
        case KEY_LEFTSHIFT:
            return 6;
        case KEY_LEFTGUI:
            return 5;
        case KEY_LEFTALT:
            return 4;
        case KEY_RIGHTALT:
            return 3;
        case KEY_RIGHTGUI:
            return 2;
        case KEY_RIGHTCONTROL:
            return 0;
        case KEY_RIGHTSHIFT:
            return 1;
    }
    return 10;
}

void usb_reset(void) {
    usb_event.mods = 0;
    for (unsigned i = 0; i < USB_CODE_MAX; ++i)
        usb_event.codes[i] = 0;
    current_code_num = 0;
}

void usb_add_key(scancode_t code) {
    if (isMod(code)) {
        usb_event.mods |= 1 << modShift(code);
    } else if (current_code_num < USB_CODE_MAX) {
        usb_event.codes[current_code_num++] = code;
    }
}
