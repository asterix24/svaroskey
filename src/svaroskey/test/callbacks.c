#include "callbacks.h"

#include "config.h"
#include "usb.h"
#include "assert.h"

#include "stdlib.h"

// Debugging
#include "stdio.h"

typedef void Callback(unsigned char);

Callback noOp;
Callback writeKey;

Callback * callbacks[] = {
    noOp,
    writeKey,
};
static const unsigned callbacksNumber = sizeof(callbacks)/sizeof(callbacks[0]);

#define DBG(x) fprintf(stderr, x "\n")
#define DBGA(x, ...) fprintf(stderr, x "\n", __VA_ARGS__)

// Used to qsort Actions on priority
int priorityCompare(const void * p1, const void * p2) {
    return (*(Action**)p1)->priority - (*(Action**)p2)->priority;
}

int processCallbacks(void) {
    DBG("resetting usb");
    usb_reset();

    DBG("copying edit buffer");
    DBGA("Pressed keys: %d", eeprom->pressed_keys_num);
    unsigned char keys_to_process = eeprom->pressed_keys_num;
    // Copy pressed keys so that we can modify the vector if needed.
    for (unsigned char i = 0; i < keys_to_process; ++i) {
        DBGA("Copying key %d: %d", i, eeprom->pressed_keys[i]);
        eeprom->edit_buffer[i] = eeprom->pressed_keys[i];
    }

    DBGA("starting process, keys_to_process: %d", keys_to_process);
    unsigned char actions = 0, current_key = 0;
    while (keys_to_process > 0 && current_key < keys_to_process) {
        // Notice that the pressed_keys array is always sorted by definition,
        // since we scan keys from lowest to highest.
        unsigned char key = eeprom->edit_buffer[current_key];

        // This is the node for our current first key. We want to know if the
        // user is activating any combination that includes this key.
        //
        // So we look if there's any combination that matches the keys we have.
        // If there is, we do its action and remove those keys from our next
        // lookup (since we have already "used" them).
        //
        // Only one combination can be matched for a given key.
        Node * p = &eeprom->keys[key];

        DBGA("Read node for current key %d: %d", current_key, key);
        int cMatch = -1;
        DBG("Starting combinations...");
        DBGA("Combinations for this key: %d", p->combinations_num);
        for (int c = 0; c < p->combinations_num; ++c) {
            // If we don't have enough keys to trigger this combination, skip it.
            if (keys_to_process - 1 < p->combinations[c].keys_num)
                continue;
            // Try to match all keys in the combination with the ones we have.
            // q is for our keys. k for the combination's keys.
            // q skips the initial key, which we already know is there.
            unsigned char q = 1, k = 0;
            while (q < keys_to_process && k < p->combinations[c].keys_num) {
                // Since everything is sorted, if we're bigger we're done.
                if (eeprom->edit_buffer[q] > p->combinations[c].keys[k])
                    break;
                if (eeprom->edit_buffer[q] == p->combinations[c].keys[k])
                    ++k;
                ++q;
            }
            // If we found all of them, save the combination as matched.
            if (k == p->combinations[c].keys_num) {
                cMatch = c;
                break;
            }
        }
        DBG("Done combinations");
        // If we didn't match anything we use the action for the key.
        if (cMatch == -1) {
            DBG("Copying actions");
            eeprom->actions[actions++] = &p->action;
        } else {
            DBG("Matched combination!");
            eeprom->actions[actions++] = &p->combinations[cMatch].action;
            // We also have to remove all keys from the combination from the
            // ones we are processing.
            unsigned char q = 1, k = 0;
            while (q < keys_to_process && k < p->combinations[cMatch].keys_num) {
                // Since everything is sorted, if we're bigger we're done.
                if (eeprom->edit_buffer[q] > p->combinations[cMatch].keys[k])
                    break;
                // If we're equal, shift the edit_buffer by one, removing the
                // equal element.
                if (eeprom->edit_buffer[q] == p->combinations[cMatch].keys[k]) {
                    for (unsigned char z = q; z < keys_to_process - 1; ++z)
                        eeprom->edit_buffer[z] = eeprom->edit_buffer[z+1];
                    ++k;
                    --keys_to_process;
                }
                ++q;
            }
        }
        DBG("Next key...");
        ++current_key;
    }
    // Sort actions by priority
    DBG("Sorting...");
    qsort(eeprom->actions, actions, sizeof(Action*), priorityCompare);

    DBG("Executing actions");
    // Execute actions
    for (unsigned a = 0; a < actions; ++a) {
        CallbackId * cbId = &eeprom->actions[a]->callback;
        DBGA("Code: %d, param: %d", cbId->code, cbId->param);
        // Don't go out of buffer
        assert(cbId->code < callbacksNumber);
        // Run callback
        callbacks[cbId->code](cbId->param);
    }
    DBG("Done.");
    return 0;
}

void noOp(unsigned char p) {
    (void)p;
}

void writeKey(unsigned char key) {
    DBGA("Adding key %d", key);
    assert(key < keycodes_count);

    usb_add_key(keycodes[key]);
}
