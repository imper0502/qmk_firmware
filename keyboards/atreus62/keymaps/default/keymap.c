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
    KC_TAB, KC_Q,   KC_W,   KC_E,   KC_R,   KC_T,                   KC_Y,   KC_U,   KC_I,   KC_O,   KC_P,   KC_PGUP,
    KC_ESC, KC_A,   KC_S,   KC_D,   KC_F,   KC_G,                   KC_H,   KC_J,   KC_K,   KC_L,   KC_SCLN,KC_QUOT,
    KC_PSCR,KC_Z,   KC_X,   KC_C,   KC_V,   KC_B,                   KC_N,   KC_M,   KC_COMM,KC_DOT, KC_SLSH,KC_PGDN,
            KC_ESC, KC_TAB, KC_LGUI,KC_LSFT,KC_BSPC,KC_LCTL,KC_LALT,KC_SPC, MO(_DG),KC_MINS,KC_EQL, KC_ENT,
                                                    KC_LCTL,KC_LALT
  ),
  /*
   *    !       @     up     {    }        ||     pgup    7     8     9    *
   *    #     left   down  right  $        ||     pgdn    4     5     6    +
   *    [       ]      (     )    &        ||       `     1     2     3    \
   *    FN2   insert super shift bksp ctrl || alt space   fn    .     0    =
   */
  [_DG] = LAYOUT( /* [> RAISE <] */
            _______,_______,_______,_______,_______,                _______,_______,_______,_______,_______,
    _______,KC_EXLM,KC_AT,  KC_UP,  KC_LCBR,KC_RCBR,                KC_PGUP,KC_7,   KC_8,   KC_9,   KC_ASTR,_______,
    _______,KC_HASH,KC_LEFT,KC_DOWN,KC_RGHT,KC_DLR,                 KC_PGDN,KC_4,   KC_5,   KC_6,   KC_PLUS,_______,
    _______,KC_LBRC,KC_RBRC,KC_LPRN,KC_RPRN,KC_AMPR,                KC_GRV, KC_1,   KC_2,   KC_3,   KC_BSLS,_______,
            TG(_FN),KC_INS, KC_LGUI,KC_LSFT,KC_BSPC,KC_LCTL,KC_LALT,KC_SPC, _______,KC_DOT, KC_0,   KC_EQL,
                                                    _______,_______
  ),
  /*
   *    insert home   up  end   pgup       ||      up     F7    F8    F9   F10
   *     del   left  down right pgdn       ||     down    F4    F5    F6   F11
   *          volup             reset      ||             F1    F2    F3   F12
   *          voldn  super shift bksp ctrl || alt space   L0  prtsc scroll pause
   */
  [_FN] = LAYOUT(
            _______,_______,_______,_______,_______,                _______,KC_F10, KC_F11, KC_F12, _______,
    _______,KC_INS, KC_HOME,KC_UP,  KC_END, KC_PGUP,                KC_UP,  KC_F7,  KC_F8,  KC_F9,  _______,_______,
    _______,KC_DEL, KC_LEFT,KC_DOWN,KC_RGHT,KC_PGDN,                KC_DOWN,KC_F4,  KC_F5,  KC_F6,  _______,_______,
    _______,KC_NO,  KC_VOLU,KC_NO,  KC_NO,  RESET,                  KC_NO,  KC_F1,  KC_F2,  KC_F3,  _______,_______,
            KC_NO,  KC_VOLD,KC_LGUI,KC_LSFT,KC_BSPC,KC_LCTL,KC_LALT,KC_SPC, TO(_BS),KC_PSCR,KC_SLCK,KC_PAUS,
                                                    _______,_______
  )
};
