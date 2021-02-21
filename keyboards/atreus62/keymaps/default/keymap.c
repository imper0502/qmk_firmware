#include QMK_KEYBOARD_H

/* 初始化指示燈 */
#define TXLED D5
#define RXLED B0

#define LED_PIN_ON_STATE 0
enum {
  LED_ON,
  LED_OFF,
};

void keyboard_pre_init_user(void) {
  setPinOutput(TXLED);
  setPinOutput(RXLED);
  writePin(TXLED, LED_OFF);
  writePin(RXLED, LED_OFF);
}

/* 自定義按鍵 */
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

#ifdef TAP_DANCE_ENABLE
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

#define TD_SCLN TD(SEMICOLON_COLON)
#define TD_CLPS TD(CAPSLOCK_PRINTSCREEN)
#define TD_REDO TD(REDO_UNDO)
#define TD_PST  TD(MULTI_PASTE)

#endif

#ifndef TAP_DANCE_ENABLE

#define TD_SCLN KC_SCOLON
#define TD_CLPS KC_CAPSLOCK
#define TD_REDO C(KC_Z)
#define TD_PST  C(KC_V)

#endif

#define C_T_D   LCTL_T(KC_D)
#define S_T_F   LSFT_T(KC_F)
#define S_T_J   RSFT_T(KC_J)
#define C_T_K   RCTL_T(KC_K)

#define KC_BTAB S(KC_TAB)
#define LT_LSPC LT(_LEFT, KC_SPC)
#define G_T_DEL GUI_T(KC_DEL)
#define G_T_ENT GUI_T(KC_ENT)
#define LT_RSPC LT(_RIGHT, KC_SPC)
#define KC_LANG G(KC_SPC)

#define MCO_T_S LOPT_T(KC_S)
#define MCG_T_D LCMD_T(KC_D)
#define MCG_T_K RCMD_T(KC_K)
#define MCO_T_L ROPT_T(KC_L)
#define C_T_ENT LCTL_T(KC_ENT)
#define C_T_DEL RCTL_T(KC_BSPC)

#define S_T_4   LSFT_T(KC_4)
#define S_T_7   RSFT_T(KC_7)

