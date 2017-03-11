#include "config.h"

#include "stddef.h"
#include "keycodes.h"

// Constants processed from the config file.
#define MAX_PRESSED_KEYS 10

// Stuff in memory, generated by processing config file.
static uint8_t pressed_keys_old_data[MAX_PRESSED_KEYS];
static uint8_t pressed_keys_data[MAX_PRESSED_KEYS];
static uint8_t edit_buffer[MAX_PRESSED_KEYS];
static Action * actions[MAX_PRESSED_KEYS];

static Combination a_combination = {
    {{1, ID_KEY_3}, 0}, 1, {34}
};

static Node keys[LAYOUT_SIZE] = {
    {{{1, ID_KEY_ESCAPE        }, 1}, 0, NULL}, // 0   ROW 1
    {{{1, ID_KEY_F1            }, 2}, 0, NULL}, // 1
    {{{1, ID_KEY_F2            }, 3}, 0, NULL}, // 2
    {{{1, ID_KEY_F3            }, 4}, 0, NULL}, // 3
    {{{1, ID_KEY_F4            }, 5}, 0, NULL}, // 4
    {{{1, ID_KEY_F5            }, 6}, 0, NULL}, // 5
    {{{1, ID_KEY_F6            }, 7}, 0, NULL}, // 6
    {{{1, ID_KEY_F7            }, 8}, 0, NULL}, // 7
    {{{1, ID_KEY_F8            }, 9}, 0, NULL}, // 8
    {{{1, ID_KEY_GRAVE         }, 10}, 0, NULL}, // 9   ROW 2
    {{{1, ID_KEY_1             }, 11}, 0, NULL}, // 10
    {{{1, ID_KEY_2             }, 12}, 0, NULL}, // 11
    {{{1, ID_KEY_3             }, 13}, 0, NULL}, // 12
    {{{1, ID_KEY_4             }, 14}, 0, NULL}, // 13
    {{{1, ID_KEY_5             }, 15}, 0, NULL}, // 14
    {{{1, ID_KEY_6             }, 16}, 0, NULL}, // 15
    {{{1, ID_KEY_7             }, 17}, 0, NULL}, // 16
    {{{1, ID_KEY_8             }, 18}, 0, NULL}, // 17
    {{{1, ID_KEY_9             }, 19}, 0, NULL}, // 18
    {{{1, ID_KEY_0             }, 20}, 0, NULL}, // 19
    {{{1, ID_KEY_TAB           }, 21}, 0, NULL}, // 20  ROW 3
    {{{1, ID_KEY_Q             }, 22}, 0, NULL}, // 21
    {{{1, ID_KEY_W             }, 23}, 0, NULL}, // 22
    {{{1, ID_KEY_E             }, 24}, 0, NULL}, // 23
    {{{1, ID_KEY_R             }, 25}, 0, NULL}, // 24
    {{{1, ID_KEY_T             }, 26}, 0, NULL}, // 25
    {{{1, ID_KEY_Y             }, 27}, 0, NULL}, // 26
    {{{1, ID_KEY_U             }, 28}, 0, NULL}, // 27
    {{{1, ID_KEY_I             }, 29}, 0, NULL}, // 28
    {{{1, ID_KEY_O             }, 30}, 0, NULL}, // 29
    {{{1, ID_KEY_CAPSLOCK      }, 31}, 0, NULL}, // 30  ROW 4
    {{{1, ID_KEY_A             }, 32}, 1, &a_combination}, // 31
    {{{1, ID_KEY_S             }, 33}, 0, NULL}, // 32
    {{{1, ID_KEY_D             }, 34}, 0, NULL}, // 33
    {{{1, ID_KEY_F             }, 35}, 0, NULL}, // 34
    {{{1, ID_KEY_G             }, 36}, 0, NULL}, // 35
    {{{1, ID_KEY_H             }, 37}, 0, NULL}, // 36
    {{{1, ID_KEY_J             }, 38}, 0, NULL}, // 37
    {{{1, ID_KEY_K             }, 39}, 0, NULL}, // 38
    {{{1, ID_KEY_L             }, 40}, 0, NULL}, // 39
    {{{1, ID_KEY_LEFTSHIFT     }, 41}, 0, NULL}, // 40  ROW 5
    {{{1, ID_KEY_Z             }, 42}, 0, NULL}, // 41
    {{{1, ID_KEY_X             }, 43}, 0, NULL}, // 42
    {{{1, ID_KEY_C             }, 44}, 0, NULL}, // 43
    {{{1, ID_KEY_V             }, 45}, 0, NULL}, // 44
    {{{1, ID_KEY_B             }, 46}, 0, NULL}, // 45
    {{{1, ID_KEY_N             }, 47}, 0, NULL}, // 46
    {{{1, ID_KEY_M             }, 48}, 0, NULL}, // 47
    {{{1, ID_KEY_COMMA         }, 49}, 0, NULL}, // 48
    {{{1, ID_KEY_PERIOD        }, 50}, 0, NULL}, // 49
    {{{1, ID_KEY_LEFTCONTROL   }, 51}, 0, NULL}, // 50  ROW 6
    {{{1, ID_KEY_LEFTGUI       }, 52}, 0, NULL}, // 51
    {{{1, ID_KEY_LEFTALT       }, 53}, 0, NULL}, // 52
    {{{1, ID_KEY_SPACE         }, 54}, 0, NULL}, // 53
    {{{1, ID_KEY_RIGHTALT      }, 55}, 0, NULL}, // 54
    {{{1, ID_KEY_F9            }, 56}, 0, NULL}, // 55  ROW 7
    {{{1, ID_KEY_F10           }, 57}, 0, NULL}, // 56
    {{{1, ID_KEY_F11           }, 58}, 0, NULL}, // 57
    {{{1, ID_KEY_F12           }, 59}, 0, NULL}, // 58
    {{{1, ID_KEY_SCROLLLOCK    }, 60}, 0, NULL}, // 59
    {{{1, ID_KEY_PRINTSCREEN   }, 61}, 0, NULL}, // 60
    {{{1, ID_KEY_PAUSE         }, 62}, 0, NULL}, // 61
    {{{1, ID_KEY_MINUS         }, 63}, 0, NULL}, // 62  ROW 8
    {{{1, ID_KEY_EQUALS        }, 64}, 0, NULL}, // 63
    {{{1, ID_KEY_DELETE        }, 65}, 0, NULL}, // 64
    {{{1, ID_KEY_INSERT        }, 66}, 0, NULL}, // 65
    {{{1, ID_KEY_HOME          }, 67}, 0, NULL}, // 66
    {{{1, ID_KEY_PAGEUP        }, 68}, 0, NULL}, // 67
    {{{1, ID_KP_NUMLOCK        }, 69}, 0, NULL}, // 68
    {{{1, ID_KP_DIVIDE         }, 70}, 0, NULL}, // 69
    {{{1, ID_KP_MULTIPLY       }, 71}, 0, NULL}, // 70
    {{{1, ID_KP_SUBTRACT       }, 72}, 0, NULL}, // 71
    {{{1, ID_KEY_P             }, 73}, 0, NULL}, // 72  ROW 9
    {{{1, ID_KEY_LEFTBRACKET   }, 74}, 0, NULL}, // 73
    {{{1, ID_KEY_RIGHTBRACKET  }, 75}, 0, NULL}, // 74
    {{{1, ID_KEY_DELETEFORWARD }, 76}, 0, NULL}, // 75
    {{{1, ID_KEY_END           }, 77}, 0, NULL}, // 76
    {{{1, ID_KEY_PAGEDOWN      }, 78}, 0, NULL}, // 77
    {{{1, ID_KP_7              }, 79}, 0, NULL}, // 78
    {{{1, ID_KP_8              }, 80}, 0, NULL}, // 79
    {{{1, ID_KP_9              }, 81}, 0, NULL}, // 80
    {{{1, ID_KEY_SEMICOLON     }, 82}, 0, NULL}, // 81  ROW 10
    {{{1, ID_KEY_QUOTE         }, 83}, 0, NULL}, // 82
    {{{1, ID_KEY_Q             }, 84}, 0, NULL}, // 83
    {{{1, ID_KEY_ENTER         }, 85}, 0, NULL}, // 84
    {{{1, ID_KEY_T             }, 86}, 0, NULL}, // 85
    {{{1, ID_KP_4              }, 87}, 0, NULL}, // 86
    {{{1, ID_KP_5              }, 88}, 0, NULL}, // 87
    {{{1, ID_KP_6              }, 89}, 0, NULL}, // 88
    {{{1, ID_KP_ADD            }, 90}, 0, NULL}, // 89
    {{{1, ID_KEY_SLASH         }, 91}, 0, NULL}, // 90  ROW 11
    {{{1, ID_KEY_BACKSLASH     }, 92}, 0, NULL}, // 91
    {{{1, ID_KEY_RIGHTSHIFT    }, 93}, 0, NULL}, // 92
    {{{1, ID_KEY_UP            }, 94}, 0, NULL}, // 93
    {{{1, ID_KP_1              }, 95}, 0, NULL}, // 94
    {{{1, ID_KP_2              }, 96}, 0, NULL}, // 95
    {{{1, ID_KP_3              }, 97}, 0, NULL}, // 96
    {{{1, ID_KEY_RIGHTGUI      }, 98}, 0, NULL}, // 97  ROW 12
    {{{1, ID_KEY_MENU          }, 99}, 0, NULL}, // 98
    {{{1, ID_KEY_RIGHTCONTROL  }, 100}, 0, NULL}, // 99
    {{{1, ID_KEY_LEFT          }, 101}, 0, NULL}, // 100
    {{{1, ID_KEY_DOWN          }, 102}, 0, NULL}, // 101
    {{{1, ID_KEY_RIGHT         }, 103}, 0, NULL}, // 102
    {{{1, ID_KP_0              }, 104}, 0, NULL}, // 103
    {{{1, ID_KP_POINT          }, 105}, 0, NULL}, // 104
    {{{1, ID_KP_ENTER          }, 106}, 0, NULL}, // 105
};

// Struct we access from outside (also in eeprom memory)
static EepromConfig data = {
    .max_pressed_keys = MAX_PRESSED_KEYS,
    .pressed_keys_old = pressed_keys_old_data,
    .pressed_keys = pressed_keys_data,
    .edit_buffer = edit_buffer,
    .pressed_keys_old_num = 0,
    .pressed_keys_num = 0,
    .actions = actions,
    .keys_num = LAYOUT_SIZE,
    .keys = keys,
};

// Exported (we get this pointer by loading the eeprom in RAM)
EepromConfig * eeprom = &data;
