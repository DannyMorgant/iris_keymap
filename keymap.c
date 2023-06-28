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
  ACCENTS,
  NUMBERS,
  UTILITY,
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

  [_AZERTY] = LAYOUT(
     KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO,                                          KC_NO, KC_NO,       KC_NO,       KC_NO,  KC_NO,   KC_NO,
     KC_TAB,KC_Q,  KC_W,  KC_E,  KC_R,  KC_T,                                           KC_Y,  KC_U,        KC_I,        KC_O,   KC_P,    LT(0, FR_QUOT),
     OSL(1),KC_A,  KC_S,  LT(2,KC_D),  LT(3,KC_F), KC_G,                                KC_H,  LT(3, KC_J), LT(2, KC_K), KC_L,   KC_M,    FR_GRV,
     LT(0, FR_LPRN), LT(0, FR_COLN), FR_W, KC_X, KC_C, LT(0,FR_DOT),    KC_BSPC,      KC_DEL,  LT(0, FR_COMM), KC_V, KC_B, KC_N, KC_EQL, LT(0, FR_RPRN),
                                          KC_LCTL,    KC_LGUI,    KC_SPC,       KC_ENT,     LT(KC_RSFT, KC_ESC), KC_RALT
  ),

  // Accented caracters
  [_ACCENTS] = LAYOUT(
     KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,                            KC_NO,   KC_NO,   KC_NO,    KC_NO,   KC_NO,   KC_NO,
     KC_NO,   FR_AGRV, KC_NO,   FR_EGRV, FR_EACU, KC_NO,                            KC_NO,   FR_UGRV, KC_NO,    KC_NO,   KC_NO,   KC_NO,
     KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,                            KC_NO,   KC_NO,   FR_CIRC,  FR_DIAE, KC_NO,   KC_NO,
     KC_NO,   KC_NO,   KC_NO,   KC_NO,   FR_CCED, KC_NO,    KC_TRNS,    KC_TRNS,    KC_NO,   KC_NO,   KC_NO,    KC_NO,   KC_NO,   KC_NO,
                                         KC_TRNS, KC_TRNS,  KC_TRNS,    KC_TRNS,    KC_TRNS, KC_TRNS 
  ),

  // "temporary" layout for numbers and special caracters
  [_NUMBERS] = LAYOUT(
     KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,                            KC_NO,   KC_NO, KC_NO,  KC_NO, KC_NO,   KC_NO,
     KC_NO,   KC_AT,   FR_AMPR, FR_EURO, KC_HASH, FR_UNDS,                          KC_PSLS, KC_P7, KC_P8,  KC_P9, KC_PMNS, KC_NO,
     KC_NO,   KC_DLR,  KC_LBRC, KC_RBRC, KC_9,    KC_NUHS,                          KC_PAST, KC_P4, KC_P5,  KC_P6, KC_PPLS, KC_NO,
     KC_NO,   KC_PERC, KC_LT,   KC_GT,   KC_QUES, KC_NO,    KC_TRNS,    KC_TRNS,    KC_P0,   KC_P1, KC_P2,  KC_P3, KC_EQL, KC_NO,
                                         KC_TRNS, KC_TRNS,  KC_TRNS,    KC_TRNS,    KC_TRNS, KC_TRNS 
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

  }
  return true;
}
