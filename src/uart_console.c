#include <fsl_common.h>
#include <fsl_debug_console.h>
#include <fsl_clock.h>

#include "uart_console.h"

/* Get debug console frequency. */
uint32_t uart_console_frequency() {
    uint32_t freq;

    /* To make it simple, we assume default PLL and divider settings, and the only variable
       from application is use PLL3 source or OSC source */
    if (CLOCK_GetMux(kCLOCK_UartMux) == 0) {
        /* PLL3 div6 80M */
        freq = (CLOCK_GetPllFreq(kCLOCK_PllUsb1) / 6U) / (CLOCK_GetDiv(kCLOCK_UartDiv) + 1U);
    } else {
        freq = CLOCK_GetOscFreq() / (CLOCK_GetDiv(kCLOCK_UartDiv) + 1U);
    }

    return freq;
}

/* Initialize debug console. */
void uart_console_init() {
    uint32_t uartClkSrcFreq = uart_console_frequency();

    DbgConsole_Init(BOARD_DEBUG_UART_INSTANCE, BOARD_DEBUG_UART_BAUDRATE, BOARD_DEBUG_UART_TYPE, uartClkSrcFreq);
}
