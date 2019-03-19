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

#include "ch.h"
#include "hal.h"

#include "print.h"
#include "debug.h"
#include "util.h"
#include "matrix.h"
#include "wait.h"

/* Matrix state (1:on, 0:off) */
static matrix_row_t matrix[MATRIX_ROWS];

inline uint8_t matrix_rows(void) {
  return MATRIX_ROWS;
}

inline uint8_t matrix_cols(void) {
  return MATRIX_COLS;
}

__attribute__ ((weak)) void matrix_init_kb(void)   { matrix_init_user(); }
__attribute__ ((weak)) void matrix_scan_kb(void)   { matrix_scan_user(); }
__attribute__ ((weak)) void matrix_init_user(void) { }
__attribute__ ((weak)) void matrix_scan_user(void) { }

void matrix_init(void) {
  /* TODO: implement me */
}

uint8_t matrix_scan(void) {
  /* TODO: implement me */
  return 1;
}

inline bool matrix_is_on(uint8_t row, uint8_t col){
  return (matrix[row] & ((matrix_row_t)1<<col));
}

inline matrix_row_t matrix_get_row(uint8_t row){
  return matrix[row];
}

void matrix_print(void) {
  /* TODO: implement me */
}
