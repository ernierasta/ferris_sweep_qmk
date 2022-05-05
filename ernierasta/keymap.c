#include QMK_KEYBOARD_H

// Callum oneshot mods and swapper (edited by ernierasta)
// https://github.com/callum-oakley/qmk_firmware/blob/master/users/callum
#include "caps_word.h"
#include "oneshot.h"
#include "swapper.h"
#include "keycodes.h"

// tap dance setup start
typedef struct {
  bool is_press_action;
  int state;
} tap;

enum {
  SINGLE_TAP = 1,
  SINGLE_HOLD = 2,
  DOUBLE_TAP = 3,
  DOUBLE_HOLD = 4,
  DOUBLE_SINGLE_TAP = 5, //send two single taps
  TRIPLE_TAP = 6,
  TRIPLE_HOLD = 7
};

// add all tap dances here
enum {
  DANCE_SHIFTRALT = 0
};


// tap dance setup end

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

	[_DEF] = LAYOUT_split_3x5_2(
			KC_Q, KC_W, KC_E, KC_R, KC_T,    KC_Y, KC_U, KC_I,    KC_O,   COLON,
			KC_A, KC_S, KC_D, KC_F, KC_G,    KC_H, KC_J, KC_K,    KC_L,   KC_SCLN,
			KC_Z, KC_X, KC_C, KC_V, KC_B,    KC_N, KC_M, KC_COMM, KC_DOT, KC_SLSH,
			                NUM, NAV_SPC,    RALT_TD_RSFT, SYM
							   ),
	[_KLW] = LAYOUT_split_3x5_2(
			KC_F,  KC_U, KC_L, KC_P, KC_D,     KC_H, KC_K, KC_T,    KC_Y,   KC_SCLN,
			KC_A,  KC_E, KC_S, KC_N, KC_M,     KC_J, KC_R, KC_Z,    KC_O,   KC_I,
			KC_V,  KC_X, KC_C, KC_G, KC_Q,     KC_B, KC_W, KC_COMM, KC_DOT, KC_SLSH,
					 NUM, NAV_SPC,     RALT_TD_RSFT, SYM
							   ),
	[_NUM] = LAYOUT_split_3x5_2(
			KC_NO,   KC_NO,   KC_NO,  KC_NO,  KC_PERC,   KC_PLUS, KC_7, KC_8, KC_9, KC_MINS,
			OS_SHFT, OS_CMD, OS_ALT, OS_CTRL, KC_EQL,    KC_DOT,  KC_4, KC_5, KC_6, KC_P,
			KC_NO,   KC_NO,   KC_NO,  KC_NO,  KC_UNDS,   KC_ASTR, KC_1, KC_2, KC_3, KC_SLSH,
			                        KC_TRNS,  KC_TRNS,   KC_0, FUN
								),

	[_SYM] = LAYOUT_split_3x5_2(
			KC_EXLM, KC_AT,   KC_HASH, KC_DLR,  KC_PERC,     KC_PIPE,  KC_AMPR, KC_ASTR, KC_UNDS, KC_MINS,
			KC_UNDS, KC_QUOT, KC_EQL, KC_DQUO,  KC_TILD,     KC_NO, OS_CTRL,  OS_ALT,  OS_CMD, OS_SHFT,
			KC_LT,   KC_GT,   KC_NO,  KC_NO,    KC_GRV,      KC_NO, PMIN,    KC_CIRC, KC_PLUS, KC_BSLS,
			                           FUN,     KC_TRNS,     KC_TRNS, KC_TRNS
								),


	[_NAV] = LAYOUT_split_3x5_2(
			SW_APP,  KILLAPP,   TAB_L, KC_TAB,  KC_DEL,    KC_DEL, KC_HOME, KC_PGDN, KC_PGUP, KC_END,
			OS_SHFT, OS_CMD, OS_ALT, OS_CTRL, KC_ESC,    KC_INS, KC_LEFT, KC_DOWN, KC_UP,   KC_RGHT,
			M_UNDO,  M_CUT,   M_COPY, M_PSTE, KC_ENT,    M_SAVE, KC_ESC,  KC_BSPC, KC_DEL,  KC_BSPC,
			                          KC_TRNS, KC_TRNS,  WNAV, MOUSE
							   ),

	[_WNAV] = LAYOUT_split_3x5_2(
      W1,      W2,      W3,      W4,      W5,        W6,      W7,      W8,     W9,     W10,
      MWLEFT,  MWUP,    MWDOWN,  MWRIGHT, RUNAPP,    KC_NO,   WLEFT,   WDOWN,  WUP,    WRIGHT,
      TG_QWTY, ARRANGE, FULLSCN, RUNTERM, KC_LSFT,   KC_RSFT, KILLAPP, SCRPAD, RUNAPP, KC_NO,
			        KC_TRNS,  KC_TRNS,   KC_TRNS, KC_TRNS
								),

	[_FUN] = LAYOUT_split_3x5_2(
			KC_NO,   KC_NO,    KC_NO,    KC_NO,    KC_CAPS,      KC_F12,  KC_F7, KC_F8, KC_F9, KC_NO,
			OS_SHFT, OS_CMD,  OS_ALT,   OS_CTRL,   KC_ESC,       KC_F11,  KC_F4, KC_F5, KC_F6, KC_NO,
			KC_NO,   KC_NO,    KC_NO,    KC_NO,    KC_NO,        KC_F10,  KC_F1, KC_F2, KC_F3, KC_NO,
			                             KC_TRNS,  KC_TRNS,      KC_TRNS, KC_TRNS
								),
        [_MOUSE] = LAYOUT_split_3x5_2(
              KC_NO, KC_NO,        KC_NO,        KC_NO,        KC_NO,   KC_NO,      KC_MS_WH_LEFT,      KC_MS_WH_DOWN,KC_MS_WH_UP, KC_MS_WH_RIGHT, 
              KC_NO, KC_NO,        KC_MS_BTN2,   KC_MS_BTN1,   KC_NO,   KC_MS_BTN1, KC_MS_LEFT, KC_MS_DOWN, KC_MS_UP, KC_MS_RIGHT,
              KC_NO, KC_MS_ACCEL0, KC_MS_ACCEL1, KC_MS_ACCEL2, KC_NO,   KC_NO,      KC_NO,      KC_NO,      KC_NO,    KC_NO,  
                                                 KC_TRNS, KC_TRNS,      KC_TRNS, KC_TRNS
                                                               )
};

