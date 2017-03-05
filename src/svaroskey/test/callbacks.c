#include "callbacks.h"

#include "config.h"
#include "usb.h"

typedef void Callback(unsigned char);

Callback writeKey;

int processCallbacks(void) {
    usb_reset();

    for (unsigned char i = 0; i < eeprom->pressed_keys_num; ++i) {
        unsigned char key = eeprom->pressed_keys[i];

        writeKey(key);
    }
    return 0;
}

void writeKey(unsigned char key) {
    // Get key from layout (needed for SDL);
    scancode_t code = tmp_sdl_conversion(key);

    usb_add_key(code);
}
