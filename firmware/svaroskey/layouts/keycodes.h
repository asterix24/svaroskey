#ifndef LAYOUTS_KEYCODES_H
#define LAYOUTS_KEYCODES_H

#define KEY_A                  4
#define KEY_B                  5
#define KEY_C                  6
#define KEY_D                  7
#define KEY_E                  8
#define KEY_F                  9
#define KEY_G                  10
#define KEY_H                  11
#define KEY_I                  12
#define KEY_J                  13
#define KEY_K                  14
#define KEY_L                  15
#define KEY_M                  16
#define KEY_N                  17
#define KEY_O                  18
#define KEY_P                  19
#define KEY_Q                  20
#define KEY_R                  21
#define KEY_S                  22
#define KEY_T                  23
#define KEY_U                  24
#define KEY_V                  25
#define KEY_W                  26
#define KEY_X                  27
#define KEY_Y                  28
#define KEY_Z                  29
#define KEY_1                  30
#define KEY_2                  31
#define KEY_3                  32
#define KEY_4                  33
#define KEY_5                  34
#define KEY_6                  35
#define KEY_7                  36
#define KEY_8                  37
#define KEY_9                  38
#define KEY_0                  39
#define KEY_ENTER              40
#define KEY_ESCAPE             41
#define KEY_DELETE             42
#define KEY_TAB                43
#define KEY_SPACE              44
#define KEY_MINUS              45
#define KEY_EQUALS             46
#define KEY_LEFTBRACKET        47
#define KEY_RIGHTBRACKET       48
#define KEY_BACKSLASH          49
#define KEY_SEMICOLON          51
#define KEY_QUOTE              52
#define KEY_GRAVE              53
#define KEY_COMMA              54
#define KEY_PERIOD             55
#define KEY_SLASH              56
#define KEY_CAPSLOCK           57
#define KEY_F1                 58
#define KEY_F2                 59
#define KEY_F3                 60
#define KEY_F4                 61
#define KEY_F5                 62
#define KEY_F6                 63
#define KEY_F7                 64
#define KEY_F8                 65
#define KEY_F9                 66
#define KEY_F10                67
#define KEY_F11                68
#define KEY_F12                69
#define KEY_PRINTSCREEN        70
#define KEY_SCROLLLOCK         71
#define KEY_PAUSE              72
#define KEY_INSERT             73
#define KEY_HOME               74
#define KEY_PAGEUP             75
#define KEY_DELETEFORWARD      76
#define KEY_END                77
#define KEY_PAGEDOWN           78
#define KEY_RIGHT              79
#define KEY_LEFT               80
#define KEY_DOWN               81
#define KEY_UP                 82
#define KP_NUMLOCK             83
#define KP_DIVIDE              84
#define KP_MULTIPLY            85
#define KP_SUBTRACT            86
#define KP_ADD                 87
#define KP_ENTER               88
#define KP_1                   89
#define KP_2                   90
#define KP_3                   91
#define KP_4                   92
#define KP_5                   93
#define KP_6                   94
#define KP_7                   95
#define KP_8                   96
#define KP_9                   97
#define KP_0                   98
#define KP_POINT               99
#define KEY_NONUSBACKSLASH     100
#define KP_EQUALS              103
#define KEY_F13                104
#define KEY_F14                105
#define KEY_F15                106
#define KEY_F16                107
#define KEY_F17                108
#define KEY_F18                109
#define KEY_F19                110
#define KEY_F20                111
#define KEY_F21                112
#define KEY_F22                113
#define KEY_F23                114
#define KEY_F24                115
#define KEY_HELP               117
#define KEY_MENU               118

#define KEY_LEFTCTRL           (BV(0) << 8) // Keyboard Left Control 224
#define KEY_LEFTSHIFT          (BV(1) << 8) // Keyboard Left Shift   225
#define KEY_LEFTALT            (BV(2) << 8) // Keyboard Left Alt     226
#define KEY_LEFTMETA           (BV(3) << 8) // Keyboard Left GUI     227
#define KEY_RIGHTCTRL          (BV(4) << 8) // Keyboard Right Control 228
#define KEY_RIGHTSHIFT         (BV(5) << 8) // Keyboard Right Shift  229
#define KEY_RIGHTALT           (BV(6) << 8) // Keyboard Right Alt    230
#define KEY_RIGHTMETA          (BV(7) << 8) // Keyboard Right GUI    231

#define KEY_MEDIA_PLAYPAUSE     0xE800
#define KEY_MEDIA_STOPCD        0xE900
#define KEY_MEDIA_PREVIOUSSONG  0xEA00
#define KEY_MEDIA_NEXTSONG      0xEB00
#define KEY_MEDIA_EJECTCD       0xEC00
#define KEY_MEDIA_VOLUMEUP      0xED00
#define KEY_MEDIA_VOLUMEDOWN    0xEE00
#define KEY_MEDIA_MUTE          0xEF00
#define KEY_MEDIA_WWW           0xF000
#define KEY_MEDIA_BACK          0xF100
#define KEY_MEDIA_FORWARD       0xF200
#define KEY_MEDIA_STOP          0xF300
#define KEY_MEDIA_FIND          0xF400
#define KEY_MEDIA_SCROLLUP      0xF500
#define KEY_MEDIA_SCROLLDOWN    0xF600
#define KEY_MEDIA_EDIT          0xF700
#define KEY_MEDIA_SLEEP         0xF800
#define KEY_MEDIA_COFFEE        0xF900
#define KEY_MEDIA_REFRESH       0xFA00
#define KEY_MEDIA_CALC          0xFB00

#endif /* LAYOUTS_KEYCODES_H */