enum combo_events {
  // qwerty layer combos
  CAPS_COMBO_Q,
  ENTER_COMBO_Q,
  TAB_COMBO_Q,
  BSP_COMBO_Q,
  DEL_COMBO_Q,
  CTRLC_COMBO_Q,
  ESC_COMBO_Q,
  // braces
  LCBR_COMBO_Q,
  LPRN_COMBO_Q,
  LBRC_COMBO_Q,
  RCBR_COMBO_Q,
  RPRN_COMBO_Q,
  RBRC_COMBO_Q,
  // alternative braces
  LCBR_COMBO_Q2,
  LPRN_COMBO_Q2,
  RCBR_COMBO_Q2,
  RPRN_COMBO_Q2,
  // beakl layer combos
  //CAPS_COMBO_B,
  //ENTER_COMBO_B,
  //TAB_COMBO_B,
  //BSP_COMBO_B,
  //DEL_COMBO_B,
  //CTRLC_COMBO_B,
  //ESC_COMBO_B,
  //// braces
  //LCBR_COMBO_B,
  //LPRN_COMBO_B,
  //LBRC_COMBO_B,
  //RCBR_COMBO_B,
  //RPRN_COMBO_B,
  //RBRC_COMBO_B,
  // Other combos...
  COMBO_LENGTH
};
uint16_t COMBO_LEN = COMBO_LENGTH;
// qwerty combos
const uint16_t PROGMEM caps_combo_q[] = {KC_F, KC_J, COMBO_END};
const uint16_t PROGMEM enter_combo_q[] = {KC_J, KC_K, COMBO_END};
const uint16_t PROGMEM tab_combo_q[] = {KC_F, KC_D, COMBO_END};
const uint16_t PROGMEM bsp_combo_q[] = {KC_F, KC_S, COMBO_END};
const uint16_t PROGMEM del_combo_q[] = {KC_J, KC_L, COMBO_END};
// Ctrl-c combo mostly for Emacs
const uint16_t PROGMEM ctrlc_combo_q[] = {KC_J, KC_K, KC_L, COMBO_END};
const uint16_t PROGMEM esc_combo_q[] = {KC_D, KC_S, COMBO_END};
// beakl combos
//const uint16_t PROGMEM caps_combo_b[] = {KC_A, KC_S, COMBO_END};
//const uint16_t PROGMEM enter_combo_b[] = {KC_S, KC_T, COMBO_END};
//const uint16_t PROGMEM tab_combo_b[] = {KC_E, KC_A, COMBO_END};
//const uint16_t PROGMEM bsp_combo_b[] = {KC_I, KC_A, COMBO_END};
//const uint16_t PROGMEM del_combo_b[] = {KC_S, KC_N, COMBO_END};
//// braces - vertical combos
//const uint16_t PROGMEM lcbr_combo_b[] = {KC_O, KC_E, COMBO_END};
//const uint16_t PROGMEM lprn_combo_b[] = {KC_U, KC_A, COMBO_END};
//const uint16_t PROGMEM lbrc_combo_b[] = {KC_X, KC_DOT, COMBO_END};
//const uint16_t PROGMEM rcbr_combo_b[] = {KC_M, KC_T, COMBO_END};
//const uint16_t PROGMEM rprn_combo_b[] = {KC_C, KC_S, COMBO_END};
//const uint16_t PROGMEM rbrc_combo_b[] = {KC_G, KC_D, COMBO_END};
// braces qwerty
const uint16_t PROGMEM lcbr_combo_q[] = {KC_D, KC_E, COMBO_END}; // {
const uint16_t PROGMEM lcbr_combo_q2[] = {KC_E, KC_R, COMBO_END}; // {
const uint16_t PROGMEM lprn_combo_q[] = {KC_F, KC_R, COMBO_END}; // (
const uint16_t PROGMEM lprn_combo_q2[] = {KC_C, KC_V, COMBO_END}; // (
const uint16_t PROGMEM lbrc_combo_q[] = {KC_T, KC_G, COMBO_END}; // [
const uint16_t PROGMEM rcbr_combo_q[] = {KC_I, KC_K, COMBO_END}; // }
const uint16_t PROGMEM rcbr_combo_q2[] = {KC_I, KC_U, COMBO_END}; // }
const uint16_t PROGMEM rprn_combo_q[] = {KC_U, KC_J, COMBO_END}; // )
const uint16_t PROGMEM rprn_combo_q2[] = {KC_M, KC_COMM, COMBO_END}; // )
const uint16_t PROGMEM rbrc_combo_q[] = {KC_Y, KC_H, COMBO_END}; // ]

