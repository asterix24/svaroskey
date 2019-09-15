/*
    Copyright 2019 Pietro Lorefice <pietro.lorefice@gmail.com>

    This program is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 2 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

#include QMK_KEYBOARD_H

// Define layer names
#define _NORMAL  0
#define _ALT1    1

enum isokey_keycodes {
  QMKBEST = SAFE_RANGE,
  EDA_MS, // Move selection
  EDA_AG, // Arrange group
  EDA_ZO, // Zoom out
  EDA_PM, // Poly Manager
  EDA_SO, // Selction out
  EDA_SL, // Selection line
};

const uint16_t keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
//   _______,          _______,    _______,  _______,  _______,    _______,   _______,    _______,  _______,    _______,   _______,  _______,   _______,    _______,  _______,   _______,   _______,   _______,   _______, _______,
//   _______, _______, _______,    _______,  _______,  _______,    _______,   _______,    _______,  _______,    _______,   _______,  _______,   _______,    _______,  _______,   _______,   _______,   _______,   _______, _______,
//   _______, _______, _______,    _______,  _______,  _______,    _______,   _______,    _______,  _______,    _______,   _______,  _______,   _______,    _______,  _______,   _______,   _______,   _______,   _______, _______,
//   _______, _______, _______,    _______,  _______,  _______,    _______,   _______,    _______,  _______,    _______,   _______,  _______,               _______,  _______,   _______,   _______,   _______,   _______, _______,
//   _______, _______, _______,    _______,  _______,  _______,    _______,   _______,    _______,  _______,    _______,   _______,  _______,                         _______,              _______,   _______,   _______,
//   _______,          _______,    _______,  _______,              _______,               _______,              _______,   _______,  _______,   _______,    _______,  _______,   _______,   _______,   _______

/*  105  LAYOUT
 | Esc   |     | F1  | F2  | F3  | F4  | F5  | F6  | F7  | F8  | F9  | F10 | F11 | F12       |    | PrtSc    | Scroll Lock | Pause Break |    | X4 Extra | X5 Extra | X6 Extra | X7 Extra |
 | ~ `   | ! 1 | @ 2 | # 3 | $ 4 | % 5 | ^ 6 | & 7 | * 8 | ( 9 | ) 0 | _ - | + = | Backspace |    | Insert   | Home        | PgUp        |    | Num Lock | /        | *        | -        |
 | Tab   | Q   | W   | E   | R   | T   | Y   | U   | I   | O   | P   | { [ | } ] |     Enter |    | Delete   | End         | PgDn        |    | 7 Home   | 8 ↑      | 9 PgUp   | +        |
 | Ctrl  | A   | S   | D   | F   | G   | H   | J   | K   | L   | : ; | \ ' | | \ |           |    | X1 Extra | X2 Extra    | X3 Extra    |    | 4 ←      | 5        | 6 →      |          |
 | Shift | Z   | X   | C   | V   | B   | N   | M   | < , | > . | ? / | XX  | Shift           |               | ↑           |                  | 1 End    | 2 ↓      | 3 PgDn   | Enter    |
 | Ctrl    |  Win  |Alt    | space     | space     | AltGr  | Win  |   Menu | Ctrl      | Fn |    | ←        | ↓           | →           |    | 0 Ins               | . Del    |          |
*/
    [_NORMAL] = LAYOUT_all (
        KC_ESC,           KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,   KC_F6,   KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_F11,  KC_F12,  KC_PSCR, KC_SLCK, KC_PAUS, KC_AUDIO_VOL_UP,  KC_AUDIO_VOL_DOWN,   KC_AUDIO_MUTE,   QMKBEST,   \
        KC_GRV,   KC_1,   KC_2,    KC_3,    KC_4,    KC_5,    KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    KC_MINS, KC_EQL,  KC_BSPC, KC_COPY, KC_CUT,  KC_PSTE, KC_NLCK, KC_PSLS, KC_PAST, KC_PMNS, \
        KC_TAB,   KC_Q,   KC_W,    KC_E,    KC_R,    KC_T,    KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,    KC_LBRC, KC_RBRC, KC_ENT,  KC_INS,  KC_HOME, KC_PGUP, KC_P7,   KC_P8,   KC_P9,   KC_PPLS, \
        MO(_ALT1),KC_A,   KC_S,    KC_D,    KC_F,    KC_G,    KC_H,    KC_J,    KC_K,    KC_L,    KC_SCLN, KC_QUOT, KC_BSLS,          KC_DEL,  KC_END,  KC_PGDN, KC_P4,   KC_P5,   KC_P6,   KC_PENT, \
        KC_LSFT,  KC_Z,   KC_X,    KC_C,    KC_V,    KC_B,    KC_N,    KC_M,    KC_COMM, KC_DOT,  KC_SLSH, KC_NO,   KC_RSFT,                   KC_UP,            KC_P1,   KC_P2,   KC_P3,            \
        KC_LCTL,        KC_LGUI,  KC_LALT,  KC_SPC,           KC_SPC,           KC_RALT,          KC_RGUI, KC_APP, KC_RCTL,  MO(_ALT1),   KC_LEFT, KC_DOWN, KC_RGHT, KC_P0,   KC_PDOT                    \
    ),
    [_ALT1] = LAYOUT_alt (
        _______,          _______,  _______,  _______,  _______,    _______,   _______,    _______,  _______,    _______,   _______,  _______,   _______,    _______,  _______,   _______,   _______,   _______,   _______, _______, \
        _______, _______, _______,  _______,  _______,  _______,    _______,   _______,    _______,  _______,    _______,   _______,  _______,   _______,    _______,  _______,   _______,   _______,   _______,   _______, _______, \
        _______, KC_DEL, _______,  _______,  _______,  _______,    _______,   _______,    _______,  _______,    _______,   _______,  _______,   _______,    _______,  _______,   _______,   _______,   _______,   _______, _______, \
        _______, EDA_MS,  EDA_AG,   EDA_ZO,  EDA_PM,  _______,    KC_LEFT,   KC_DOWN,    KC_UP,    KC_RGHT,    _______,   _______,  _______,               _______,  _______,   _______,   _______,   _______,   _______, _______, \
        _______, EDA_SO,  EDA_SL,  _______,  _______,  _______,    _______,   _______,    _______,  _______,    _______,   _______,  _______,                         _______,              _______,   _______,   _______,          \
        _______,          _______,  _______,  _______,              _______,               _______,              _______,   _______,  _______,   _______,    _______,  _______,   _______,   _______,   _______                      \
    ),
};

