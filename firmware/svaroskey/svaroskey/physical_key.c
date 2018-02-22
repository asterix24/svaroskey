#include "physical_key.h"

#include "definitions.h"

#include "hw/hw_keymap.h"

#if !defined CONFIG_MAPPING_REVISION
#error CONFIG_MAPPING_REVISION is not defined.
#elif (CONFIG_MAPPING_REVISION > CONFIG_MAPPING_LATEST_REVISION)
#error CONFIG_MAPPING_REVISION is not valid.
#endif

#define KPA KEYBOARD_PORT_A
#define KPB KEYBOARD_PORT_B
#define KPC KEYBOARD_PORT_C
#define KPD KEYBOARD_PORT_D

struct PhysicalKey
{
	uint8_t row_port;
	uint8_t row_pin;
	uint8_t col_port;
	uint8_t col_pin;
};

struct PressedPhysicalKeys
{
	key_id_t pressed_keys[LAYOUT_SIZE];
	uint8_t num_pressed_keys;
};

static struct PressedPhysicalKeys physical_keys;

struct PhysicalKey keyboard_keys[LAYOUT_SIZE] = {
#if (CONFIG_MAPPING_REVISION == 0)
	/* #0 - #11 */
	{ KPB, 0,  KPC, 0  }, { KPB, 1,  KPC, 0  }, { KPB, 3,  KPC, 0  },
	{ KPB, 4,  KPC, 0  }, { KPB, 5,  KPC, 0  }, { KPB, 6,  KPC, 0  },
	{ KPB, 7,  KPC, 0  }, { KPB, 8,  KPC, 0  }, { KPB, 9,  KPC, 0  },
	{ KPB, 12, KPC, 0  }, { KPB, 13, KPC, 0  }, { KPB, 14, KPC, 0  },

	/* #12 - #23 */
	{ KPB, 0,  KPC, 1  }, { KPB, 1,  KPC, 1  }, { KPB, 3,  KPC, 1  },
	{ KPB, 4,  KPC, 1  }, { KPB, 5,  KPC, 1  }, { KPB, 6,  KPC, 1  },
	{ KPB, 7,  KPC, 1  }, { KPB, 8,  KPC, 1  }, { KPB, 9,  KPC, 1  },
	{ KPB, 12, KPC, 1  }, { KPB, 13, KPC, 1  }, { KPB, 14, KPC, 1  },

	/* #24 - #35 */
	{ KPB, 0,  KPC, 2  }, { KPB, 1,  KPC, 2  }, { KPB, 3,  KPC, 2  },
	{ KPB, 4,  KPC, 2  }, { KPB, 5,  KPC, 2  }, { KPB, 6,  KPC, 2  },
	{ KPB, 7,  KPC, 2  }, { KPB, 8,  KPC, 2  }, { KPB, 9,  KPC, 2  },
	{ KPB, 12, KPC, 2  }, { KPB, 13, KPC, 2  }, { KPB, 14, KPC, 2  },

	/* #36 - #47 */
	{ KPB, 0,  KPC, 3  }, { KPB, 1,  KPC, 3  }, { KPB, 3,  KPC, 3  },
	{ KPB, 4,  KPC, 3  }, { KPB, 5,  KPC, 3  }, { KPB, 6,  KPC, 3  },
	{ KPB, 7,  KPC, 3  }, { KPB, 8,  KPC, 3  }, { KPB, 9,  KPC, 3  },
	{ KPB, 12, KPC, 3  }, { KPB, 13, KPC, 3  }, { KPB, 14, KPC, 3  },

	/* #48 - #59 */
	{ KPB, 0,  KPC, 4  }, { KPB, 1,  KPC, 4  }, { KPB, 3,  KPC, 4  },
	{ KPB, 4,  KPC, 4  }, { KPB, 5,  KPC, 4  }, { KPB, 6,  KPC, 4  },
	{ KPB, 7,  KPC, 4  }, { KPB, 8,  KPC, 4  }, { KPB, 9,  KPC, 4  },
	{ KPB, 12, KPC, 4  }, { KPB, 13, KPC, 4  }, { KPB, 14, KPC, 4  },

	/* #60 - #71 */
	{ KPB, 0,  KPC, 5  }, { KPB, 1,  KPC, 5  }, { KPB, 3,  KPC, 5  },
	{ KPB, 4,  KPC, 5  }, { KPB, 5,  KPC, 5  },
#elif (CONFIG_MAPPING_REVISION == 1)
	/* Row 0 */
	{ KPC, 0,  KPB, 0  }, { KPC, 0,  KPB, 3  }, { KPC, 0,  KPB, 4  },
	{ KPC, 0,  KPB, 5  }, { KPC, 0,  KPB, 6  }, { KPC, 0,  KPB, 7  },
	{ KPC, 0,  KPB, 8  }, { KPC, 0,  KPB, 9  }, { KPC, 0,  KPB, 12 },

	/* Row 1 */
	{ KPC, 1,  KPB, 0  }, { KPC, 1,  KPB, 1  }, { KPC, 1,  KPB, 3  },
	{ KPC, 1,  KPB, 4  }, { KPC, 1,  KPB, 5  }, { KPC, 1,  KPB, 6  },
	{ KPC, 1,  KPB, 7  }, { KPC, 1,  KPB, 8  }, { KPC, 1,  KPB, 9  },
	{ KPC, 1,  KPB, 12 }, { KPC, 1,  KPB, 13 },

