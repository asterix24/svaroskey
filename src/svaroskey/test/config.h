#ifndef SVAROSKEY_CONFIG_H
#define SVAROSKEY_CONFIG_H

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
 * @brief A combination of keys, with respective action.
 */
typedef struct Combination {
    Action action;
    unsigned char keys_num;
    unsigned char keys[];
} Combination;

/**
 * @brief A node in the tree of Actions.
 *
 * Each node contains the Action for the currently selected key, and an array
 * of possible combinations, if other keys are simultaneously present.
 *
 * Combinations MUST be sorted by length (longest first), and then
 * lexicographically (lower numbers first). This allows for efficient matching
 * with no backtracking.
 */
typedef struct Node {
    Action action;

    unsigned char combinations_num;
    Combination * combinations;
} Node;

/**
 * @brief This structure represents what is written in the eeprom.
 *
 * This datastructure is needed in order to customize events depending on
 * single/multiple physical keypresses. In addition, it gives a place where to
 * write arrays whose dimension is configuration dependent.
 */
typedef struct EepromConfig {
    /// Max number of physical pressed keys at any one time
    unsigned char max_pressed_keys;
    /// Array of previosly pressed physical keys
    unsigned char * pressed_keys_old;
    /// Array of currently pressed physical keys
    unsigned char * pressed_keys;
    /// Array to to operations in.
    unsigned char * edit_buffer;
    /// Number of previously pressed keys
    unsigned char pressed_keys_old_num;
    /// Number of currently pressed keys
    unsigned char pressed_keys_num;
    /// Array for triggerable actions of size max_pressed_keys
    Action ** actions;

    /**
     * @brief The number of keys this config has been configured for.
     *
     * This value, loaded from the config, MUST match the LAYOUT_SIZE value.
     */
    unsigned char keys_num;
    /// Callbacks datastructure
    Node * keys;
} EepromConfig;

extern EepromConfig * eeprom;

#endif /* SVAROSKEY_CONFIG_H */
