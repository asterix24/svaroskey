#include "cfg/cfg_keymap.h"

#include "layouts.h"
#include "keymap.h"
#include "keycodes.h"

#define CONFIG_LAYOUT_LATEST_REVISION 0

#if !defined CONFIG_LAYOUT_REVISION
#error CONFIG_LAYOUT_REVISION is not defined.
#elif (CONFIG_LAYOUT_REVISION > CONFIG_LAYOUT_LATEST_REVISION)
#error CONFIG_LAYOUT_REVISION is not valid.
#endif

KeyBinding keymap_layout[LAYOUT_SIZE] = {
#if (CONFIG_LAYOUT_REVISION == 0)
	/* Row 1 */
	{ 0,    KEY_GRAVE         },
	{ 1,    KEY_1             },
	{ 2,    KEY_2             },
	{ 3,    KEY_3             },
	{ 4,    KEY_4             },
	{ 5,    KEY_5             },
	{ 6,    KEY_6             },
	{ 7,    KEY_7             },
	{ 8,    KEY_8             },
	{ 9,    KEY_9             },
	{ 10,   KEY_0             },
	{ 11,   KEY_MINUS         },
	{ 12,   KEY_EQUALS        },
	{ 13,   KEY_DELETE        },

	/* Row 2 */
	{ 14,   KEY_TAB           },
	{ 15,   KEY_Q             },
	{ 16,   KEY_W             },
	{ 17,   KEY_E             },
	{ 18,   KEY_R             },
	{ 19,   KEY_T             },
	{ 20,   KEY_Y             },
	{ 21,   KEY_U             },
	{ 22,   KEY_I             },
	{ 23,   KEY_O             },
	{ 24,   KEY_P             },
	{ 25,   KEY_LEFTBRACKET   },
	{ 26,   KEY_RIGHTBRACKET  },
	{ 27,   KEY_ENTER         },

	/* Row 3 */
	{ 28,   KEY_CAPSLOCK      },
	{ 29,   KEY_A             },
	{ 30,   KEY_S             },
	{ 31,   KEY_D             },
	{ 32,   KEY_F             },
	{ 33,   KEY_G             },
	{ 34,   KEY_H             },
	{ 35,   KEY_J             },
	{ 36,   KEY_K             },
	{ 37,   KEY_L             },
	{ 38,   KEY_SEMICOLON     },
	{ 39,   KEY_QUOTE         },
	{ 40,   KEY_BACKSLASH     },

	/* Row 4 */
	{ 41,   KEY_LEFTSHIFT     },
	{ 42,   KEY_ESCAPE        },
	{ 43,   KEY_Z             },
	{ 44,   KEY_X             },
	{ 45,   KEY_C             },
	{ 46,   KEY_V             },
	{ 47,   KEY_B             },
	{ 48,   KEY_N             },
	{ 49,   KEY_M             },
	{ 50,   KEY_COMMA         },
	{ 51,   KEY_PERIOD        },
	{ 52,   KEY_SLASH         },
	{ 53,   KEY_RIGHTSHIFT    },

	/* Row 5 */
	{ 54,   KEY_LEFTCONTROL   },
	{ 55,   KEY_LEFTGUI       },
	{ 56,   KEY_LEFTALT       },
	{ 57,   KEY_SPACE         },
	{ 58,   KEY_ESCAPE        },
	{ 59,   KEY_SPACE         },
	{ 60,   KEY_RIGHTALT      },
	{ 61,   KEY_RIGHTGUI      },
	{ 62,   KEY_MENU          },
	{ 63,   KEY_RIGHTCONTROL  },
	{ 64,   KEY_ESCAPE        },
#endif
};
