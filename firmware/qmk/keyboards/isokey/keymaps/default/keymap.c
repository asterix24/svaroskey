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
#define _NORMAL 0

const uint16_t keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

/*  105  LAYOUT
 | Esc   |     | F1  | F2  | F3  | F4  | F5  | F6  | F7  | F8  | F9  | F10 | F11 | F12       |    | PrtSc    | Scroll Lock | Pause Break |    | X4 Extra | X5 Extra | X6 Extra | X7 Extra |
 | ~ `   | ! 1 | @ 2 | # 3 | $ 4 | % 5 | ^ 6 | & 7 | * 8 | ( 9 | ) 0 | _ - | + = | Backspace |    | Insert   | Home        | PgUp        |    | Num Lock | /        | *        | -        |
 | Tab   | Q   | W   | E   | R   | T   | Y   | U   | I   | O   | P   | { [ | } ] |     Enter |    | Delete   | End         | PgDn        |    | 7 Home   | 8 ↑      | 9 PgUp   | +        |
 | Ctrl  | A   | S   | D   | F   | G   | H   | J   | K   | L   | : ; | \ ' | | \ |           |    | X1 Extra | X2 Extra    | X3 Extra    |    | 4 ←      | 5        | 6 →      |          |
 | Shift | Z   | X   | C   | V   | B   | N   | M   | < , | > . | ? / | XX  | Shift           |               | ↑           |                  | 1 End    | 2 ↓      | 3 PgDn   | Enter    |
 | Ctrl    |  Win  |Alt    | space     | space     | AltGr  | Win  |   Menu | Ctrl      | Fn |    | ←        | ↓           | →           |    | 0 Ins               | . Del    |          |
*/

    [_NORMAL] = LAYOUT_all (
        KC_ESC,           KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,   KC_F6,   KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_F11,  KC_F12,  KC_PSCR, KC_SLCK, KC_PAUS, KC_NO,   KC_NO,   KC_NO,   KC_NO,   \
        KC_GRV,  KC_1,    KC_2,    KC_3,    KC_4,    KC_5,    KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    KC_MINS, KC_EQL,  KC_BSPC, KC_INS,  KC_HOME, KC_PGUP, KC_NLCK, KC_PSLS, KC_PAST, KC_PMNS, \
        KC_TAB,  KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,    KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,    KC_LBRC, KC_RBRC, KC_ENT,  KC_DEL,  KC_END,  KC_PGDN, KC_P7,   KC_P8,   KC_P9,   KC_PPLS, \
        KC_LCTL, KC_A,    KC_S,    KC_D,    KC_F,    KC_G,    KC_H,    KC_J,    KC_K,    KC_L,    KC_SCLN, KC_QUOT, KC_BSLS,          KC_NO,   KC_NO,   KC_NO,   KC_P4,   KC_P5,   KC_P6,            \
        KC_LSFT, KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,    KC_N,    KC_M,    KC_COMM, KC_DOT,  KC_SLSH, KC_NO,   KC_RSFT,                   KC_UP,            KC_P1,   KC_P2,   KC_P3,   KC_PENT, \
        KC_LCTL,   KC_LGUI,    KC_LALT,     KC_SPC,           KC_SPC,           KC_RALT,     KC_RGUI,    KC_APP,   KC_RCTL,  KC_NO,   KC_LEFT, KC_DOWN, KC_RGHT, KC_P0,   KC_PDOT                    \
    ),
};
