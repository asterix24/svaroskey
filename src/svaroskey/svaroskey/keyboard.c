#include "keyboard.h"
#include "grid.h"
#include "layout.h"

#include "hw/hw_keyboard.h"
#include "cfg/cfg_keyboard.h"

void keyboard_set_layout(struct Keyboard *kb, struct Layout *layout)
{
	kb->layout = layout;
}

void keyboard_set_grid(struct Keyboard *kb, struct Grid *grid)
{
	kb->grid = grid;
}

void keyboard_scan(struct Keyboard *kb)
{
	// TODO: implement me
}

void keyboard_init(struct Keyboard *kb)
{
	/* Low-level initialization */
	KEYBOARD_INIT();
}

