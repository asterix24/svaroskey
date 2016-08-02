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
	{ 0,    KEY_ESCAPE        },
	{ 1,    KEY_F1            },
	{ 2,    KEY_F2            },
	{ 3,    KEY_F3            },
	{ 4,    KEY_F4            },
	{ 5,    KEY_F5            },
	{ 6,    KEY_F6            },
	{ 7,    KEY_F7            },
	{ 8,    KEY_F8            },
	{ 9,    KEY_F9            },
	{ 10,   KEY_F10           },
	{ 11,   KEY_F11           },
	{ 12,   KEY_F12           },
	{ 13,   KEY_PRINTSCREEN   },
	{ 14,   KEY_SCROLLLOCK    },
	{ 15,   KEY_PAUSE         },
	{ 16,   KEY_GRAVE         },
	{ 17,   KEY_1             },
	{ 18,   KEY_2             },
	{ 19,   KEY_3             },
	{ 20,   KEY_4             },
	{ 21,   KEY_5             },
	{ 22,   KEY_6             },
	{ 23,   KEY_7             },
	{ 24,   KEY_8             },
	{ 25,   KEY_9             },
	{ 26,   KEY_0             },
	{ 27,   KEY_MINUS         },
	{ 28,   KEY_EQUALS        },
	{ 29,   KEY_DELETE        },
	{ 30,   KEY_TAB           },
	{ 31,   KEY_Q             },
	{ 32,   KEY_W             },
	{ 33,   KEY_E             },
	{ 34,   KEY_R             },
	{ 35,   KEY_T             },
	{ 36,   KEY_Y             },
	{ 37,   KEY_U             },
	{ 38,   KEY_I             },
	{ 39,   KEY_O             },
	{ 40,   KEY_P             },
	{ 41,   KEY_LEFTBRACKET   },
	{ 42,   KEY_RIGHTBRACKET  },
	{ 43,   KEY_ENTER         },
	{ 44,   KEY_CAPSLOCK      },
	{ 45,   KEY_A             },
	{ 46,   KEY_S             },
	{ 47,   KEY_D             },
	{ 48,   KEY_F             },
	{ 49,   KEY_G             },
	{ 50,   KEY_H             },
	{ 51,   KEY_J             },
	{ 52,   KEY_K             },
	{ 53,   KEY_L             },
	{ 54,   KEY_SEMICOLON     },
	{ 55,   KEY_QUOTE         },
	{ 56,   KEY_BACKSLASH     },
	{ 57,   KEY_LEFTSHIFT     },
	{ 58,   KEY_Z             },
	{ 59,   KEY_X             },
	{ 60,   KEY_C             },
	{ 61,   KEY_V             },
	{ 62,   KEY_B             },
	{ 63,   KEY_N             },
	{ 64,   KEY_M             },
	{ 65,   KEY_COMMA         },
	{ 66,   KEY_PERIOD        },
	{ 67,   KEY_SLASH         },
	{ 68,   KEY_RIGHTSHIFT    },
	{ 69,   KEY_LEFTCONTROL   },
	{ 70,   KEY_LEFTGUI       },
	{ 71,   KEY_LEFTALT       },
	{ 72,   KEY_SPACE         },
	{ 73,   KEY_RIGHTALT      },
	{ 74,   KEY_RIGHTGUI      },
	{ 75,   KEY_MENU          },
	{ 76,   KEY_RIGHTCONTROL  },
	{ 77,   KEY_INSERT        },
	{ 78,   KEY_HOME          },
	{ 79,   KEY_PAGEUP        },
	{ 80,   KEY_DELETEFORWARD },
	{ 81,   KEY_END           },
	{ 82,   KEY_PAGEDOWN      },
	{ 83,   KEY_UP            },
	{ 84,   KEY_DOWN          },
	{ 85,   KEY_LEFT          },
	{ 86,   KEY_RIGHT         },
	{ 87,   KP_NUMLOCK        },
	{ 88,   KP_DIVIDE         },
	{ 89,   KP_MULTIPLY       },
	{ 90,   KP_SUBTRACT       },
	{ 91,   KP_ADD            },
	{ 92,   KP_ENTER          },
	{ 93,   KP_POINT          },
	{ 94,   KP_0              },
	{ 95,   KP_1              },
	{ 96,   KP_2              },
	{ 97,   KP_3              },
	{ 98,   KP_4              },
	{ 99,   KP_5              },
	{ 100,  KP_6              },
	{ 101,  KP_7              },
	{ 102,  KP_8              },
	{ 103,  KP_9              },
#endif
};
