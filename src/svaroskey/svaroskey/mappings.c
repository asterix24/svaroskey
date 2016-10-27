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

KeyMapping keymap_mapping[] = {
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
    { KPB, 4,  KPC, 5  }, { KPB, 5,  KPC, 5  }, { KPB, 6,  KPC, 5  },
    { KPB, 7,  KPC, 5  }, { KPB, 8,  KPC, 5  }, { KPB, 9,  KPC, 5  },
    { KPB, 12, KPC, 5  }, { KPB, 13, KPC, 5  }, { KPB, 14, KPC, 5  },
#endif
};
