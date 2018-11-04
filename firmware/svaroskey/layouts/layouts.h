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
#ifndef SVAROSKEY_LAYOUTS_H
#define SVAROSKEY_LAYOUTS_H

#include "keyboard.h"

#include <cpu/types.h>

#include <kern/msg.h>

#include <drv/usbkbd.h>




#define KEY_TIME_SINGLEPRESS   50
#define KEY_TIME_LONGPRESS     80
#define KEY_TIME_LOOP          (KEY_TIME_SINGLEPRESS + \
                                  KEY_TIME_LONGPRESS)

#define MAX_PRESSED_KEY  10

typedef struct {
	Msg msg;
	size_t len;
	uint8_t status[MAX_PRESSED_KEY];
	uint8_t index[MAX_PRESSED_KEY];
} PressedKeyEvent;

#define NODE_TO_KEYEV(n)   (containerof(containerof((n), Msg, link), PressedKeyEvent, msg))
#define KEYEV_TO_NODE(ev)  (&((ev)->msg.link))

typedef struct
{
	uint16_t scancode;
	void *extra_level;
} KeyBinding;

extern KeyBinding keymap_layout[KEYBOARD_LAYOUT_NUM_KEYS];

int layout_usbEvent(UsbKbdEvent *event, KeyScanCtx *key_status);
void layout_init(void);

#endif /* SVAROSKEY_LAYOUTS_H */
