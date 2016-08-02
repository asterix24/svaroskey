#include "keymap.h"
#include "keycodes.h"
#include "cfg/cfg_keymap.h"

#define CONFIG_MAPPING_LATEST_REVISION 0

#if !defined CONFIG_MAPPING_REVISION
#error CONFIG_MAPPING_REVISION is not defined.
#elif (CONFIG_MAPPING_REVISION > CONFIG_MAPPING_LATEST_REVISION)
#error CONFIG_MAPPING_REVISION is not valid.
#endif

#define KPA 0
#define KPB 1
#define KPC 2

static const keymapping_t keyboard_mapping[] = {
#if (CONFIG_MAPPING_REVISION == 0)
    { KPA, 0,  KPB, 0  }, { KPA, 0,  KPB, 1  }, { KPA, 0,  KPB, 3  },
    { KPA, 0,  KPB, 4  }, { KPA, 0,  KPB, 5  }, { KPA, 0,  KPB, 6  },
    { KPA, 0,  KPB, 7  }, { KPA, 0,  KPB, 8  }, { KPA, 0,  KPB, 9  },
    { KPA, 0,  KPB, 12 }, { KPA, 0,  KPB, 13 }, { KPA, 0,  KPB, 14 },

    { KPA, 1,  KPB, 0  }, { KPA, 1,  KPB, 1  }, { KPA, 1,  KPB, 3  },
    { KPA, 1,  KPB, 4  }, { KPA, 1,  KPB, 5  }, { KPA, 1,  KPB, 6  },
    { KPA, 1,  KPB, 7  }, { KPA, 1,  KPB, 8  }, { KPA, 1,  KPB, 9  },
    { KPA, 1,  KPB, 12 }, { KPA, 1,  KPB, 13 }, { KPA, 1,  KPB, 14 },

    { KPA, 4,  KPB, 0  }, { KPA, 4,  KPB, 1  }, { KPA, 4,  KPB, 3  },
    { KPA, 4,  KPB, 4  }, { KPA, 4,  KPB, 5  }, { KPA, 4,  KPB, 6  },
    { KPA, 4,  KPB, 7  }, { KPA, 4,  KPB, 8  }, { KPA, 4,  KPB, 9  },
    { KPA, 4,  KPB, 12 }, { KPA, 4,  KPB, 13 }, { KPA, 4,  KPB, 14 },

    { KPA, 5,  KPB, 0  }, { KPA, 5,  KPB, 1  }, { KPA, 5,  KPB, 3  },
    { KPA, 5,  KPB, 4  }, { KPA, 5,  KPB, 5  }, { KPA, 5,  KPB, 6  },
    { KPA, 5,  KPB, 7  }, { KPA, 5,  KPB, 8  }, { KPA, 5,  KPB, 9  },
    { KPA, 5,  KPB, 12 }, { KPA, 5,  KPB, 13 }, { KPA, 5,  KPB, 14 },

    { KPA, 6,  KPB, 0  }, { KPA, 6,  KPB, 1  }, { KPA, 6,  KPB, 3  },
    { KPA, 6,  KPB, 4  }, { KPA, 6,  KPB, 5  }, { KPA, 6,  KPB, 6  },
    { KPA, 6,  KPB, 7  }, { KPA, 6,  KPB, 8  }, { KPA, 6,  KPB, 9  },
    { KPA, 6,  KPB, 12 }, { KPA, 6,  KPB, 13 }, { KPA, 6,  KPB, 14 },

    { KPA, 7,  KPB, 0  }, { KPA, 7,  KPB, 1  }, { KPA, 7,  KPB, 3  },
    { KPA, 7,  KPB, 4  }, { KPA, 7,  KPB, 5  }, { KPA, 7,  KPB, 6  },
    { KPA, 7,  KPB, 7  }, { KPA, 7,  KPB, 8  }, { KPA, 7,  KPB, 9  },
    { KPA, 7,  KPB, 12 }, { KPA, 7,  KPB, 13 }, { KPA, 7,  KPB, 14 },

    { KPA, 8,  KPB, 0  }, { KPA, 8,  KPB, 1  }, { KPA, 8,  KPB, 3  },
    { KPA, 8,  KPB, 4  }, { KPA, 8,  KPB, 5  }, { KPA, 8,  KPB, 6  },
    { KPA, 8,  KPB, 7  }, { KPA, 8,  KPB, 8  }, { KPA, 8,  KPB, 9  },
    { KPA, 8,  KPB, 12 }, { KPA, 8,  KPB, 13 }, { KPA, 8,  KPB, 14 },

    { KPA, 9,  KPB, 0  }, { KPA, 9,  KPB, 1  }, { KPA, 9,  KPB, 3  },
    { KPA, 9,  KPB, 4  }, { KPA, 9,  KPB, 5  }, { KPA, 9,  KPB, 6  },
    { KPA, 9,  KPB, 7  }, { KPA, 9,  KPB, 8  }, { KPA, 9,  KPB, 9  },
    { KPA, 9,  KPB, 12 }, { KPA, 9,  KPB, 13 }, { KPA, 9,  KPB, 14 },

    { KPA, 10, KPB, 0  }, { KPA, 10, KPB, 1  }, { KPA, 10, KPB, 3  },
    { KPA, 10, KPB, 4  }, { KPA, 10, KPB, 5  }, { KPA, 10, KPB, 6  },
    { KPA, 10, KPB, 7  }, { KPA, 10, KPB, 8  }, { KPA, 10, KPB, 9  },
    { KPA, 10, KPB, 12 }, { KPA, 10, KPB, 13 }, { KPA, 10, KPB, 14 },

    { KPA, 13, KPB, 0  }, { KPA, 13, KPB, 1  }, { KPA, 13, KPB, 3  },
    { KPA, 13, KPB, 4  }, { KPA, 13, KPB, 5  }, { KPA, 13, KPB, 6  },
    { KPA, 13, KPB, 7  }, { KPA, 13, KPB, 8  }, { KPA, 13, KPB, 9  },
    { KPA, 13, KPB, 12 }, { KPA, 13, KPB, 13 }, { KPA, 13, KPB, 14 },

    { KPA, 14, KPB, 0  }, { KPA, 14, KPB, 1  }, { KPA, 14, KPB, 3  },
    { KPA, 14, KPB, 4  }, { KPA, 14, KPB, 5  }, { KPA, 14, KPB, 6  },
    { KPA, 14, KPB, 7  }, { KPA, 14, KPB, 8  }, { KPA, 14, KPB, 9  },
    { KPA, 14, KPB, 12 }, { KPA, 14, KPB, 13 }, { KPA, 14, KPB, 14 },

    { KPA, 15, KPB, 0  }, { KPA, 15, KPB, 1  }, { KPA, 15, KPB, 3  },
    { KPA, 15, KPB, 4  }, { KPA, 15, KPB, 5  }, { KPA, 15, KPB, 6  },
    { KPA, 15, KPB, 7  }, { KPA, 15, KPB, 8  }, { KPA, 15, KPB, 9  },
    { KPA, 15, KPB, 12 }, { KPA, 15, KPB, 13 }, { KPA, 15, KPB, 14 },
#endif
};