void keyboard_post_init_user(void) {
    // Customise these values to desired behaviour
    debug_enable=true;
    //debug_matrix=true;
    //debug_keyboard=true;
    ////debug_mouse=true;
}


bool process_record_user(uint16_t keycode, keyrecord_t *record) {
  // If console is enabled, it will print the matrix position and status of each key pressed
#ifdef CONSOLE_ENABLE
    uprintf("KL: kc: %u, col: %u, row: %u, pressed: %u\n", keycode, record->event.key.col, record->event.key.row, record->event.pressed);
#endif
    switch (keycode) {
        case EDA_MS: // Move selection
            if (record->event.pressed) {
                // when keycode QMKBEST is pressed
                SEND_STRING("ms");
            }
        break;
        case EDA_AG: // Arrange group
            if (record->event.pressed) {
                // when keycode QMKBEST is pressed
                SEND_STRING("ag");
            }
        break;
        case EDA_ZO: // Zoom out
            if (record->event.pressed) {
                // when keycode QMKBEST is pressed
                SEND_STRING("zo");
            }
        break;
        case EDA_PM: // Poly Manager
            if (record->event.pressed) {
                // when keycode QMKBEST is pressed
                SEND_STRING("pm");
            }
        break;
        case EDA_SO: // Selction out
            if (record->event.pressed) {
                // when keycode QMKBEST is pressed
                SEND_STRING("so");
            }
        break;
        case EDA_SL: // Selection line
            if (record->event.pressed) {
                // when keycode QMKBEST is pressed
                SEND_STRING("sl");
            }
        break;
    }
    return true;
}