// Ctrl-c combo mostly for Emacs
const uint16_t PROGMEM ctrlc_combo_b[] = {KC_S, KC_T, KC_N, COMBO_END};
const uint16_t PROGMEM esc_combo_b[] = {KC_I, KC_E, KC_A, COMBO_END};

combo_t key_combos[] = {
  [CAPS_COMBO_Q] = COMBO_ACTION(caps_combo_q),
  [ENTER_COMBO_Q] = COMBO(enter_combo_q, KC_ENT),
  [TAB_COMBO_Q] = COMBO(tab_combo_q, KC_TAB),
  [BSP_COMBO_Q] = COMBO(bsp_combo_q, KC_BSPC),
  [DEL_COMBO_Q] = COMBO(del_combo_q, KC_DEL),
  [CTRLC_COMBO_Q] = COMBO(ctrlc_combo_q, LCTL(KC_C)),
  [ESC_COMBO_Q] = COMBO(esc_combo_q, KC_ESC),
  [LCBR_COMBO_Q] = COMBO(lcbr_combo_q, KC_LCBR),
  [LPRN_COMBO_Q] = COMBO(lprn_combo_q, KC_LPRN),
  [LBRC_COMBO_Q] = COMBO(lbrc_combo_q, KC_LBRC),
  [RCBR_COMBO_Q] = COMBO(rcbr_combo_q, KC_RCBR),
  [RPRN_COMBO_Q] = COMBO(rprn_combo_q, KC_RPRN),
  [RBRC_COMBO_Q] = COMBO(rbrc_combo_q, KC_RBRC),
  // alternative braces
  [LCBR_COMBO_Q2] = COMBO(lcbr_combo_q2, KC_LCBR),
  [LPRN_COMBO_Q2] = COMBO(lprn_combo_q2, KC_LPRN),
  [RCBR_COMBO_Q2] = COMBO(rcbr_combo_q2, KC_RCBR),
  [RPRN_COMBO_Q2] = COMBO(rprn_combo_q2, KC_RPRN),

  // Other combos...
  //[CAPS_COMBO_B] = COMBO_ACTION(caps_combo_b),
  //[ENTER_COMBO_B] = COMBO(enter_combo_b, KC_ENT),
  //[TAB_COMBO_B] = COMBO(tab_combo_b, KC_TAB),
  //[BSP_COMBO_B] = COMBO(bsp_combo_b, KC_BSPC),
  //[DEL_COMBO_B] = COMBO(del_combo_b, KC_DEL),
  //[CTRLC_COMBO_B] = COMBO(ctrlc_combo_b, LCTL(KC_C)),
  //[ESC_COMBO_B] = COMBO(esc_combo_b, KC_ESC),
  //[LCBR_COMBO_B] = COMBO(lcbr_combo_b, KC_LCBR),
  //[LPRN_COMBO_B] = COMBO(lprn_combo_b, KC_LPRN),
  //[LBRC_COMBO_B] = COMBO(lbrc_combo_b, KC_LBRC),
  //[RCBR_COMBO_B] = COMBO(rcbr_combo_b, KC_RCBR),
  //[RPRN_COMBO_B] = COMBO(rprn_combo_b, KC_RPRN),
  //[RBRC_COMBO_B] = COMBO(rbrc_combo_b, KC_RBRC),
};

