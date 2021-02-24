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
  // if (!led_state.num_lock) tap_code(KC_NUMLOCK);
}

/* 自定義按鍵 */
enum atreus60_keycodes {
  CPY_PST = SAFE_RANGE,
  ALT_TAB,
  KC_SPCL,
  KC_SPCR,
};
uint16_t alt_tab_timer = 0;
bool is_alt_tab_active = false;
bool is_shift_hold = false;

// Tap Dance keycodes
enum td_keycodes {
    SEMICOLON_COLON,
    REDO_UNDO,
    MULTI_PASTE,
    ESCAPE_PRINTSCREEN,
    LANGUAGE_CAPSLOCK,
};

// Define a type containing as many tapdance states as you need
typedef enum {
    SINGLE_TAP,
    SINGLE_HOLD,
    DOUBLE_TAP,
    OTHERWISE
} td_state_t;

// Create a global instance of the tapdance state type
static td_state_t td_state;

// Declare tap dance functions:
// Function to determine the current tapdance state
uint8_t current_dance(qk_tap_dance_state_t *state);

// `finished` and `reset` functions for each tapdance keycode
void dance_redo_undo_finished(qk_tap_dance_state_t *state, void *user_data);
void dance_redo_undo_reset(qk_tap_dance_state_t *state, void *user_data);

void dance_multipaste_finished(qk_tap_dance_state_t *state, void *user_data);
void dance_multipaste_reset(qk_tap_dance_state_t *state, void *user_data);

void dance_esc_screenshot_finished(qk_tap_dance_state_t *state, void *user_data);
void dance_esc_screenshot_reset(qk_tap_dance_state_t *state, void *user_data);

void dance_language_capslock_finished(qk_tap_dance_state_t *state, void *user_data);
void dance_language_capslock_reset(qk_tap_dance_state_t *state, void *user_data);

#define TD_SCLN TD(SEMICOLON_COLON)
#define TD_REDO TD(REDO_UNDO)
#define TD_MPST TD(MULTI_PASTE)
#define TD_ESCS TD(ESCAPE_PRINTSCREEN)
#define TD_CAPS TD(LANGUAGE_CAPSLOCK)

#define C_T_D   LCTL_T(KC_D)
#define S_T_F   LSFT_T(KC_F)
#define S_T_J   RSFT_T(KC_J)
#define C_T_K   RCTL_T(KC_K)

#define LT_LDEL LT(_LEFT, KC_BSPC)
#define LT_LSPC LT(_RIGHT, KC_SPC)
#define G_T_TAB GUI_T(KC_TAB)
#define G_T_ENT GUI_T(KC_ENT)
#define LT_RSPC LT(_RIGHT, KC_SPC)
#define LT_RDEL LT(_LEFT, KC_DEL)

#define S_T_4   LSFT_T(KC_4)
#define S_T_7   RSFT_T(KC_7)

#define LC_T_DN LCTL_T(KC_DOWN)
#define LS_T_RT LSFT_T(KC_RIGHT)
#define RS_T_LT RSFT_T(KC_LEFT)
#define RC_T_DN RCTL_T(KC_DOWN)

/* For macOS */
#define MCO_T_S LOPT_T(KC_S)
#define MCG_T_D LCMD_T(KC_D)
#define MCG_T_K RCMD_T(KC_K)
#define MCO_T_L ROPT_T(KC_L)
#define C_T_ENT LCTL_T(KC_ENT)
#define C_T_DEL RCTL_T(KC_BSPC)


