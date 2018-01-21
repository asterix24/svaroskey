#include "logical_key.h"

#include "definitions.h"
#include "keycodes.h"

#define LKP(sc, mods) &(LogicalKey){.scancode = (sc), .modifiers = (mods)}

typedef LogicalKey** layout_layer_t;

LogicalKey noop_lk = {.scancode = KEY_NOOP, .modifiers = 0};

LogicalKey* layer0[LAYOUT_SIZE] = {
#if (CONFIG_LAYOUT_REVISION == 0)
	/* Row 1 */
	LKP(KEY_ESCAPE, 0),
	LKP(KEY_1     , 0),
	LKP(KEY_2     , 0),
	LKP(KEY_3     , 0),
	LKP(KEY_4     , 0),
	LKP(KEY_5     , 0),
	LKP(KEY_6     , 0),
	LKP(KEY_7     , 0),
	LKP(KEY_8     , 0),
	LKP(KEY_9     , 0),
	LKP(KEY_0     , 0),
	LKP(KEY_MINUS , 0),
	LKP(KEY_EQUALS, 0),
	LKP(KEY_DELETE, 0),

	/* Row 2 */
	LKP(KEY_TAB         , 0),
	LKP(KEY_Q           , 0),
	LKP(KEY_W           , 0),
	LKP(KEY_E           , 0),
	LKP(KEY_R           , 0),
	LKP(KEY_T           , 0),
	LKP(KEY_Y           , 0),
	LKP(KEY_U           , 0),
	LKP(KEY_I           , 0),
	LKP(KEY_O           , 0),
	LKP(KEY_P           , 0),
	LKP(KEY_LEFTBRACKET , 0),
	LKP(KEY_RIGHTBRACKET, 0),
	LKP(KEY_ENTER       , 0),

	/* Row 3 */
	LKP(KEY_RIGHTCONTROL, MOD_RIGHTCONTROL),
	LKP(KEY_A           , 0),
	LKP(KEY_S           , 0),
	LKP(KEY_D           , 0),
	LKP(KEY_F           , 0),
	LKP(KEY_G           , 0),
	LKP(KEY_H           , 0),
	LKP(KEY_J           , 0),
	LKP(KEY_K           , 0),
	LKP(KEY_L           , 0),
	LKP(KEY_SEMICOLON   , 0),
	LKP(KEY_QUOTE       , 0),
	LKP(KEY_BACKSLASH   , 0),

	/* Row 4 */
	LKP(KEY_LEFTSHIFT, MOD_LEFTSHIFT),
	LKP(KEY_GRAVE    , 0),
	LKP(KEY_Z        , 0),
	LKP(KEY_X        , 0),
	LKP(KEY_C        , 0),
	LKP(KEY_V        , 0),
	LKP(KEY_B        , 0),
	LKP(KEY_N        , 0),
	LKP(KEY_M        , 0),
	LKP(KEY_COMMA    , 0),
	LKP(KEY_PERIOD   , 0),
	LKP(KEY_SLASH    , 0),
	LKP(KEY_LEFTSHIFT, MOD_LEFTSHIFT),

	/* Row 5 */
	LKP(KEY_LAYER_1, 0),
	LKP(KEY_LEFTGUI, MOD_LEFTGUI),
	LKP(KEY_LAYER_2, 0),
	LKP(KEY_SPACE        , 0),
	LKP(KEY_DELETEFORWARD, 0),
	LKP(KEY_SPACE        , 0),
	LKP(KEY_RIGHTALT     , MOD_RIGHTALT),
	LKP(KEY_RIGHTCONTROL , MOD_RIGHTCONTROL),
	LKP(KEY_END          , 0),
	LKP(KEY_PAGEDOWN     , 0),
	LKP(KEY_PAGEUP       , 0),
#elif (CONFIG_LAYOUT_REVISION == 1)
	/* Row 1 */
	LKP(KEY_ESCAPE, 0),
	LKP(KEY_F1    , 0),
	LKP(KEY_F2    , 0),
	LKP(KEY_F3    , 0),
	LKP(KEY_F4    , 0),
	LKP(KEY_F5    , 0),
	LKP(KEY_F6    , 0),
	LKP(KEY_F7    , 0),
	LKP(KEY_F8    , 0),

	/* Row 2 */
	LKP(KEY_GRAVE, 0),
	LKP(KEY_1    , 0),
	LKP(KEY_2    , 0),
	LKP(KEY_3    , 0),
	LKP(KEY_4    , 0),
	LKP(KEY_5    , 0),
	LKP(KEY_6    , 0),
	LKP(KEY_7    , 0),
	LKP(KEY_8    , 0),
	LKP(KEY_9    , 0),
	LKP(KEY_0    , 0),

	/* Row 3 */
	LKP(KEY_TAB, 0),
	LKP(KEY_Q  , 0),
	LKP(KEY_W  , 0),
	LKP(KEY_E  , 0),
	LKP(KEY_R  , 0),
	LKP(KEY_T  , 0),
	LKP(KEY_Y  , 0),
	LKP(KEY_U  , 0),
	LKP(KEY_I  , 0),
	LKP(KEY_O  , 0),

	/* Row 4 */
	LKP(KEY_CAPSLOCK, 0),
	LKP(KEY_A       , 0),
	LKP(KEY_S       , 0),
	LKP(KEY_D       , 0),
	LKP(KEY_F       , 0),
	LKP(KEY_G       , 0),
	LKP(KEY_H       , 0),
	LKP(KEY_J       , 0),
	LKP(KEY_K       , 0),
	LKP(KEY_L       , 0),

	/* Row 5 */
	LKP(KEY_LEFTSHIFT, MOD_LEFTSHIFT),
	LKP(KEY_Z        , 0),
	LKP(KEY_X        , 0),
	LKP(KEY_C        , 0),
	LKP(KEY_V        , 0),
	LKP(KEY_B        , 0),
	LKP(KEY_N        , 0),
	LKP(KEY_M        , 0),
	LKP(KEY_COMMA    , 0),
	LKP(KEY_PERIOD   , 0),

	/* Row 6 */
	LKP(KEY_LEFTCONTROL, MOD_LEFTCONTROL),
	LKP(KEY_LEFTGUI    , MOD_LEFTGUI),
	LKP(KEY_LEFTALT    , MOD_LEFTALT),
	LKP(KEY_SPACE      , 0),
	LKP(KEY_RIGHTALT   , MOD_RIGHTALT),

	/* Row 7 */
	LKP(KEY_F9         , 0),
	LKP(KEY_F10        , 0),
	LKP(KEY_F11        , 0),
	LKP(KEY_F12        , 0),
	LKP(KEY_SCROLLLOCK , 0),
	LKP(KEY_PRINTSCREEN, 0),
	LKP(KEY_PAUSE      , 0),

	/* Row 8 */
	LKP(KEY_MINUS  , 0),
	LKP(KEY_EQUALS , 0),
	LKP(KEY_DELETE , 0),
	LKP(KEY_INSERT , 0),
	LKP(KEY_HOME   , 0),
	LKP(KEY_PAGEUP , 0),
	LKP(KP_NUMLOCK , 0),
	LKP(KP_DIVIDE  , 0),
	LKP(KP_MULTIPLY, 0),
	LKP(KP_SUBTRACT, 0),

	/* Row 9 */
	LKP(KEY_P            , 0),
	LKP(KEY_LEFTBRACKET  , 0),
	LKP(KEY_RIGHTBRACKET , 0),
	LKP(KEY_DELETEFORWARD, 0),
	LKP(KEY_END          , 0),
	LKP(KEY_PAGEDOWN     , 0),
	LKP(KP_7             , 0),
	LKP(KP_8             , 0),
	LKP(KP_9             , 0),

	/* Row 10 */
	LKP(KEY_SEMICOLON, 0),
	LKP(KEY_QUOTE    , 0),
	LKP(KEY_Q        , 0),
	LKP(KEY_ENTER    , 0),
	LKP(KEY_T        , 0),
	LKP(KP_4         , 0),
	LKP(KP_5         , 0),
	LKP(KP_6         , 0),
	LKP(KP_ADD       , 0),

	/* Row 11 */
	LKP(KEY_SLASH     , 0),
	LKP(KEY_BACKSLASH , 0),
	LKP(KEY_RIGHTSHIFT, MOD_RIGHTSHIFT),
	LKP(KEY_UP        , 0),
	LKP(KP_1          , 0),
	LKP(KP_2          , 0),
	LKP(KP_3          , 0),

	/* Row 12 */
	LKP(KEY_RIGHTGUI    , MOD_RIGHTGUI),
	LKP(KEY_MENU        , 0),
	LKP(KEY_RIGHTCONTROL, MOD_RIGHTCONTROL),
	LKP(KEY_LEFT        , 0),
	LKP(KEY_DOWN        , 0),
	LKP(KEY_RIGHT       , 0),
	LKP(KP_0            , 0),
	LKP(KP_POINT        , 0),
	LKP(KP_ENTER        , 0),
#endif
};