void process_combo_event(uint16_t combo_index, bool pressed) {
  switch(combo_index) {
    case CAPS_COMBO_Q:
    //case CAPS_COMBO_B:
      if (pressed) {
        caps_word_set(true);  // Activate Caps Word!
      }
      break;

    // Other combos...
  }
}

// customize OS cancel keys here
bool is_oneshot_cancel_key(uint16_t keycode) {
    switch (keycode) {
	case CLEAR:
        case NUM:
        case SYM:
        case OS_RALT:
        case KC_RALT:
            return true;
        default:
           return false;
    }
}

// customize OS ignore keys here (you want your mods here)
bool is_oneshot_ignored_key(uint16_t keycode) {
    switch (keycode) {
	case CLEAR:
    case NUM:
    case SYM:
    case NAV_SPC:
    case MOUSE:
    case OS_SHFT:
    case OS_CTRL:
    case OS_ALT:
    case OS_RALT:
    case OS_SYM:
    case OS_CMD:
        return true;
    default:
        return false;
    }
}

// customize capsword, add ; as ignored (creates problem with SW klawa)
bool caps_word_press_user(uint16_t keycode) {
  switch (keycode) {
    // Keycodes that continue Caps Word, with shift applied.
    case KC_SCLN:
    case KC_A ... KC_Z:
      add_weak_mods(MOD_BIT(KC_LSFT));  // Apply shift to the next key.
      return true;

    // Keycodes that continue Caps Word, without shifting.
    case KC_1 ... KC_0:
    case KC_BSPC:
    case KC_MINS:
    case KC_UNDS:
    case KC_RALT:
      return true;

    default:
      return false;  // Deactivate Caps Word.
  }
}

// tap dance bits

