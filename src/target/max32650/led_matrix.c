#include <stdlib.h>
#include <stdio.h>

#include "mxc_delay.h"
#include "i2c.h"
#include "i2c_regs.h"

#include <led_matrix.h>
#include <key_def.h>

struct led_driver led_drivers[LED_NUM_DRIVER] = {
    [0] = {
        .base_address = 0x40,
        .i2c = MXC_I2C1
    },
    [1] = {
        .base_address = 0x4C,
        .i2c = MXC_I2C1
    }
};

struct led_matrix led_matrix[KEY_LEN] = {
    [KEY_ESC] = { &led_drivers[0], 0, 0, 1, 2 },
    [KEY_BACKTICK] = { &led_drivers[0], 0, 3, 4, 5 },
    [KEY_TAB] = { &led_drivers[0], 0, 6, 7, 8 },
    [KEY_CAPS_LOCK] = { &led_drivers[0], 0, 9, 10, 11 },
    [KEY_LEFT_CONTROL] = { &led_drivers[0], 0, 15, 16, 17 },

    [KEY_ONE] = { &led_drivers[0], 1, 3, 4, 5 },
    [KEY_LEFT_SHIFT] = { &led_drivers[0], 1, 12, 13, 14 },
    [KEY_LEFT_SUPER] = { &led_drivers[0], 1, 15, 16, 17 },

    [KEY_F1] = { &led_drivers[0], 2, 2, 1, 2 },
    [KEY_TWO] = { &led_drivers[0], 2, 3, 4, 5 },
    [KEY_Q] = { &led_drivers[0], 2, 6, 7, 8 },
    [KEY_A] = { &led_drivers[0], 2, 9, 12, 11 },
    [KEY_Z] = { &led_drivers[0], 2, 12, 13, 14 },

    [KEY_F2] = { &led_drivers[0], 3, 3, 1, 2 },
    [KEY_THREE] = { &led_drivers[0], 3, 3, 4, 5 },
    [KEY_W] = { &led_drivers[0], 3, 6, 7, 8 },
    [KEY_S] = { &led_drivers[0], 3, 9, 13, 11 },
    [KEY_X] = { &led_drivers[0], 3, 12, 13, 14 },
    [KEY_LEFT_ALT] = { &led_drivers[0], 3, 15, 16, 17 },

    [KEY_F3] = { &led_drivers[0], 4, 4, 1, 2 },
    [KEY_FOUR] = { &led_drivers[0], 4, 3, 4, 5 },
    [KEY_E] = { &led_drivers[0], 4, 6, 7, 8 },
    [KEY_D] = { &led_drivers[0], 4, 9, 14, 11 },
    [KEY_C] = { &led_drivers[0], 4, 12, 13, 14 },

    [KEY_F4] = { &led_drivers[0], 5, 5, 1, 2 },
    [KEY_FIVE] = { &led_drivers[0], 5, 3, 4, 5 },
    [KEY_R] = { &led_drivers[0], 5, 6, 7, 8 },
    [KEY_F] = { &led_drivers[0], 5, 9, 15, 11 },
    [KEY_V] = { &led_drivers[0], 5, 12, 13, 14 },

    [KEY_SIX] = { &led_drivers[0], 6, 3, 4, 5 },
    [KEY_T] = { &led_drivers[0], 6, 6, 7, 8 },
    [KEY_G] = { &led_drivers[0], 6, 9, 16, 11 },
    [KEY_B] = { &led_drivers[0], 6, 12, 13, 14 },
    [KEY_SPACE] = { &led_drivers[0], 6, 15, 16, 17 },

    [KEY_F5] = { &led_drivers[0], 7, 7, 1, 2 },
    [KEY_SEVEN] = { &led_drivers[0], 7, 3, 4, 5 },
    [KEY_Y] = { &led_drivers[0], 7, 6, 7, 8 },
    [KEY_H] = { &led_drivers[0], 7, 9, 17, 11 },
    [KEY_N] = { &led_drivers[0], 7, 12, 13, 14 },

    [KEY_F6] = { &led_drivers[0], 8, 8, 1, 2 },
    [KEY_EIGHT] = { &led_drivers[0], 8, 3, 4, 5 },
    [KEY_U] = { &led_drivers[0], 8, 6, 7, 8 },
    [KEY_J] = { &led_drivers[0], 8, 9, 18, 11 },
    [KEY_M] = { &led_drivers[0], 8, 12, 13, 14 },

