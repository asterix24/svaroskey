/*
Copyright 2015 Jun Wako <wakojun@gmail.com>

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

#pragma once

/* USB Device descriptor parameter */
#define VENDOR_ID       0xDEAD
#define PRODUCT_ID      0xBEEF
#define DEVICE_VER      0x0001

#define MANUFACTURER    asterix
#define PRODUCT         IsoK
#define SERIAL_NUMBER   001
#define DESCRIPTION     QMK keyboard firmware with ChibiOS

/* Key matrix size */
#define MATRIX_ROWS 6
#define MATRIX_COLS 21
#define DIODE_DIRECTION COL2ROW

#define MATRIX_ROW_PINS { C0, C1, C2, C3, C4, C5 }
#define MATRIX_COL_PINS { B0, B1, B3, B4, B5, B6, B7, B8, B9, B12, B13, B14, B15, A0, A1, A4, A5, A6, A7, A8, A9 }

// Iso fix for Space Cadet, comment for ANSI layouts
#define LSPO_KEY KC_8
#define RSPC_KEY KC_9

/* Define if matrix has ghost */
// #define MATRIX_HAS_GHOST

/* Set 0 if debouncing isn't needed */
#define DEBOUNCE    1

/* Mechanical locking support. Use KC_LCAP, KC_LNUM or KC_LSCR instead in keymap */
// #define LOCKING_SUPPORT_ENABLE
/* Locking resynchronize hack */
// #define LOCKING_RESYNC_ENABLE

/* Backlighting include */
// #define BACKLIGHT_PIN 19
// #define BACKLIGHT_LEVELS 5
// #define BACKLIGHT_BREATHING
// #define BREATHING_PERIOD 6

/*
 * Feature disable options
 *  These options are also useful to firmware size reduction.
 */

/* disable debug print */
// #define NO_DEBUG

/* disable print */
// #define NO_PRINT

/* disable action features */
// #define NO_ACTION_LAYER
// #define NO_ACTION_TAPPING
// #define NO_ACTION_ONESHOT
// #define NO_ACTION_MACRO
// #define NO_ACTION_FUNCTION