// cur_dance is taken from qmk documentation
// it is called by every _finished tap dance function
// it allowes us to use more user-friendly status names
int cur_dance (qk_tap_dance_state_t *state) {
  if (state->count == 1) {
    if (state->interrupted || !state->pressed)  return SINGLE_TAP;
    //key has not been interrupted, but they key is still held. Means you want to send a 'HOLD'.
    else return SINGLE_HOLD;
  }
  else if (state->count == 2) {
    /*
     * DOUBLE_SINGLE_TAP is to distinguish between typing "pepper", and actually wanting a double tap
     * action when hitting 'pp'. Suggested use case for this return value is when you want to send two
     * keystrokes of the key, and not the 'double tap' action/macro.
    */
    if (state->interrupted) return DOUBLE_SINGLE_TAP;
    else if (state->pressed) return DOUBLE_HOLD;
    else return DOUBLE_TAP;
  }
  //Assumes no one is trying to type the same letter three times (at least not quickly).
  //If your tap dance key is 'KC_W', and you want to type "www." quickly - then you will need to add
  //an exception here to return a 'TRIPLE_SINGLE_TAP', and define that enum just like 'DOUBLE_SINGLE_TAP'
  if (state->count == 3) {
    if (state->interrupted || !state->pressed)  return TRIPLE_TAP;
    else return TRIPLE_HOLD;
  }
  else return 8; //magic number. At some point this method will expand to work for more presses
}

//instanalize an instance of 'tap' for the 'shiftalt' tap dance.
static tap shiftralttap_state = {
  .is_press_action = true,
  .state = 0
};

oneshot_state os_shft_state = os_up_unqueued;
oneshot_state os_ralt_state = os_up_unqueued;

void shiftralt_finished (qk_tap_dance_state_t *state, void *user_data) {
  shiftralttap_state.state = cur_dance(state);
  keyrecord_t record = { .event.pressed = true };

  switch (shiftralttap_state.state) {
    case SINGLE_TAP: 
                       update_oneshot(&os_ralt_state, KC_RALT, OS_RALT,
                                   OS_RALT, &record, false);
                      break;
    case SINGLE_HOLD: register_code(KC_RALT); break;
    case DOUBLE_SINGLE_TAP: 
    case DOUBLE_TAP: 
                      update_oneshot(&os_shft_state, KC_LSFT, OS_SHFT,
                                   OS_SHFT, &record, false); 
                      break;
    case DOUBLE_HOLD: register_code(KC_LSFT); break;
    //Last case is for fast typing. Assuming your key is `f`:
    //For example, when typing the word `buffer`, and you want to make sure that you send `ff` and not `Esc`.
    //In order to type `ff` when typing fast, the next character will have to be hit within the `TAPPING_TERM`, which by default is 200ms.
  }
}

void shiftralt_reset (qk_tap_dance_state_t *state, void *user_data) {
  keyrecord_t record = { .event.pressed = false };
  switch (shiftralttap_state.state) {
    case SINGLE_TAP:
                    ;
                    update_oneshot(&os_ralt_state, KC_RALT, OS_RALT,
                                   OS_RALT, &record, false);
                    break;
    case SINGLE_HOLD: unregister_code(KC_RALT); break;
    case DOUBLE_SINGLE_TAP: 
    case DOUBLE_TAP: 
                      ;
                      update_oneshot(&os_shft_state, KC_LSFT, OS_SHFT,
                                   OS_SHFT, &record, false); 
                      break;
    case DOUBLE_HOLD: unregister_code(KC_LSFT);
    
  }
  shiftralttap_state.state = 0;
}

qk_tap_dance_action_t tap_dance_actions[] = {
  [DANCE_SHIFTRALT]     = ACTION_TAP_DANCE_FN_ADVANCED(NULL,shiftralt_finished, shiftralt_reset)
};

// tap dance code end

// key override start

// alt_wnav_override allowes me to press NAV_SPC+RALT_TD_RSFT or RALT_TD_RSFT+NAV_SPC to switch to 
// _WNAV (window navigation layer). Without override only NAV_SPC+RALT_TD_RSFT works.

