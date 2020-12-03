#include QMK_KEYBOARD_H

extern keymap_config_t keymap_config;

// Each layer gets a name for readability, which is then used in the keymap matrix below.
// The underscores don't mean anything - you can have a layer called STUFF or any other name.
// Layer names don't all need to be of the same length, obviously, and you can also skip them
// entirely and just use numbers.
#define MAC_0 0
#define MAC_1 1
#define MAC_2 2

bool is_alt_tab_active = false;
uint16_t alt_tab_timer = 0;

enum custom_keycodes {
  QWERTY = SAFE_RANGE,
  SWORDL,
  SWORDR,
  SLEFT,
  SRIGHT,
  CLUT,
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
  [MAC_0] = LAYOUT_65_with_macro(
    _______,    KC_ESC,     KC_GRV,     KC_1,       KC_2,       KC_3,       KC_4,       KC_5,       KC_6,       KC_7,       KC_8,       KC_9,       KC_0,       KC_MINS,    KC_EQL,     KC_DEL,     KC_BSPC,    KC_MEDIA_PLAY_PAUSE, \
    KC_F1,      KC_F2,      KC_TAB,     KC_Q,       KC_W,       KC_E,       KC_R,       KC_T,       KC_Y,       KC_U,       KC_I,       KC_O,       KC_P,       KC_LBRC,    KC_RBRC,    KC_BSLS,    KC_END,     \
    KC_F3,      KC_F4,      KC_CAPS,    KC_A,       KC_S,       KC_D,       KC_F,       KC_G,       KC_H,       KC_J,       KC_K,       KC_L,       KC_SCLN,    KC_QUOT,    KC_ENT,     KC_PGUP,    \
    KC_F5,      KC_F6,      KC_LSFT,    KC_Z,       KC_X,       KC_C,       KC_V,       KC_B,       KC_N,       KC_M,       KC_COMM,    KC_DOT,     KC_SLSH,    KC_RSFT,    KC_UP,      KC_PGDN,    \
    RGB_TOG,    RGB_MOD,    KC_LCTL,    KC_LALT,    MO(MAC_1),  KC_LGUI,    MO(MAC_1),              _______,    KC_SPC,     MO(MAC_1),  KC_RCTL,    KC_RGUI,    KC_LEFT,    KC_DOWN,    KC_RGHT
  ),

  [MAC_1] = LAYOUT_65_with_macro(
    _______,    _______,    _______,    KC_F1,      KC_F2,      KC_F3,      KC_F4,      KC_F5,      KC_F6,      KC_F7,      KC_F8,      KC_F9,      KC_F10,     KC_F11,     KC_F12,     KC_DEL,     KC_DEL,     _______, \
    _______,    _______,    CLUT,       _______,    _______,    _______,    _______,    _______,    _______,    _______,    KC_UP,      _______,    _______,    _______,    _______,    _______,    _______,    \
    _______,    _______,    MO(MAC_2),  _______,    _______,    SLEFT,      SRIGHT,     _______,    _______,    KC_LEFT,    KC_DOWN,    KC_RGHT,    _______,    _______,    _______,    _______,    \
    _______,    _______,    _______,    _______,    _______,    _______,    _______,    _______,    _______,    _______,    _______,    _______,    _______,    _______,    _______,    _______,    \
    RGB_TOG,    RGB_MOD,    _______,    _______,    _______,    _______,    _______,                _______,    MO(MAC_2),  _______,    _______,    _______,    _______,    _______,    _______
  ),

  [MAC_2] = LAYOUT_65_with_macro(
    _______,    _______,    _______,    _______,    _______,    _______,    _______,    _______,    _______,    _______,    _______,    _______,    _______,    _______,    _______,    _______,    _______,    _______, \
    _______,    _______,    _______,    _______,    _______,    _______,    _______,    _______,    _______,    _______,    KC_PGUP,    _______,    _______,    _______,    _______,    _______,    _______,    \
    _______,    _______,    _______,    _______,    _______,    _______,    _______,    _______,    _______,    SWORDL,     KC_PGDN,    SWORDR,     _______,    _______,    _______,    _______,    \
    _______,    _______,    _______,    _______,    _______,    _______,    _______,    _______,    _______,    _______,    _______,    _______,    _______,    _______,    _______,    _______,    \
    _______,    _______,    _______,    _______,    _______,    _______,    _______,                _______,    _______,    _______,    _______,    _______,    _______,    _______,    _______
  )
};

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    if (!record->event.pressed) {
        return true;
    }
    switch (keycode) {
        case CLUT:
            register_code(KC_LCTL);
            tap_code(KC_W);
            unregister_code(KC_LCTL);
            break;
        case SLEFT:
            register_code(KC_LCTL);
            tap_code(KC_LEFT);
            unregister_code(KC_LCTL);
            break;
        case SRIGHT:
            register_code(KC_LCTL);
            tap_code(KC_RGHT);
            unregister_code(KC_LCTL);
            break;
        case SWORDL:
            register_code(KC_LALT);
            register_code(KC_LSFT);
            tap_code(KC_LEFT);
            unregister_code(KC_LSFT);
            unregister_code(KC_LALT);
            break;
        case SWORDR:
            register_code(KC_LALT);
            register_code(KC_LSFT);
            tap_code(KC_RGHT);
            unregister_code(KC_LSFT);
            unregister_code(KC_LALT);
            break;
    }
    return true;
}

void matrix_scan_user(void) {
    if (is_alt_tab_active) {
        if (timer_elapsed(alt_tab_timer) > 750) {
            unregister_code(KC_LGUI);
            is_alt_tab_active = false;
        }
    }
}

void left_encoder(bool clockwise) {
    switch (biton32(layer_state)) {
        case 1:
            register_code(KC_LCTRL);
            if (!clockwise) {
                register_code(KC_LSHIFT);
            }
            tap_code(KC_TAB);
            if (!clockwise) {
                unregister_code(KC_LSHIFT);
            }
            unregister_code(KC_LCTRL);
            break;
        case 0:
        default:
            if (!is_alt_tab_active) {
                is_alt_tab_active = true;
                register_code(KC_LGUI);
            }
            alt_tab_timer = timer_read();
            if (!clockwise) {
                register_code(KC_LSHIFT);
            }
            tap_code(KC_TAB);
            if (!clockwise) {
                unregister_code(KC_LSHIFT);
            }
            break;
    }
}

void right_encoder(bool clockwise) {
    switch (biton32(layer_state)) {
        case 1:
            tap_code(clockwise ? KC_MEDIA_NEXT_TRACK : KC_MEDIA_PREV_TRACK);
            break;
        case MAC_0:
        default:
            tap_code(clockwise ? KC_VOLU : KC_VOLD);
            break;
    }
}

void encoder_update_user(uint8_t index, bool clockwise) {
    if (index == 0) {
        left_encoder(clockwise);
    } else if (index == 1) {
        right_encoder(clockwise);
    }
}
