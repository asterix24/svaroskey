#ifndef SVAROSKEY_LAYOUTS_H
#define SVAROSKEY_LAYOUTS_H

#include "stdint.h"

#define LAYOUT_SIZE 106

typedef uint16_t scancode_t;

// FIXME: This file and its .c will need to be removed.
//
// This is going to be replaced by the custom callback structures, even for
// default mappings. Only the LAYOUT_SIZE macro and scancode_t will need to be
// defined somewhere else.
//
// Here it is needed in order to interface with SDL.

scancode_t tmp_sdl_conversion(unsigned char id);

#endif /* SVAROSKEY_LAYOUTS_H */
