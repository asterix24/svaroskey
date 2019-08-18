#pragma once

#include "quantum.h"
#include "led.h"

#define LAYOUT_all( \
    K00,            K02,    K03,    K04,    K05,    K06,    K07,    K08,    K09,    K010,   K011,   K012,   K013,   K014,   K015,   K016,   K017,   K018,   K019,   K020,   \
    K10,    K11,    K12,    K13,    K14,    K15,    K16,    K17,    K18,    K19,    K110,   K111,   K112,   K113,   K114,   K115,   K116,   K117,   K118,   K119,   K120,   \
    K20,    K21,    K22,    K23,    K24,    K25,    K26,    K27,    K28,    K29,    K210,   K211,   K212,   K213,   K214,   K215,   K216,   K217,   K218,   K219,   K220,   \
    K30,    K31,    K32,    K33,    K34,    K35,    K36,    K37,    K38,    K39,    K310,   K311,   K312,           K314,   K315,   K316,   K317,   K318,   K319,           \
    K40,    K41,    K42,    K43,    K44,    K45,    K46,    K47,    K48,    K49,    K410,   K411,   K412,                   K415,           K417,   K418,   K419,   K420,   \
    K50,       K51,    K52,         K54,            K56,            K58,      K59,    K510,        K511,    K513,   K514,   K515,   K516,   K517,           K519            \
    ) \
{ \
    {  K00,    KC_NO,  K02,    K03,    K04,    K05,    K06,    K07,    K08,    K09,    K010,   K011,   K012,   K013,   K014,   K015,   K016,   K017,   K018,   K019,   K020  }, \
    {  K10,    K11,    K12,    K13,    K14,    K15,    K16,    K17,    K18,    K19,    K110,   K111,   K112,   K113,   K114,   K115,   K116,   K117,   K118,   K119,   K120  }, \
    {  K20,    K21,    K22,    K23,    K24,    K25,    K26,    K27,    K28,    K29,    K210,   K211,   K212,   K213,   K214,   K215,   K216,   K217,   K218,   K219,   K220  }, \
    {  K30,    K31,    K32,    K33,    K34,    K35,    K36,    K37,    K38,    K39,    K310,   K311,   K312,   KC_NO,  K314,   K315,   K316,   K317,   K318,   K319,   KC_NO }, \
    {  K40,    K41,    K42,    K43,    K44,    K45,    K46,    K47,    K48,    K49,    K410,   K411,   K412,   KC_NO,  KC_NO,  K415,   KC_NO,  K417,   K418,   K419,   K420  }, \
    {  K50,    K51,    K52,    KC_NO,  K54,    KC_NO,  K56,    KC_NO,  K58,    K59,    K510,   K511,   KC_NO,  K513,   K514,   K515,   K516,   K517,   KC_NO,  K519,   KC_NO }, \
}
