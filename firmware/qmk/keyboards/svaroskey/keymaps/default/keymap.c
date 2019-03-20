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
  
/*  60% ISO LAYOUT
    ESC| 1  | 2  | 3  | 4  | 5  | 6  | 7  | 8  | 9  | 0  | '  | ¡  |BKS
    TAB| Q  | W  | E  | R  | T  | Y  | U  | I  | O  | P  | `  | +  |RET
    CAP| A  | S  | D  | F  | G  | H  | J  | K  | L  | Ñ  | ´  | Ç  |
    LSI| <  | Z  | X  | C  | V  | B  | N  | M  | ,  | .  | -  |   RSHIF
    LCT| WIN | ALT |  SPACE  | FN |  SPACE  | ALG | RCT  | LEF| DOW| RIG
*/

  [_NORMAL] = LAYOUT_sixty_iso(
    KC_GRV, KC_1,      KC_2,    KC_3,   KC_4,   KC_5,   KC_6,   KC_7,   KC_8,   KC_9,    KC_0,    KC_MINS, KC_EQL,        KC_BSPC,  \
    KC_TAB, KC_Q,      KC_W,    KC_E,   KC_R,   KC_T,   KC_Y,   KC_U,   KC_I,   KC_O,    KC_P,    KC_LBRC, KC_RBRC,       KC_ENTER, \
   KC_CAPS, KC_A,      KC_S,    KC_D,   KC_F,   KC_G,   KC_H,   KC_J,   KC_K,   KC_L,    KC_SCLN, KC_QUOT, KC_NONUS_HASH,           \
   KC_LSPO, KC_BSLASH, KC_Z,    KC_X,   KC_C,   KC_V,   KC_B,   KC_N,   KC_M,   KC_COMM, KC_DOT,  KC_SLSH,                KC_RSPC,  \
   KC_LCTL, KC_LGUI,   KC_LALT,      KC_SPC,       RESET,       KC_SPC,    KC_RALT,      KC_RCTL, KC_LEFT, KC_DOWN,       KC_RIGHT ),
};
