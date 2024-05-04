#ifndef LED_MATRIX_H
#define LED_MATRIX_H

#include <stdint.h>

#include "i2c.h"
#include "i2c_regs.h"

#include <color.h>

#define LED_NUM_DRIVER 2

#define LP5860_REG_CHIP_EN 0x0000
#define LP5860_REG_CHIP_EN_MASK_EN 0x01

#define LP5860_REG_DEV_INITIAL 0x0001
#define LP5860_REG_DEV_INITIAL_MASK_DATA_REFRESH_MODE 0x06
#define LP5860_REG_DEV_INITIAL_MASK_PWM_FREQUENCY 0x01
#define LP5860_REG_DEV_INITIAL_DATA_REFRESH_MODE_ONE 0x00
#define LP5860_REG_DEV_INITIAL_DATA_REFRESH_MODE_TWO 0x01
#define LP5860_REG_DEV_INITIAL_DATA_REFRESH_MODE_THREE 0x02

#define LP5860_REG_DEV_CONFIG1 0x0002

#define LP5860_REG_DEV_CONFIG2 0x0003

#define LP5860_REG_DEV_CONFIG3 0x0004
#define LP5860_REG_DEV_CONFIG3_MAXIMUM_CURRENT_3MA (0x00 << 1)
#define LP5860_REG_DEV_CONFIG3_MAXIMUM_CURRENT_5MA (0x01 << 1)
#define LP5860_REG_DEV_CONFIG3_MAXIMUM_CURRENT_10MA (0x02 << 1)
#define LP5860_REG_DEV_CONFIG3_MAXIMUM_CURRENT_15MA (0x03 << 1)
#define LP5860_REG_DEV_CONFIG3_MAXIMUM_CURRENT_20MA (0x04 << 1)
#define LP5860_REG_DEV_CONFIG3_MAXIMUM_CURRENT_30MA (0x05 << 1)
#define LP5860_REG_DEV_CONFIG3_MAXIMUM_CURRENT_40MA (0x06 << 1)
#define LP5860_REG_DEV_CONFIG3_MAXIMUM_CURRENT_50MA (0x07 << 1)

#define LP5860_REG_MASTER_BRIGHTNESS 0x0005
#define LP5860_REG_GROUP0_BRIGHTNESS 0x0006
#define LP5860_REG_GROUP1_BRIGHTNESS 0x0007
#define LP5860_REG_GROUP2_BRIGHTNESS 0x0008

#define LP5860_REG_DOT0_GROUP 0x000C
#define LP5860_REG_DOT1_GROUP 0x000D
#define LP5860_REG_DOT2_GROUP 0x000E
#define LP5860_REG_DOT3_GROUP 0x000F
#define LP5860_REG_DOT4_GROUP 0x0010

#define LP5860_REG_DOT0_ON 0x0043
#define LP5860_REG_DOT1_ON 0x0044
#define LP5860_REG_DOT2_ON 0x0045

#define LP5860_REG_RESET 0x00A9
#define LP5860_RESET_KEY 0xFF

#define LP5860_REG_DOT0_PWM 0x0200

struct led_driver {
    uint8_t base_address;
    mxc_i2c_regs_t *i2c;
};

struct led_matrix {
    struct led_driver *driver;

    uint8_t column;
    uint8_t row_red;
    uint8_t row_green;
    uint8_t row_blue;

    uint8_t red;
    uint8_t green;
    uint8_t blue;
};

extern struct led_driver led_drivers[LED_NUM_DRIVER];
extern struct led_matrix led_matrix[];

int led_matrix_read_byte(struct led_driver *driver, uint16_t reg, uint8_t *data);
int led_matrix_write_byte(struct led_driver *driver, uint16_t reg, uint8_t data);

int led_matrix_write_rgb(struct led_matrix *led, uint8_t red, uint8_t green, uint8_t blue);
int led_matrix_write_color(struct led_matrix *led, enum color color);

int led_matrix_init();

#endif
