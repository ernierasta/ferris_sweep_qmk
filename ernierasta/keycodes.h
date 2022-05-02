#pragma once

#include QMK_KEYBOARD_H

#include "quantum.h"
#include "oneshot.h"

// Layer keys
//#define NUM OSL(_NUM)
#define NUM LT(_NUM, OS_SHFT)
//#define SYM OSL(_SYM)
#define SYM LT(OS_SYM, KC_BSPC) // OS SYM Switch on hold, Backspace on tap (intercepted in process_record_user)
#define RSFT_TRALT RSFT_T(OS_RALT) // Shift held, OS RAlt tapped (intercepted in process_record_user) 
#define WNAV MO(_WNAV) // Workspace navigation and media
#define FUN MO(_FUN) // Fkeys and mods only
#define MOUSE MO(_MOUSE)
#define NAV_SPC LT(_NAV, KC_SPC)

// shortcuts
#define M_UNDO C(KC_Z)
#define M_CUT C(KC_X)
#define M_COPY C(KC_C)
#define M_PSTE C(KC_V)
#define M_SAVE C(KC_D)
#define TAB_L S(KC_TAB)
#define TAB_R KC_TAB
#define ALF LGUI(KC_SPC)
#define HOOK HYPR(KC_H)
#define COLON RSFT(KC_P)
// window resizing shortcuts
// left, right, full
// workspace shortcuts
#define W1 LALT(KC_Q)
#define W2 LALT(KC_W)
#define W3 LALT(KC_E)
#define W4 LALT(KC_R)
#define W5 LALT(KC_T)
#define W6 LALT(KC_Y)
#define W7 LALT(KC_U)
#define W8 LALT(KC_I)
#define W9 LALT(KC_O)
#define W10 LALT(KC_P)
// windows manipulation - swaywm
#define WLEFT LALT(KC_J)
#define WDOWN LALT(KC_K)
#define WUP LALT(KC_L)
#define WRIGHT LALT(KC_SCLN)
// move windows
#define MWLEFT LSA(KC_J)
#define MWDOWN LSA(KC_K)
#define MWUP LSA(KC_L)
#define MWRIGHT LSA(KC_SCLN)
// arrange & run
#define RUNAPP A(KC_F) 
#define RUNTERM A(KC_ENT) 
#define KILLAPP LSA(KC_A)
#define FULLSCN A(KC_A)
#define ARRANGE A(KC_D)
#define SCRPAD A(KC_S)
// to klawa layer

#define TG_QWTY TG(_KLW)
// awkward symbols to type
#define GBPD LALT(KC_3) // UK pound sign
#define PMIN LALT(KC_PLUS) // plus/minus symbol

enum layers {
	_DEF,
	_KLW,
	_NUM,
	_SYM,
	_NAV,
	_WNAV,
	_FUN,
        _MOUSE
};

enum keycodes {
	// Custom oneshot mod implementation with no timers.
	OS_SHFT = SAFE_RANGE,
	OS_CTRL,
	OS_ALT,
        OS_RALT,
	OS_CMD,
        OS_SYM,

	NUMWORD,

	CLEAR,

	SW_APP,
};