#define _TO_DO_ KC_TRNS

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
  _GAME,
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
  [_BS] = LAYOUT( /* [> QWERTY <] */
            _TO_DO_,TD_REDO,CPY_PST,TD_MPST,_TO_DO_,                KC_APP ,KC_INS,TG(_TOP),TG(MAC),TO(_GAME),
    KC_EQL ,KC_Q   ,KC_W   ,KC_E   ,KC_R   ,KC_T   ,                KC_Y   ,KC_U   ,KC_I   ,KC_O   ,KC_P   ,KC_GRV,
    KC_MINS,KC_A   ,KC_S   ,C_T_D  ,S_T_F  ,KC_G   ,                KC_H   ,S_T_J  ,C_T_K  ,KC_L   ,TD_SCLN,KC_QUOT,
    KC_ESC ,KC_Z   ,KC_X   ,KC_C   ,KC_V   ,KC_B   ,                KC_N   ,KC_M   ,KC_COMM,KC_DOT ,KC_SLSH,KC_BSLS,
            XXXXXXX,XXXXXXX,TD_ESCS,LT_LDEL,LT_LSPC,G_T_TAB,G_T_ENT,LT_RSPC,LT_RDEL,TD_CAPS,XXXXXXX,XXXXXXX,
                                                    CPY_PST,ALT_TAB
  ),
  [MAC] = LAYOUT(
            _______,G(KC_Z),_______,G(KC_V),_______,                _______,_______,_______,_______,_______,
    _______,_______,_______,_______,_______,_______,                _______,_______,_______,_______,_______,_______,
    _______,_______,MCO_T_S,MCG_T_D,_______,_______,                _______,_______,MCG_T_K,MCO_T_L,_______,_______,
    _______,_______,_______,_______,_______,_______,                _______,_______,_______,_______,_______,_______,
            XXXXXXX,XXXXXXX,_______,_______,_______,C_T_DEL,C_T_ENT,_______,_______,KC_CAPS,XXXXXXX,XXXXXXX,
                                                    CPY_PST,_TO_DO_
  ),
  [_LEFT] = LAYOUT(
            _______,_______,_______,_______,_______,                _______,_______,_______,_______,_______,
    _______,KC_6   ,KC_7   ,KC_8   ,KC_9   ,KC_0   ,                _TO_DO_,_TO_DO_,_TO_DO_,_TO_DO_,_TO_DO_,_______,
    _______,KC_1   ,KC_2   ,KC_3   ,KC_4   ,KC_5   ,                KC_6   ,KC_7   ,KC_8   ,KC_9   ,KC_0   ,_______,
    _______,_TO_DO_,KC_LGUI,KC_LCTL,KC_LSFT,_TO_DO_,                _TO_DO_,KC_RSFT,KC_RCTL,KC_RGUI,_TO_DO_,_______,
            XXXXXXX,XXXXXXX,_TO_DO_,KC_DOT, KC_LALT,_______,_______,KC_RALT,KC_DOT, _TO_DO_,XXXXXXX,XXXXXXX,
                                                    _______,_______
  ),
  [_RIGHT] = LAYOUT(
            KC_F2  ,KC_F3  ,KC_F4  ,KC_F5  ,KC_F6  ,                KC_F7  ,KC_F8  ,KC_F9  ,KC_F10 ,KC_F11 ,
    _______,KC_LCBR,KC_HOME,KC_UP,  KC_END, KC_PGUP,                KC_PGUP,KC_HOME,KC_UP,  KC_END, KC_RCBR,_______,
    _______,KC_LBRC,KC_LEFT,KC_DOWN,KC_RGHT,KC_PGDN,                KC_PGDN,KC_LEFT,KC_DOWN,KC_RGHT,KC_RBRC,_______,
    _______,KC_LSPO,KC_LGUI,KC_LCTL,KC_LSFT,_TO_DO_,                _TO_DO_,KC_RSFT,KC_RCTL,KC_RGUI,KC_RSPC,_______,
            XXXXXXX,XXXXXXX,KC_F1  ,_TO_DO_,KC_LALT,_______,_______,KC_RALT,_TO_DO_,KC_F12 ,XXXXXXX,XXXXXXX,
                                                    _______,_______
  ),
  [_TOP] = LAYOUT(
            KC_MUTE,KC_VOLD,KC_VOLU,_TO_DO_,KC_BRID,                KC_BRIU,_TO_DO_,TO(_BS),TG(MAC),TO(_GAME),
    _______,_______,_______,_______, RESET ,_______,                KC_PSLS,KC_P7  ,KC_P8  ,KC_P9  ,KC_PMNS,KC_BSPC,
    _______,_______,_______,_______,_______,_______,                KC_PAST,KC_P4  ,KC_P5  ,KC_P6  ,KC_PPLS,XXXXXXX,
    _______,_______,_______,_______,_______,_______,                KC_NLCK,KC_P1  ,KC_P2  ,KC_P3  ,KC_PENT,XXXXXXX,
            _______,_______,_______,_______,_______,_______,_______,TO(_BS),KC_P0,  KC_PDOT,XXXXXXX,XXXXXXX,
                                                    _______,_______
  ),
  [_GAME] = LAYOUT( /* [> QWERTY <] */
            KC_1,   KC_2,   KC_3,   KC_4,   KC_5,                   KC_6,   KC_7,   KC_8,   KC_9,   KC_0,
    KC_ESC, KC_2,   KC_Q,   KC_W,   KC_E,   KC_R,                   KC_Y,   KC_U,   KC_I,   KC_O,   KC_P,   KC_GRV,
    KC_TAB, KC_3,   KC_A,   KC_S,   KC_D,   KC_F,                   KC_H,   KC_J,   KC_K,   KC_L,   KC_SCLN,KC_QUOT,
    KC_ENT, KC_4,   KC_Z,   KC_X,   KC_C,   KC_V,                   KC_N,   KC_M,   KC_COMM,KC_DOT, KC_SLSH,KC_BSLS,
            XXXXXXX,XXXXXXX,_TO_DO_,KC_BSPC,KC_SPC, _______,_______,TO(_BS),KC_PSCR,G(KC_G),XXXXXXX,XXXXXXX,
                                                    _______,_______
  )
};

