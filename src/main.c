/******************************************************************************
 *
 * Copyright (C) 2022-2023 Maxim Integrated Products, Inc. All Rights Reserved.
 * (now owned by Analog Devices, Inc.),
 * Copyright (C) 2023 Analog Devices, Inc. All Rights Reserved. This software
 * is proprietary to Analog Devices, Inc. and its licensors.
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 *
 ******************************************************************************/

/**
 * @file        main.c
 * @brief     Example code for scanning the available addresses on an I2C bus
 * @details     This example uses the I2C Master to found addresses of the I2C Slave devices 
 *              connected to the bus. You must connect the pull-up jumpers (JP21 and JP22) 
 *              to the proper I/O voltage.
 */

/***** Includes *****/
#include <stdio.h>
#include <stdint.h>
#include <string.h>
#include "mxc_device.h"
#include "mxc_delay.h"
#include "nvic_table.h"
#include "i2c.h"
#include "i2c_regs.h"
#include "uart.h"
#include "tmr.h"

#include <color.h>
#include <key_def.h>
#include <led_matrix.h>

/***** Definitions *****/
#define I2C_MASTER MXC_I2C1 // SDA P2_17; SCL P2_18
#define I2C_FREQ 10000 // 100kHZ

const mxc_gpio_cfg_t row[6] = {
    { MXC_GPIO2, MXC_GPIO_PIN_0, MXC_GPIO_FUNC_IN, MXC_GPIO_PAD_WEAK_PULL_DOWN, MXC_GPIO_VSSEL_VDDIOH, MXC_GPIO_DRVSTR_0 },
    { MXC_GPIO2, MXC_GPIO_PIN_1, MXC_GPIO_FUNC_IN, MXC_GPIO_PAD_WEAK_PULL_DOWN, MXC_GPIO_VSSEL_VDDIOH, MXC_GPIO_DRVSTR_0 },
    { MXC_GPIO2, MXC_GPIO_PIN_2, MXC_GPIO_FUNC_IN, MXC_GPIO_PAD_WEAK_PULL_DOWN, MXC_GPIO_VSSEL_VDDIOH, MXC_GPIO_DRVSTR_0 },
    { MXC_GPIO2, MXC_GPIO_PIN_3, MXC_GPIO_FUNC_IN, MXC_GPIO_PAD_WEAK_PULL_DOWN, MXC_GPIO_VSSEL_VDDIOH, MXC_GPIO_DRVSTR_0 },
    { MXC_GPIO2, MXC_GPIO_PIN_4, MXC_GPIO_FUNC_IN, MXC_GPIO_PAD_WEAK_PULL_DOWN, MXC_GPIO_VSSEL_VDDIOH, MXC_GPIO_DRVSTR_0 },
    { MXC_GPIO2, MXC_GPIO_PIN_5, MXC_GPIO_FUNC_IN, MXC_GPIO_PAD_WEAK_PULL_DOWN, MXC_GPIO_VSSEL_VDDIOH, MXC_GPIO_DRVSTR_0 },
};

const mxc_gpio_cfg_t column[4] = {
    { MXC_GPIO3, MXC_GPIO_PIN_1, MXC_GPIO_FUNC_OUT, MXC_GPIO_PAD_NONE, MXC_GPIO_VSSEL_VDDIOH, MXC_GPIO_DRVSTR_0 },
    { MXC_GPIO3, MXC_GPIO_PIN_2, MXC_GPIO_FUNC_OUT, MXC_GPIO_PAD_NONE, MXC_GPIO_VSSEL_VDDIOH, MXC_GPIO_DRVSTR_0 },
    { MXC_GPIO3, MXC_GPIO_PIN_3, MXC_GPIO_FUNC_OUT, MXC_GPIO_PAD_NONE, MXC_GPIO_VSSEL_VDDIOH, MXC_GPIO_DRVSTR_0 },
    { MXC_GPIO3, MXC_GPIO_PIN_4, MXC_GPIO_FUNC_OUT, MXC_GPIO_PAD_NONE, MXC_GPIO_VSSEL_VDDIOH, MXC_GPIO_DRVSTR_0 },
};

/***** Globals *****/
const mxc_gpio_cfg_t vsync = {
    MXC_GPIO2, MXC_GPIO_PIN_13, MXC_GPIO_FUNC_OUT, MXC_GPIO_PAD_NONE, MXC_GPIO_VSSEL_VDDIO, MXC_GPIO_DRVSTR_0
};

