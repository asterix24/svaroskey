/**
 * \file
 * <!--
 * Copyright 2018 Daniele Basile <asterix24@gmail.com>
 * All Rights Reserved.
 * -->
 *
 * \brief Keyboard Map
 *
 * \author Daniele Basile <asterix24@gmail.com>
 */

#include "keyboard.h"
#include "keycodes.h"
#include "layouts.h"

#include "cfg/cfg_keymap.h"

#if CFG_KEYBOARD_LAYOUT == KEYBOARD_PETROSKEY_LAYOUT
	#include "map/petroskey.c"
#else
	#error No layout defined
#endif