/* 定義鍵盤佈局 */
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
  NUM,
  _GAME,
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
  [_BS] = LAYOUT( /* [> QWERTY <] */
            TD_REDO,KC_LALT,KC_LCTL,KC_LSFT,TD_PST,                 OSL(NUM),KC_RSFT,KC_RCTL,KC_RALT,KC_LANG,
    KC_EQL, KC_Q,   KC_W,   KC_E,   KC_R,   KC_T,                   KC_Y,   KC_U,   KC_I,   KC_O,   KC_P,   KC_GRV,
    KC_MINS,KC_A,   KC_S,   C_T_D,  S_T_F,  KC_G,                   KC_H,   S_T_J,  C_T_K,  KC_L,   TD_SCLN,KC_QUOT,
    KC_ESC, KC_Z,   KC_X,   KC_C,   KC_V,   KC_B,                   KC_N,   KC_M,   KC_COMM,KC_DOT, KC_SLSH,KC_BSLS,
            TD_REDO,KC_LALT,KC_BTAB,KC_BSPC,LT_LSPC,G_T_DEL,G_T_ENT,LT_RSPC,KC_TAB, TD_CLPS,KC_RALT,KC_LANG,
                                                    CPY_PST,ALT_TAB
  ),
  [MAC] = LAYOUT(
            G(KC_Z),_______,KC_LGUI,_______,G(KC_V),                _______,_______,KC_RGUI,_______,XXXXXXX,
    _______,_______,_______,_______,_______,_______,                _______,_______,_______,_______,_______,_______,
    _______,_______,MCO_T_S,MCG_T_D,_______,_______,                _______,_______,MCG_T_K,MCO_T_L,_______,_______,
    _______,_______,_______,_______,_______,_______,                _______,_______,_______,_______,_______,_______,
            _______,_______,_______,_______,_______,C_T_DEL,C_T_ENT,_______,_______,KC_CAPS,_______,_______,
                                                    CPY_PST,XXXXXXX
  ),
  [_LEFT] = LAYOUT(
            _______,_______,_______,_______,_______,                _______,_______,_______,_______,_______,
    _______,SFT_LCK,KC_LCBR,KC_LBRC,KC_LSPO,KC_LABK,                KC_RABK,KC_RSPC,KC_RBRC,KC_RCBR,KC_DOT, _______,
    _______,KC_1,   KC_2,   KC_3,   S_T_4,  KC_5,                   KC_6,   S_T_7,  KC_8,   KC_9   ,KC_0   ,_______,
    _______,KC_0,   KC_9,   KC_8,   S_T_7,  KC_6,                   _______,_______,_______,_______,_______,_______,
            _______,_______,_______,_______,_______,_______,_______,_______,_______,_______,_______,_______,
                                                    _______,_______
  ),
  [_RIGHT] = LAYOUT(
            _______,_______,_______,_______,_______,                _______,_______,_______,_______,_______,
    XXXXXXX,XXXXXXX,KC_HOME,KC_UP,  KC_END, KC_PGUP,                KC_PGUP,KC_HOME,KC_UP,  KC_END, XXXXXXX,XXXXXXX,
    XXXXXXX,XXXXXXX,KC_LEFT,KC_DOWN,KC_RGHT,KC_PGDN,                KC_PGDN,KC_LEFT,KC_DOWN,KC_RGHT,XXXXXXX,XXXXXXX,
    KC_F1,  KC_F2,  KC_F3,  KC_F4,  KC_F5,  KC_F6,                  KC_F7,  KC_F8,  KC_F9,  KC_F10, KC_F11, KC_F12,
            _______,_______,_______,_______,_______,_______,_______,_______,_______,_______,_______,_______,
                                                    _______,_______
  ),
  [_TOP] = LAYOUT(
            KC_MUTE,KC_VOLD,KC_VOLU,XXXXXXX,KC_BRID,                KC_BRIU,XXXXXXX,XXXXXXX,TG(MAC),TO(_GAME),
    _______,_______,_______,_______, RESET, _______,                KC_PSLS,KC_P7,  KC_P8,  KC_P9,  KC_PMNS,KC_BSPC,
    _______,_______,_______,_______,_______,_______,                KC_PAST,KC_P4,  KC_P5,  KC_P6,  KC_PPLS,XXXXXXX,
    _______,_______,_______,_______,_______,_______,                TO(NUM),KC_P1,  KC_P2,  KC_P3,  KC_PENT,XXXXXXX,
            _______,_______,_______,_______,TO(_BS),_______,_______,TO(_BS),KC_P0,  KC_PDOT,XXXXXXX,XXXXXXX,
                                                    _______,_______
  ),
  [NUM] = LAYOUT(
            KC_MUTE,KC_VOLD,KC_VOLU,XXXXXXX,KC_BRID,                KC_BRIU,XXXXXXX,XXXXXXX,TG(MAC),TO(_GAME),
    _______,_______,_______,_______, RESET, _______,                KC_PSLS,KC_P7,  KC_P8,  KC_P9,  KC_PMNS,KC_BSPC,
    _______,_______,_______,_______,_______,_______,                KC_PAST,KC_P4,  KC_P5,  KC_P6,  KC_PPLS,XXXXXXX,
    _______,_______,_______,_______,_______,_______,                KC_NLCK,KC_P1,  KC_P2,  KC_P3,  KC_PENT,XXXXXXX,
            _______,_______,_______,_______,TO(_BS),_______,_______,TO(_BS),KC_P0,  KC_PDOT,XXXXXXX,XXXXXXX,
                                                    _______,_______
  ),
  [_GAME] = LAYOUT( /* [> QWERTY <] */
            KC_1,   KC_2,   KC_3,   KC_4,   KC_5,                   KC_6,   KC_7,   KC_8,   KC_9,   KC_0,
    KC_ESC, KC_2,   KC_Q,   KC_W,   KC_E,   KC_R,                   KC_Y,   KC_U,   KC_I,   KC_O,   KC_P,   KC_GRV,
    KC_TAB, KC_3,   KC_A,   KC_S,   KC_D,   KC_F,                   KC_H,   KC_J,   KC_K,   KC_L,   KC_SCLN,KC_QUOT,
    KC_ENT, KC_4,   KC_Z,   KC_X,   KC_C,   KC_V,                   KC_N,   KC_M,   KC_COMM,KC_DOT, KC_SLSH,KC_BSLS,
            XXXXXXX,XXXXXXX,XXXXXXX,KC_BSPC,KC_SPC, _______,_______,TO(_BS),XXXXXXX,KC_PSCR,G(KC_G),XXXXXXX,
                                                    _______,_______
  )
};

/* 自定義按鍵佈局切換行為*/
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

    #ifndef OLED_DRIVER_ENABLE
        led_t led_state = host_keyboard_led_state();
        switch (get_highest_layer(state)) {
        case _TOP:
        case NUM:
            if (!led_state.num_lock) tap_code(KC_NUMLOCK);
            writePin(RXLED, LED_ON); // 0 means turn-on.
            break;
        default: //  for any other layers, or the default layer
            writePin(RXLED, LED_OFF); // 1 means turn-off.
            break;
        }
    #endif

    return state;
}

/* 定義常態行為*/
void matrix_scan_user(void) {     //# The very important timer.
    if (is_alt_tab_active) {
        if (timer_elapsed(alt_tab_timer) > 1000) {
            unregister_code(KC_LALT);
            is_alt_tab_active = false;
        }
    }
/* 檢查自定義指示燈 */
    #ifndef OLED_DRIVER_ENABLE
    led_t led_state = host_keyboard_led_state();
    if (IS_LAYER_ON(_TOP) || IS_LAYER_ON(NUM)) {
        if (readPin(TXLED) == led_state.num_lock) writePin(TXLED, !led_state.num_lock);
    } else {
        if (readPin(TXLED) == led_state.caps_lock) writePin(TXLED, !led_state.caps_lock);
    }
    #endif
}