    [KEY_F7] = { &led_drivers[0], 9, 9, 1, 2 },
    [KEY_NINE] = { &led_drivers[0], 9, 3, 4, 5 },
    [KEY_I] = { &led_drivers[0], 9, 6, 7, 8 },
    [KEY_K] = { &led_drivers[0], 9, 9, 19, 11 },
    [KEY_COMMA] = { &led_drivers[0], 9, 12, 13, 14 },

    [KEY_F8] = { &led_drivers[0], 10, 10, 1, 2 },
    [KEY_ZERO] = { &led_drivers[0], 10, 3, 4, 5 },
    [KEY_O] = { &led_drivers[0], 10, 6, 7, 8 },
    [KEY_L] = { &led_drivers[0], 10, 9, 110, 11 },
    [KEY_PERIOD] = { &led_drivers[0], 10, 12, 13, 14 },
    [KEY_RIGHT_ALT] = { &led_drivers[0], 10, 15, 16, 17 },

    [KEY_F9] = { &led_drivers[1], 0, 0, 1, 2 },
    [KEY_MINUS] = { &led_drivers[1], 0, 3, 4, 5 },
    [KEY_P] = { &led_drivers[1], 0, 6, 7, 8 },
    [KEY_SEMICOLON] = { &led_drivers[1], 0, 9, 10, 11 },
    [KEY_SLASH] = { &led_drivers[1], 0, 12, 13, 14 },
    [KEY_RIGHT_SUPER] = { &led_drivers[1], 0, 15, 16, 17 },

    [KEY_F10] = { &led_drivers[1], 1, 0, 1, 2 },
    [KEY_PLUS] = { &led_drivers[1], 1, 3, 4, 5 },
    [KEY_LEFT_SQUARE] = { &led_drivers[1], 1, 6, 7, 8 },
    [KEY_APOSTROPHE] = { &led_drivers[1], 1, 9, 10, 11 },

    [KEY_F11] = { &led_drivers[1], 2, 0, 1, 2 },
    [KEY_RIGHT_SQUARE] = { &led_drivers[1], 2, 6, 7, 8 },
    [KEY_RIGHT_SHIFT] = { &led_drivers[1], 2, 9, 10, 11 },
    [KEY_ENTER] = { &led_drivers[1], 2, 12, 13, 14 },
    [KEY_RIGHT_FN] = { &led_drivers[1], 2, 15, 16, 17 },

    [KEY_F12] = { &led_drivers[1], 3, 0, 1, 2 },
    [KEY_BACKSPACE] = { &led_drivers[1], 3, 3, 4, 5 },
    [KEY_BACKSLASH] = { &led_drivers[1], 3, 6, 7, 8 },
    [KEY_RIGHT_CONTROL] = { &led_drivers[1], 3, 15, 16, 17 },

    [KEY_PRINT_SCREEN] = { &led_drivers[1], 4, 0, 1, 2 },
    [KEY_INSERT] = { &led_drivers[1], 4, 3, 4, 5 },
    [KEY_DELETE] = { &led_drivers[1], 4, 6, 7, 8 },
    [KEY_LEFT_ARROW] = { &led_drivers[1], 4, 15, 16, 17 },

    [KEY_SCROLL_LOCK] = { &led_drivers[1], 5, 0, 1, 2 },
    [KEY_HOME] = { &led_drivers[1], 5, 3, 4, 5 },
    [KEY_END] = { &led_drivers[1], 5, 6, 7, 8 },
    [KEY_UP_ARROW] = { &led_drivers[1], 5, 12, 13, 14 },
    [KEY_DOWN_ARROW] = { &led_drivers[1], 5, 15, 16, 17 },

    [KEY_PAUSE] = { &led_drivers[1], 6, 0, 1, 2 },
    [KEY_PAGE_UP] = { &led_drivers[1], 6, 3, 4, 5 },
    [KEY_PAGE_DOWN] = { &led_drivers[1], 6, 6, 7, 8 },
    [KEY_RIGHT_ARROW] = { &led_drivers[1], 6, 15, 16, 17 },

