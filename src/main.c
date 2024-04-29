#include <stdlib.h>
#include <stdint.h>

int main() {
    clock_config();
    mpu_config();

    uart_console_init();
}
