#include QMK_KEYBOARD_H

// Each layer gets a name for readability, which is then used in the keymap matrix below.
// The underscores don't mean anything - you can have a layer called STUFF or any other name.
// Layer names don't all need to be of the same length, obviously, and you can also skip them
// entirely and just use numbers.
enum atreus60_layers {
  _BS,
  MAC,
  _LEFT,
  _RIGHT,
  _TOP,
  _GAME,
};

// 自定義按鍵在此設定
enum atreus60_keycodes {
  CPY_PST = SAFE_RANGE,
  ALT_TAB,
  ALT_LCK,
  CTL_LCK,
  SFT_LCK,
  LCK_CLR,
};
bool is_alt_tab_active = false;    //# ADD this near the begining of keymap.c
uint16_t alt_tab_timer = 0;        //# we will be using them soon.
bool is_alt_lock = false;
bool is_ctrl_lock = false;
bool is_shift_lock = false;

// Tap Dance declarations
enum {
  SEMICOLON_COLON,
  CAPSLOCK_PRINTSCREEN,
};

// Tap Dance definitions
qk_tap_dance_action_t tap_dance_actions[] = {
  [SEMICOLON_COLON] = ACTION_TAP_DANCE_DOUBLE(KC_SCOLON, KC_COLON),
  [CAPSLOCK_PRINTSCREEN] = ACTION_TAP_DANCE_DOUBLE(KC_CAPSLOCK, KC_PSCREEN),
};

#define C_T_D   LCTL_T(KC_D)
#define S_T_F   LSFT_T(KC_F)
#define S_T_J   RSFT_T(KC_J)
#define C_T_K   RCTL_T(KC_K)
#define TD_SCLN TD(SEMICOLON_COLON)
#define TD_CLPS TD(CAPSLOCK_PRINTSCREEN)
#define LT_LSPC LT(_LEFT, KC_SPC)
#define LT_RSPC LT(_RIGHT, KC_SPC)
#define G_T_DEL GUI_T(KC_DEL)
#define A_T_ENT RALT_T(KC_ENT)
#define KC_LANG G(KC_SPC)

#define G_T_D LCMD_T(KC_D)
#define G_T_K RCMD_T(KC_K)
#define C_T_DEL LCTL_T(KC_DEL)

#define TXLED D5
#define RXLED B0
enum {
  LED_ON,
  LED_OFF,
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
  [_BS] = LAYOUT( /* [> QWERTY <] */
            KC_1,   KC_2,   KC_3,   KC_4,   KC_5,                   KC_6,   KC_7,   KC_8,   KC_9,   KC_0,
    KC_TAB, KC_Q,   KC_W,   KC_E,   KC_R,   KC_T,                   KC_Y,   KC_U,   KC_I,   KC_O,   KC_P,   KC_GRV,
    KC_MINS,KC_A,   KC_S,   C_T_D,  S_T_F,  KC_G,                   KC_H,   S_T_J,  C_T_K,  KC_L,   TD_SCLN,KC_QUOT,
    KC_EQL, KC_Z,   KC_X,   KC_C,   KC_V,   KC_B,                   KC_N,   KC_M,   KC_COMM,KC_DOT, KC_SLSH,KC_BSLS,
            KC_ESC, G(KC_V),C(KC_Z),KC_BSPC,LT_LSPC,G_T_DEL,A_T_ENT,LT_RSPC,KC_TAB, TD_CLPS,KC_LANG,KC_ESC,
                                                    CPY_PST,ALT_TAB
  ),
  [MAC] = LAYOUT( /* [> QWERTY <] */
            _______,_______,_______,_______,_______,                _______,_______,_______,_______,_______,
    _______,_______,_______,_______,_______,_______,                _______,_______,_______,_______,_______,_______,
    _______,_______,_______,G_T_D,  _______,_______,                _______,_______,G_T_K,  _______,_______,_______,
    _______,_______,_______,_______,_______,_______,                _______,_______,_______,_______,_______,_______,
            _______,XXXXXXX,G(KC_Z),_______,_______,C_T_DEL,A_T_ENT,_______,_______,KC_CAPS,XXXXXXX,_______,
                                                    CPY_PST,XXXXXXX
  ),
  [_LEFT] = LAYOUT(
            XXXXXXX,XXXXXXX,XXXXXXX,XXXXXXX,XXXXXXX,                XXXXXXX,XXXXXXX,XXXXXXX,XXXXXXX,TG(MAC),
    LCK_CLR,ALT_LCK,KC_HOME,KC_UP,  KC_END, KC_PGUP,                XXXXXXX,KC_BRID,XXXXXXX,KC_BRIU,XXXXXXX,XXXXXXX,
    CTL_LCK,SFT_LCK,KC_LEFT,KC_DOWN,KC_RGHT,KC_PGDN,                XXXXXXX,KC_VOLD,KC_MUTE,KC_VOLU,XXXXXXX,XXXXXXX,
    KC_F1,  KC_F2,  KC_F3,  KC_F4,  KC_F5,  KC_F6,                  KC_F7,  KC_F8,  KC_F9,  KC_F10, KC_F11, KC_F12,
            _______,_______,_______,_______,_______,_______,_______,_______,_______,_______,_______,_______,
                                                    _______,_______
  ),

