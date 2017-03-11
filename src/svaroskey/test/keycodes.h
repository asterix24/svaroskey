#ifndef SVAROSKEY_KEYCODES_H
#define SVAROSKEY_KEYCODES_H

/** @file */

#include "stdint.h"

#define LAYOUT_SIZE 106

typedef uint16_t keycode_t;

/**
 * @brief Actually used keycodes in the keyboard.
 *
 * This array contains all the keycodes that can actually be accessed and used
 * by the user via callbacks. The number of keycodes that the user will be able
 * to access depends on the type of the callback parameters (uint8_t for
 * example will only allow for 256 used characters - or less if this array's
 * length is less).
 *
 * Any character that one wants to be able to use can be inserted in this array
 * (be it ASCII, Unicode, whatever).
 */
extern keycode_t keycodes[];
// NOTE: This can't be a define since it is defined in the .c
extern uint8_t keycodes_count;

/**
 * @name Keycodes definitions.
 *
 * These defines are used in order to define each useful character's keycode
 * (as in, ASCII/unicode/whatever).
 *
 * These defines are not limited in number, as we can preemptively define all
 * possible characters we may want to use ever.
 *
 * After defining them, one can then use these to populate the keycodes[] array
 * below in a readable manner.
 *
 * @{
 */

#define   KEY_A                 4
#define   KEY_B                 5
#define   KEY_C                 6
#define   KEY_D                 7
#define   KEY_E                 8
#define   KEY_F                 9
#define   KEY_G                 10
#define   KEY_H                 11
#define   KEY_I                 12
#define   KEY_J                 13
#define   KEY_K                 14
#define   KEY_L                 15
#define   KEY_M                 16
#define   KEY_N                 17
#define   KEY_O                 18
#define   KEY_P                 19
#define   KEY_Q                 20
#define   KEY_R                 21
#define   KEY_S                 22
#define   KEY_T                 23
#define   KEY_U                 24
#define   KEY_V                 25
#define   KEY_W                 26
#define   KEY_X                 27
#define   KEY_Y                 28
#define   KEY_Z                 29
#define   KEY_1                 30
#define   KEY_2                 31
#define   KEY_3                 32
#define   KEY_4                 33
#define   KEY_5                 34
#define   KEY_6                 35
#define   KEY_7                 36
#define   KEY_8                 37
#define   KEY_9                 38
#define   KEY_0                 39
#define   KEY_ENTER             40
#define   KEY_ESCAPE            41
#define   KEY_DELETE            42
#define   KEY_TAB               43
#define   KEY_SPACE             44
#define   KEY_MINUS             45
#define   KEY_EQUALS            46
#define   KEY_LEFTBRACKET       47
#define   KEY_RIGHTBRACKET      48
#define   KEY_BACKSLASH         49
#define   KEY_SEMICOLON         51
#define   KEY_QUOTE             52
#define   KEY_GRAVE             53
#define   KEY_COMMA             54
#define   KEY_PERIOD            55
#define   KEY_SLASH             56
#define   KEY_CAPSLOCK          57
#define   KEY_F1                58
#define   KEY_F2                59
#define   KEY_F3                60
#define   KEY_F4                61
#define   KEY_F5                62
#define   KEY_F6                63
#define   KEY_F7                64
#define   KEY_F8                65
#define   KEY_F9                66
#define   KEY_F10               67
#define   KEY_F11               68
#define   KEY_F12               69
#define   KEY_PRINTSCREEN       70
#define   KEY_SCROLLLOCK        71
#define   KEY_PAUSE             72
#define   KEY_INSERT            73
#define   KEY_HOME              74
#define   KEY_PAGEUP            75
#define   KEY_DELETEFORWARD     76
#define   KEY_END               77
#define   KEY_PAGEDOWN          78
#define   KEY_RIGHT             79
#define   KEY_LEFT              80
#define   KEY_DOWN              81
#define   KEY_UP                82
#define   KP_NUMLOCK            83
#define   KP_DIVIDE             84
#define   KP_MULTIPLY           85
#define   KP_SUBTRACT           86
#define   KP_ADD                87
#define   KP_ENTER              88
#define   KP_1                  89
#define   KP_2                  90
#define   KP_3                  91
#define   KP_4                  92
#define   KP_5                  93
#define   KP_6                  94
#define   KP_7                  95
#define   KP_8                  96
#define   KP_9                  97
#define   KP_0                  98
#define   KP_POINT              99
#define   KEY_NONUSBACKSLASH    100
#define   KP_EQUALS             103
#define   KEY_F13               104
#define   KEY_F14               105
#define   KEY_F15               106
#define   KEY_F16               107
#define   KEY_F17               108
#define   KEY_F18               109
#define   KEY_F19               110
#define   KEY_F20               111
#define   KEY_F21               112
#define   KEY_F22               113
#define   KEY_F23               114
#define   KEY_F24               115
#define   KEY_HELP              117
#define   KEY_MENU              118
#define   KEY_LEFTCONTROL       ((1 << 0) << 8) // 224
#define   KEY_LEFTSHIFT         ((1 << 1) << 8) // 225
#define   KEY_LEFTALT           ((1 << 2) << 8) // 226
#define   KEY_LEFTGUI           ((1 << 3) << 8) // 227
#define   KEY_RIGHTCONTROL      ((1 << 4) << 8) // 228
#define   KEY_RIGHTSHIFT        ((1 << 5) << 8) // 229
#define   KEY_RIGHTALT          ((1 << 6) << 8) // 230
#define   KEY_RIGHTGUI          ((1 << 7) << 8) // 231