/* 自定義按鍵與巨集 */
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
    // case ALT_LCK:
    //   if (record->event.pressed) {
    //     if (!is_alt_lock) {
    //         register_code(KC_LALT);
    //         is_alt_lock = true;
    //     } else {
    //         unregister_code(KC_LALT);
    //         is_alt_lock = false;
    //     }
    //   }
    //   break;
    // case CTL_LCK:
    //   if (record->event.pressed) {
    //     if (!is_ctrl_lock) {
    //         if (IS_LAYER_ON(MAC)) register_code(KC_LCMD);
    //         else register_code(KC_LCTL);
    //         is_ctrl_lock = true;
    //     } else {
    //         if (IS_LAYER_ON(MAC)) unregister_code(KC_LCMD);
    //         else unregister_code(KC_LCTL);
    //         is_ctrl_lock = false;
    //     }
    //   }
    //   break;
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
    // case LCK_CLR:
    //     if (record->event.pressed) {
    //         if (is_alt_lock) {
    //             unregister_code(KC_LALT);
    //             is_alt_lock = false;
    //         }
    //         if (is_ctrl_lock) {
    //             unregister_code(KC_LCTL);
    //             is_ctrl_lock = false;
    //         }
    //         if (is_shift_lock) {
    //             unregister_code(KC_LSFT);
    //             is_shift_lock = false;
    //         }
    //     }
    // break;
  }
  return true;
}

/* 擊鍵後連帶行為 */
void post_process_record_user(uint16_t keycode, keyrecord_t *record) {
  switch (keycode) {
  case LT_LSPC:
    if (record->event.pressed) { update_tri_layer(_LEFT, _RIGHT, _TOP); }
    else { update_tri_layer(_LEFT, _RIGHT, _TOP); }
    break;
  case LT_RSPC:
    if (record->event.pressed) { update_tri_layer(_LEFT, _RIGHT, _TOP); }
    else { update_tri_layer(_LEFT, _RIGHT, _TOP); }
    break;
  }
}

/* 擊鍵設定 */
#ifdef RETRO_TAPPING_PER_KEY
bool get_retro_tapping(uint16_t keycode, keyrecord_t *record) {
    switch (keycode) {
    case G_T_ENT:
    case G_T_DEL:
        return false;
    default:
        return true;
    }
}
#endif

/* OLED 設定 */
#ifdef OLED_DRIVER_ENABLE
static void render_logo(void) {
    static const char PROGMEM qmk_logo[] = {
        0x80, 0x81, 0x82, 0x83, 0x84, 0x85, 0x86, 0x87, 0x88, 0x89, 0x8A, 0x8B, 0x8C, 0x8D, 0x8E, 0x8F, 0x90, 0x91, 0x92, 0x93, 0x94,
        0xA0, 0xA1, 0xA2, 0xA3, 0xA4, 0xA5, 0xA6, 0xA7, 0xA8, 0xA9, 0xAA, 0xAB, 0xAC, 0xAD, 0xAE, 0xAF, 0xB0, 0xB1, 0xB2, 0xB3, 0xB4,
        0xC0, 0xC1, 0xC2, 0xC3, 0xC4, 0xC5, 0xC6, 0xC7, 0xC8, 0xC9, 0xCA, 0xCB, 0xCC, 0xCD, 0xCE, 0xCF, 0xD0, 0xD1, 0xD2, 0xD3, 0xD4, 0x00
    };

    oled_write_P(qmk_logo, false);
}

void oled_task_user(void) {
    // QMK Logo
    render_logo();
    oled_write_P(PSTR("\n"), false);

    // Host Keyboard Layer Status
    oled_write_P(PSTR(" Layer: "), false);

    switch (get_highest_layer(layer_state)) {
        case _BS:
            oled_write_P(PSTR("Default\n"), false);
            break;
        case _LEFT:
            oled_write_P(PSTR("Left\n"), false);
            break;
        case _RIGHT:
            oled_write_P(PSTR("Right\n"), false);
            break;
        case _TOP:
            oled_write("Top\n", false);
            break;
        case NUM:
            oled_write_P(PSTR("Number Keypad"), false);
            break;
        case _GAME:
            oled_write_P(PSTR("Game Mode\n"), false);
            break;
        default:
            // Or use the write_ln shortcut over adding '\n' to the end of your string
            oled_write_ln_P(PSTR("Undefined"), false);
    }

    // Host Keyboard LED Status
    led_t led_state = host_keyboard_led_state();
    oled_write_P(PSTR("\n"), false);
    oled_write_P(led_state.num_lock ? PSTR(" NumLock ") : PSTR("        "), false);
    oled_write_P(led_state.caps_lock ? PSTR( "CapsLock ") : PSTR("         "), false);
}

#endif