  [_RIGHT] = LAYOUT(
            _______,_______,_______,_______,_______,                _______,_______,_______,_______,_______,
    _______,KC_1,   KC_2,   KC_3,   KC_4,   KC_5,                   KC_6,   KC_7,   KC_8,   KC_9   ,KC_0   ,_______,
    _______,XXXXXXX,KC_LCBR,KC_LBRC,KC_LSPO,KC_LABK,                KC_RABK,KC_RSPC,KC_RBRC,KC_RCBR,XXXXXXX,_______,
    _______,KC_EXLM,KC_AT,  KC_HASH,KC_DLR, KC_PERC,                KC_CIRC,KC_AMPR,KC_ASTR,XXXXXXX,XXXXXXX,_______,
            _______,_______,_______,_______,_______,_______,_______,_______,_______,_______,_______,_______,
                                                    _______,_______
  ),
  [_TOP] = LAYOUT(
            XXXXXXX,XXXXXXX,XXXXXXX,XXXXXXX,XXXXXXX,                RESET,  XXXXXXX,XXXXXXX,XXXXXXX,TO(_GAME),
    _______,KC_BTN4,KC_BTN1,KC_MS_U,KC_BTN2,KC_WH_U,                KC_PSLS,KC_P7,  KC_P8,  KC_P9,  KC_PMNS,KC_BSPC,
    _______,KC_BTN5,KC_MS_L,KC_MS_D,KC_MS_R,KC_WH_D,                KC_PAST,KC_P4,  KC_P5,  KC_P6,  KC_PPLS,XXXXXXX,
    _______,_______,_______,_______,_______,_______,                KC_NLCK,KC_P1,  KC_P2,  KC_P3,  KC_PENT,XXXXXXX,
            _______,_______,_______,_______,TO(_BS),_______,_______,TO(_BS),KC_P0,  KC_PDOT,XXXXXXX,XXXXXXX,
                                                    _______,_______
  ),
  [_GAME] = LAYOUT( /* [> QWERTY <] */
            KC_1,   KC_2,   KC_3,   KC_4,   KC_5,                   KC_6,   KC_7,   KC_8,   KC_9,   KC_0,
    KC_ESC, KC_Q,   KC_W,   KC_E,   KC_R,   KC_T,                   KC_Y,   KC_U,   KC_I,   KC_O,   KC_P,   KC_GRV,
    KC_TAB, KC_A,   KC_S,   KC_D,   KC_F,   KC_G,                   KC_H,   KC_J,   KC_K,   KC_L,   KC_SCLN,KC_QUOT,
    KC_ENT, KC_Z,   KC_X,   KC_C,   KC_V,   KC_B,                   KC_N,   KC_M,   KC_COMM,KC_DOT, KC_SLSH,KC_BSLS,
            XXXXXXX,XXXXXXX,XXXXXXX,KC_BSPC,KC_SPC, _______,_______,TO(_BS),XXXXXXX,KC_PSCR,G(KC_G),XXXXXXX,
                                                    _______,_______
  )
};

void keyboard_pre_init_user(void) {
  setPinOutput(TXLED);
  setPinOutput(RXLED);
}

bool get_retro_tapping(uint16_t keycode, keyrecord_t *record) {
    switch (keycode) {
    case G_T_DEL:
    case A_T_ENT:
        return false;
    default:
        return true;
    }
}

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
  switch (keycode) {
    case CPY_PST:
      if (record->event.pressed) {
        if (IS_LAYER_ON(MAC))
          SEND_STRING(SS_LGUI("c"));
        else
          SEND_STRING(SS_LCTL("c"));
      } else {
        if (IS_LAYER_ON(MAC))
          SEND_STRING(SS_LGUI("v"));
        else
          SEND_STRING(SS_LCTL("v"));
      }
      break;
    case ALT_TAB:
      if (record->event.pressed) {
        if (!is_alt_tab_active) {
          is_alt_tab_active = true;
          register_code(KC_LALT);
        }
        alt_tab_timer = timer_read();
        register_code(KC_TAB);
      } else {
        unregister_code(KC_TAB);
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
            if (IS_LAYER_ON(MAC)) register_code(KC_LCMD);
            else register_code(KC_LCTL);
            is_ctrl_lock = true;
        } else {
            if (IS_LAYER_ON(MAC)) unregister_code(KC_LCMD);
            else unregister_code(KC_LCTL);
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

void matrix_scan_user(void) {     //# The very important timer.
  led_t led_state = host_keyboard_led_state();
  if (IS_LAYER_OFF(_TOP)) {
    if (readPin(TXLED) == led_state.caps_lock) writePin(TXLED, !led_state.caps_lock);
  } else {
    if (readPin(TXLED) == led_state.num_lock) writePin(TXLED, !led_state.num_lock);
  }
  if (is_alt_tab_active) {
    if (timer_elapsed(alt_tab_timer) > 1000) {
      unregister_code(KC_LALT);
      is_alt_tab_active = false;
    }
  }
}

void post_process_record_user(uint16_t keycode, keyrecord_t *record) {
  switch (keycode) {
  case LT_LSPC:
    if (record->event.pressed) { update_tri_layer(_LEFT, _RIGHT, _TOP); }
    break;
  case LT_RSPC:
    if (record->event.pressed) { update_tri_layer(_LEFT, _RIGHT, _TOP); }
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
  case _TOP:
    if (!led_state.num_lock) tap_code(KC_NUMLOCK);
    writePin(RXLED, LED_ON); // 0 means turn-on.
    break;
  default: //  for any other layers, or the default layer
    writePin(RXLED, LED_OFF); // 1 means turn-off.
    break;
  }
  return state;
}
