/***************************************************************************//**
 * @file    ad70081z_user_config.c
 * @brief   User configurations for AD70081z No-OS driver
********************************************************************************
* Copyright (c) 2021 Analog Devices, Inc.
* All rights reserved.
*
* This software is proprietary to Analog Devices, Inc. and its licensors.
* By using this software you agree to the terms of the associated
* Analog Devices Software License Agreement.
*******************************************************************************/

/******************************************************************************/
/***************************** Include Files **********************************/
/******************************************************************************/

#include "ad70081z_user_config.h"
#include "app_config.h"
#include "gpio.h"

/******************************************************************************/
/********************* Macros and Constants Definition ************************/
/******************************************************************************/

/******************************************************************************/
/******************** Variables and User Defined Data Types *******************/
/******************************************************************************/

/* LDAC GPIO init parameters */
struct gpio_init_param ldac_gpio_init_param = {
	.number = LDACB_GPIO,
	.platform_ops = NULL,
	.extra = &ldac_gpio_extra_init_params
};

/* RESET GPIO init parameters */
struct gpio_init_param reset_gpio_init_param = {
	.number = RESETB_GPIO,
	.platform_ops = NULL,
	.extra = &reset_gpio_extra_init_params
};

/* TGP GPIO init parameters */
struct gpio_init_param tgp_gpio_init_param = {
	.number = TGP_GPIO,
	.platform_ops = NULL,
	.extra = &tgp_gpio_extra_init_params
};

/* CONVST GPIO init parameters */
struct gpio_init_param convst_gpio_init_param = {
	.number = CONVST_GPIO,
	.platform_ops = NULL,
	.extra = &convst_gpio_extra_init_params
};

/* BUSY GPIO init parameters */
struct gpio_init_param busy_gpio_init_param = {
	.number = BUSY_GPIO,
	.platform_ops = NULL,
	.extra = &busy_gpio_extra_init_params
};

/* AD70081z No-OS driver init parameters */
struct ad70081z_init_param ad70081z_init_params = {
	.spi_init = {
		.max_speed_hz = 20000000,
		.mode = SPI_MODE_0,
		.chip_select = SPI_CSB,
		.extra = &spi_extra_init_params
	},

	.gpio_reset_n = &reset_gpio_init_param,
	.gpio_ldac_n = &ldac_gpio_init_param,
	.gpio_tgp = &tgp_gpio_init_param,
	.gpio_convst = &convst_gpio_init_param,

	.dev_spi_settings = {
		.addr_ascension = false,
		.short_instruction = false,
		.crc_enabled = false
	},

	.custom_mode = AD70081Z_REGISTER_ACCESS_MODE,
	.osr = (enum ad70081z_adc_config_osr)DEFAULT_OSR,
	.enable_internal_reference = true,

	/* IADC channels Rsense value */
	.iadc_rsense[0] = 0,
	.iadc_rsense[1] = 0,
	.iadc_rsense[2] = 0,
	.iadc_rsense[3] = 0,
	.iadc_rsense[4] = 0,
	.iadc_rsense[5] = 0,
	.iadc_rsense[6] = 0,
	.iadc_rsense[7] = 0,

	/* IADC TOND_IS channels input current range */
	.idac_tond_is_current_range[0] = AD70081Z_IADC_RANGE_6p25_50uA,
	.idac_tond_is_current_range[1] = AD70081Z_IADC_RANGE_6p25_50uA,
	.idac_tond_is_current_range[2] = AD70081Z_IADC_RANGE_6p25_50uA,
	.idac_tond_is_current_range[3] = AD70081Z_IADC_RANGE_6p25_50uA,
};
