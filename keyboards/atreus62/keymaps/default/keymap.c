// this is the style you want to emulate.
// This is the canonical layout file for the Quantum project. If you want to add another keyboard,

#include QMK_KEYBOARD_H

// Each layer gets a name for readability, which is then used in the keymap matrix below.
// The underscores don't mean anything - you can have a layer called STUFF or any other name.
// Layer names don't all need to be of the same length, obviously, and you can also skip them
// entirely and just use numbers.
enum atreus60_layers {
    _BS,
    _BD,
    _SD,
    _PN,
    _FN,
    _GM
};

// #define LT(layer, kc) (QK_LAYER_TAP | (((layer)&0xF) << 8) | ((kc)&0xFF))
// #define LM(layer, mod) (QK_LAYER_MOD | (((layer)&0xF) << 4) | ((mod)&0xF))
#define CT_D LCTL_T(KC_D)
#define ST_F LSFT_T(KC_F)
#define ST_J RSFT_T(KC_J)
#define CT_K RCTL_T(KC_K)
#define LT_BSPC LT(_SD, KC_BSPC)
#define LT_LSPC LT(_BD, KC_SPC)
#define LT_RSPC LT(_PN, KC_SPC)
#define LT_DEL  LT(_PN, KC_DEL)

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
  [_BS] = LAYOUT( /* [> QWERTY <] */
            KC_1,   KC_2,   KC_3,   KC_4,   KC_5,                          KC_6,   KC_7,   KC_8,   KC_9,   KC_0,
    KC_GESC,KC_Q,   KC_W,   KC_E,   KC_R,   KC_T,                          KC_Y,   KC_U,   KC_I,   KC_O,   KC_P,   KC_ENT,
    KC_TAB, KC_A,   KC_S,   CT_D,   ST_F,   KC_G,                          KC_H,   ST_J,   CT_K,   KC_L,   KC_SCLN,KC_QUOT,
    C(KC_X),KC_Z,   KC_X,   KC_C,   KC_V,   KC_B,                          KC_N,   KC_M,   KC_COMM,KC_DOT, KC_SLSH,KC_BSLS,
            C(KC_C),C(KC_V),KC_CAPS,LT_BSPC,LT_LSPC,KC_LCTL,RALT_T(KC_ENT),LT_RSPC,LT_DEL, KC_PSCR,XXXXXXX,TO(_BS),
                                              GUI_T(KC_APP),KC_RSFT
  ),
  [_BD] = LAYOUT(
            XXXXXXX,XXXXXXX,XXXXXXX,XXXXXXX,XXXXXXX,                XXXXXXX,XXXXXXX,XXXXXXX,XXXXXXX,TO(_GM),
    TG(_FN),XXXXXXX,KC_GRV, KC_UP,  KC_MINS,KC_EQL,                 _______,_______,_______,_______,_______,_______,
    KC_TAB ,KC_HOME,KC_LEFT,KC_DOWN,KC_RGHT,KC_END,                 _______,_______,_______,_______,_______,_______,
    XXXXXXX,XXXXXXX,XXXXXXX,XXXXXXX,XXXXXXX,XXXXXXX,                _______,_______,_______,_______,_______,_______,
            _______,_______,_______,_______,_______,_______,_______,TO(_BS),_______,_______,_______,_______,
                                                    _______,_______
  ),
  [_SD] = LAYOUT(
             XXXXXXX,   XXXXXXX,   XXXXXXX,   XXXXXXX,   XXXXXXX,                   XXXXXXX,XXXXXXX,XXXXXXX,XXXXXXX,TO(_GM),
  TG(_FN),   XXXXXXX,   KC_TILD,   S(KC_UP),  KC_UNDS,   KC_PLUS,                   _______,_______,_______,_______,_______,_______,
  S(KC_TAB), S(KC_HOME),S(KC_LEFT),S(KC_DOWN),S(KC_RGHT),S(KC_END),                 _______,_______,_______,_______,_______,_______,
  XXXXXXX,   XXXXXXX,   XXXXXXX,   XXXXXXX,   XXXXXXX,   XXXXXXX,                   _______,_______,_______,_______,_______,_______,
             _______,   _______,   _______,   _______,   _______,   _______,_______,TO(_BS),_______,_______,_______,_______,
                                                                    _______,_______
  ),
  [_PN] = LAYOUT(
            XXXXXXX,XXXXXXX,XXXXXXX,XXXXXXX,XXXXXXX,                XXXXXXX,XXXXXXX,XXXXXXX,XXXXXXX,XXXXXXX,
    XXXXXXX,XXXXXXX,KC_GRV, KC_MINS,KC_EQL, XXXXXXX,                XXXXXXX,KC_PLUS,KC_UNDS,KC_TILD,XXXXXXX,XXXXXXX,
    XXXXXXX,KC_EXLM,KC_AT,  KC_HASH,KC_DLR, XXXXXXX,                XXXXXXX,KC_PERC,KC_CIRC,KC_AMPR,KC_ASTR,XXXXXXX,
    XXXXXXX,XXXXXXX,KC_LCBR,KC_LBRC,KC_LPRN,XXXXXXX,                XXXXXXX,KC_RPRN,KC_RBRC,KC_RCBR,XXXXXXX,XXXXXXX,
            _______,_______,_______,_______,_______,_______,_______,TO(_BS),_______,_______,_______,_______,
                                                    _______,_______
  ),
  [_FN] = LAYOUT(
            XXXXXXX,XXXXXXX,XXXXXXX,XXXXXXX,XXXXXXX,                XXXXXXX,XXXXXXX,XXXXXXX,XXXXXXX,XXXXXXX,
    XXXXXXX,KC_F9,  KC_F10, KC_F11, KC_F12, KC_MUTE,                KC_PSLS,KC_P7,  KC_P8,  KC_P9,  KC_PMNS,XXXXXXX,
    KC_BRIU,KC_F5,  KC_F6,  KC_F7,  KC_F8,  KC_VOLU,                KC_PAST,KC_P4,  KC_P5,  KC_P6,  KC_PPLS,C(KC_PLUS),
    KC_BRID,KC_F1,  KC_F2,  KC_F3,  KC_F4,  KC_VOLD,                KC_NLCK,KC_P1,  KC_P2,  KC_P3,  KC_PENT,C(KC_MINS),
            XXXXXXX,XXXXXXX,XXXXXXX,KC_BSPC,TO(_BS),_______,_______,TO(_BS),KC_P0,  KC_PDOT,XXXXXXX,XXXXXXX,
                                                    _______,_______
  ),
  [_GM] = LAYOUT( /* [> QWERTY <] */
            KC_1,   KC_2,   KC_3,   KC_4,   KC_5,                   KC_6,   KC_7,   KC_8,   KC_9,   KC_0,
    KC_GESC,KC_Q,   KC_W,   KC_E,   KC_R,   KC_T,                   KC_Y,   KC_U,   KC_I,   KC_O,   KC_P,   XXXXXXX,
    KC_TAB, KC_A,   KC_S,   KC_D,   KC_F,   KC_G,                   KC_H,   KC_J,   KC_K,   KC_L,   KC_SCLN,KC_QUOT,
    KC_ENT, KC_Z,   KC_X,   KC_C,   KC_V,   KC_B,                   KC_N,   KC_M,   KC_COMM,KC_DOT, KC_SLSH,KC_BSLS,
            XXXXXXX,XXXXXXX,XXXXXXX,KC_BSPC,KC_SPC, _______,_______,TO(_BS),KC_DEL, KC_PSCR,XXXXXXX,XXXXXXX,
                                                    _______,_______
  )
};

