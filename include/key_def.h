#ifndef KEY_DEF_H
#define KEY_DEF_H

#include <stdint.h>

#define KEY_NUM_COLUMN 22
#define KEY_NUM_ROW 6

enum key_matrix {
    KEY_ESC, KEY_BACKTICK, KEY_TAB, KEY_CAPS_LOCK, KEY_UNUSED0, KEY_LEFT_CONTROL,
    KEY_UNUSED1, KEY_ONE, KEY_UNUSED2, KEY_UNUSED3, KEY_LEFT_SHIFT, KEY_LEFT_SUPER,
    KEY_F1, KEY_TWO, KEY_Q, KEY_A, KEY_Z, KEY_UNUSED4,
    KEY_F2, KEY_THREE, KEY_W, KEY_S, KEY_X, KEY_LEFT_ALT,
    KEY_F3, KEY_FOUR, KEY_E, KEY_D, KEY_C, KEY_UNUSED5,
    KEY_F4, KEY_FIVE, KEY_R, KEY_F, KEY_V, KEY_UNUSED6,
    KEY_UNUSED7, KEY_SIX, KEY_T, KEY_G, KEY_B, KEY_SPACE,
    KEY_F5, KEY_SEVEN, KEY_Y, KEY_H, KEY_N, KEY_UNUSED8,
    KEY_F6, KEY_EIGHT, KEY_U, KEY_J, KEY_M, KEY_UNUSED9,
    KEY_F7, KEY_NINE, KEY_I, KEY_K, KEY_COMMA, KEY_UNUSED10,
    KEY_F8, KEY_ZERO, KEY_O, KEY_L, KEY_PERIOD, KEY_RIGHT_ALT,
    KEY_F9, KEY_MINUS, KEY_P, KEY_SEMICOLON, KEY_SLASH, KEY_RIGHT_SUPER,
    KEY_F10, KEY_PLUS, KEY_LEFT_SQUARE, KEY_APOSTROPHE, KEY_UNUSED11, KEY_UNUSED12,
    KEY_F11, KEY_UNUSED13, KEY_RIGHT_SQUARE, KEY_RIGHT_SHIFT, KEY_ENTER, KEY_RIGHT_FN,
    KEY_F12, KEY_BACKSPACE, KEY_BACKSLASH, KEY_UNUSED14, KEY_UNUSED15, KEY_RIGHT_CONTROL,
    KEY_PRINT_SCREEN, KEY_INSERT, KEY_DELETE, KEY_UNUSED16, KEY_UNUSED17, KEY_LEFT_ARROW,
    KEY_SCROLL_LOCK, KEY_HOME, KEY_END, KEY_UNUSED18, KEY_UP_ARROW, KEY_DOWN_ARROW,
    KEY_PAUSE, KEY_PAGE_UP, KEY_PAGE_DOWN, KEY_UNUSED19, KEY_UNUSED20, KEY_RIGHT_ARROW,
    KEY_UNUSED21, KEY_NUM_LOCK, KEY_NUMPAD_SEVEN, KEY_NUMPAD_FOUR, KEY_NUMPAD_ONE, KEY_NUMPAD_ZERO,
    KEY_UNUSED22, KEY_NUMPAD_DIVIDE, KEY_NUMPAD_EIGHT, KEY_NUMPAD_FIVE, KEY_NUMPAD_TWO, KEY_UNUSED23,
    KEY_UNUSED24, KEY_NUMPAD_MULTIPLY, KEY_NUMPAD_NINE, KEY_NUMPAD_SIX, KEY_NUMPAD_THREE, KEY_NUMPAD_PERIOD,
    KEY_UNUSED25, KEY_NUMPAD_MINUS, KEY_NUMPAD_PLUS, KEY_UNUSED26, KEY_NUMPAD_ENTER, KEY_UNUSED28,
    KEY_LEN,
    KEY_INVALID
};

struct key_state {
    uint8_t pressed;
};

extern const enum key_matrix key_matrix[KEY_NUM_COLUMN][KEY_NUM_ROW];
extern struct key_state key_matrix_state[KEY_NUM_COLUMN][KEY_NUM_ROW];

#endif
