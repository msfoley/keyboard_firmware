#ifndef COLORS_H
#define COLORS_H

#include <stdint.h>

enum color {
    COLOR_OFF,
    COLOR_RED,
    COLOR_GREEN,
    COLOR_BLUE,
    COLOR_YELLOW,
    COLOR_CYAN,
    COLOR_PURPLE,
    COLOR_WHITE,
    COLOR_LEN,
    COLOR_CUSTOM
};

struct color_prescale {
    uint8_t red;
    uint8_t green;
    uint8_t blue;
};

union color_definition {
    uint32_t value;

    struct {
        uint8_t red;
        uint8_t green;
        uint8_t blue;
        uint8_t pad;
    };
};

extern struct color_prescale color_prescale;
extern union color_definition color_values[COLOR_LEN];

#endif
