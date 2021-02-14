/*
Copyright 2012 Jun Wako <wakojun@gmail.com>

This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 2 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

#ifndef CONFIG_H
#define CONFIG_H

#include "config_common.h"

/* USB Device descriptor parameter */

#define VENDOR_ID       0xFEED
#define PRODUCT_ID      0x6062
#define DEVICE_VER      0x0001
#define MANUFACTURER    Jay
#define PRODUCT         Atreus60

/* key matrix size */
// Rows are doubled-up
#define MATRIX_ROWS 6
#define MATRIX_COLS 10

// wiring of each half
#define MATRIX_ROW_PINS { B6, B2, B3, B1, F7, F6 }
#define MATRIX_COL_PINS { B5, B4, E6, D7, C6, D4, D0, D1, D2, D3 }

/* COL2ROW or ROW2COL */
#define DIODE_DIRECTION ROW2COL

/* define if matrix has ghost */
// #define MATRIX_HAS_GHOST

/* 背光LED */
// #define BACKLIGHT_PIN D5
// #define BACKLIGHT_LEVELS 3
// #define BACKLIGHT_ON_STATE 0

/* 自定義LED指示燈 */
#define LED_PIN_ON_STATE 0

/* Set 0 if debouncing isn't needed */
#define DEBOUNCE 5

/* Mechanical locking support. Use KC_LCAP, KC_LNUM or KC_LSCR instead in keymap */
// #define LOCKING_SUPPORT_ENABLE

/* Locking resynchronize hack */
#define LOCKING_RESYNC_ENABLE

/* Tap Configuration */
#define TAPPING_TERM 300 // 擊鍵時間、長按時間
#define IGNORE_MOD_TAP_INTERRUPT
#define RETRO_TAPPING_PER_KEY

/* Combo */
// #define COMBO_COUNT 1
// #define COMBO_ALLOW_ACTION_KEYS

/*
 * Feature disable options
 *  These options are also useful to firmware size reduction.
 */

/* disable debug print */
// #define NO_DEBUG

/* disable print */
// #define NO_PRINT

/* disable action features */
//#define NO_ACTION_LAYER
//#define NO_ACTION_TAPPING
//#define NO_ACTION_ONESHOT
//#define NO_ACTION_MACRO
//#define NO_ACTION_FUNCTION

#endif
