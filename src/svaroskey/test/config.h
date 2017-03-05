#ifndef SVAROSKEY_CONFIG_H
#define SVAROSKEY_CONFIG_H

#include "layouts.h"

typedef struct CallbackId {
    unsigned char code;
    unsigned char param;
} CallbackId;

typedef struct Action {
    CallbackId callback;
    unsigned char priority;
} Action;

typedef struct Node {
    unsigned char key;
    Action action;

    unsigned char alternatives;
    struct Node * what;
} Node;

typedef struct EepromConfig {
    // Max number of physical pressed keys at any one time
    unsigned char max_pressed_keys;
    // Arrays of size max_pressed_keys where to write them
    unsigned char * pressed_keys_old;
    unsigned char * pressed_keys;
    // Pressed keys in a given reading round
    unsigned char pressed_keys_old_num;
    unsigned char pressed_keys_num;

    // Events datastructure
    Node callbacks[LAYOUT_SIZE];
} EepromConfig;

extern EepromConfig * eeprom;

#endif /* SVAROSKEY_CONFIG_H */
