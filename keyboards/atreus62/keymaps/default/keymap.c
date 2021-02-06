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
            KC_1,   KC_2,   KC_3,   KC_4,   KC_5,                   KC_6,   KC_7,   KC_8,   KC_9,   KC_0,
    KC_TAB, KC_Q,   KC_W,   KC_E,   KC_R,   KC_T,                   KC_Y,   KC_U,   KC_I,   KC_O,   KC_P,   KC_ENT,
    KC_ESC, KC_A,   KC_S,   KC_D,   KC_F,   KC_G,                   KC_H,   KC_J,   KC_K,   KC_L,   KC_SCLN,KC_QUOT,
    KC_PSCR,KC_Z,   KC_X,   KC_C,   KC_V,   KC_B,                   KC_N,   KC_M,   KC_COMM,KC_DOT, KC_SLSH,KC_PGDN,
            KC_ESC, KC_TAB, KC_LGUI,MO(_DG),KC_BSPC,KC_LCTL,KC_LALT,KC_SPC, MO(_DG),KC_MINS,KC_EQL, KC_ENT,
                                                    KC_LGUI,KC_LSFT
  ),
  [_DG] = LAYOUT( /* [> RAISE <] */
            XXXXXXX,XXXXXXX,XXXXXXX,XXXXXXX,XXXXXXX,                XXXXXXX,XXXXXXX,KC_PSLS,KC_PAST,KC_BSPC,
    XXXXXXX,KC_EXLM,KC_AT,  KC_UP,  KC_LCBR,KC_RCBR,                KC_PGUP,KC_7,   KC_8,   KC_9,   KC_PMNS,XXXXXXX,
    TG(_FN),KC_HASH,KC_LEFT,KC_DOWN,KC_RGHT,KC_DLR,                 KC_PGDN,KC_4,   KC_5,   KC_6,   KC_PPLS,TG(_FN),
    XXXXXXX,KC_LBRC,KC_RBRC,KC_LPRN,KC_RPRN,KC_AMPR,                KC_GRV, KC_1,   KC_2,   KC_3,   KC_PEQL,XXXXXXX,
            KC_PSCR,KC_INS, KC_LGUI,_______,_______,_______,_______,_______,KC_0,   KC_COMM,KC_DOT, KC_EQL,
                                                    _______,_______
  ),
  [_FN] = LAYOUT(
            XXXXXXX,XXXXXXX,XXXXXXX,XXXXXXX,XXXXXXX,                XXXXXXX,KC_F10, KC_F11, KC_F12, XXXXXXX,
    XXXXXXX,KC_INS, KC_HOME,KC_UP,  KC_END, KC_PGUP,                _______,KC_F7,  KC_F8,  KC_F9,  XXXXXXX,XXXXXXX,
    XXXXXXX,KC_DEL, KC_LEFT,KC_DOWN,KC_RGHT,KC_PGDN,                _______,KC_F4,  KC_F5,  KC_F6,  XXXXXXX,XXXXXXX,
    XXXXXXX,XXXXXXX,KC_VOLU,XXXXXXX,XXXXXXX,  RESET,                XXXXXXX,KC_F1,  KC_F2,  KC_F3,  XXXXXXX,XXXXXXX,
            XXXXXXX,KC_VOLD,_______,TO(_BS),_______,_______,_______,_______,TO(_BS),KC_PSCR,KC_SLCK,KC_PAUS,
                                                    _______,_______
  )
};
