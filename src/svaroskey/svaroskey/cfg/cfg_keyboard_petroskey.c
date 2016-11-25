#include "cfg/cfg_keyboard_petroskey.h"

#include "layout.h"
#include "grid.h"
#include "key.h"

CREATE_LAYOUT(default)
	KEY_DEF(0,  KEY_CODES( NONUSBACKSLASH ), KEY_FUNCS( NULL ))
	KEY_DEF(1,  KEY_CODES( 1              ), KEY_FUNCS( NULL ))
	KEY_DEF(2,  KEY_CODES( 2              ), KEY_FUNCS( NULL ))
	KEY_DEF(3,  KEY_CODES( 3              ), KEY_FUNCS( NULL ))
	KEY_DEF(4,  KEY_CODES( 4              ), KEY_FUNCS( NULL ))
	KEY_DEF(5,  KEY_CODES( 5              ), KEY_FUNCS( NULL ))
	KEY_DEF(6,  KEY_CODES( 6              ), KEY_FUNCS( NULL ))
	KEY_DEF(7,  KEY_CODES( 7              ), KEY_FUNCS( NULL ))
	KEY_DEF(8,  KEY_CODES( 8              ), KEY_FUNCS( NULL ))
	KEY_DEF(9,  KEY_CODES( 9              ), KEY_FUNCS( NULL ))
	KEY_DEF(10, KEY_CODES( 0              ), KEY_FUNCS( NULL ))
	KEY_DEF(11, KEY_CODES( MINUS          ), KEY_FUNCS( NULL ))
	KEY_DEF(12, KEY_CODES( EQUALS         ), KEY_FUNCS( NULL ))
	KEY_DEF(13, KEY_CODES( DELETE         ), KEY_FUNCS( NULL ))
	KEY_DEF(14, KEY_CODES( TAB            ), KEY_FUNCS( NULL ))
	KEY_DEF(15, KEY_CODES( Q              ), KEY_FUNCS( NULL ))
	KEY_DEF(16, KEY_CODES( W              ), KEY_FUNCS( NULL ))
	KEY_DEF(17, KEY_CODES( E              ), KEY_FUNCS( NULL ))
	KEY_DEF(18, KEY_CODES( R              ), KEY_FUNCS( NULL ))
	KEY_DEF(19, KEY_CODES( T              ), KEY_FUNCS( NULL ))
	KEY_DEF(20, KEY_CODES( Y              ), KEY_FUNCS( NULL ))
	KEY_DEF(21, KEY_CODES( U              ), KEY_FUNCS( NULL ))
	KEY_DEF(22, KEY_CODES( I              ), KEY_FUNCS( NULL ))
	KEY_DEF(23, KEY_CODES( O              ), KEY_FUNCS( NULL ))
	KEY_DEF(24, KEY_CODES( P              ), KEY_FUNCS( NULL ))
	KEY_DEF(25, KEY_CODES( LEFTBRACKET    ), KEY_FUNCS( NULL ))
	KEY_DEF(26, KEY_CODES( RIGHTBRACKET   ), KEY_FUNCS( NULL ))
	KEY_DEF(27, KEY_CODES( ENTER          ), KEY_FUNCS( NULL ))
	KEY_DEF(28, KEY_CODES( CAPSLOCK       ), KEY_FUNCS( NULL ))
	KEY_DEF(29, KEY_CODES( A              ), KEY_FUNCS( NULL ))
	KEY_DEF(30, KEY_CODES( S              ), KEY_FUNCS( NULL ))
	KEY_DEF(31, KEY_CODES( D              ), KEY_FUNCS( NULL ))
	KEY_DEF(32, KEY_CODES( F              ), KEY_FUNCS( NULL ))
	KEY_DEF(33, KEY_CODES( G              ), KEY_FUNCS( NULL ))
	KEY_DEF(34, KEY_CODES( H              ), KEY_FUNCS( NULL ))
	KEY_DEF(35, KEY_CODES( J              ), KEY_FUNCS( NULL ))
	KEY_DEF(36, KEY_CODES( K              ), KEY_FUNCS( NULL ))
	KEY_DEF(37, KEY_CODES( L              ), KEY_FUNCS( NULL ))
	KEY_DEF(38, KEY_CODES( SEMICOLON      ), KEY_FUNCS( NULL ))
	KEY_DEF(39, KEY_CODES( QUOTE          ), KEY_FUNCS( NULL ))
	KEY_DEF(40, KEY_CODES( BACKSLASH      ), KEY_FUNCS( NULL ))
	KEY_DEF(41, KEY_CODES( LEFTSHIFT      ), KEY_FUNCS( NULL ))
	KEY_DEF(42, KEY_CODES( GRAVE          ), KEY_FUNCS( NULL ))
	KEY_DEF(43, KEY_CODES( Z              ), KEY_FUNCS( NULL ))
	KEY_DEF(44, KEY_CODES( X              ), KEY_FUNCS( NULL ))
	KEY_DEF(45, KEY_CODES( C              ), KEY_FUNCS( NULL ))
	KEY_DEF(46, KEY_CODES( V              ), KEY_FUNCS( NULL ))
	KEY_DEF(47, KEY_CODES( B              ), KEY_FUNCS( NULL ))
	KEY_DEF(48, KEY_CODES( N              ), KEY_FUNCS( NULL ))
	KEY_DEF(49, KEY_CODES( M              ), KEY_FUNCS( NULL ))
	KEY_DEF(50, KEY_CODES( COMMA          ), KEY_FUNCS( NULL ))
	KEY_DEF(51, KEY_CODES( PERIOD         ), KEY_FUNCS( NULL ))
	KEY_DEF(52, KEY_CODES( SLASH          ), KEY_FUNCS( NULL ))
	KEY_DEF(53, KEY_CODES( UP             ), KEY_FUNCS( NULL ))
	KEY_DEF(54, KEY_CODES( LEFTCONTROL    ), KEY_FUNCS( NULL ))
	KEY_DEF(55, KEY_CODES( LEFTGUI        ), KEY_FUNCS( NULL ))
	KEY_DEF(56, KEY_CODES( LEFTALT        ), KEY_FUNCS( NULL ))
	KEY_DEF(57, KEY_CODES( SPACE          ), KEY_FUNCS( NULL ))
	KEY_DEF(58, KEY_CODES( ESCAPE         ), KEY_FUNCS( NULL ))
	KEY_DEF(59, KEY_CODES( SPACE          ), KEY_FUNCS( NULL ))
	KEY_DEF(60, KEY_CODES( RIGHTALT       ), KEY_FUNCS( NULL ))
	KEY_DEF(61, KEY_CODES( RIGHTCONTROL   ), KEY_FUNCS( NULL ))
	KEY_DEF(62, KEY_CODES( LEFT           ), KEY_FUNCS( NULL ))
	KEY_DEF(63, KEY_CODES( DOWN           ), KEY_FUNCS( NULL ))
	KEY_DEF(64, KEY_CODES( RIGHT          ), KEY_FUNCS( NULL ))
