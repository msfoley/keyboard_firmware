#ifndef UART_CONSOLE_H
#define UART_CONSOLE_H

#include <stdint.h>

#define UART_CONSOLE_TYPE     kSerialPort_Uart
#define UART_CONSOLE_BASEADDR (uint32_t) LPUART6
#define UART_CONSOLE_INSTANCE 6U

#define UART_CONSOLE_CLK_FREQ BOARD_DebugConsoleSrcFreq()

#define UART_CONSOLE_IRQ         LPUART6_IRQn
#define UART_CONSOLE_IRQ_HANDLER LPUART6_IRQHandler

#ifndef UART_CONSOLE_BAUDRATE
#define UART_CONSOLE_BAUDRATE (115200U)
#endif

void uart_console_frequency();
void uart_console_init();

#endif
