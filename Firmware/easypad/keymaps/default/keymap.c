// Copyright 2023 QMK
// SPDX-License-Identifier: GPL-2.0-or-later

#include QMK_KEYBOARD_H
#include <stdint.h>

enum layers{
    _QWERTY
};
const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    /*
     * ┌───┬───┬───┬───┐
     * │ 7 │ 8 │ 9 │ / │
     * ├───┼───┼───┼───┤
     * │ 4 │ 5 │ 6 │ * │
     * ├───┼───┼───┼───┤
     * │ 1 │ 2 │ 3 │ - │
     * ├───┼───┼───┼───┤
     * │ 0 │ . │Ent│ + │
     * └───┴───┴───┴───┘
     */
    [_QWERTY] = LAYOUT(
        KC_P1,   KC_P2,   KC_P3,   KC_PWR,
        KC_ENT,   KC_W,   KC_ESC,   KC_SLEP,
        KC_A,   KC_S,   KC_D,   KC_WAKE
    )
};
#ifdef ENCODER_ENABLE

bool encoder_update_user(uint8_t index, bool clockwise){
    if(clockwise) {
        tap_code(KC_VOLU);
    }
    else {
        tap_code(KC_VOLD);
    }
    return false;
}
#endif
#ifdef OLED_ENABLE
bool oled_task_user(void) {
    oled_write_P(PSTR("Layer: "), false);

    switch(get_highest_layer(layer_state)){
        case _QWERTY:
            oled_write_P(PSTR("Default\n"), false);
            break;
        default:
            oled_write_ln_P(PSTR("Undefined"), false);
    }
    led_t led_state = host_keyboard_led_state();
    oled_write_P(led_state.num_lock ? PSTR("NUM ") : PSTR("    "), false);
    oled_write_P(led_state.caps_lock ? PSTR("CAP ") : PSTR("    "), false);
    oled_write_P(led_state.scroll_lock ? PSTR("SCR ") : PSTR("    "), false);
    return false;
}
#endif