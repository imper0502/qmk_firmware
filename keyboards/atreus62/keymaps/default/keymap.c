// this is the style you want to emulate.
// This is the canonical layout file for the Quantum project. If you want to add another keyboard,

#include QMK_KEYBOARD_H

// Each layer gets a name for readability, which is then used in the keymap matrix below.
// The underscores don't mean anything - you can have a layer called STUFF or any other name.
// Layer names don't all need to be of the same length, obviously, and you can also skip them
// entirely and just use numbers.
enum atreus60_layers {
    _BS,
    _LT,
    _RT,
    _TP,
    _GM
};

// 自定義按鍵在此設定
// #define LT(layer, kc) (QK_LAYER_TAP | (((layer)&0xF) << 8) | ((kc)&0xFF))
// #define LM(layer, mod) (QK_LAYER_MOD | (((layer)&0xF) << 4) | ((mod)&0xF))
enum atreus60_keycodes {
    CPY_PST = SAFE_RANGE,
    ALT_LCK,
    CTL_LCK,
    SFT_LCK,
    LCK_CLR
};
bool is_alt_lock = false;
bool is_ctrl_lock = false;
bool is_shift_lock = false;
#define CT_D LCTL_T(KC_D)
#define ST_F LSFT_T(KC_F)
#define ST_J RSFT_T(KC_J)
#define CT_K RCTL_T(KC_K)
#define LT_LSPC LT(_LT, KC_SPC)
#define LT_RSPC LT(_RT, KC_SPC)

// #define LT_CAPS LT(_FN, KC_CAPS)
#define LT_BSPC LT(_RT, KC_BSPC)
#define LT_DEL  LT(_RT, KC_DEL)

// Tap Dance declarations
enum {
    SC_C,
};