/// @}

/**
 * @name Keycodes IDs definitions.
 *
 * These defines are used solely in order to create legible code that accesses
 * the keycodes[] array.
 *
 * They simply report which key is at which index in the keycodes[] array.
 *
 * @{
 */

#define   ID_KEY_A              0
#define   ID_KEY_B              1
#define   ID_KEY_C              2
#define   ID_KEY_D              3
#define   ID_KEY_E              4
#define   ID_KEY_F              5
#define   ID_KEY_G              6
#define   ID_KEY_H              7
#define   ID_KEY_I              8
#define   ID_KEY_J              9
#define   ID_KEY_K              10
#define   ID_KEY_L              11
#define   ID_KEY_M              12
#define   ID_KEY_N              13
#define   ID_KEY_O              14
#define   ID_KEY_P              15
#define   ID_KEY_Q              16
#define   ID_KEY_R              17
#define   ID_KEY_S              18
#define   ID_KEY_T              19
#define   ID_KEY_U              20
#define   ID_KEY_V              21
#define   ID_KEY_W              22
#define   ID_KEY_X              23
#define   ID_KEY_Y              24
#define   ID_KEY_Z              25
#define   ID_KEY_1              26
#define   ID_KEY_2              27
#define   ID_KEY_3              28
#define   ID_KEY_4              29
#define   ID_KEY_5              30
#define   ID_KEY_6              31
#define   ID_KEY_7              32
#define   ID_KEY_8              33
#define   ID_KEY_9              34
#define   ID_KEY_0              35
#define   ID_KEY_ENTER          36
#define   ID_KEY_ESCAPE         37
#define   ID_KEY_DELETE         38
#define   ID_KEY_TAB            39
#define   ID_KEY_SPACE          40
#define   ID_KEY_MINUS          41
#define   ID_KEY_EQUALS         42
#define   ID_KEY_LEFTBRACKET    43
#define   ID_KEY_RIGHTBRACKET   44
#define   ID_KEY_BACKSLASH      45
#define   ID_KEY_SEMICOLON      46
#define   ID_KEY_QUOTE          47
#define   ID_KEY_GRAVE          48
#define   ID_KEY_COMMA          49
#define   ID_KEY_PERIOD         50
#define   ID_KEY_SLASH          51
#define   ID_KEY_CAPSLOCK       52
#define   ID_KEY_F1             53
#define   ID_KEY_F2             54
#define   ID_KEY_F3             55
#define   ID_KEY_F4             56
#define   ID_KEY_F5             57
#define   ID_KEY_F6             58
#define   ID_KEY_F7             59
#define   ID_KEY_F8             60
#define   ID_KEY_F9             61
#define   ID_KEY_F10            62
#define   ID_KEY_F11            63
#define   ID_KEY_F12            64
#define   ID_KEY_PRINTSCREEN    65
#define   ID_KEY_SCROLLLOCK     66
#define   ID_KEY_PAUSE          67
#define   ID_KEY_INSERT         68
#define   ID_KEY_HOME           69
#define   ID_KEY_PAGEUP         70
#define   ID_KEY_DELETEFORWARD  71
#define   ID_KEY_END            72
#define   ID_KEY_PAGEDOWN       73
#define   ID_KEY_RIGHT          74
#define   ID_KEY_LEFT           75
#define   ID_KEY_DOWN           76
#define   ID_KEY_UP             77
#define   ID_KP_NUMLOCK         78
#define   ID_KP_DIVIDE          79
#define   ID_KP_MULTIPLY        80
#define   ID_KP_SUBTRACT        81
#define   ID_KP_ADD             82
#define   ID_KP_ENTER           83
#define   ID_KP_1               84
#define   ID_KP_2               85
#define   ID_KP_3               86
#define   ID_KP_4               87
#define   ID_KP_5               88
#define   ID_KP_6               89
#define   ID_KP_7               90
#define   ID_KP_8               91
#define   ID_KP_9               92
#define   ID_KP_0               93
#define   ID_KP_POINT           94
#define   ID_KEY_NONUSBACKSLASH 95
#define   ID_KP_EQUALS          96
#define   ID_KEY_F13            97
#define   ID_KEY_F14            98
#define   ID_KEY_F15            99
#define   ID_KEY_F16            100
#define   ID_KEY_F17            101
#define   ID_KEY_F18            102
#define   ID_KEY_F19            103
#define   ID_KEY_F20            104
#define   ID_KEY_F21            105
#define   ID_KEY_F22            106
#define   ID_KEY_F23            107
#define   ID_KEY_F24            108
#define   ID_KEY_HELP           109
#define   ID_KEY_MENU           110
#define   ID_KEY_LEFTCONTROL    111
#define   ID_KEY_LEFTSHIFT      112
#define   ID_KEY_LEFTALT        113
#define   ID_KEY_LEFTGUI        114
#define   ID_KEY_RIGHTCONTROL   115
#define   ID_KEY_RIGHTSHIFT     116
#define   ID_KEY_RIGHTALT       117
#define   ID_KEY_RIGHTGUI       118

/// @}

#endif /* SVAROSKEY_KEYCODES_H */
