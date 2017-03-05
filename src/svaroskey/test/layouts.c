#include "layouts.h"

#include "keycodes.h"

typedef struct
{
	uint16_t mapping_id;
	scancode_t code;
} KeyBinding;

KeyBinding keymap_layout[LAYOUT_SIZE] = {
	/* Row 1 */
	{ 0,    KEY_ESCAPE        },
	{ 1,    KEY_F1            },
	{ 2,    KEY_F2            },
	{ 3,    KEY_F3            },
	{ 4,    KEY_F4            },
	{ 5,    KEY_F5            },
	{ 6,    KEY_F6            },
	{ 7,    KEY_F7            },
	{ 8,    KEY_F8            },

	/* Row 2 */
	{ 9,    KEY_GRAVE         },
	{ 10,   KEY_1             },
	{ 11,   KEY_2             },
	{ 12,   KEY_3             },
	{ 13,   KEY_4             },
	{ 14,   KEY_5             },
	{ 15,   KEY_6             },
	{ 16,   KEY_7             },
	{ 17,   KEY_8             },
	{ 18,   KEY_9             },
	{ 19,   KEY_0             },

	/* Row 3 */
	{ 20,   KEY_TAB           },
	{ 21,   KEY_Q             },
	{ 22,   KEY_W             },
	{ 23,   KEY_E             },
	{ 24,   KEY_R             },
	{ 25,   KEY_T             },
	{ 26,   KEY_Y             },
	{ 27,   KEY_U             },
	{ 28,   KEY_I             },
	{ 29,   KEY_O             },

	/* Row 4 */
	{ 30,   KEY_CAPSLOCK      },
	{ 31,   KEY_A             },
	{ 32,   KEY_S             },
	{ 33,   KEY_D             },
	{ 34,   KEY_F             },
	{ 35,   KEY_G             },
	{ 36,   KEY_H             },
	{ 37,   KEY_J             },
	{ 38,   KEY_K             },
	{ 39,   KEY_L             },

	/* Row 5 */
	{ 40,   KEY_LEFTSHIFT     },
	{ 41,   KEY_Z             },
	{ 42,   KEY_X             },
	{ 43,   KEY_C             },
	{ 44,   KEY_V             },
	{ 45,   KEY_B             },
	{ 46,   KEY_N             },
	{ 47,   KEY_M             },
	{ 48,   KEY_COMMA         },
	{ 49,   KEY_PERIOD        },

	/* Row 6 */
	{ 50,   KEY_LEFTCONTROL   },
	{ 51,   KEY_LEFTGUI       },
	{ 52,   KEY_LEFTALT       },
	{ 53,   KEY_SPACE         },
	{ 54,   KEY_RIGHTALT      },

	/* Row 7 */
	{ 55,   KEY_F9            },
	{ 56,   KEY_F10           },
	{ 57,   KEY_F11           },
	{ 58,   KEY_F12           },
	{ 59,   KEY_SCROLLLOCK    },
	{ 60,   KEY_PRINTSCREEN   },
	{ 61,   KEY_PAUSE         },

	/* Row 8 */
	{ 62,   KEY_MINUS         },
	{ 63,   KEY_EQUALS        },
	{ 64,   KEY_DELETE        },
	{ 65,   KEY_INSERT        },
	{ 66,   KEY_HOME          },
	{ 67,   KEY_PAGEUP        },
	{ 68,   KP_NUMLOCK        },
	{ 69,   KP_DIVIDE         },
	{ 70,   KP_MULTIPLY       },
	{ 71,   KP_SUBTRACT       },

	/* Row 9 */
	{ 72,   KEY_P             },
	{ 73,   KEY_LEFTBRACKET   },
	{ 74,   KEY_RIGHTBRACKET  },
	{ 75,   KEY_DELETEFORWARD },
	{ 76,   KEY_END           },
	{ 77,   KEY_PAGEDOWN      },
	{ 78,   KP_7              },
	{ 79,   KP_8              },
	{ 80,   KP_9              },

	/* Row 10 */
	{ 81,   KEY_SEMICOLON     },
	{ 82,   KEY_QUOTE         },
	{ 83,   KEY_Q             },
	{ 84,   KEY_ENTER         },
	{ 85,   KEY_T             },
	{ 86,   KP_4              },
	{ 87,   KP_5              },
	{ 88,   KP_6              },
	{ 89,   KP_ADD            },

	/* Row 11 */
	{ 90,   KEY_SLASH         },
	{ 91,   KEY_BACKSLASH     },
	{ 92,   KEY_RIGHTSHIFT    },
	{ 93,   KEY_UP            },
	{ 94,   KP_1              },
	{ 95,   KP_2              },
	{ 96,   KP_3              },

	/* Row 12 */
	{ 97,   KEY_RIGHTGUI      },
	{ 98,   KEY_MENU          },
	{ 99,   KEY_RIGHTCONTROL  },
	{ 100,  KEY_LEFT          },
	{ 101,  KEY_DOWN          },
	{ 102,  KEY_RIGHT         },
	{ 103,  KP_0              },
	{ 104,  KP_POINT          },
	{ 105,  KP_ENTER          },
};

scancode_t tmp_sdl_conversion(unsigned char id) {
    KeyBinding * key = &keymap_layout[id];
    return key->code;
}