    [KEY_NUM_LOCK] = { &led_drivers[1], 7, 3, 4, 5 },
    [KEY_NUMPAD_SEVEN] = { &led_drivers[1], 7, 6, 7, 8 },
    [KEY_NUMPAD_FOUR] = { &led_drivers[1], 7, 9, 10, 11 },
    [KEY_NUMPAD_ONE] = { &led_drivers[1], 7, 12, 13, 14 },
    [KEY_NUMPAD_ZERO] = { &led_drivers[1], 7, 15, 16, 17 },

    [KEY_NUMPAD_DIVIDE] = { &led_drivers[1], 8, 3, 4, 5 },
    [KEY_NUMPAD_EIGHT] = { &led_drivers[1], 8, 6, 7, 8 },
    [KEY_NUMPAD_FIVE] = { &led_drivers[1], 8, 9, 10, 11 },
    [KEY_NUMPAD_TWO] = { &led_drivers[1], 8, 12, 13, 14 },

    [KEY_NUMPAD_MULTIPLY] = { &led_drivers[1], 9, 3, 4, 5 },
    [KEY_NUMPAD_NINE] = { &led_drivers[1], 9, 6, 7, 8 },
    [KEY_NUMPAD_SIX] = { &led_drivers[1], 9, 9, 19, 11 },
    [KEY_NUMPAD_THREE] = { &led_drivers[1], 9, 12, 13, 14 },
    [KEY_NUMPAD_PERIOD] = { &led_drivers[1], 9, 15, 16, 17 },

    [KEY_NUMPAD_MINUS] = { &led_drivers[1], 10, 3, 4, 5 },
    [KEY_NUMPAD_PLUS] = { &led_drivers[1], 10, 6, 7, 8 },
    [KEY_NUMPAD_ENTER] = { &led_drivers[1], 10, 12, 13, 14 },
};

int led_matrix_read_byte(struct led_driver *driver, uint16_t reg, uint8_t *data) {
    uint8_t buf[1];
    uint8_t addr = driver->base_address | ((reg >> 8) & 0x03);
    mxc_i2c_req_t req = {
        .i2c = driver->i2c,
        .addr = addr,
        .tx_buf = buf,
        .tx_len = 1,
        .rx_buf = data,
        .rx_len = 1,
        .restart = 0,
        .callback = NULL
    };

    buf[0] = reg & 0xFF;

    return MXC_I2C_MasterTransaction(&req);
}

int led_matrix_write_byte(struct led_driver *driver, uint16_t reg, uint8_t data) {
    uint8_t buf[2];
    uint8_t addr = driver->base_address | ((reg >> 8) & 0x03);
    mxc_i2c_req_t req = {
        .i2c = driver->i2c,
        .addr = addr,
        .tx_buf = buf,
        .tx_len = 2,
        .rx_buf = NULL,
        .rx_len = 0,
        .restart = 0,
        .callback = NULL
    };

    buf[0] = reg & 0xFF;
    buf[1] = data;

    return MXC_I2C_MasterTransaction(&req);
}

int led_matrix_write_rgb(struct led_matrix *led, uint8_t red, uint8_t green, uint8_t blue) {
    int ret;
    uint8_t buf[4];
    uint16_t reg = LP5860_REG_DOT0_PWM + (led->column * 18) + led->row_red;
    uint8_t addr = led->driver->base_address | ((reg >> 8) & 0x03);
    mxc_i2c_req_t req = {
        .i2c = led->driver->i2c,
        .addr = addr,
        .tx_buf = buf,
        .tx_len = 2,
        .rx_buf = NULL,
        .rx_len = 0,
        .restart = 0,
        .callback = NULL
    };

    size_t offset = led - led_matrix;
    if (offset >= KEY_LEN || ((uint8_t *) key_matrix)[offset] == KEY_INVALID) {
        // TODO: error here?
        return E_NO_ERROR;
    }

    buf[0] = reg & 0xFF;
    buf[1] = red;
    buf[2] = green;
    buf[3] = blue;

    uint16_t reg2 = LP5860_REG_DOT0_PWM + (led->column * 18);
    ret = led_matrix_write_byte(led->driver, reg2 + led->row_red, red);
    ret = led_matrix_write_byte(led->driver, reg2 + led->row_green, green);
    ret = led_matrix_write_byte(led->driver, reg2 + led->row_blue, blue);
    //ret = MXC_I2C_MasterTransaction(&req);
    if (ret == E_NO_ERROR) {
        led->red = red;
        led->green = green;
        led->blue = blue;
    }

    return ret;
}