END_LAYOUT(default)


CREATE_GRID(default)
	CELL_DEF( KPB, 0,  KPC, 0, CELL_KEY(0 ) )
	CELL_DEF( KPB, 1,  KPC, 0, CELL_KEY(1 ) )
	CELL_DEF( KPB, 3,  KPC, 0, CELL_KEY(2 ) )
	CELL_DEF( KPB, 4,  KPC, 0, CELL_KEY(3 ) )
	CELL_DEF( KPB, 5,  KPC, 0, CELL_KEY(4 ) )
	CELL_DEF( KPB, 6,  KPC, 0, CELL_KEY(5 ) )
	CELL_DEF( KPB, 7,  KPC, 0, CELL_KEY(6 ) )
	CELL_DEF( KPB, 8,  KPC, 0, CELL_KEY(7 ) )
	CELL_DEF( KPB, 9,  KPC, 0, CELL_KEY(8 ) )
	CELL_DEF( KPB, 12, KPC, 0, CELL_KEY(9 ) )
	CELL_DEF( KPB, 13, KPC, 0, CELL_KEY(10) )
	CELL_DEF( KPB, 14, KPC, 0, CELL_KEY(11) )
	CELL_DEF( KPB, 0,  KPC, 1, CELL_KEY(12) )
	CELL_DEF( KPB, 1,  KPC, 1, CELL_KEY(13) )
	CELL_DEF( KPB, 3,  KPC, 1, CELL_KEY(14) )
	CELL_DEF( KPB, 4,  KPC, 1, CELL_KEY(15) )
	CELL_DEF( KPB, 5,  KPC, 1, CELL_KEY(16) )
	CELL_DEF( KPB, 6,  KPC, 1, CELL_KEY(17) )
	CELL_DEF( KPB, 7,  KPC, 1, CELL_KEY(18) )
	CELL_DEF( KPB, 8,  KPC, 1, CELL_KEY(19) )
	CELL_DEF( KPB, 9,  KPC, 1, CELL_KEY(20) )
	CELL_DEF( KPB, 12, KPC, 1, CELL_KEY(21) )
	CELL_DEF( KPB, 13, KPC, 1, CELL_KEY(22) )
	CELL_DEF( KPB, 14, KPC, 1, CELL_KEY(23) )
	CELL_DEF( KPB, 0,  KPC, 2, CELL_KEY(24) )
	CELL_DEF( KPB, 1,  KPC, 2, CELL_KEY(25) )
	CELL_DEF( KPB, 3,  KPC, 2, CELL_KEY(26) )
	CELL_DEF( KPB, 4,  KPC, 2, CELL_KEY(27) )
	CELL_DEF( KPB, 5,  KPC, 2, CELL_KEY(28) )
	CELL_DEF( KPB, 6,  KPC, 2, CELL_KEY(29) )
	CELL_DEF( KPB, 7,  KPC, 2, CELL_KEY(30) )
	CELL_DEF( KPB, 8,  KPC, 2, CELL_KEY(31) )
	CELL_DEF( KPB, 9,  KPC, 2, CELL_KEY(32) )
	CELL_DEF( KPB, 12, KPC, 2, CELL_KEY(33) )
	CELL_DEF( KPB, 13, KPC, 2, CELL_KEY(34) )
	CELL_DEF( KPB, 14, KPC, 2, CELL_KEY(35) )
	CELL_DEF( KPB, 0,  KPC, 3, CELL_KEY(36) )
	CELL_DEF( KPB, 1,  KPC, 3, CELL_KEY(37) )
	CELL_DEF( KPB, 3,  KPC, 3, CELL_KEY(38) )
	CELL_DEF( KPB, 4,  KPC, 3, CELL_KEY(39) )
	CELL_DEF( KPB, 5,  KPC, 3, CELL_KEY(40) )
	CELL_DEF( KPB, 6,  KPC, 3, CELL_KEY(41) )
	CELL_DEF( KPB, 7,  KPC, 3, CELL_KEY(42) )
	CELL_DEF( KPB, 8,  KPC, 3, CELL_KEY(43) )
	CELL_DEF( KPB, 9,  KPC, 3, CELL_KEY(44) )
	CELL_DEF( KPB, 12, KPC, 3, CELL_KEY(45) )
	CELL_DEF( KPB, 13, KPC, 3, CELL_KEY(46) )
	CELL_DEF( KPB, 14, KPC, 3, CELL_KEY(47) )
	CELL_DEF( KPB, 0,  KPC, 4, CELL_KEY(48) )
	CELL_DEF( KPB, 1,  KPC, 4, CELL_KEY(49) )
	CELL_DEF( KPB, 3,  KPC, 4, CELL_KEY(50) )
	CELL_DEF( KPB, 4,  KPC, 4, CELL_KEY(51) )
	CELL_DEF( KPB, 5,  KPC, 4, CELL_KEY(52) )
	CELL_DEF( KPB, 6,  KPC, 4, CELL_KEY(53) )
	CELL_DEF( KPB, 7,  KPC, 4, CELL_KEY(54) )
	CELL_DEF( KPB, 8,  KPC, 4, CELL_KEY(55) )
	CELL_DEF( KPB, 9,  KPC, 4, CELL_KEY(56) )
	CELL_DEF( KPB, 12, KPC, 4, CELL_KEY(57) )
	CELL_DEF( KPB, 13, KPC, 4, CELL_KEY(58) )
	CELL_DEF( KPB, 14, KPC, 4, CELL_KEY(59) )
	CELL_DEF( KPB, 0,  KPC, 5, CELL_KEY(60) )
	CELL_DEF( KPB, 1,  KPC, 5, CELL_KEY(61) )
	CELL_DEF( KPB, 3,  KPC, 5, CELL_KEY(62) )
	CELL_DEF( KPB, 4,  KPC, 5, CELL_KEY(63) )
	CELL_DEF( KPB, 5,  KPC, 5, CELL_KEY(64) )
	CELL_DEF( KPB, 6,  KPC, 5, CELL_KEY(-1) )
	CELL_DEF( KPB, 7,  KPC, 5, CELL_KEY(-1) )
	CELL_DEF( KPB, 8,  KPC, 5, CELL_KEY(-1) )
	CELL_DEF( KPB, 9,  KPC, 5, CELL_KEY(-1) )
	CELL_DEF( KPB, 12, KPC, 5, CELL_KEY(-1) )
	CELL_DEF( KPB, 13, KPC, 5, CELL_KEY(-1) )
	CELL_DEF( KPB, 14, KPC, 5, CELL_KEY(-1) )
END_GRID(default)
