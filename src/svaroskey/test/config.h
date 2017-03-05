#ifndef SVAROSKEY_CONFIG_H
#define SVAROSKEY_CONFIG_H

#include "layouts.h"

/**
 * @brief Id and parameter to perform an internal callback.
 */
typedef struct CallbackId {
    unsigned char code;
    unsigned char param;
} CallbackId;

/**
 * @brief A callback with its priority.
 *
 * Each action has to have an UNIQUE priority, so that at runtime different
 * actions can be sorted. This allows the result of executing all callbacks to
 * be deterministic, no matter the order in which any physical key is read.
 */
typedef struct Action {
    CallbackId callback;
    unsigned char priority;
} Action;

/**
 * @brief A node in the tree of Actions.
 *
 * Each node contains the Action for the currently selected key, and an array
 * of alternatives, if other keys are simultaneously present.
 *
 * See callbacks.h to see how the structure is actually used.
 */
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
