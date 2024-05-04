#include <color.h>

struct color_prescale color_prescale = {
    .red = 0xE0,
    .green = 0x40, 
    .blue = 0x40
};

union color_definition color_values[COLOR_LEN] = {
    [COLOR_OFF] = { .red = 0x00, .green = 0x00, .blue = 0x00 },
    [COLOR_RED] = { .red = 0xFF, .green = 0x00, .blue = 0x00 },
    [COLOR_GREEN] = { .red = 0x00, .green = 0xFF, .blue = 0x00 },
    [COLOR_BLUE] = { .red = 0x00, .green = 0x00, .blue = 0xFF },
    [COLOR_YELLOW] = { .red = 0xFF, .green = 0xFF, .blue = 0x00 },
    [COLOR_CYAN] = { .red = 0x00, .green = 0xFF, .blue = 0xFF },
    [COLOR_PURPLE] = { .red = 0xFF, .green = 0x00, .blue = 0xFF },
    [COLOR_WHITE] = { .red = 0xFF, .green = 0xFF , .blue = 0xFF }
};