/* 自定義按鍵佈局切換行為*/
layer_state_t layer_state_set_user(layer_state_t state) {
    led_t led_state = host_keyboard_led_state();
    switch (get_highest_layer(state)) {
        case _TOP:
            if (!led_state.num_lock) tap_code(KC_NUMLOCK);
            writePin(RXLED, LED_ON);
            break;
        default: //  for any other layers, or the default layer
            writePin(RXLED, LED_OFF);
    }
    return state;
}

/* 定義常態行為*/
void matrix_scan_user(void) {
    if (is_alt_tab_active) {
        if (timer_elapsed(alt_tab_timer) > 1000) {
            unregister_code(KC_LALT);
            is_alt_tab_active = false;
        }
    }
    /* 檢查自定義指示燈 */
    led_t led_state = host_keyboard_led_state();
    if (IS_LAYER_ON(_TOP)) {
        if (readPin(TXLED) == led_state.num_lock) writePin(TXLED, !led_state.num_lock);
    } else {
        if (readPin(TXLED) == led_state.caps_lock) writePin(TXLED, !led_state.caps_lock);
    }
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
    }
    return true;
}

/* 擊鍵後連帶行為 */
void post_process_record_user(uint16_t keycode, keyrecord_t *record) {
    oled_render();
    switch (keycode) {
    case LT_LDEL:
    case LT_RDEL:
        if (record->event.pressed) { update_tri_layer(_LEFT, _RIGHT, _TOP); }
        break;
    }
}

/* 擊鍵設定 */
bool get_retro_tapping(uint16_t keycode, keyrecord_t *record) {
    switch (keycode) {
    case LT_LDEL:
    case LT_RDEL:
        return false;
    default:
        return true;
    }
}

/* Tap Dance Functions Defination */
// Determine the tapdance state to return
uint8_t current_dance(qk_tap_dance_state_t *state) {
    switch (state->count) {
        case 1:
            if (state->interrupted || !state->pressed) return SINGLE_TAP;
            else return SINGLE_HOLD;
        case 2:
            return DOUBLE_TAP;
        default:
            return OTHERWISE;
    }
}

void dance_redo_undo_finished(qk_tap_dance_state_t *state, void *user_data) {
    td_state = current_dance(state);
    switch (td_state) {
        case SINGLE_TAP:
            register_code16(C(KC_Z));
            break;
        case SINGLE_HOLD:
            register_code16(C(KC_S));
            break;
        case DOUBLE_TAP:
            register_code16(C(KC_Y));
            break;
        default:;
    }
}
void dance_redo_undo_reset(qk_tap_dance_state_t *state, void *user_data) {
    switch (td_state) {
        case SINGLE_TAP:
            unregister_code16(C(KC_Z));
            break;
        case SINGLE_HOLD:
            unregister_code16(C(KC_S));
            break;
        case DOUBLE_TAP:
            unregister_code16(C(KC_Y));
            break;
        default:;
    }
}

