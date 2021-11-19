/***************************************************************************//**
 *   @file    app_config_mbed.c
 *   @brief   Application configurations module for Mbed platform
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

#include <stdbool.h>
#include "app_config.h"
#include "app_config_mbed.h"

/******************************************************************************/
/************************ Macros/Constants ************************************/
/******************************************************************************/

/******************************************************************************/
/******************** Variables and User Defined Data Types *******************/
/******************************************************************************/

/* UART Mbed platform specific init parameters */
mbed_uart_init_param mbed_uart_extra_init_params = {
#if defined(USE_VIRTUAL_COM_PORT)
	.virtual_com_enable = true,
	.vendor_id = VIRTUAL_COM_PORT_VID,
	.product_id = VIRTUAL_COM_PORT_PID,
	.serial_number = VIRTUAL_COM_SERIAL_NUM
#else
	.uart_tx_pin = UART_TX,
	.uart_rx_pin = UART_RX,
	.virtual_com_enable = false
#endif
};

/* SPI Mbed platform specific parameters */
mbed_spi_init_param mbed_spi_extra_init_params = {
	.spi_clk_pin = SPI_SCK,
	.spi_miso_pin = SPI_HOST_SDI,
	.spi_mosi_pin = SPI_HOST_SDO,
	.use_sw_csb = false		// Use hw controlled CSB pin
};

/* External interrupt Mbed platform specific parameters */
mbed_irq_init_param mbed_ext_int_extra_init_params = {
	.int_mode = EXT_IRQ_FALL,
	.ext_int_pin = CONV_INT_GPIO,
	.int_obj_type = NULL
};

/* PWM Mbed platform specific parameters */
mbed_pwm_init_param mbed_pwm_extra_init_params = {
	.pwm_pin = CONV_INT_GPIO	// Unused currently. PWM ID is used for seting GPIO
};

/* Define LDACB pin platform specific parameters structure */
mbed_gpio_init_param mbed_ldac_gpio_extra_init_params = {
	.pin_mode = PullNone
};

/* Define RESETB pin platform specific parameters structure */
mbed_gpio_init_param mbed_reset_gpio_extra_init_params = {
	.pin_mode = PullNone
};

/* Define TGP pin platform specific parameters structure */
mbed_gpio_init_param mbed_tgp_gpio_extra_init_params = {
	.pin_mode = PullNone
};

/* Define CONVSTB pin platform specific parameters structure */
mbed_gpio_init_param mbed_convst_gpio_extra_init_params = {
	.pin_mode = PullNone
};

/* Define BUSY pin platform specific parameters structure */
mbed_gpio_init_param mbed_busy_gpio_extra_init_params = {
	.pin_mode = PullNone
};

/* Define CONV_INT pin platform specific parameters structure */
mbed_gpio_init_param mbed_conv_int_gpio_extra_init_params = {
	.pin_mode = PullNone
};

/******************************************************************************/
/************************** Functions Declarations ****************************/
/******************************************************************************/

/******************************************************************************/
/************************** Functions Definitions *****************************/
/******************************************************************************/
