#include "layouts.h"

#include "keycodes.h"

#include "SDL.h"

typedef struct
{
    uint16_t mapping_id;
    keycode_t code;
} KeyBinding;

// This is just to make SDL work without the need to rewrite stuff - since this
// is a tmp file whatever.
#define   TMP_KEY_A                 SDL_SCANCODE_A
#define   TMP_KEY_B                 SDL_SCANCODE_B
#define   TMP_KEY_C                 SDL_SCANCODE_C
#define   TMP_KEY_D                 SDL_SCANCODE_D
#define   TMP_KEY_E                 SDL_SCANCODE_E
#define   TMP_KEY_F                 SDL_SCANCODE_F
#define   TMP_KEY_G                 SDL_SCANCODE_G
#define   TMP_KEY_H                 SDL_SCANCODE_H
#define   TMP_KEY_I                 SDL_SCANCODE_I
#define   TMP_KEY_J                 SDL_SCANCODE_J
#define   TMP_KEY_K                 SDL_SCANCODE_K
#define   TMP_KEY_L                 SDL_SCANCODE_L
#define   TMP_KEY_M                 SDL_SCANCODE_M
#define   TMP_KEY_N                 SDL_SCANCODE_N
#define   TMP_KEY_O                 SDL_SCANCODE_O
#define   TMP_KEY_P                 SDL_SCANCODE_P
#define   TMP_KEY_Q                 SDL_SCANCODE_Q
#define   TMP_KEY_R                 SDL_SCANCODE_R
#define   TMP_KEY_S                 SDL_SCANCODE_S
#define   TMP_KEY_T                 SDL_SCANCODE_T
#define   TMP_KEY_U                 SDL_SCANCODE_U
#define   TMP_KEY_V                 SDL_SCANCODE_V
#define   TMP_KEY_W                 SDL_SCANCODE_W
#define   TMP_KEY_X                 SDL_SCANCODE_X
#define   TMP_KEY_Y                 SDL_SCANCODE_Y
#define   TMP_KEY_Z                 SDL_SCANCODE_Z
#define   TMP_KEY_1                 SDL_SCANCODE_1
#define   TMP_KEY_2                 SDL_SCANCODE_2
#define   TMP_KEY_3                 SDL_SCANCODE_3
#define   TMP_KEY_4                 SDL_SCANCODE_4
#define   TMP_KEY_5                 SDL_SCANCODE_5
#define   TMP_KEY_6                 SDL_SCANCODE_6
#define   TMP_KEY_7                 SDL_SCANCODE_7
#define   TMP_KEY_8                 SDL_SCANCODE_8
#define   TMP_KEY_9                 SDL_SCANCODE_9
#define   TMP_KEY_0                 SDL_SCANCODE_0
#define   TMP_KEY_ENTER             SDL_SCANCODE_RETURN
#define   TMP_KEY_ESCAPE            SDL_SCANCODE_ESCAPE
#define   TMP_KEY_DELETE            SDL_SCANCODE_BACKSPACE
#define   TMP_KEY_TAB               SDL_SCANCODE_TAB
#define   TMP_KEY_SPACE             SDL_SCANCODE_SPACE
#define   TMP_KEY_MINUS             SDL_SCANCODE_MINUS
#define   TMP_KEY_EQUALS            SDL_SCANCODE_EQUALS
#define   TMP_KEY_LEFTBRACKET       SDL_SCANCODE_LEFTBRACKET
#define   TMP_KEY_RIGHTBRACKET      SDL_SCANCODE_RIGHTBRACKET
#define   TMP_KEY_BACKSLASH         SDL_SCANCODE_BACKSLASH
#define   TMP_KEY_SEMICOLON         SDL_SCANCODE_SEMICOLON
#define   TMP_KEY_QUOTE             SDL_SCANCODE_APOSTROPHE
#define   TMP_KEY_GRAVE             SDL_SCANCODE_GRAVE
#define   TMP_KEY_COMMA             SDL_SCANCODE_COMMA
#define   TMP_KEY_PERIOD            SDL_SCANCODE_PERIOD
#define   TMP_KEY_SLASH             SDL_SCANCODE_SLASH
#define   TMP_KEY_CAPSLOCK          SDL_SCANCODE_CAPSLOCK
#define   TMP_KEY_F1                SDL_SCANCODE_F1
#define   TMP_KEY_F2                SDL_SCANCODE_F2
#define   TMP_KEY_F3                SDL_SCANCODE_F3
#define   TMP_KEY_F4                SDL_SCANCODE_F4
#define   TMP_KEY_F5                SDL_SCANCODE_F5
#define   TMP_KEY_F6                SDL_SCANCODE_F6
#define   TMP_KEY_F7                SDL_SCANCODE_F7
#define   TMP_KEY_F8                SDL_SCANCODE_F8
#define   TMP_KEY_F9                SDL_SCANCODE_F9
#define   TMP_KEY_F10               SDL_SCANCODE_F10
#define   TMP_KEY_F11               SDL_SCANCODE_F11
#define   TMP_KEY_F12               SDL_SCANCODE_F12
#define   TMP_KEY_PRINTSCREEN       SDL_SCANCODE_PRINTSCREEN
#define   TMP_KEY_SCROLLLOCK        SDL_SCANCODE_SCROLLLOCK
#define   TMP_KEY_PAUSE             SDL_SCANCODE_PAUSE
#define   TMP_KEY_INSERT            SDL_SCANCODE_INSERT
#define   TMP_KEY_HOME              SDL_SCANCODE_HOME
#define   TMP_KEY_PAGEUP            SDL_SCANCODE_PAGEUP
#define   TMP_KEY_DELETEFORWARD     SDL_SCANCODE_DELETE
#define   TMP_KEY_END               SDL_SCANCODE_END
#define   TMP_KEY_PAGEDOWN          SDL_SCANCODE_PAGEDOWN
#define   TMP_KEY_RIGHT             SDL_SCANCODE_RIGHT
#define   TMP_KEY_LEFT              SDL_SCANCODE_LEFT
#define   TMP_KEY_DOWN              SDL_SCANCODE_DOWN
#define   TMP_KEY_UP                SDL_SCANCODE_UP
#define   TMP_KP_NUMLOCK            SDL_SCANCODE_NUMLOCKCLEAR
#define   TMP_KP_DIVIDE             SDL_SCANCODE_KP_DIVIDE
#define   TMP_KP_MULTIPLY           SDL_SCANCODE_KP_MULTIPLY
#define   TMP_KP_SUBTRACT           SDL_SCANCODE_KP_MINUS
#define   TMP_KP_ADD                SDL_SCANCODE_KP_PLUS
#define   TMP_KP_ENTER              SDL_SCANCODE_KP_ENTER
#define   TMP_KP_1                  SDL_SCANCODE_KP_1
#define   TMP_KP_2                  SDL_SCANCODE_KP_2
#define   TMP_KP_3                  SDL_SCANCODE_KP_3
#define   TMP_KP_4                  SDL_SCANCODE_KP_4
#define   TMP_KP_5                  SDL_SCANCODE_KP_5
#define   TMP_KP_6                  SDL_SCANCODE_KP_6
#define   TMP_KP_7                  SDL_SCANCODE_KP_7
#define   TMP_KP_8                  SDL_SCANCODE_KP_8
#define   TMP_KP_9                  SDL_SCANCODE_KP_9
#define   TMP_KP_0                  SDL_SCANCODE_KP_0
#define   TMP_KP_POINT              SDL_SCANCODE_KP_PERIOD
#define   TMP_KEY_NONUSBACKSLASH    SDL_SCANCODE_NONUSBACKSLASH
#define   TMP_KP_EQUALS             SDL_SCANCODE_KP_EQUALS
#define   TMP_KEY_F13               SDL_SCANCODE_F13
#define   TMP_KEY_F14               SDL_SCANCODE_F14
#define   TMP_KEY_F15               SDL_SCANCODE_F15
#define   TMP_KEY_F16               SDL_SCANCODE_F16
#define   TMP_KEY_F17               SDL_SCANCODE_F17
#define   TMP_KEY_F18               SDL_SCANCODE_F18
#define   TMP_KEY_F19               SDL_SCANCODE_F19
#define   TMP_KEY_F20               SDL_SCANCODE_F20
#define   TMP_KEY_F21               SDL_SCANCODE_F21
#define   TMP_KEY_F22               SDL_SCANCODE_F22
#define   TMP_KEY_F23               SDL_SCANCODE_F23
#define   TMP_KEY_F24               SDL_SCANCODE_F24
#define   TMP_KEY_HELP              SDL_SCANCODE_HELP
#define   TMP_KEY_MENU              SDL_SCANCODE_MENU
#define   TMP_KEY_LEFTCONTROL       SDL_SCANCODE_LCTRL
#define   TMP_KEY_LEFTSHIFT         SDL_SCANCODE_LSHIFT
#define   TMP_KEY_LEFTALT           SDL_SCANCODE_LALT
#define   TMP_KEY_LEFTGUI           SDL_SCANCODE_LGUI
#define   TMP_KEY_RIGHTCONTROL      SDL_SCANCODE_RCTRL
#define   TMP_KEY_RIGHTSHIFT        SDL_SCANCODE_RSHIFT
#define   TMP_KEY_RIGHTALT          SDL_SCANCODE_RALT
#define   TMP_KEY_RIGHTGUI          SDL_SCANCODE_RGUI

