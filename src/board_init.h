// Copyright (c) 2020 XMOS LIMITED. This Software is subject to the terms of the
// XMOS Public License: Version 1

#ifndef BOARD_INIT_H_
#define BOARD_INIT_H_

#include "rtos/drivers/intertile/api/rtos_intertile.h"
#include "rtos/drivers/mic_array/api/rtos_mic_array.h"
#include "rtos/drivers/i2c/api/rtos_i2c_master.h"
#include "rtos/drivers/i2s/api/rtos_i2s.h"
#include "rtos/drivers/qspi_flash/api/rtos_qspi_flash.h"
#include "rtos/drivers/gpio/api/rtos_gpio.h"

#define AUDIO_CLOCK_FREQUENCY 24576000
#define PDM_CLOCK_FREQUENCY    3072000

void board_tile0_init(
        chanend_t tile1,
        rtos_intertile_t *intertile_ctx,
        rtos_i2c_master_t *i2c_master_ctx,
        rtos_gpio_t *gpio_ctx_t0,
        rtos_gpio_t *gpio_ctx_t1,
        rtos_qspi_flash_t *qspi_flash_ctx);

void board_tile1_init(
        chanend_t tile0,
        rtos_intertile_t *intertile_ctx,
        rtos_mic_array_t *mic_array_ctx,
        rtos_i2s_t *i2s_ctx,
        rtos_gpio_t *gpio_ctx_t0,
        rtos_gpio_t *gpio_ctx_t1);

#endif /* BOARD_INIT_H_ */