#if (CONFIG_LAYOUT_REVISION == 0)
LogicalKey* layer1[] = {
	/* Row 1 */
	&noop_lk, &noop_lk, &noop_lk, &noop_lk, &noop_lk,
	&noop_lk, &noop_lk, &noop_lk, &noop_lk, &noop_lk,
	&noop_lk, &noop_lk, &noop_lk, &noop_lk,

	/* Row 2 */
	&noop_lk,
	LKP(KEY_4, MOD_LEFTSHIFT),
	&noop_lk,
	&noop_lk,
	&noop_lk,

	&noop_lk, &noop_lk, &noop_lk, &noop_lk, &noop_lk,
	&noop_lk, &noop_lk, &noop_lk, &noop_lk,

	/* Row 3 */
	&noop_lk, &noop_lk, &noop_lk, &noop_lk, &noop_lk,
	&noop_lk, &noop_lk, &noop_lk, &noop_lk, &noop_lk,
	&noop_lk, &noop_lk, &noop_lk,

	/* Row 4 */
	&noop_lk, &noop_lk, &noop_lk, &noop_lk, &noop_lk,
	&noop_lk, &noop_lk, &noop_lk, &noop_lk, &noop_lk,
	&noop_lk, &noop_lk, &noop_lk,

	/* Row 5 */
	&noop_lk, &noop_lk, &noop_lk, &noop_lk, &noop_lk,
	&noop_lk, &noop_lk, &noop_lk, &noop_lk, &noop_lk,
	&noop_lk,
};