// This is called when the override activates and deactivates. Enable the fn layer on activation and disable on deactivation
bool momentary_layer(bool key_down, void *layer) {
    if (key_down) {
        layer_on((uint8_t)(uintptr_t)layer);
    } else {
        layer_off((uint8_t)(uintptr_t)layer);
    }

    return false;
}

const key_override_t alt_wnav_override = {.trigger_mods     = MOD_BIT(KC_RALT),
                                    .layers                 = ~0,
                                    .trigger                = NAV_SPC,
                                    .suppressed_mods        = MOD_BIT(KC_RALT),
                                    .options                = ko_option_no_unregister_on_other_key_down,
                                    //.negative_mod_mask      = (uint8_t) ~(MOD_BIT(KC_RALT)),
                                    .custom_action          = momentary_layer,
                                    .context                = (void *)_WNAV,
                                    .replacement            = KC_NO,
                                    .enabled                = NULL};


// This globally defines all key overrides to be used
const key_override_t **key_overrides = (const key_override_t *[]){
	&alt_wnav_override,
	NULL // Null terminate the array of overrides!
};
// key override end

bool sw_app_active = false;

oneshot_state os_ctrl_state = os_up_unqueued;
oneshot_state os_alt_state = os_up_unqueued;
oneshot_state os_cmd_state = os_up_unqueued;
oneshot_state os_sym_state = os_up_unqueued;


bool process_record_user(uint16_t keycode, keyrecord_t* record) {
	if (!process_caps_word(keycode, record)) { return false; }

	update_swapper(
				   &sw_app_active, KC_LGUI, KC_TAB, SW_APP,
				   keycode, record
				   );
	update_oneshot(
				   &os_ctrl_state, KC_LCTL, OS_CTRL,
				   keycode, record, false
				   );
	update_oneshot(
				   &os_alt_state, KC_LALT, OS_ALT,
				   keycode, record, false
				   );
	update_oneshot(
				   &os_cmd_state, KC_LCMD, OS_CMD,
				   keycode, record, false
				   );

	switch (keycode) {

		case CLEAR:
			clear_oneshot_mods();
			if (get_oneshot_layer() != 0) {
				clear_oneshot_layer_state(ONESHOT_OTHER_KEY_PRESSED);
			}
			layer_move(_KLW);
			return false;

                // support sending oneshot RAlt, the only code needed is in this case statement
                case RSFT_TRALT:
                        if (record->tap.count) {
                              // there must be a better way ... but this works ;-)
                              update_oneshot(&os_ralt_state, KC_RALT, OS_RALT,
                                   OS_RALT, record, false);
                              return false;        // Return false to ignore further processing of key
                        }
                        break;
                case NUM:
                        if (record->tap.count) {
                              // there must be a better way ... but this works ;-)
                              update_oneshot(&os_shft_state, KC_LSFT, OS_SHFT,
                                   OS_SHFT, record, false);
                              return false;        // Return false to ignore further processing of key
                        }
                        break;

                // enable oneshot layer switch on hold
                case SYM:
                        if (!record->tap.count) {
                            update_oneshot(&os_sym_state, _SYM, OS_SYM,
                                   OS_SYM, record, true);
                            return false;
                        } else {
                            if (record->tap.count > 1 && record->event.pressed) { // tap & hold
                                register_code(KC_BSPC);
                                return false;
                            } else if (record->tap.count > 1) {
                                unregister_code(KC_BSPC);
                                return false;
                            }
                        }
                        break;
                case TD(DANCE_SHIFTRALT):
                case DANCE_SHIFTRALT:
                        break;
                default:
                          update_oneshot(&os_ralt_state, KC_RALT, OS_RALT,
                                         keycode, record, false);
                          update_oneshot(&os_shft_state, KC_LSFT, OS_SHFT,
				         keycode, record, false);
                          update_oneshot(&os_sym_state, _SYM, OS_SYM,
                                         keycode, record, true);
	}

	return true;
}

/* layer_state_t layer_state_set_user(layer_state_t state) { */
/*     return update_tri_layer_state(state, _LMOD, _RMOD, _NUM); */
/* } */
