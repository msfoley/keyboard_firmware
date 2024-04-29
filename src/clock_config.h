#ifndef CLOCK_CONFIG_H
#define CLOCK_CONFIG_H

#include "fsl_common.h"

#define BOARD_XTAL0_CLK_HZ                         24000000U  /*!< Board xtal0 frequency in Hz */
#define BOARD_XTAL32K_CLK_HZ                          32768U  /*!< Board xtal32k frequency in Hz */
#define BOARD_BOOTCLOCKRUN_CORE_CLOCK              12000000U  /*!< Core clock frequency: 12000000Hz */

/* Clock outputs (values are in Hz): */
#define BOARD_BOOTCLOCKRUN_AHB_CLK_ROOT               12000000UL
#define BOARD_BOOTCLOCKRUN_CAN_CLK_ROOT               2000000UL
#define BOARD_BOOTCLOCKRUN_CKIL_SYNC_CLK_ROOT         0UL
#define BOARD_BOOTCLOCKRUN_CLKO1_CLK                  0UL
#define BOARD_BOOTCLOCKRUN_CLKO2_CLK                  0UL
#define BOARD_BOOTCLOCKRUN_CLK_1M                     1000000UL
#define BOARD_BOOTCLOCKRUN_CLK_24M                    24000000UL
#define BOARD_BOOTCLOCKRUN_ENET2_125M_CLK             1200000UL
#define BOARD_BOOTCLOCKRUN_ENET2_REF_CLK              0UL
#define BOARD_BOOTCLOCKRUN_ENET2_TX_CLK               0UL
#define BOARD_BOOTCLOCKRUN_ENET_125M_CLK              2400000UL
#define BOARD_BOOTCLOCKRUN_ENET_25M_REF_CLK           1200000UL
#define BOARD_BOOTCLOCKRUN_ENET_REF_CLK               0UL
#define BOARD_BOOTCLOCKRUN_ENET_TX_CLK                0UL
#define BOARD_BOOTCLOCKRUN_FLEXIO1_CLK_ROOT           1500000UL
#define BOARD_BOOTCLOCKRUN_FLEXIO2_CLK_ROOT           1500000UL
#define BOARD_BOOTCLOCKRUN_FLEXSPI2_CLK_ROOT          12000000UL
#define BOARD_BOOTCLOCKRUN_FLEXSPI_CLK_ROOT           2000000UL
#define BOARD_BOOTCLOCKRUN_GPT1_IPG_CLK_HIGHFREQ      3000000UL
#define BOARD_BOOTCLOCKRUN_GPT2_IPG_CLK_HIGHFREQ      3000000UL
#define BOARD_BOOTCLOCKRUN_IPG_CLK_ROOT               3000000UL
#define BOARD_BOOTCLOCKRUN_LPI2C_CLK_ROOT             3000000UL
#define BOARD_BOOTCLOCKRUN_LPSPI_CLK_ROOT             6000000UL
#define BOARD_BOOTCLOCKRUN_LVDS1_CLK                  24000000UL
#define BOARD_BOOTCLOCKRUN_MQS_MCLK                   3000000UL
#define BOARD_BOOTCLOCKRUN_PERCLK_CLK_ROOT            3000000UL
#define BOARD_BOOTCLOCKRUN_PLL7_MAIN_CLK              24000000UL
#define BOARD_BOOTCLOCKRUN_SAI1_CLK_ROOT              3000000UL
#define BOARD_BOOTCLOCKRUN_SAI1_MCLK1                 3000000UL
#define BOARD_BOOTCLOCKRUN_SAI1_MCLK2                 3000000UL
#define BOARD_BOOTCLOCKRUN_SAI1_MCLK3                 1500000UL
#define BOARD_BOOTCLOCKRUN_SAI2_CLK_ROOT              3000000UL
#define BOARD_BOOTCLOCKRUN_SAI2_MCLK1                 3000000UL
#define BOARD_BOOTCLOCKRUN_SAI2_MCLK2                 0UL
#define BOARD_BOOTCLOCKRUN_SAI2_MCLK3                 1500000UL
#define BOARD_BOOTCLOCKRUN_SAI3_CLK_ROOT              3000000UL
#define BOARD_BOOTCLOCKRUN_SAI3_MCLK1                 3000000UL
#define BOARD_BOOTCLOCKRUN_SAI3_MCLK2                 0UL
#define BOARD_BOOTCLOCKRUN_SAI3_MCLK3                 1500000UL
#define BOARD_BOOTCLOCKRUN_SEMC_CLK_ROOT              4000000UL
#define BOARD_BOOTCLOCKRUN_SPDIF0_CLK_ROOT            1500000UL
#define BOARD_BOOTCLOCKRUN_SPDIF0_EXTCLK_OUT          0UL
#define BOARD_BOOTCLOCKRUN_TRACE_CLK_ROOT             6000000UL
#define BOARD_BOOTCLOCKRUN_UART_CLK_ROOT              4000000UL
#define BOARD_BOOTCLOCKRUN_USBPHY1_CLK                0UL
#define BOARD_BOOTCLOCKRUN_USBPHY2_CLK                0UL
#define BOARD_BOOTCLOCKRUN_USDHC1_CLK_ROOT            12000000UL
#define BOARD_BOOTCLOCKRUN_USDHC2_CLK_ROOT            12000000UL

extern const clock_arm_pll_config_t clock_config_pll_arm;
extern const clock_sys_pll_config_t clock_config_pll_sys;
extern const clock_enet_pll_config_t clock_config_pll_enet;

void clock_config();

#endif /* CLOCK_CONFIG_H */

