#ifndef CFG_KEYBOARD_H
#define CFG_KEYBOARD_H

#ifdef SVAROSKEY
#include "cfg/cfg_keyboard_svaroskey.h"
#else
#include "cfg/cfg_keyboard_petroskey.h"
#endif

#endif /* CFG_KEYBOARD_H */
