/*
Copyright 2019 @foostan
Copyright 2020 Drashna Jaelre <@drashna>

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
#include QMK_KEYBOARD_H

enum layers {
    _BASE = 0,
    _LOWER, // FN + movement
    _RAISE, // symbos
    _NUMBERS,
    _NUKE
};

// clang-format off
#define ___BASE1___ KC_Q, KC_W, KC_E, KC_R, KC_T, KC_Y, KC_U, KC_I, KC_O, KC_P
#define ___BASE2___ KC_A, KC_S, KC_D, KC_F, KC_G, KC_H, KC_J, KC_K, KC_L, KC_SCLN
#define ___BASE3___ KC_Z, KC_X, KC_C, KC_V, KC_B, KC_N, KC_M, KC_COMM, KC_DOT, KC_SLSH
#define ___BASE4___ LALT_T(KC_LGUI), MO(_LOWER), KC_SPC, KC_BSPC, MO(_RAISE), MO(_NUMBERS)

#define ___LOWER1___ KC_F11, KC_F12, KC_LCAP, KC_NUM, RALT(KC_LSFT), KC_PGUP, KC_END, _______, _______, _______
#define ___LOWER2___ KC_F1, KC_F2, KC_F3, KC_F4, KC_F5, KC_LEFT, KC_DOWN, KC_UP, KC_RIGHT, _______
#define ___LOWER3___ KC_F6, KC_F7, KC_F8, KC_F9, KC_F10, KC_PGDN, _______, _______, _______, _______
#define ___LOWER4___ _______, _______, _______, _______, MO(_NUKE), _______

#define ___RAISE1___ KC_TILD, _______,  _______, _______, _______, _______, _______, _______, _______, _______
#define ___RAISE2___ KC_DLR, KC_PLUS, KC_LPRN, KC_RPRN, KC_AT, KC_PIPE, KC_QUOT, KC_DQT,  KC_EQL, KC_ASTR
#define ___RAISE3___ KC_EXLM, KC_HASH, KC_LCBR, KC_RCBR, KC_GRV, KC_AMPR, KC_LBRC, KC_RBRC, KC_PERC, KC_BSLS
#define ___RAISE4___ _______, MO(_NUKE), _______, _______, _______, _______

#define ___NUMBERS1___ _______, _______, _______, _______, _______, _______, KC_PLUS, KC_MINUS, KC_EQL, _______
#define ___NUMBERS2___ KC_4, KC_2, KC_3, KC_1, KC_5, KC_6, KC_0, KC_8, KC_9, KC_7
#define ___NUMBERS3___ _______, _______, _______, _______, _______, _______, _______, KC_COMMA, KC_DOT, KC_SLSH
#define ___NUMBERS4___ _______, _______, _______, _______, _______, _______

#define ___NUKE1___ _______, _______, _______, _______, _______, KC_VOLU, _______, _______, _______, _______
#define ___NUKE2___ QK_UNDERGLOW_MODE_NEXT, QK_UNDERGLOW_SATURATION_UP, QK_UNDERGLOW_VALUE_UP, _______, _______, KC_MPRV, KC_MNXT, KC_MPLY, _______, _______
#define ___NUKE3___ QK_UNDERGLOW_MODE_PREVIOUS, QK_UNDERGLOW_SATURATION_DOWN, QK_UNDERGLOW_VALUE_DOWN, _______, _______, KC_VOLD, _______, _______, _______, _______
#define ___NUKE4___ _______, _______, _______, _______, _______, _______

#define LAYOUT_spider9375_3x6(...) LAYOUT_split_3x6_3(__VA_ARGS__)
// clang-format on

enum custom_keycodes {
    CTRL_CMD = SAFE_RANGE,
    TOGGLE_OS,
};

typedef union {
    uint8_t raw;
    struct {
        bool is_mac_os: 1;
    };
} user_config_t;

user_config_t user_config;

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    switch (keycode) {
        case CTRL_CMD:
            if (record->event.pressed) {
                if (user_config.is_mac_os) {
                    register_code(KC_LGUI);
                } else {
                    register_code(KC_LCTL);
                }
            } else {
                if (user_config.is_mac_os) {
                    unregister_code(KC_LGUI);
                } else {
                    unregister_code(KC_LCTL);
                }
            }
            return false;
        case TOGGLE_OS:
            if (record->event.pressed) {
                user_config.is_mac_os = !user_config.is_mac_os;
                eeconfig_update_user(user_config.raw);
            }
            return false;
        default:
            return true;
    }
}

void keyboard_post_init_user(void) {
    user_config.raw = eeconfig_read_user();
}

void eeconfig_init_user(void) {
  user_config.raw = 0;
  user_config.is_mac_os = false;
  eeconfig_update_user(user_config.raw);
}

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    [_BASE] = LAYOUT_spider9375_3x6(
       KC_TAB, ___BASE1___, KC_BSPC,
       CTRL_CMD, ___BASE2___, KC_ENTER,
       KC_LSFT, ___BASE3___, XXXXXXX,
                  ___BASE4___

  ),
    [_LOWER] = LAYOUT_spider9375_3x6(
      KC_ESC, ___LOWER1___, KC_BSPC,
      CTRL_CMD, ___LOWER2___, KC_ENTER,
      KC_LSFT, ___LOWER3___, XXXXXXX,
                 ___LOWER4___
 ),
    [_RAISE] =LAYOUT_spider9375_3x6(
      KC_ESC, ___RAISE1___,  KC_BSPC,
      KC_MINUS, ___RAISE2___, KC_ENTER,
      KC_UNDS, ___RAISE3___,  KC_CIRC,
                  ___RAISE4___
),
    [_NUMBERS] = LAYOUT_spider9375_3x6(
      KC_ESC, ___NUMBERS1___,  KC_BSPC,
      _______, ___NUMBERS2___, KC_ENTER,
      _______, ___NUMBERS3___,  _______,
                  ___NUMBERS4___
),
    [_NUKE] = LAYOUT_spider9375_3x6(
      QK_BOOT, ___NUKE1___,  KC_BSPC,
      QK_UNDERGLOW_TOGGLE, ___NUKE2___, KC_ENTER,
      TOGGLE_OS, ___NUKE3___,  _______,
                  ___NUKE4___
)
};