void dance_multipaste_finished(qk_tap_dance_state_t *state, void *user_data) {
    td_state = current_dance(state);
    switch (td_state) {
        case SINGLE_TAP:
            register_code16(C(KC_V));
            break;
        case SINGLE_HOLD:
            register_code16(G(KC_V));
            break;
        case DOUBLE_TAP:
            register_code16(C(KC_C));
            break;
        default:;
    }
}
void dance_multipaste_reset(qk_tap_dance_state_t *state, void *user_data) {
    switch (td_state) {
        case SINGLE_TAP:
            unregister_code16(C(KC_V));
            break;
        case SINGLE_HOLD:
            unregister_code16(G(KC_V));
            break;
        case DOUBLE_TAP:
            unregister_code16(C(KC_C));
            break;
        default:;
    }
}

void dance_esc_screenshot_finished(qk_tap_dance_state_t *state, void *user_data) {
    td_state = current_dance(state);
    switch (td_state) {
        case SINGLE_TAP:
            register_code(KC_ESC);
            break;
        case SINGLE_HOLD:
            register_code(KC_PSCREEN);
            break;
        case DOUBLE_TAP:
            break;
        default:;
    }
}
void dance_esc_screenshot_reset(qk_tap_dance_state_t *state, void *user_data) {
    switch (td_state) {
        case SINGLE_TAP:
            unregister_code(KC_ESC);
            break;
        case SINGLE_HOLD:
            unregister_code(KC_PSCREEN);
            break;
        case DOUBLE_TAP:
            break;
        default:;
    }
}

void dance_language_capslock_finished(qk_tap_dance_state_t *state, void *user_data) {
    td_state = current_dance(state);
    switch (td_state) {
        case SINGLE_TAP:
            register_code16(G(KC_SPC));
            break;
        case SINGLE_HOLD:
            register_code(KC_CAPSLOCK);
            break;
        case DOUBLE_TAP:
            break;
        default:;
    }
}
void dance_language_capslock_reset(qk_tap_dance_state_t *state, void *user_data) {
    switch (td_state) {
        case SINGLE_TAP:
            unregister_code16(G(KC_SPC));
            break;
        case SINGLE_HOLD:
            unregister_code(KC_CAPSLOCK);
            break;
        case DOUBLE_TAP:
            break;
        default:;
    }
}

// Tap Dance definitions
qk_tap_dance_action_t tap_dance_actions[] = {
  [SEMICOLON_COLON] = ACTION_TAP_DANCE_DOUBLE(KC_SCOLON, KC_COLON),
  [REDO_UNDO] = ACTION_TAP_DANCE_FN_ADVANCED(NULL, dance_redo_undo_finished, dance_redo_undo_reset),
  [MULTI_PASTE] = ACTION_TAP_DANCE_FN_ADVANCED(NULL, dance_multipaste_finished, dance_multipaste_reset),
  [ESCAPE_PRINTSCREEN] = ACTION_TAP_DANCE_FN_ADVANCED(NULL, dance_esc_screenshot_finished, dance_esc_screenshot_reset),
  [LANGUAGE_CAPSLOCK] = ACTION_TAP_DANCE_FN_ADVANCED(NULL, dance_language_capslock_finished, dance_language_capslock_reset)
};

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
        case MAC:
            oled_write_P(PSTR("Default\n"), false);
            break;
        case _LEFT:
            oled_write_P(PSTR("Num. & Punc.\n"), false);
            break;
        case _RIGHT:
            oled_write_P(PSTR("Navigation\n"), false);
            break;
        case _TOP:
            oled_write("Number Pad\n", false);
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
    oled_write_P(led_state.num_lock ? PSTR("NumLock ") : PSTR("        "), false);
    oled_write_P(led_state.caps_lock ? PSTR( "CapsLock ") : PSTR("         "), false);
    oled_write_P(IS_LAYER_ON(MAC) ? PSTR( "mac") : PSTR("Win"), false);
}
#endif
