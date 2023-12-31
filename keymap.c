// Copyright 2023 Danny Nguyen (@nooges)
// SPDX-License-Identifier: GPL-2.0-or-later

#include QMK_KEYBOARD_H
#include "keymap_french.h"
#include "sendstring_french.h" //otherwise sendstring converts caracters as if inputted from QWERTY keyboard

#define _AZERTY 0
#define _ACCENTS 1
#define _NUMBERS 2
#define _UTILITY 3

enum custom_keycodes {
  AZERTY = SAFE_RANGE,
  NUMBERS,
  UTILITY,
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

  [_AZERTY] = LAYOUT(
     KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO,                                               KC_NO, KC_NO,          KC_NO,       KC_NO,       KC_NO,  KC_NO,
     KC_TAB,LT(0,FR_A),  KC_W,  LT(0, FR_E),  LT(0, FR_R),  KC_T,                            KC_Y,  LT(0, FR_U),    LT(0, FR_I), LT(0, FR_O), KC_P,   LT(0, FR_QUOT),
     KC_NO, KC_A,  KC_S,  LT(2,KC_D),  LT(3,KC_F), KC_G,                                     KC_H,  LT(3, KC_J),    LT(2, KC_K), KC_L,        KC_M,   FR_GRV,
     LT(0, FR_LPRN), LT(0, FR_COLN), FR_W, KC_X, LT(0, FR_C), LT(0,FR_DOT),    KC_BSPC,      KC_DEL,LT(0, FR_COMM), KC_V, KC_B, KC_N, LT(0,KC_EQL), LT(0, FR_RPRN),
                                          KC_LCTL,    KC_LGUI,    KC_SPC,       KC_ENT,     LT(KC_RSFT, KC_ESC), KC_RALT
  ),

  // "temporary" layout for numbers and special caracters
  [_NUMBERS] = LAYOUT(
     KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,                            KC_NO,         KC_NO, KC_NO,  KC_NO, KC_NO,   KC_NO,
     KC_NO,   FR_AT,   FR_AMPR, FR_EURO, FR_HASH, KC_NO,                            LT(2,FR_SLSH), KC_P7, KC_P8,  KC_P9, KC_PMNS, KC_NO,
     KC_NO,   FR_DLR,  FR_LBRC, FR_RBRC, FR_UNDS, KC_NO,                            KC_PAST,       KC_P4, KC_P5,  KC_P6, KC_PPLS, KC_NO,
     KC_NO,   FR_PERC, FR_LABK, FR_RABK, FR_TILD, KC_NO,    KC_TRNS,    KC_TRNS,    KC_P0,         KC_P1, KC_P2,  KC_P3, KC_EQL, KC_NO,
                                         KC_TRNS, KC_TRNS,  KC_TRNS,    KC_TRNS,    KC_TRNS,       KC_TRNS 
  ),

  // "temporary" layout for mouse, navigation, and shortcuts
  [_UTILITY] = LAYOUT(
     KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,                                KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,    KC_NO,
     KC_NO,   KC_NO,   KC_BTN2, KC_BTN3, KC_BTN1, KC_WH_U,                              KC_PGUP, KC_HOME, KC_END,  KC_PGDN,  KC_NO, KC_NO,
     KC_NO,   KC_MS_L, KC_MS_D, KC_MS_U, KC_MS_R, KC_WH_D,                              KC_LEFT, KC_UP,   KC_DOWN, KC_RIGHT, KC_NO, KC_NO,
     KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,      KC_TRNS,      KC_TRNS,    KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,    KC_NO,
                                         KC_TRNS, KC_TRNS,    KC_TRNS,      KC_TRNS,    KC_TRNS, KC_TRNS 
  )

};