// LT() Retro Tapping Setting Here.
bool get_retro_tapping(uint16_t keycode, keyrecord_t *record) {
    switch (keycode) {
    case RALT_T(KC_ENT):
    case GUI_T(KC_APP):
    case LT_BSPC:
    case LT_DEL:
        return false;
    default:
        return true;
    }
}

void post_process_record_user(uint16_t keycode, keyrecord_t *record) {
    led_t led_state = host_keyboard_led_state();
    switch (keycode) {
    case LT_BSPC:
        if (record->event.pressed) {
            update_tri_layer(_SD, _PN, _FN);
            backlight_enable();
        } else {
            if (IS_LAYER_OFF(_FN)) backlight_disable();
        }
        break;
    case LT_DEL:
        if (record->event.pressed) { update_tri_layer(_SD, _PN, _FN); }
        break;
    case KC_CAPS:
        if (!record->event.pressed) { writePin(B0, !led_state.caps_lock); }
        break;
    case KC_NLCK:
        if (!record->event.pressed) { writePin(B0, !led_state.num_lock); }
        break;
    }
}

layer_state_t layer_state_set_user(layer_state_t state) {
    led_t led_state = host_keyboard_led_state();
    switch (get_highest_layer(state)) {
    case _FN:
        backlight_enable();
        writePin(B0, !led_state.num_lock);
        break;
    default: //  for any other layers, or the default layer
        backlight_disable();
        writePin(B0, !led_state.caps_lock);
        break;
    }
  return state;
}

// 自定義按鍵
// 在此設定
// enum atreus60_keycodes {
//     MY_LSPC = SAFE_RANGE,
//     MY_RSPC
// };

// 自定義併擊
// 在此設定
// enum combo_events {
//   DAUL_ALT,
//   DAUL_CTRL
// };

// const uint16_t PROGMEM altalt_combo[] = {KC_LALT, KC_RALT, COMBO_END};
// const uint16_t PROGMEM ctrlctrl_combo[] = {KC_LCTL, KC_RCTL, COMBO_END};

// combo_t key_combos[COMBO_COUNT] = {
//   [DAUL_ALT] = COMBO_ACTION(altalt_combo),
//   [DAUL_CTRL] = COMBO(ctrlctrl_combo, KC_LSFT)
// };

// void process_combo_event(uint16_t combo_index, bool pressed) {
//   switch(combo_index) {
//     case DAUL_ALT:
//       if (pressed) {
//           tap_code(KC_LGUI);
//       }
//       break;
//   }
// }