// Tap Dance definitions
qk_tap_dance_action_t tap_dance_actions[] = {
    // Tap once for Escape, twice for Caps Lock
    [SC_C] = ACTION_TAP_DANCE_DOUBLE(KC_SCOLON, KC_COLON),
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
  [_BS] = LAYOUT( /* [> QWERTY <] */
            KC_1,   KC_2,   KC_3,   KC_4,   KC_5,                                 KC_6,   KC_7,   KC_8,   KC_9,   KC_0,
    KC_GESC,KC_Q,   KC_W,   KC_E,   KC_R,   KC_T,                                 KC_Y,   KC_U,   KC_I,   KC_O,   KC_P,   KC_GRV,
    KC_MINS,KC_A,   KC_S,   CT_D,   ST_F,   KC_G,                                 KC_H,   ST_J,   CT_K,   KC_L,  TD(SC_C),KC_QUOT,
    KC_EQL, KC_Z,   KC_X,   KC_C,   KC_V,   KC_B,                                 KC_N,   KC_M,   KC_COMM,KC_DOT, KC_SLSH,KC_BSLS,
            CPY_PST,C(KC_Z),G(KC_V),KC_BSPC,LT_LSPC,LALT_T(KC_DEL),RALT_T(KC_ENT),LT_RSPC,KC_TAB, KC_PSCR,KC_CAPS,XXXXXXX,
                                                     GUI_T(KC_APP),KC_RSFT
  ),

  [_LT] = LAYOUT(
            XXXXXXX,XXXXXXX,XXXXXXX,XXXXXXX,XXXXXXX,                XXXXXXX,XXXXXXX,XXXXXXX,XXXXXXX,TO(_GM),
    LCK_CLR,ALT_LCK,KC_HOME,KC_UP,  KC_END, KC_PGUP,                XXXXXXX,KC_F9,  KC_F10, KC_F11, KC_F12, KC_MUTE,
    CTL_LCK,SFT_LCK,KC_LEFT,KC_DOWN,KC_RGHT,KC_PGDN,                KC_BRIU,KC_F5,  KC_F6,  KC_F7,  KC_F8,  KC_VOLU,
    XXXXXXX,XXXXXXX,XXXXXXX,XXXXXXX,XXXXXXX,TG(_TP),                KC_BRID,KC_F1,  KC_F2,  KC_F3,  KC_F4,  KC_VOLD,
            _______,_______,_______,_______,_______,_______,_______,_______,_______,_______,_______,_______,
                                                    _______,_______
  ),

  [_RT] = LAYOUT(
            XXXXXXX,XXXXXXX,XXXXXXX,XXXXXXX,XXXXXXX,                XXXXXXX,XXXXXXX,XXXXXXX,XXXXXXX,XXXXXXX,
    XXXXXXX,XXXXXXX,KC_LCBR,KC_LBRC,KC_LPRN,XXXXXXX,                XXXXXXX,KC_RPRN,KC_RBRC,KC_RCBR,XXXXXXX,XXXXXXX,
    XXXXXXX,KC_EXLM,KC_AT,  KC_HASH,KC_DLR, XXXXXXX,                XXXXXXX,KC_PERC,KC_CIRC,KC_AMPR,KC_ASTR,XXXXXXX,
    XXXXXXX,XXXXXXX,KC_LCBR,KC_LBRC,KC_LPRN,XXXXXXX,                XXXXXXX,KC_RPRN,KC_RBRC,KC_RCBR,XXXXXXX,XXXXXXX,
            _______,_______,_______,_______,_______,_______,_______,_______,_______,_______,_______,_______,
                                                    _______,_______
  ),
    [_TP] = LAYOUT(
            XXXXXXX,XXXXXXX,XXXXXXX,XXXXXXX,XXXXXXX,                RESET,  XXXXXXX,XXXXXXX,XXXXXXX,XXXXXXX,
    _______,KC_PMNS,KC_P7,  KC_P8,  KC_P9,  KC_PSLS,                KC_PSLS,KC_P7,  KC_P8,  KC_P9,  KC_PMNS,_______,
    KC_BSPC,KC_PPLS,KC_P4,  KC_P5,  KC_P6,  KC_PAST,                KC_PAST,KC_P4,  KC_P5,  KC_P6,  KC_PPLS,KC_BSPC,
    _______,KC_PENT,KC_P1,  KC_P2,  KC_P3,  KC_NLCK,                KC_NLCK,KC_P1,  KC_P2,  KC_P3,  KC_PENT,_______,
            _______,_______,KC_PDOT,KC_P0,  TO(_BS),_______,_______,TO(_BS),KC_P0,  KC_PDOT,_______,_______,
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

bool get_retro_tapping(uint16_t keycode, keyrecord_t *record) {
    switch (keycode) {
    case LALT_T(KC_DEL):
    case RALT_T(KC_ENT):
    case GUI_T(KC_APP):
    // case LT_CAPS:
    case LT_BSPC:
    case LT_DEL:
        return false;
    default:
        return true;
    }
}

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
  switch (keycode) {
    case CPY_PST:
      if (record->event.pressed) {
        SEND_STRING(SS_LCTL("c"));
      } else {
        SEND_STRING(SS_LCTL("v"));
      }
      break;
    case ALT_LCK:
      if (record->event.pressed) {
        if (!is_alt_lock) {
            register_code(KC_LALT);
            is_alt_lock = true;
        } else {
            unregister_code(KC_LALT);
            is_alt_lock = false;
        }
      }
      break;
    case CTL_LCK:
      if (record->event.pressed) {
        if (!is_ctrl_lock) {
            register_code(KC_LCTL);
            is_ctrl_lock = true;
        } else {
            unregister_code(KC_LCTL);
            is_ctrl_lock = false;
        }
      }
      break;
    case SFT_LCK:
      if (record->event.pressed) {
        if (!is_shift_lock) {
            register_code(KC_LSFT);
            is_shift_lock = true;
        } else {
            unregister_code(KC_LSFT);
            is_shift_lock = false;
        }
      }
      break;
    case LCK_CLR:
        if (record->event.pressed) {
            if (is_alt_lock) {
                unregister_code(KC_LALT);
                is_alt_lock = false;
            }
            if (is_ctrl_lock) {
                unregister_code(KC_LCTL);
                is_ctrl_lock = false;
            }
            if (is_shift_lock) {
                unregister_code(KC_LSFT);
                is_shift_lock = false;
            }
        }
    break;
  }
  return true;
}

void post_process_record_user(uint16_t keycode, keyrecord_t *record) {
    led_t led_state = host_keyboard_led_state();
    switch (keycode) {
    case LT_LSPC:
        if (record->event.pressed) { update_tri_layer(_LT, _RT, _TP); }
        break;
    case LT_RSPC:
        if (record->event.pressed) { update_tri_layer(_LT, _RT, _TP); }
        break;
    // case LT_CAPS:
    //     if (!record->event.pressed) { writePin(B0, !led_state.caps_lock); }
    //     break;
    case KC_CAPS:
        if (!record->event.pressed) { writePin(B0, !led_state.caps_lock); }
        break;
    case KC_NLCK:
        if (!record->event.pressed) { writePin(B0, !led_state.num_lock); }
        break;
    }
}

layer_state_t layer_state_set_user(layer_state_t state) {
    if (is_alt_lock) {
        unregister_code(KC_LALT);
        is_alt_lock = false;
    }
    if (is_ctrl_lock) {
        unregister_code(KC_LCTL);
        is_ctrl_lock = false;
    }
    if (is_shift_lock) {
        unregister_code(KC_LSFT);
        is_shift_lock = false;
    }
    led_t led_state = host_keyboard_led_state();
    switch (get_highest_layer(state)) {
    case _TP:
        writePin(D5, 0); // 0 means turn-on.
        if (!led_state.num_lock) tap_code(KC_NUMLOCK);
        writePin(B0, !led_state.num_lock);
        break;
    default: //  for any other layers, or the default layer
        writePin(D5, 1); // 1 means turn-off.
        writePin(B0, !led_state.caps_lock);
        break;
    }
  return state;
}

// Joystick
// Set Pins
// uint8_t xPin  = 20;   // VRx = F5
// uint8_t yPin  = 21;   // VRy = F4

// Set Parameters
uint16_t minAxisValue = 0;
uint16_t maxAxisValue = 1023;

uint8_t maxCursorSpeed = 2;
uint8_t precisionSpeed = 1;
uint8_t speedRegulator = 20;  // Lower Values Create Faster Movement

int8_t xPolarity = 1;
int8_t yPolarity = 1;

uint8_t cursorTimeout = 10;

int16_t xOrigin, yOrigin;

uint16_t lastCursor = 0;
