#include "logical_key.h"

#include "definitions.h"
#include "keycodes.h"

typedef LogicalKey* layout_layer_t;

LogicalKey layer0[LAYOUT_SIZE] = {
#if (CONFIG_LAYOUT_REVISION == 0)
	/* Row 1 */
	{.scancode = KEY_ESCAPE, .modifiers = 0},
	{.scancode = KEY_1     , .modifiers = 0},
	{.scancode = KEY_2     , .modifiers = 0},
	{.scancode = KEY_3     , .modifiers = 0},
	{.scancode = KEY_4     , .modifiers = 0},
	{.scancode = KEY_5     , .modifiers = 0},
	{.scancode = KEY_6     , .modifiers = 0},
	{.scancode = KEY_7     , .modifiers = 0},
	{.scancode = KEY_8     , .modifiers = 0},
	{.scancode = KEY_9     , .modifiers = 0},
	{.scancode = KEY_0     , .modifiers = 0},
	{.scancode = KEY_MINUS , .modifiers = 0},
	{.scancode = KEY_EQUALS, .modifiers = 0},
	{.scancode = KEY_DELETE, .modifiers = 0},

	/* Row 2 */
	{.scancode = KEY_TAB         , .modifiers = 0},
	{.scancode = KEY_Q           , .modifiers = 0},
	{.scancode = KEY_W           , .modifiers = 0},
	{.scancode = KEY_E           , .modifiers = 0},
	{.scancode = KEY_R           , .modifiers = 0},
	{.scancode = KEY_T           , .modifiers = 0},
	{.scancode = KEY_Y           , .modifiers = 0},
	{.scancode = KEY_U           , .modifiers = 0},
	{.scancode = KEY_I           , .modifiers = 0},
	{.scancode = KEY_O           , .modifiers = 0},
	{.scancode = KEY_P           , .modifiers = 0},
	{.scancode = KEY_LEFTBRACKET , .modifiers = 0},
	{.scancode = KEY_RIGHTBRACKET, .modifiers = 0},
	{.scancode = KEY_ENTER       , .modifiers = 0},

	/* Row 3 */
	{.scancode = KEY_RIGHTCONTROL, .modifiers = MOD_RIGHTCONTROL},
	{.scancode = KEY_A           , .modifiers = 0},
	{.scancode = KEY_S           , .modifiers = 0},
	{.scancode = KEY_D           , .modifiers = 0},
	{.scancode = KEY_F           , .modifiers = 0},
	{.scancode = KEY_G           , .modifiers = 0},
	{.scancode = KEY_H           , .modifiers = 0},
	{.scancode = KEY_J           , .modifiers = 0},
	{.scancode = KEY_K           , .modifiers = 0},
	{.scancode = KEY_L           , .modifiers = 0},
	{.scancode = KEY_SEMICOLON   , .modifiers = 0},
	{.scancode = KEY_QUOTE       , .modifiers = 0},
	{.scancode = KEY_BACKSLASH   , .modifiers = 0},

	/* Row 4 */
	{.scancode = KEY_LEFTSHIFT, .modifiers = MOD_LEFTSHIFT},
	{.scancode = KEY_GRAVE    , .modifiers = 0},
	{.scancode = KEY_Z        , .modifiers = 0},
	{.scancode = KEY_X        , .modifiers = 0},
	{.scancode = KEY_C        , .modifiers = 0},
	{.scancode = KEY_V        , .modifiers = 0},
	{.scancode = KEY_B        , .modifiers = 0},
	{.scancode = KEY_N        , .modifiers = 0},
	{.scancode = KEY_M        , .modifiers = 0},
	{.scancode = KEY_COMMA    , .modifiers = 0},
	{.scancode = KEY_PERIOD   , .modifiers = 0},
	{.scancode = KEY_SLASH    , .modifiers = 0},
	{.scancode = KEY_LEFTSHIFT, .modifiers = MOD_LEFTSHIFT},

	/* Row 5 */
	{.scancode = KEY_LEFTCONTROL  , .modifiers = MOD_LEFTCONTROL},
	{.scancode = KEY_LAYER_1      , .modifiers = 0},
	{.scancode = KEY_LEFTALT      , .modifiers = MOD_LEFTALT},
	{.scancode = KEY_SPACE        , .modifiers = 0},
	{.scancode = KEY_DELETEFORWARD, .modifiers = 0},
	{.scancode = KEY_SPACE        , .modifiers = 0},
	{.scancode = KEY_RIGHTALT     , .modifiers = MOD_RIGHTALT},
	{.scancode = KEY_RIGHTCONTROL , .modifiers = MOD_RIGHTCONTROL},
	{.scancode = KEY_END          , .modifiers = 0},
	{.scancode = KEY_PAGEDOWN     , .modifiers = 0},
	{.scancode = KEY_PAGEUP       , .modifiers = 0},
#elif (CONFIG_LAYOUT_REVISION == 1)
	/* Row 1 */
	{.scancode = KEY_ESCAPE, .modifiers = 0},
	{.scancode = KEY_F1    , .modifiers = 0},
	{.scancode = KEY_F2    , .modifiers = 0},
	{.scancode = KEY_F3    , .modifiers = 0},
	{.scancode = KEY_F4    , .modifiers = 0},
	{.scancode = KEY_F5    , .modifiers = 0},
	{.scancode = KEY_F6    , .modifiers = 0},
	{.scancode = KEY_F7    , .modifiers = 0},
	{.scancode = KEY_F8    , .modifiers = 0},

	/* Row 2 */
	{.scancode = KEY_GRAVE, .modifiers = 0},
	{.scancode = KEY_1    , .modifiers = 0},
	{.scancode = KEY_2    , .modifiers = 0},
	{.scancode = KEY_3    , .modifiers = 0},
	{.scancode = KEY_4    , .modifiers = 0},
	{.scancode = KEY_5    , .modifiers = 0},
	{.scancode = KEY_6    , .modifiers = 0},
	{.scancode = KEY_7    , .modifiers = 0},
	{.scancode = KEY_8    , .modifiers = 0},
	{.scancode = KEY_9    , .modifiers = 0},
	{.scancode = KEY_0    , .modifiers = 0},

	/* Row 3 */
	{.scancode = KEY_TAB, .modifiers = 0},
	{.scancode = KEY_Q  , .modifiers = 0},
	{.scancode = KEY_W  , .modifiers = 0},
	{.scancode = KEY_E  , .modifiers = 0},
	{.scancode = KEY_R  , .modifiers = 0},
	{.scancode = KEY_T  , .modifiers = 0},
	{.scancode = KEY_Y  , .modifiers = 0},
	{.scancode = KEY_U  , .modifiers = 0},
	{.scancode = KEY_I  , .modifiers = 0},
	{.scancode = KEY_O  , .modifiers = 0},

	/* Row 4 */
	{.scancode = KEY_CAPSLOCK, .modifiers = 0},
	{.scancode = KEY_A       , .modifiers = 0},
	{.scancode = KEY_S       , .modifiers = 0},
	{.scancode = KEY_D       , .modifiers = 0},
	{.scancode = KEY_F       , .modifiers = 0},
	{.scancode = KEY_G       , .modifiers = 0},
	{.scancode = KEY_H       , .modifiers = 0},
	{.scancode = KEY_J       , .modifiers = 0},
	{.scancode = KEY_K       , .modifiers = 0},
	{.scancode = KEY_L       , .modifiers = 0},

	/* Row 5 */
	{.scancode = KEY_LEFTSHIFT, .modifiers = MOD_LEFTSHIFT},
	{.scancode = KEY_Z        , .modifiers = 0},
	{.scancode = KEY_X        , .modifiers = 0},
	{.scancode = KEY_C        , .modifiers = 0},
	{.scancode = KEY_V        , .modifiers = 0},
	{.scancode = KEY_B        , .modifiers = 0},
	{.scancode = KEY_N        , .modifiers = 0},
	{.scancode = KEY_M        , .modifiers = 0},
	{.scancode = KEY_COMMA    , .modifiers = 0},
	{.scancode = KEY_PERIOD   , .modifiers = 0},

	/* Row 6 */
	{.scancode = KEY_LEFTCONTROL, .modifiers = MOD_LEFTCONTROL},
	{.scancode = KEY_LEFTGUI    , .modifiers = MOD_LEFTGUI},
	{.scancode = KEY_LEFTALT    , .modifiers = MOD_LEFTALT},
	{.scancode = KEY_SPACE      , .modifiers = 0},
	{.scancode = KEY_RIGHTALT   , .modifiers = MOD_RIGHTALT},

	/* Row 7 */
	{.scancode = KEY_F9         , .modifiers = 0},
	{.scancode = KEY_F10        , .modifiers = 0},
	{.scancode = KEY_F11        , .modifiers = 0},
	{.scancode = KEY_F12        , .modifiers = 0},
	{.scancode = KEY_SCROLLLOCK , .modifiers = 0},
	{.scancode = KEY_PRINTSCREEN, .modifiers = 0},
	{.scancode = KEY_PAUSE      , .modifiers = 0},

	/* Row 8 */
	{.scancode = KEY_MINUS  , .modifiers = 0},
	{.scancode = KEY_EQUALS , .modifiers = 0},
	{.scancode = KEY_DELETE , .modifiers = 0},
	{.scancode = KEY_INSERT , .modifiers = 0},
	{.scancode = KEY_HOME   , .modifiers = 0},
	{.scancode = KEY_PAGEUP , .modifiers = 0},
	{.scancode = KP_NUMLOCK , .modifiers = 0},
	{.scancode = KP_DIVIDE  , .modifiers = 0},
	{.scancode = KP_MULTIPLY, .modifiers = 0},
	{.scancode = KP_SUBTRACT, .modifiers = 0},

	/* Row 9 */
	{.scancode = KEY_P            , .modifiers = 0},
	{.scancode = KEY_LEFTBRACKET  , .modifiers = 0},
	{.scancode = KEY_RIGHTBRACKET , .modifiers = 0},
	{.scancode = KEY_DELETEFORWARD, .modifiers = 0},
	{.scancode = KEY_END          , .modifiers = 0},
	{.scancode = KEY_PAGEDOWN     , .modifiers = 0},
	{.scancode = KP_7             , .modifiers = 0},
	{.scancode = KP_8             , .modifiers = 0},
	{.scancode = KP_9             , .modifiers = 0},

	/* Row 10 */
	{.scancode = KEY_SEMICOLON, .modifiers = 0},
	{.scancode = KEY_QUOTE    , .modifiers = 0},
	{.scancode = KEY_Q        , .modifiers = 0},
	{.scancode = KEY_ENTER    , .modifiers = 0},
	{.scancode = KEY_T        , .modifiers = 0},
	{.scancode = KP_4         , .modifiers = 0},
	{.scancode = KP_5         , .modifiers = 0},
	{.scancode = KP_6         , .modifiers = 0},
	{.scancode = KP_ADD       , .modifiers = 0},

	/* Row 11 */
	{.scancode = KEY_SLASH     , .modifiers = 0},
	{.scancode = KEY_BACKSLASH , .modifiers = 0},
	{.scancode = KEY_RIGHTSHIFT, .modifiers = MOD_RIGHTSHIFT},
	{.scancode = KEY_UP        , .modifiers = 0},
	{.scancode = KP_1          , .modifiers = 0},
	{.scancode = KP_2          , .modifiers = 0},
	{.scancode = KP_3          , .modifiers = 0},

	/* Row 12 */
	{.scancode = KEY_RIGHTGUI    , .modifiers = MOD_RIGHTGUI},
	{.scancode = KEY_MENU        , .modifiers = 0},
	{.scancode = KEY_RIGHTCONTROL, .modifiers = MOD_RIGHTCONTROL},
	{.scancode = KEY_LEFT        , .modifiers = 0},
	{.scancode = KEY_DOWN        , .modifiers = 0},
	{.scancode = KEY_RIGHT       , .modifiers = 0},
	{.scancode = KP_0            , .modifiers = 0},
	{.scancode = KP_POINT        , .modifiers = 0},
	{.scancode = KP_ENTER        , .modifiers = 0},
#endif
};

