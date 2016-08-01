#ifndef SVAROSKEY_KEYMAP_H
#define SVAROSKEY_KEYMAP_H

#include <cpu/types.h>

typedef struct
{
	char mod, scan;
} keystate_t;

keystate_t * keymap_get_next(void);
void keymap_scan(void);
void keymap_init(void);

#endif