const mxc_gpio_cfg_t vio_en = {
    MXC_GPIO2, MXC_GPIO_PIN_15, MXC_GPIO_FUNC_OUT, MXC_GPIO_PAD_NONE, MXC_GPIO_VSSEL_VDDIO, MXC_GPIO_DRVSTR_0
};

void ContinuousTimerHandler() {
    // Clear interrupt
    MXC_TMR_ClearFlags(MXC_TMR0);
    MXC_GPIO_OutToggle(vsync.port, vsync.mask);
}

void ContinuousTimer() {
    // Declare variables
    mxc_tmr_cfg_t tmr;

    /*
    Steps for configuring a timer for PWM mode:
    1. Disable the timer
    2. Set the prescale value
    3  Configure the timer for continuous mode
    4. Set polarity, timer parameters
    5. Enable Timer
    */

    MXC_TMR_Shutdown(MXC_TMR0);

    MXC_NVIC_SetVector(TMR0_IRQn, ContinuousTimerHandler);
    NVIC_EnableIRQ(TMR0_IRQn);

    tmr.pres = TMR_PRES_4;
    tmr.mode = TMR_MODE_CONTINUOUS;
    tmr.cmp_cnt = PeripheralClock / 480; //SystemCoreClock*(1/interval_time);
    tmr.pol = 0;

    MXC_TMR_Init(MXC_TMR0, &tmr);

    MXC_TMR_Start(MXC_TMR0);
}

// *****************************************************************************
int main() {
    int error;
    
    MXC_GPIO_Init(MXC_GPIO_GET_IDX(MXC_GPIO2));
    MXC_GPIO_Init(MXC_GPIO_GET_IDX(MXC_GPIO3));

    MXC_GPIO_Config(&vsync);
    MXC_GPIO_OutSet(vsync.port, vsync.mask);

    MXC_GPIO_Config(&vio_en);
    MXC_GPIO_OutSet(vio_en.port, vio_en.mask);
    //MXC_UART_Init(ConsoleUart, CONSOLE_BAUD);

    //Setup the I2CM
    error = MXC_I2C_Init(I2C_MASTER, 1, 0);
    if (error != E_NO_ERROR) {
        printf("-->Failed master, err:%d\n", error);
        return -1;
    } else {
        printf("\n-->I2C Master Initialization Complete\n");
    }
    MXC_I2C_SetFrequency(I2C_MASTER, 100000);

    led_matrix_init();

    for (int i = KEY_F9; i < KEY_LEN; i++) {
        led_matrix_write_color(&led_matrix[i], COLOR_OFF);
    }

    //ContinuousTimer();

    MXC_Delay(MXC_DELAY_MSEC(1000));

    enum color color = COLOR_OFF;
    /*while (1) {
        for (int i = KEY_F9; i < KEY_LEN; i++) {
            led_matrix_write_color(&led_matrix[i], color);
            //MXC_Delay(MXC_DELAY_MSEC(50));
        }

        if (++color >= COLOR_LEN) {
            color = COLOR_OFF;
        }
        MXC_Delay(MXC_DELAY_MSEC(250));
    }*/
    
    uint8_t pin_mask = 0;
    for (int i = 0; i < 4; i++) {
        MXC_GPIO_Config(&column[i]);
    }
    for (int i = 0; i < 6; i++) {
        MXC_GPIO_Config(&row[i]);
        pin_mask |= row[i].mask;
    }

    enum color current_color[KEY_NUM_COLUMN][KEY_NUM_ROW] = { COLOR_OFF };
    while (1) {
        for (int i = 0; i < 4; i++) {
            uint32_t r = 0;
            MXC_GPIO_OutSet(column[i].port, column[i].mask);
            MXC_Delay(MXC_DELAY_MSEC(1));
            r = (MXC_GPIO_InGet(row[0].port, pin_mask));
            MXC_GPIO_OutClr(column[i].port, column[i].mask);

            for (int j = 0; j < 6; j++) {
                enum key_matrix key = key_matrix[i + 18][j];
                int pressed = (r >> j) & 0x01;

                if (pressed && !key_matrix_state[i + 18][j].pressed) {
                    current_color[i + 18][j]++;
                    if (current_color[i + 18][j] >= COLOR_LEN) {
                        current_color[i + 18][j] = COLOR_OFF;
                    }

                    led_matrix_write_color(&led_matrix[key], current_color[i + 18][j]);
                }
                key_matrix_state[i + 18][j].pressed = pressed;
            }
        }
    }

    return 0;
}