KeyBinding keymap_layout[LAYOUT_SIZE] = {
    /* Row 1 */
    { 0,    TMP_KEY_ESCAPE        },
    { 1,    TMP_KEY_F1            },
    { 2,    TMP_KEY_F2            },
    { 3,    TMP_KEY_F3            },
    { 4,    TMP_KEY_F4            },
    { 5,    TMP_KEY_F5            },
    { 6,    TMP_KEY_F6            },
    { 7,    TMP_KEY_F7            },
    { 8,    TMP_KEY_F8            },

    /* Row 2TMP_ */
    { 9,    TMP_KEY_GRAVE         },
    { 10,   TMP_KEY_1             },
    { 11,   TMP_KEY_2             },
    { 12,   TMP_KEY_3             },
    { 13,   TMP_KEY_4             },
    { 14,   TMP_KEY_5             },
    { 15,   TMP_KEY_6             },
    { 16,   TMP_KEY_7             },
    { 17,   TMP_KEY_8             },
    { 18,   TMP_KEY_9             },
    { 19,   TMP_KEY_0             },

    /* Row 3TMP_ */
    { 20,   TMP_KEY_TAB           },
    { 21,   TMP_KEY_Q             },
    { 22,   TMP_KEY_W             },
    { 23,   TMP_KEY_E             },
    { 24,   TMP_KEY_R             },
    { 25,   TMP_KEY_T             },
    { 26,   TMP_KEY_Y             },
    { 27,   TMP_KEY_U             },
    { 28,   TMP_KEY_I             },
    { 29,   TMP_KEY_O             },

    /* Row 4TMP_ */
    { 30,   TMP_KEY_CAPSLOCK      },
    { 31,   TMP_KEY_A             },
    { 32,   TMP_KEY_S             },
    { 33,   TMP_KEY_D             },
    { 34,   TMP_KEY_F             },
    { 35,   TMP_KEY_G             },
    { 36,   TMP_KEY_H             },
    { 37,   TMP_KEY_J             },
    { 38,   TMP_KEY_K             },
    { 39,   TMP_KEY_L             },

    /* Row 5TMP_ */
    { 40,   TMP_KEY_LEFTSHIFT     },
    { 41,   TMP_KEY_Z             },
    { 42,   TMP_KEY_X             },
    { 43,   TMP_KEY_C             },
    { 44,   TMP_KEY_V             },
    { 45,   TMP_KEY_B             },
    { 46,   TMP_KEY_N             },
    { 47,   TMP_KEY_M             },
    { 48,   TMP_KEY_COMMA         },
    { 49,   TMP_KEY_PERIOD        },

    /* Row 6TMP_ */
    { 50,   TMP_KEY_LEFTCONTROL   },
    { 51,   TMP_KEY_LEFTGUI       },
    { 52,   TMP_KEY_LEFTALT       },
    { 53,   TMP_KEY_SPACE         },
    { 54,   TMP_KEY_RIGHTALT      },

    /* Row 7TMP_ */
    { 55,   TMP_KEY_F9            },
    { 56,   TMP_KEY_F10           },
    { 57,   TMP_KEY_F11           },
    { 58,   TMP_KEY_F12           },
    { 59,   TMP_KEY_SCROLLLOCK    },
    { 60,   TMP_KEY_PRINTSCREEN   },
    { 61,   TMP_KEY_PAUSE         },

    /* Row 8TMP_ */
    { 62,   TMP_KEY_MINUS         },
    { 63,   TMP_KEY_EQUALS        },
    { 64,   TMP_KEY_DELETE        },
    { 65,   TMP_KEY_INSERT        },
    { 66,   TMP_KEY_HOME          },
    { 67,   TMP_KEY_PAGEUP        },
    { 68,   TMP_KP_NUMLOCK        },
    { 69,   TMP_KP_DIVIDE         },
    { 70,   TMP_KP_MULTIPLY       },
    { 71,   TMP_KP_SUBTRACT       },

    /* Row 9TMP_ */
    { 72,   TMP_KEY_P             },
    { 73,   TMP_KEY_LEFTBRACKET   },
    { 74,   TMP_KEY_RIGHTBRACKET  },
    { 75,   TMP_KEY_DELETEFORWARD },
    { 76,   TMP_KEY_END           },
    { 77,   TMP_KEY_PAGEDOWN      },
    { 78,   TMP_KP_7              },
    { 79,   TMP_KP_8              },
    { 80,   TMP_KP_9              },

    /* Row 1TMP_0 */
    { 81,   TMP_KEY_SEMICOLON     },
    { 82,   TMP_KEY_QUOTE         },
    { 83,   TMP_KEY_Q             },
    { 84,   TMP_KEY_ENTER         },
    { 85,   TMP_KEY_T             },
    { 86,   TMP_KP_4              },
    { 87,   TMP_KP_5              },
    { 88,   TMP_KP_6              },
    { 89,   TMP_KP_ADD            },

    /* Row 1TMP_1 */
    { 90,   TMP_KEY_SLASH         },
    { 91,   TMP_KEY_BACKSLASH     },
    { 92,   TMP_KEY_RIGHTSHIFT    },
    { 93,   TMP_KEY_UP            },
    { 94,   TMP_KP_1              },
    { 95,   TMP_KP_2              },
    { 96,   TMP_KP_3              },

    /* Row 1TMP_2 */
    { 97,   TMP_KEY_RIGHTGUI      },
    { 98,   TMP_KEY_MENU          },
    { 99,   TMP_KEY_RIGHTCONTROL  },
    { 100,  TMP_KEY_LEFT          },
    { 101,  TMP_KEY_DOWN          },
    { 102,  TMP_KEY_RIGHT         },
    { 103,  TMP_KP_0              },
    { 104,  TMP_KP_POINT          },
    { 105,  TMP_KP_ENTER          },
};

keycode_t tmp_sdl_conversion(unsigned char id) {
    KeyBinding * key = &keymap_layout[id];
    return key->code;
}
