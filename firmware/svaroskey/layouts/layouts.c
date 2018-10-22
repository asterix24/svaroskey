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

#include <cfg/debug.h>
#define LOG_LEVEL  3
#define LOG_FORMAT 0

#include <cfg/log.h>

#include <drv/usbkbd.h>

#if CFG_KEYBOARD_LAYOUT == KEYBOARD_PETROSKEY_LAYOUT
	#include "map/petroskey.c"
#else
	#error No layout defined
#endif

int layout_usbEvent(UsbKbdEvent *event, PressedKeyEvent *key_ev)
{
	ASSERT(event);

	if(!key_ev)
		return -1;

	kputs("USB [ ");
	size_t index = 0;
	for (size_t i =  0; i < key_ev->len; i++)
	{
		uint16_t key_id = key_ev->key_index[i];
		if (key_id > KEYBOARD_LAYOUT_NUM_KEYS)
			return -2;

		uint16_t scancode = keymap_layout[key_id].scancode;


		// Check if the key is a modifier key
		if (scancode > 0xff)
		{
			event->mods |= (scancode >> 8);
			kprintf("{%0x} ", event->mods);
		}
		// Otherwise see if it is different from before
		else if (index < USBKBD_MAX_SCANCODE_NUM)
		{
			event->codes[index] = (0xff & scancode);
			kprintf(" %0x ", event->codes[index]);
			index++;
		}
	}
	kputs(" ]\n");

	return 0;
}


void layout_init(void)
{

}