	/* Row 2 */
	{ KPC, 2,  KPB, 0  }, { KPC, 2,  KPB, 3  }, { KPC, 2,  KPB, 4  },
	{ KPC, 2,  KPB, 5  }, { KPC, 2,  KPB, 6  }, { KPC, 2,  KPB, 7  },
	{ KPC, 2,  KPB, 8  }, { KPC, 2,  KPB, 9  }, { KPC, 2,  KPB, 12 },
	{ KPC, 2,  KPB, 13 },

	/* Row 3 */
	{ KPC, 3,  KPB, 0  }, { KPC, 3,  KPB, 3  }, { KPC, 3,  KPB, 4  },
	{ KPC, 3,  KPB, 5  }, { KPC, 3,  KPB, 6  }, { KPC, 3,  KPB, 7  },
	{ KPC, 3,  KPB, 8  }, { KPC, 3,  KPB, 9  }, { KPC, 3,  KPB, 12 },
	{ KPC, 3,  KPB, 13 },

	/* Row 4 */
	{ KPC, 4,  KPB, 0  }, { KPC, 4,  KPB, 3  }, { KPC, 4,  KPB, 4  },
	{ KPC, 4,  KPB, 5  }, { KPC, 4,  KPB, 6  }, { KPC, 4,  KPB, 7  },
	{ KPC, 4,  KPB, 8  }, { KPC, 4,  KPB, 9  }, { KPC, 4,  KPB, 12 },
	{ KPC, 4,  KPB, 13 },

	/* Row 5 */
	{ KPC, 5,  KPB, 0  }, { KPC, 5,  KPB, 1  }, { KPC, 5,  KPB, 3  },
	{ KPC, 5,  KPB, 7  }, { KPC, 5,  KPB, 13 },

	/* Row 6 */
	{ KPC, 6,  KPB, 0  }, { KPC, 6,  KPB, 1  }, { KPC, 6,  KPB, 3  },
	{ KPC, 6,  KPB, 4  }, { KPC, 6,  KPB, 5  }, { KPC, 6,  KPB, 6  },
	{ KPC, 6,  KPB, 7  },

	/* Row 7 */
	{ KPC, 7,  KPB, 0  }, { KPC, 7,  KPB, 1  }, { KPC, 7,  KPB, 4  },
	{ KPC, 7,  KPB, 5  }, { KPC, 7,  KPB, 6  }, { KPC, 7,  KPB, 7  },
	{ KPC, 7,  KPB, 8  }, { KPC, 7,  KPB, 9  }, { KPC, 7,  KPB, 12 },
	{ KPC, 7,  KPB, 13 },

	/* Row 8 */
	{ KPC, 8,  KPB, 0  }, { KPC, 8,  KPB, 1  }, { KPC, 8,  KPB, 3  },
	{ KPC, 8,  KPB, 5  }, { KPC, 8,  KPB, 6  }, { KPC, 8,  KPB, 7  },
	{ KPC, 8,  KPB, 8  }, { KPC, 8,  KPB, 9  }, { KPC, 8,  KPB, 12 },

	/* Row 9 */
	{ KPC, 9,  KPB, 0  }, { KPC, 9,  KPB, 1  }, { KPC, 9,  KPB, 3  },
	{ KPC, 9,  KPB, 4  }, { KPC, 9,  KPB, 6  }, { KPC, 9,  KPB, 8  },
	{ KPC, 9,  KPB, 9  }, { KPC, 9,  KPB, 12 }, { KPC, 9,  KPB, 13 },

	/* Row 10 */
	{ KPC, 10, KPB, 0  }, { KPC, 10, KPB, 1  }, { KPC, 10, KPB, 4  },
	{ KPC, 10, KPB, 6  }, { KPC, 10, KPB, 8  }, { KPC, 10, KPB, 9  },
	{ KPC, 10, KPB, 12 },

	/* Row 11 */
	{ KPC, 12, KPB, 0  }, { KPC, 12, KPB, 3  }, { KPC, 12, KPB, 4  },
	{ KPC, 12, KPB, 5  }, { KPC, 12, KPB, 6  }, { KPC, 12, KPB, 7  },
	{ KPC, 12, KPB, 8  }, { KPC, 12, KPB, 12 }, { KPC, 12, KPB, 13 },
#endif
};

const struct PressedPhysicalKeys* get_physical_keys()
{
	key_id_t k_id = 0;
	uint8_t num_pressed_keys = 0;

	for (k_id = 0; k_id < LAYOUT_SIZE; k_id++)
	{
		struct PhysicalKey pk = keyboard_keys[k_id];
		if (!is_key_down(pk.row_port, pk.row_pin, pk.col_port, pk.col_pin))
		{
			continue;
		}

		physical_keys.pressed_keys[num_pressed_keys] = k_id;
	}

	physical_keys.num_pressed_keys = num_pressed_keys;
	return &physical_keys;
}

uint8_t get_num_keys(const struct PressedPhysicalKeys* pkeys)
{
	return pkeys->num_pressed_keys;
}

key_id_t get_key_id(uint8_t key, const struct PressedPhysicalKeys* pkeys)
{
	// TODO bounds checking
	return pkeys->pressed_keys[key];
}
