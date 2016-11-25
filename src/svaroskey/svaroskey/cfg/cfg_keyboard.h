#ifndef CFG_KEYBOARD_H
#define CFG_KEYBOARD_H

#include <stdlib.h>

#define CREATE_LAYOUT(name)	struct Key _layout_keys_##name[] = {
#define KEY_DEF(id,def,fun)	{ id, NULL, def, fun },
#define KEY_CODES(...)		{ KEY_##__VA_ARGS__ }
#define KEY_FUNCS(...)		{ __VA_ARGS__ }
#define END_LAYOUT(name)	}; \
				struct Layout _layout_##name = { \
					.keys = _layout_keys_##name , \
					.num_keys = \
						sizeof(_layout_keys_##name) / \
						sizeof(struct Key), \
				};
#define EXPORT_LAYOUT(name)	extern struct Layout _layout_##name ;


#define CREATE_GRID(name)	struct Cell _grid_cells_##name[] = {
#define CELL_DEF(R, r, C, c, k)	{ k, { R, r }, { C, c }, false },
#define CELL_KEY(key)		(struct Key *)key
#define END_GRID(name)		}; \
				struct Grid _grid_##name = { \
					.cells = _grid_cells_##name , \
					.num_cells = \
						sizeof(_grid_cells_##name) / \
						sizeof(struct Cell), \
				};
#define EXPORT_GRID(name)	extern struct Grid _grid_##name ;

#define KPA 0
#define KPB 1
#define KPC 2
#define KPD 3

#ifdef SVAROSKEY
#include "cfg/cfg_keyboard_svaroskey.h"
#else
#include "cfg/cfg_keyboard_petroskey.h"
#endif

#endif /* CFG_KEYBOARD_H */
