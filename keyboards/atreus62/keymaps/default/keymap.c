// this is the style you want to emulate.
// This is the canonical layout file for the Quantum project. If you want to add another keyboard,

#include QMK_KEYBOARD_H

// Each layer gets a name for readability, which is then used in the keymap matrix below.
// The underscores don't mean anything - you can have a layer called STUFF or any other name.
// Layer names don't all need to be of the same length, obviously, and you can also skip them
// entirely and just use numbers.
#define _BS 0
#define _DG 1
#define _FN 2

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
  [_BS] = LAYOUT( /* [> QWERTY <] */
              KC_1,   KC_2,   KC_3,        KC_4,       KC_5,                           KC_6,          KC_7,           KC_8,     KC_9,   KC_0,
    KC_ESC,   KC_Q,   KC_W,   KC_E,        KC_R,       KC_T,                           KC_Y,          KC_U,           KC_I,     KC_O,   KC_P,   KC_ENT,
    KC_TAB,   KC_A,   KC_S,LALT_T(KC_D),LSFT_T(KC_F),  KC_G,                           KC_H,          RSFT_T(KC_J),RALT_T(KC_K),KC_L,   KC_SCLN,KC_QUOT,
    S(KC_TAB),KC_Z,   KC_X,   KC_C,        KC_V,       KC_B,                           KC_N,          KC_M,           KC_COMM,  KC_DOT, KC_SLSH,KC_BSLS,
              C(KC_C),C(KC_V),KC_CAPS,  LT(_DG,KC_DEL),LCTL_T(KC_SPC), KC_LCTL,KC_RCTL,RCTL_T(KC_SPC),LT(_DG,KC_BSPC),KC_PSCR,  KC_HOME,KC_END,
                                                                       KC_LGUI,KC_RGUI
  ),
  [_DG] = LAYOUT(
            KC_EXLM,KC_AT,  KC_HASH,KC_DLR, KC_PERC,                KC_CIRC,KC_AMPR,   KC_ASTR,   KC_LPRN,   KC_RPRN,
    _______,KC_TILD,KC_GRV, KC_UP,  KC_MINS,KC_UNDS,                KC_RCBR,KC_LCBR,   S(KC_UP),  KC_EQL,    KC_PLUS,_______,
    KC_PGUP,C(KC_A),KC_LEFT,KC_DOWN,KC_RGHT,KC_LPRN,                KC_RPRN,S(KC_LEFT),S(KC_DOWN),S(KC_RGHT),KC_COLN,KC_DQUO,
    KC_PGDN,C(KC_Z),C(KC_X),C(KC_C),C(KC_V),TG(_FN),                KC_RBRC,KC_LBRC,   KC_LABK,   KC_RABK,   KC_QUES,KC_PIPE,
            XXXXXXX,XXXXXXX,XXXXXXX,_______,_______,_______,_______,_______,_______,   _______,   _______,   _______,
                                                    _______,_______
  ),
  [_FN] = LAYOUT(
            XXXXXXX,XXXXXXX,XXXXXXX,XXXXXXX,XXXXXXX,                XXXXXXX,XXXXXXX,XXXXXXX,XXXXXXX,XXXXXXX,
    TO(_BS),KC_F1,  KC_F2,  KC_F3,  KC_F4,  XXXXXXX,                KC_PSLS,KC_P7,  KC_P8,  KC_P9,  KC_PMNS,_______,
    _______,KC_F5,  KC_F6,  KC_F7,  KC_F8,  KC_VOLU,                KC_PAST,KC_P4,  KC_P5,  KC_P6,  KC_PPLS,S(KC_HOME),
    _______,KC_F9,  KC_F10, KC_F11, KC_F12, KC_VOLD,                KC_PEQL,KC_P1,  KC_P2,  KC_P3,  KC_PENT,S(KC_END),
            XXXXXXX,XXXXXXX,XXXXXXX,TO(_BS),_______,_______,_______,_______,KC_P0,  KC_PDOT,_______,_______,
                                                    _______,_______
  )
};

enum combo_events {
  DAUL_ALT,
  DAUL_CTRL
};

const uint16_t PROGMEM altalt_combo[] = {KC_LALT, KC_RALT, COMBO_END};
const uint16_t PROGMEM ctrlctrl_combo[] = {KC_LCTL, KC_RCTL, COMBO_END};

combo_t key_combos[COMBO_COUNT] = {
  [DAUL_ALT] = COMBO(altalt_combo, KC_LGUI),
  [DAUL_CTRL] = COMBO_ACTION(ctrlctrl_combo)
};

void process_combo_event(uint16_t combo_index, bool pressed) {
  switch(combo_index) {
    case DAUL_CTRL:
      if (pressed) {
          tap_code(KC_LSFT);
      }
      break;
  }
}
