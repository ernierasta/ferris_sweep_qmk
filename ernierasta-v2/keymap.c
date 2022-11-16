#include QMK_KEYBOARD_H
#include "features/achordion.h"

// this file is for swoop (3 thumb keys) and
// based on this, sweep (2 thumb keys) is generated

// external libraries:
// - achordion - better mod/tap decisions, based on 2nd key pressed
// https://getreuer.info/posts/keyboards/achordion/index.html

enum layers {
    _QWERTY,
    _MOVE,
    _NUMBER,
    _FLAYER,
    _SYMBOL
};

#define X_NUM LT(_NUMBER, KC_X)
#define DOT_FLAYER LT(_FLAYER, KC_DOT)
#define S_LCTL LCTL_T(KC_S)
#define L_RCTL LCTL_T(KC_L)
#define SLSH_LALT LALT_T(KC_SLSH)
#define Z_LALT LALT_T(KC_Z)
#define ENT_RALT RALT_T(KC_ENT)
#define SPC_MOVE LT(_MOVE, KC_SPC)
#define ENT_SYM LT(_SYMBOL, KC_ENT)
#define BSPC_SYM LT(_SYMBOL, KC_BSPC)

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
/*
 * QWERTY
 * ,---------------------------------.     ,----------------------------------.
 * |  Q  |   W  |   E  |   R  |   T  |     |   Y  |   U  |   I  |   O  |   P  |
 * |-----+------+------+------+------|     |------+------+------+------+------|
 * |  A  |   S  |   D  |   F  |   G  |     |   H  |   J  |   K  |   L  |   ;  |
 * |-----+------+------+------+------|     ,------+------+------+------+------|
 * |  Z  |   X  |   C  |   V  |   B  |     |   N  |   M  |   ,  |   .  |   /  |
 * `------------+------+------+------|     |------+------+------+-------------'
 *              | LCTL | BSpc | Esc  |     | Ent  | Spc  | LAlt |
 *              `--------------------'     `--------------------'
 */

    [_QWERTY] = LAYOUT(
      KC_Q,           KC_W, KC_E, KC_R, KC_T,           KC_Y,    KC_U,    KC_I,      KC_O,   S(KC_P),
      LSFT_T(KC_A), S_LCTL, KC_D, KC_F, KC_G,           KC_H,    KC_J,    KC_K,     L_RCTL, RSFT_T(KC_SCLN),
      Z_LALT,        X_NUM, KC_C, KC_V, KC_B,           KC_N,    KC_M, KC_COMM, DOT_FLAYER, SLSH_LALT,
                           ENT_SYM, SPC_MOVE,           ENT_RALT, BSPC_SYM
    ),
    [_MOVE] = LAYOUT(
            ___,     LSA(KC_A), ___,     ___,     KC_DEL,        KC_INS, KC_HOME, KC_PGDN, KC_PGUP, KC_END,
            KC_LSFT, KC_LGUI,   KC_LALT, KC_LCTL, ___,           KC_INS, KC_LEFT, KC_DOWN, KC_UP, KC_RIGHT,
            C(KC_Z), C(KC_X),   C(KC_C), ___,     ___,           KC_BTN2, KC_MS_L, KC_MS_D, KC_MS_U, KC_MS_R,
                                         ___,     ___,           KC_BTN1, KC_BTN3
            ),
    [_NUMBER] = LAYOUT(
            KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,    KC_PLUS,    KC_7, KC_8, KC_9, KC_MINS,
            KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,        ___,    KC_4, KC_5, KC_6, KC_EQL,
            KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,        ___,    KC_1, KC_2, KC_3, ___,
                                       KC_TRNS, KC_TRNS,        KC_0,  KC_DOT
            ), // _NUMBER layer broken to 2 layers to prevent rollover accidental trigerring
    [_FLAYER] = LAYOUT(
            ___, KC_F7, KC_F8, KC_F9, KC_F12,    KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
            ___, KC_F4, KC_F5, KC_F6, KC_F11,    KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
            ___, KC_F1, KC_F2, KC_F3, KC_F10,    KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
                                 ___,    ___,    KC_TRNS, KC_TRNS
            ),
    [_SYMBOL] = LAYOUT(
            KC_EXLM, KC_AT,   KC_HASH, KC_DLR,  KC_PERC,    KC_PIPE, KC_AMPR, KC_ASTR, KC_CIRC, KC_MINS, 
            KC_UNDS, KC_LCBR, KC_LBRC, KC_LPRN, KC_TILD,    KC_EQL,  KC_RPRN, KC_RBRC, KC_RCBR, KC_P,
            ___,     ___,     KC_QUOT, KC_DQT,  KC_GRAVE,   ___,      KC_EQL,     ___,     ___, KC_BSLS,
                                          ___,       ___,   ___, ___
            )
};

// Combos settings
enum combos {
    ESC_Q,
    TAB_Q,
    CAP_Q,
    COMBO_LENGTH
};

uint16_t COMBO_LEN = COMBO_LENGTH;

const uint16_t PROGMEM esc_q[] = {S_LCTL, KC_D, COMBO_END};
const uint16_t PROGMEM tab_q[] = {KC_D, KC_F, COMBO_END};
const uint16_t PROGMEM cap_q[] = {KC_F, KC_J, COMBO_END};

combo_t key_combos[] = {
    [ESC_Q] = COMBO(esc_q, KC_ESC),
    [TAB_Q] = COMBO(tab_q, KC_TAB),
    [CAP_Q] = COMBO(cap_q, CAPSWRD)
};

// CAPSWORD setttings

#undef CAPS_WORD_IDLE_TIMEOUT
#define CAPS_WORD_IDLE_TIMEOUT 10000

bool caps_word_press_user(uint16_t keycode) {
    switch (keycode) {
        // Keycodes that continue Caps Word, with shift applied.
        case KC_A ... KC_Z:
        case KC_MINS:
        case KC_SCLN:
            add_weak_mods(MOD_BIT(KC_LSFT));  // Apply shift to next key.
            return true;

        // Keycodes that continue Caps Word, without shifting.
        case KC_1 ... KC_0:
        case KC_BSPC:
        case KC_DEL:
        case KC_UNDS:
            return true;

        default:
            return false;  // Deactivate Caps Word.
    }
}

// achordion - better tap/hold detection (fixes rolls like oi io, where o is ctrl and i is shift, klawa layout)

void matrix_scan_user(void) {
  achordion_task();
}

bool achordion_chord(uint16_t tap_hold_keycode,
                     keyrecord_t* tap_hold_record,
                     uint16_t other_keycode,
                     keyrecord_t* other_record) {
  // exceptions defined here
  // we need f.e. LALT to work for both sides
  switch (tap_hold_keycode) {
    case ENT_RALT:
    case SPC_MOVE:
    case BSPC_SYM:
    case ENT_SYM:
      return true;
      break;
  }


  // Also allow same-hand holds when the other key is in the rows below the
  // alphas. I need the `% (MATRIX_ROWS / 2)` because my keyboard is split.
  //
  // this is for some reason not working for sweep, it would be ideal
  //if (other_record->event.key.row % (MATRIX_ROWS / 2) >= 4) { return true; }

  // Otherwise, follow the opposite hands rule.
  return achordion_opposite_hands(tap_hold_record, other_record);
}


bool process_record_user(uint16_t keycode, keyrecord_t* record) {
  if (!process_achordion(keycode, record)) { return false; }
  // Your macros ...

  return true;
}

