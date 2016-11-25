#ifndef SVAROSKEY_MAPPING_H
#define SVAROSKEY_MAPPING_H

#include <stdint.h>
#include <stdbool.h>

#include "cfg/cfg_keyboard.h"

/* Forward decl */
struct Key;

struct Pin {
	uint8_t		port, pin;
};

struct Cell {
	struct Key	*key;
	struct Pin	row, col;
	bool		is_active;
};

struct Grid {
	struct Cell	*cells;
	int		num_cells;
};

bool grid_scan_all(struct Grid *grid);
bool cell_read_state(struct Cell *cell);

#endif /* SVAROSKEY_MAPPING_H */