LogicalKey* layer2[] = {
	/* Row 1 */
	&noop_lk, &noop_lk, &noop_lk, &noop_lk, &noop_lk,
	&noop_lk, &noop_lk, &noop_lk, &noop_lk, &noop_lk,
	&noop_lk, &noop_lk, &noop_lk, &noop_lk,

	/* Row 2 */
	&noop_lk,
	LKP(KEY_LEFTGUI, MOD_LEFTGUI),
	&noop_lk,
	&noop_lk,
	&noop_lk,

	&noop_lk, &noop_lk, &noop_lk, &noop_lk, &noop_lk,
	&noop_lk, &noop_lk, &noop_lk, &noop_lk,

	/* Row 3 */
	&noop_lk, &noop_lk, &noop_lk, &noop_lk, &noop_lk,
	&noop_lk, &noop_lk, &noop_lk, &noop_lk, &noop_lk,
	&noop_lk, &noop_lk, &noop_lk,

	/* Row 4 */
	&noop_lk, &noop_lk, &noop_lk, &noop_lk, &noop_lk,
	&noop_lk, &noop_lk, &noop_lk, &noop_lk, &noop_lk,
	&noop_lk, &noop_lk, &noop_lk,

	/* Row 5 */
	&noop_lk, &noop_lk, &noop_lk, &noop_lk, &noop_lk,
	&noop_lk, &noop_lk, &noop_lk, &noop_lk, &noop_lk,
	&noop_lk,
};

LogicalKey* layer3[] = {
	/* Row 1 */
	&noop_lk, &noop_lk, &noop_lk, &noop_lk, &noop_lk,
	&noop_lk, &noop_lk, &noop_lk, &noop_lk, &noop_lk,
	&noop_lk, &noop_lk, &noop_lk, &noop_lk,

	/* Row 2 */
	&noop_lk,
	LKP(KEY_1, MOD_LEFTSHIFT),
	LKP(KEY_8, 0),
	&noop_lk,
	&noop_lk,

	&noop_lk, &noop_lk, &noop_lk, &noop_lk, &noop_lk,
	&noop_lk, &noop_lk, &noop_lk, &noop_lk,

	/* Row 3 */
	&noop_lk, &noop_lk, &noop_lk, &noop_lk, &noop_lk,
	&noop_lk, &noop_lk, &noop_lk, &noop_lk, &noop_lk,
	&noop_lk, &noop_lk, &noop_lk,

	/* Row 4 */
	&noop_lk, &noop_lk, &noop_lk, &noop_lk, &noop_lk,
	&noop_lk, &noop_lk, &noop_lk, &noop_lk, &noop_lk,
	&noop_lk, &noop_lk, &noop_lk,

	/* Row 5 */
	&noop_lk, &noop_lk, &noop_lk, &noop_lk, &noop_lk,
	&noop_lk, &noop_lk, &noop_lk, &noop_lk, &noop_lk,
	&noop_lk,
};
#endif

layout_layer_t layers[] = {
	layer0,
#if (CONFIG_LAYOUT_REVISION == 0)
	layer1,
	layer2,
	layer3
#endif
};

const LogicalKey* get_logical_key(size_t layer, key_id_t key_id)
{
	return layers[layer][key_id];
}

bool is_modifier(const LogicalKey* lk)
{
	return lk->scancode >= KEY_LEFTCONTROL
	       && lk->scancode <= KEY_RIGHTGUI;
}

bool is_custom(const LogicalKey* lk)
{
	return lk->scancode >= KEY_CUSTOM_START
	       && lk->scancode <= KEY_CUSTOM_END;
}
