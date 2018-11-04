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

int layout_usbEvent(UsbKbdEvent *event, KeyScanCtx *key_status)
{
	ASSERT(event);

	if(!key_status)
		return -1;

	kputs("USB [ ");
	size_t index = 0;
	for (size_t i =  0; i < MAX_KEY_STATUS; i++)
	{

		uint16_t key_id = key_status->index[i];
		if (key_id > KEYBOARD_LAYOUT_NUM_KEYS)
		{
			//key_status->status[i] = 0;
			//key_status->index[i] = 0xff;
			//kprintf("Invalid key id {%d} idx[%d]\n", key_id, i);
			continue;
		}

		uint16_t scancode;
		if (key_status->status[i] & KEY_PRESSED)
		{
			// key used, reset changed flag.
			scancode = keymap_layout[key_id].scancode;
		}
		else
		{
			scancode = 0;
			key_status->index[i] = 0xff;
			key_status->status[i] = 0;
		}

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