#if (CONFIG_LAYOUT_REVISION == 0)
LogicalKey layer1[] = {
	/* Row 1 */
	{.scancode = KEY_ESCAPE, .modifiers = 0},
	{.scancode = KEY_1     , .modifiers = 0},
	{.scancode = KEY_2     , .modifiers = 0},
	{.scancode = KEY_3     , .modifiers = 0},
	{.scancode = KEY_4     , .modifiers = 0},
	{.scancode = KEY_5     , .modifiers = 0},
	{.scancode = KEY_6     , .modifiers = 0},
	{.scancode = KEY_7     , .modifiers = 0},
	{.scancode = KEY_8     , .modifiers = 0},
	{.scancode = KEY_9     , .modifiers = 0},
	{.scancode = KEY_0     , .modifiers = 0},
	{.scancode = KEY_MINUS , .modifiers = 0},
	{.scancode = KEY_EQUALS, .modifiers = 0},
	{.scancode = KEY_DELETE, .modifiers = 0},

	/* Row 2 */
	{.scancode = KEY_TAB         , .modifiers = 0},
	{.scancode = KEY_Q           , .modifiers = 0},
	{.scancode = KEY_W           , .modifiers = 0},
	{.scancode = KEY_E           , .modifiers = 0},
	{.scancode = KEY_R           , .modifiers = 0},
	{.scancode = KEY_T           , .modifiers = 0},
	{.scancode = KEY_Y           , .modifiers = 0},
	{.scancode = KEY_U           , .modifiers = 0},
	{.scancode = KEY_I           , .modifiers = 0},
	{.scancode = KEY_O           , .modifiers = 0},
	{.scancode = KEY_P           , .modifiers = 0},
	{.scancode = KEY_LEFTBRACKET , .modifiers = 0},
	{.scancode = KEY_RIGHTBRACKET, .modifiers = 0},
	{.scancode = KEY_ENTER       , .modifiers = 0},

	/* Row 3 */
	{.scancode = KEY_RIGHTCONTROL, .modifiers = MOD_RIGHTCONTROL},
	{.scancode = KEY_A           , .modifiers = 0},
	{.scancode = KEY_S           , .modifiers = 0},
	{.scancode = KEY_D           , .modifiers = 0},
	{.scancode = KEY_F           , .modifiers = 0},
	{.scancode = KEY_G           , .modifiers = 0},
	{.scancode = KEY_LEFT        , .modifiers = 0},
	{.scancode = KEY_DOWN        , .modifiers = 0},
	{.scancode = KEY_UP          , .modifiers = 0},
	{.scancode = KEY_RIGHT       , .modifiers = 0},
	{.scancode = KEY_SEMICOLON   , .modifiers = 0},
	{.scancode = KEY_QUOTE       , .modifiers = 0},
	{.scancode = KEY_BACKSLASH   , .modifiers = 0},

	/* Row 4 */
	{.scancode = KEY_LEFTSHIFT, .modifiers = MOD_LEFTSHIFT},
	{.scancode = KEY_GRAVE    , .modifiers = 0},
	{.scancode = KEY_Z        , .modifiers = 0},
	{.scancode = KEY_X        , .modifiers = 0},
	{.scancode = KEY_C        , .modifiers = 0},
	{.scancode = KEY_V        , .modifiers = 0},
	{.scancode = KEY_B        , .modifiers = 0},
	{.scancode = KEY_N        , .modifiers = 0},
	{.scancode = KEY_M        , .modifiers = 0},
	{.scancode = KEY_COMMA    , .modifiers = 0},
	{.scancode = KEY_PERIOD   , .modifiers = 0},
	{.scancode = KEY_SLASH    , .modifiers = 0},
	{.scancode = KEY_UP       , .modifiers = 0},

	/* Row 5 */
	{.scancode = KEY_LEFTCONTROL  , .modifiers = MOD_LEFTCONTROL},
	{.scancode = KEY_LEFTGUI      , .modifiers = MOD_LEFTGUI},
	{.scancode = KEY_LEFTALT      , .modifiers = MOD_LEFTALT},
	{.scancode = KEY_SPACE        , .modifiers = 0},
	{.scancode = KEY_DELETEFORWARD, .modifiers = 0},
	{.scancode = KEY_SPACE        , .modifiers = 0},
	{.scancode = KEY_RIGHTALT     , .modifiers = MOD_RIGHTALT},
	{.scancode = KEY_RIGHTCONTROL , .modifiers = MOD_RIGHTCONTROL},
	{.scancode = KEY_LEFT         , .modifiers = 0},
	{.scancode = KEY_DOWN         , .modifiers = 0},
	{.scancode = KEY_RIGHT        , .modifiers = 0},
};
#endif

layout_layer_t layers[] = {
	layer0,
#if (CONFIG_LAYOUT_REVISION == 0)
	layer1,
#endif
};

const LogicalKey* get_logical_key(int layer, key_id_t key_id)
{
	return &layers[layer][key_id];
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