int led_matrix_write_color(struct led_matrix *led, enum color color) {
    union color_definition cd = color_values[color];

    return led_matrix_write_rgb(led, cd.red, cd.green, cd.blue);
}

int led_matrix_init() {
    uint8_t reg;

    for (int i = 1; i < LED_NUM_DRIVER; i++) {
        led_matrix_write_byte(&led_drivers[i], LP5860_REG_RESET, LP5860_RESET_KEY);
    }
    MXC_Delay(MXC_DELAY_MSEC(50));    

    for (int i = 1; i < LED_NUM_DRIVER; i++) {
        // Enable the chip
        led_matrix_write_byte(&led_drivers[i], LP5860_REG_CHIP_EN, LP5860_REG_CHIP_EN_MASK_EN);

        // Set refresh mode to one to get rid of the VSYNC requirement
        led_matrix_read_byte(&led_drivers[i], LP5860_REG_DEV_INITIAL, &reg);
        reg &= ~LP5860_REG_DEV_INITIAL_MASK_DATA_REFRESH_MODE;
        reg |= LP5860_REG_DEV_INITIAL_DATA_REFRESH_MODE_ONE;
        led_matrix_write_byte(&led_drivers[i], LP5860_REG_DEV_INITIAL, reg);

        led_matrix_read_byte(&led_drivers[i], LP5860_REG_DEV_CONFIG2, &reg);
        reg |= 0x02;
        led_matrix_write_byte(&led_drivers[i], LP5860_REG_DEV_CONFIG2, reg);

        // Write group data so all red, green, and blue LEDs are separate groups
        for (int j = 0; j < 11; j++) {
            led_matrix_write_byte(&led_drivers[i], LP5860_REG_DOT0_GROUP + (5 * j), 0b01111001);
            led_matrix_write_byte(&led_drivers[i], LP5860_REG_DOT1_GROUP + (5 * j), 0b10011110);
            led_matrix_write_byte(&led_drivers[i], LP5860_REG_DOT2_GROUP + (5 * j), 0b11100111);
            led_matrix_write_byte(&led_drivers[i], LP5860_REG_DOT3_GROUP + (5 * j), 0b01111001);
            led_matrix_write_byte(&led_drivers[i], LP5860_REG_DOT4_GROUP + (5 * j), 0b00001110);
        }

        for (int j = 0; j < 11; j++) {
            uint8_t on[3];

            led_matrix_read_byte(&led_drivers[i], LP5860_REG_DOT0_ON + (3 * j), &on[0]);
            led_matrix_read_byte(&led_drivers[i], LP5860_REG_DOT1_ON + (3 * j), &on[1]);
            led_matrix_read_byte(&led_drivers[i], LP5860_REG_DOT2_ON + (3 * j), &on[2]);

            if (on[0] != 0xFF) {
                printf("Invalid DOT ON0 0x%02X: 0x%02X\n", LP5860_REG_DOT0_ON + (3 * j), on[0]);
            }
            if (on[1] != 0xFF) {
                printf("Invalid DOT ON1 0x%02X: 0x%02X\n", LP5860_REG_DOT1_ON + (3 * j), on[1]);
            }
            if (on[2] != 0x03) {
                printf("Invalid DOT ON2 0x%02X: 0x%02X\n", LP5860_REG_DOT2_ON + (3 * j), on[2]);
            }
        }

        // Prescale LED PWMs by group so they have roughly the same brightness
        led_matrix_write_byte(&led_drivers[i], LP5860_REG_GROUP0_BRIGHTNESS, color_prescale.red);
        led_matrix_write_byte(&led_drivers[i], LP5860_REG_GROUP1_BRIGHTNESS, color_prescale.green);
        led_matrix_write_byte(&led_drivers[i], LP5860_REG_GROUP2_BRIGHTNESS, color_prescale.blue);
    }

    return 0;
}
