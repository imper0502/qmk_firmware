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
  REDO_UNDO,
  MULTI_PASTE,
};

void dance_redo_undo_finished(qk_tap_dance_state_t *state, void *user_data) {
    if (state->count == 1) {
        register_code16(C(KC_Z));
    } else {
        register_code16(C(KC_Y));
    }
}

void dance_redo_undo_reset(qk_tap_dance_state_t *state, void *user_data) {
    if (state->count == 1) {
        unregister_code16(C(KC_Z));
    } else {
        unregister_code16(C(KC_Y));
    }
}

void dance_multipaste_finished(qk_tap_dance_state_t *state, void *user_data) {
    if (state->count == 1) {
        register_code16(C(KC_V));
    } else {
        register_code16(G(KC_V));
    }
}

void dance_multipaste_reset(qk_tap_dance_state_t *state, void *user_data) {
    if (state->count == 1) {
        unregister_code16(C(KC_V));
    } else {
        unregister_code16(G(KC_V));
    }
}

// Tap Dance definitions
qk_tap_dance_action_t tap_dance_actions[] = {
  [SEMICOLON_COLON] = ACTION_TAP_DANCE_DOUBLE(KC_SCOLON, KC_COLON),
  [CAPSLOCK_PRINTSCREEN] = ACTION_TAP_DANCE_DOUBLE(KC_CAPSLOCK, KC_PSCREEN),
  [REDO_UNDO] = ACTION_TAP_DANCE_FN_ADVANCED(NULL, dance_redo_undo_finished, dance_redo_undo_reset),
  [MULTI_PASTE] = ACTION_TAP_DANCE_FN_ADVANCED(NULL, dance_multipaste_finished, dance_multipaste_reset),
};

#define C_T_D   LCTL_T(KC_D)
#define S_T_F   LSFT_T(KC_F)
#define S_T_J   RSFT_T(KC_J)
#define C_T_K   RCTL_T(KC_K)
#define TD_SCLN TD(SEMICOLON_COLON)
#define TD_CLPS TD(CAPSLOCK_PRINTSCREEN)
#define TD_REDO TD(REDO_UNDO)
#define TD_PST  TD(MULTI_PASTE)
#define LT_LSPC LT(_LEFT, KC_SPC)
#define LT_RSPC LT(_RIGHT, KC_SPC)
#define A_T_BSP RALT_T(KC_BSPC)
#define G_T_ENT GUI_T(KC_ENT)
#define KC_LANG G(KC_SPC)

#define MCO_T_S LOPT_T(KC_S)
#define MCG_T_D LCMD_T(KC_D)
#define MCG_T_K RCMD_T(KC_K)
#define MCO_T_L ROPT_T(KC_L)
#define C_T_ENT LCTL_T(KC_ENT)
#define C_T_DEL RCTL_T(KC_BSPC)

#define S_T_4   LSFT_T(KC_4)
#define S_T_7   RSFT_T(KC_7)

#define TXLED D5
#define RXLED B0
enum {
  LED_ON,
  LED_OFF,
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
  [_BS] = LAYOUT( /* [> QWERTY <] */
            KC_1,   KC_2,   KC_3,   KC_4,   KC_5,                   KC_6,   KC_7,   KC_8,   KC_9,   KC_0,
    KC_MINS,KC_Q,   KC_W,   KC_E,   KC_R,   KC_T,                   KC_Y,   KC_U,   KC_I,   KC_O,   KC_P,   CPY_PST,
    KC_EQL, KC_A,   KC_S,   C_T_D,  S_T_F,  KC_G,                   KC_H,   S_T_J,  C_T_K,  KC_L,   TD_SCLN,KC_QUOT,
    KC_GRV, KC_Z,   KC_X,   KC_C,   KC_V,   KC_B,                   KC_N,   KC_M,   KC_COMM,KC_DOT, KC_SLSH,KC_BSLS,
            KC_ESC, TD_PST, TD_REDO,KC_TAB, LT_LSPC,G_T_ENT,A_T_BSP,LT_RSPC,KC_DEL ,TD_CLPS,KC_LANG,KC_ESC,
                                                    CPY_PST,ALT_TAB
  ),
  [MAC] = LAYOUT( /* [> QWERTY <] */
            _______,_______,_______,_______,_______,                _______,_______,_______,_______,_______,
    _______,_______,_______,_______,_______,_______,                _______,_______,_______,_______,_______,_______,
    _______,_______,MCO_T_S,MCG_T_D,_______,_______,                _______,_______,MCG_T_K,MCO_T_L,_______,_______,
    _______,_______,_______,_______,_______,_______,                _______,_______,_______,_______,_______,_______,
            _______,G(KC_V),G(KC_Z),_______,_______,C_T_ENT,C_T_DEL,_______,_______,KC_CAPS,KC_CAPS,_______,
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
    _______,XXXXXXX,KC_LCBR,KC_LBRC,KC_LSPO,KC_LABK,                KC_RABK,KC_RSPC,KC_RBRC,KC_RCBR,XXXXXXX,_______,
    _______,KC_1,   KC_2,   KC_3,   S_T_4,  KC_5,                   KC_6,   S_T_7,  KC_8,   KC_9   ,KC_0   ,_______,
    _______,KC_EXLM,KC_AT,  KC_HASH,KC_DLR, KC_PERC,                KC_CIRC,KC_AMPR,KC_ASTR,XXXXXXX,XXXXXXX,_______,
            _______,_______,_______,_______,_______,_______,_______,_______,_______,_______,_______,_______,
                                                    _______,_______
  ),
  [_TOP] = LAYOUT(
            XXXXXXX,XXXXXXX,XXXXXXX,XXXXXXX,XXXXXXX,                RESET,  XXXXXXX,XXXXXXX,XXXXXXX,TO(_GAME),
    _______,_______,_______,_______,_______,_______,                KC_PSLS,KC_P7,  KC_P8,  KC_P9,  KC_PMNS,KC_BSPC,
    _______,_______,_______,_______,_______,_______,                KC_PAST,KC_P4,  KC_P5,  KC_P6,  KC_PPLS,XXXXXXX,
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
    case G_T_ENT:
    case A_T_BSP:
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