bool process_record_user(uint16_t keycode, keyrecord_t *record) {
  switch (keycode) {

    case AZERTY:
      if (record->event.pressed) {
        set_single_persistent_default_layer(_AZERTY);
      }
      return false;
      break;

    // Code for sending different simple keycodes if we tap or hold keys.
    // Reference: https://www.reddit.com/r/olkb/comments/qyrogi/qmk_two_actions_tap_and_hold_for_simple_key_codes/
    case LT(0,FR_LPRN): //sends ( on tap and { on hold
        if (record->tap.count && record->event.pressed) {
            return true; // Return true for normal processing of tap keycode
            break;
        } else if (record->event.pressed) {
            tap_code16(FR_RCBR); // Intercept hold function to send SEMICOLON    
            return false;
        }
        return true; // this allows for normal processing of key release!

    case LT(0,FR_COLN): // : ;
        if (record->tap.count && record->event.pressed) {
            return true;
            break;
        } else if (record->event.pressed) {
            tap_code16(FR_SCLN);
            return false;
        }
        return true;

    case LT(0,FR_DOT): // . !
        if (record->tap.count && record->event.pressed) {
            SEND_STRING("."); // for some reason KC_DOT and all stuff never send .
            return false; 
            break;
        } else if (record->event.pressed) {
            tap_code16(FR_EXLM); 
            return false;
        }
        return true;

    case LT(0,FR_COMM): // , ?
        if (record->tap.count && record->event.pressed) {
            return true; 
            break;
        } else if (record->event.pressed) {
            tap_code16(FR_QUES); 
            return false;
        }
        return true;

    case LT(0,FR_RPRN): // ) }
        if (record->tap.count && record->event.pressed) {
            return true; 
            break;
        } else if (record->event.pressed) {
            tap_code16(FR_RCBR); 
            return false;
        }
        return true;

    case LT(0,FR_QUOT): // " '
        if (record->tap.count && record->event.pressed) {
            return true; 
            break;
        } else if (record->event.pressed) {
            tap_code16(FR_DQUO); 
            return false;
        }
        return true;

    case LT(0,FR_A): // a à
        if (record->tap.count && record->event.pressed) {
            return true; 
            break;
        } else if (record->event.pressed) {
            tap_code16(FR_AGRV); 
            return false;
        }
        return true;

    case LT(0,FR_E): // e è
        if (record->tap.count && record->event.pressed) {
            return true; 
            break;
        } else if (record->event.pressed) {
            tap_code16(FR_EGRV); 
            return false;
        }
        return true;

    case LT(0,FR_R): // r é
        if (record->tap.count && record->event.pressed) {
            return true; 
            break;
        } else if (record->event.pressed) {
            tap_code16(FR_EACU); 
            return false;
        }
        return true;

    case LT(0,FR_U): // u ù
        if (record->tap.count && record->event.pressed) {
            return true; 
            break;
        } else if (record->event.pressed) {
            tap_code16(FR_UGRV); 
            return false;
        }
        return true;

    case LT(0,FR_C): // c ç
        if (record->tap.count && record->event.pressed) {
            return true; 
            break;
        } else if (record->event.pressed) {
            tap_code16(FR_CCED); 
            return false;
        }
        return true;

    case LT(0,FR_I): // i ^
        if (record->tap.count && record->event.pressed) {
            return true; 
            break;
        } else if (record->event.pressed) {
            tap_code16(FR_CIRC); 
            return false;
        }
        return true;

    case LT(0,FR_O): // o ¨
        if (record->tap.count && record->event.pressed) {
            return true; 
            break;
        } else if (record->event.pressed) {
            tap_code16(FR_DIAE); 
            return false;
        }
        return true;

    case LT(2,FR_SLSH): // / backslash
        if (record->tap.count && record->event.pressed) {
            return true; 
            break;
        } else if (record->event.pressed) {
            SEND_STRING("\\");
            return false;
        }
        return true;

    case LT(0,KC_EQL): // = |
        if (record->tap.count && record->event.pressed) {
            return true; 
            break;
        } else if (record->event.pressed) {
            SEND_STRING("|");
            return false;
        }
        return true;
  }
  return true;
}
