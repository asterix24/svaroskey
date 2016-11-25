#include "grid.h"

#include "hw/hw_keyboard.h"

bool grid_scan_all(struct Grid *grid)
{
	bool any_active = false;
	int i;

	for (i = 0; i < grid->num_cells; i++)
		any_active = any_active || cell_read_state(&grid->cells[i]);

	return any_active;
}

bool cell_read_state(struct Cell *cell)
{
	return (cell->is_active = KEYBOARD_READ_CELL(cell));
}

// #define KPA 0
// #define KPB 1
// #define KPC 2
// #define KPD 3
// 
// KeyMapping keymap_mapping[] = {
// #if (CONFIG_MAPPING_REVISION == 0)
// 	/* #0 - #11 */
// 	{ KPB, 0,  KPC, 0  }, { KPB, 1,  KPC, 0  }, { KPB, 3,  KPC, 0  },
// 	{ KPB, 4,  KPC, 0  }, { KPB, 5,  KPC, 0  }, { KPB, 6,  KPC, 0  },
// 	{ KPB, 7,  KPC, 0  }, { KPB, 8,  KPC, 0  }, { KPB, 9,  KPC, 0  },
// 	{ KPB, 12, KPC, 0  }, { KPB, 13, KPC, 0  }, { KPB, 14, KPC, 0  },
// 
// 	/* #12 - #23 */
// 	{ KPB, 0,  KPC, 1  }, { KPB, 1,  KPC, 1  }, { KPB, 3,  KPC, 1  },
// 	{ KPB, 4,  KPC, 1  }, { KPB, 5,  KPC, 1  }, { KPB, 6,  KPC, 1  },
// 	{ KPB, 7,  KPC, 1  }, { KPB, 8,  KPC, 1  }, { KPB, 9,  KPC, 1  },
// 	{ KPB, 12, KPC, 1  }, { KPB, 13, KPC, 1  }, { KPB, 14, KPC, 1  },
// 
// 	/* #24 - #35 */
// 	{ KPB, 0,  KPC, 2  }, { KPB, 1,  KPC, 2  }, { KPB, 3,  KPC, 2  },
// 	{ KPB, 4,  KPC, 2  }, { KPB, 5,  KPC, 2  }, { KPB, 6,  KPC, 2  },
// 	{ KPB, 7,  KPC, 2  }, { KPB, 8,  KPC, 2  }, { KPB, 9,  KPC, 2  },
// 	{ KPB, 12, KPC, 2  }, { KPB, 13, KPC, 2  }, { KPB, 14, KPC, 2  },
// 
// 	/* #36 - #47 */
// 	{ KPB, 0,  KPC, 3  }, { KPB, 1,  KPC, 3  }, { KPB, 3,  KPC, 3  },
// 	{ KPB, 4,  KPC, 3  }, { KPB, 5,  KPC, 3  }, { KPB, 6,  KPC, 3  },
// 	{ KPB, 7,  KPC, 3  }, { KPB, 8,  KPC, 3  }, { KPB, 9,  KPC, 3  },
// 	{ KPB, 12, KPC, 3  }, { KPB, 13, KPC, 3  }, { KPB, 14, KPC, 3  },
// 
// 	/* #48 - #59 */
// 	{ KPB, 0,  KPC, 4  }, { KPB, 1,  KPC, 4  }, { KPB, 3,  KPC, 4  },
// 	{ KPB, 4,  KPC, 4  }, { KPB, 5,  KPC, 4  }, { KPB, 6,  KPC, 4  },
// 	{ KPB, 7,  KPC, 4  }, { KPB, 8,  KPC, 4  }, { KPB, 9,  KPC, 4  },
// 	{ KPB, 12, KPC, 4  }, { KPB, 13, KPC, 4  }, { KPB, 14, KPC, 4  },
// 
// 	/* #60 - #71 */
// 	{ KPB, 0,  KPC, 5  }, { KPB, 1,  KPC, 5  }, { KPB, 3,  KPC, 5  },
// 	{ KPB, 4,  KPC, 5  }, { KPB, 5,  KPC, 5  }, { KPB, 6,  KPC, 5  },
// 	{ KPB, 7,  KPC, 5  }, { KPB, 8,  KPC, 5  }, { KPB, 9,  KPC, 5  },
// 	{ KPB, 12, KPC, 5  }, { KPB, 13, KPC, 5  }, { KPB, 14, KPC, 5  },
// #elif (CONFIG_MAPPING_REVISION == 1)
// 	/* Row 0 */
// 	{ KPC, 0,  KPB, 0  }, { KPC, 0,  KPB, 3  }, { KPC, 0,  KPB, 4  },
// 	{ KPC, 0,  KPB, 5  }, { KPC, 0,  KPB, 6  }, { KPC, 0,  KPB, 7  },
// 	{ KPC, 0,  KPB, 8  }, { KPC, 0,  KPB, 9  }, { KPC, 0,  KPB, 12 },
// 
// 	/* Row 1 */
// 	{ KPC, 1,  KPB, 0  }, { KPC, 1,  KPB, 1  }, { KPC, 1,  KPB, 3  },
// 	{ KPC, 1,  KPB, 4  }, { KPC, 1,  KPB, 5  }, { KPC, 1,  KPB, 6  },
// 	{ KPC, 1,  KPB, 7  }, { KPC, 1,  KPB, 8  }, { KPC, 1,  KPB, 9  },
// 	{ KPC, 1,  KPB, 12 }, { KPC, 1,  KPB, 13 },
// 
// 	/* Row 2 */
// 	{ KPC, 2,  KPB, 0  }, { KPC, 2,  KPB, 3  }, { KPC, 2,  KPB, 4  },
// 	{ KPC, 2,  KPB, 5  }, { KPC, 2,  KPB, 6  }, { KPC, 2,  KPB, 7  },
// 	{ KPC, 2,  KPB, 8  }, { KPC, 2,  KPB, 9  }, { KPC, 2,  KPB, 12 },
// 	{ KPC, 2,  KPB, 13 },
// 
// 	/* Row 3 */
// 	{ KPC, 3,  KPB, 0  }, { KPC, 3,  KPB, 3  }, { KPC, 3,  KPB, 4  },
// 	{ KPC, 3,  KPB, 5  }, { KPC, 3,  KPB, 6  }, { KPC, 3,  KPB, 7  },
// 	{ KPC, 3,  KPB, 8  }, { KPC, 3,  KPB, 9  }, { KPC, 3,  KPB, 12 },
// 	{ KPC, 3,  KPB, 13 },
// 
// 	/* Row 4 */
// 	{ KPC, 4,  KPB, 0  }, { KPC, 4,  KPB, 3  }, { KPC, 4,  KPB, 4  },
// 	{ KPC, 4,  KPB, 5  }, { KPC, 4,  KPB, 6  }, { KPC, 4,  KPB, 7  },
// 	{ KPC, 4,  KPB, 8  }, { KPC, 4,  KPB, 9  }, { KPC, 4,  KPB, 12 },
// 	{ KPC, 4,  KPB, 13 },
// 
// 	/* Row 5 */
// 	{ KPC, 5,  KPB, 0  }, { KPC, 5,  KPB, 1  }, { KPC, 5,  KPB, 3  },
// 	{ KPC, 5,  KPB, 7  }, { KPC, 5,  KPB, 13 },
// 
// 	/* Row 6 */
// 	{ KPC, 6,  KPB, 0  }, { KPC, 6,  KPB, 1  }, { KPC, 6,  KPB, 3  },
// 	{ KPC, 6,  KPB, 4  }, { KPC, 6,  KPB, 5  }, { KPC, 6,  KPB, 6  },
// 	{ KPC, 6,  KPB, 7  },
// 
// 	/* Row 7 */
// 	{ KPC, 7,  KPB, 0  }, { KPC, 7,  KPB, 1  }, { KPC, 7,  KPB, 4  },
// 	{ KPC, 7,  KPB, 5  }, { KPC, 7,  KPB, 6  }, { KPC, 7,  KPB, 7  },
// 	{ KPC, 7,  KPB, 8  }, { KPC, 7,  KPB, 9  }, { KPC, 7,  KPB, 12 },
// 	{ KPC, 7,  KPB, 13 },
// 
// 	/* Row 8 */
// 	{ KPC, 8,  KPB, 0  }, { KPC, 8,  KPB, 1  }, { KPC, 8,  KPB, 3  },
// 	{ KPC, 8,  KPB, 5  }, { KPC, 8,  KPB, 6  }, { KPC, 8,  KPB, 7  },
// 	{ KPC, 8,  KPB, 8  }, { KPC, 8,  KPB, 9  }, { KPC, 8,  KPB, 12 },
// 
// 	/* Row 9 */
// 	{ KPC, 9,  KPB, 0  }, { KPC, 9,  KPB, 1  }, { KPC, 9,  KPB, 3  },
// 	{ KPC, 9,  KPB, 4  }, { KPC, 9,  KPB, 6  }, { KPC, 9,  KPB, 8  },
// 	{ KPC, 9,  KPB, 9  }, { KPC, 9,  KPB, 12 }, { KPC, 9,  KPB, 13 },
// 
// 	/* Row 10 */
// 	{ KPC, 10, KPB, 0  }, { KPC, 10, KPB, 1  }, { KPC, 10, KPB, 4  },
// 	{ KPC, 10, KPB, 6  }, { KPC, 10, KPB, 8  }, { KPC, 10, KPB, 9  },
// 	{ KPC, 10, KPB, 12 },
// 
// 	/* Row 11 */
// 	{ KPC, 12, KPB, 0  }, { KPC, 12, KPB, 3  }, { KPC, 12, KPB, 4  },
// 	{ KPC, 12, KPB, 5  }, { KPC, 12, KPB, 6  }, { KPC, 12, KPB, 7  },
// 	{ KPC, 12, KPB, 8  }, { KPC, 12, KPB, 12 }, { KPC, 12, KPB, 13 },
// #endif
// };
