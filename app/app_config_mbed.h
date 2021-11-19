/***************************************************************************//**
 *   @file    app_config_mbed.h
 *   @brief   Header file for Mbed platform configurations
********************************************************************************
 * Copyright (c) 2021 Analog Devices, Inc.
 * All rights reserved.
 *
 * This software is proprietary to Analog Devices, Inc. and its licensors.
 * By using this software you agree to the terms of the associated
 * Analog Devices Software License Agreement.
*******************************************************************************/

#ifndef APP_CONFIG_MBED_H_
#define APP_CONFIG_MBED_H_

/******************************************************************************/
/***************************** Include Files **********************************/
/******************************************************************************/

#include <stdint.h>
#include <PinNames.h>

#include "uart_extra.h"
#include "spi_extra.h"
#include "gpio_extra.h"
#include "irq_extra.h"
#include "pwm_extra.h"

/******************************************************************************/
/********************** Macros and Constants Definition ***********************/
/******************************************************************************/

/* Pin mapping of SDP-K1 w.r.t Arduino connector */
#define SPI_CSB			D10
#define SPI_HOST_SDO	D11
#define SPI_HOST_SDI	D12
#define SPI_SCK			D13
#define LDACB_GPIO		D9
#define RESETB_GPIO		D8
#define TGP_GPIO		D7
#define CONVST_GPIO		D6
#define BUSY_GPIO		D5

/* This pin is used as conversion trigger and EOC (both pwm and interrupt) */
#define CONV_INT_GPIO	D3

/* Common pin mapping on SDP-K1 */
#define UART_TX			USBTX
#define	UART_RX			USBRX

/* Define the max possible sampling (or output data) rates for a given platform.
 * This are not an actual sampling rates of a device but rather a max approximate
 * sampling rates achieved in the firmware for a given platform.
 * This is also used to find the time period to trigger a periodic conversion in CC mode.
 * Note: Max possible ODR is 80KSPS per channel for continuous data capture on
 * IIO client. This is derived by testing the firmware on SDP-K1 controller board
 * @20Mhz SPI clock. The max possible ODR can vary from board to board and
 * data continuity is not guaranteed above this ODR on IIO oscilloscope */
#define SAMPLING_RATE_CC_OSR0		(80000)		// 80KSPS
#define SAMPLING_RATE_CC_OSR4		(64000)		// 64KSPS
#define SAMPLING_RATE_CC_OSR16		(42000)		// 42KSPS
#define SAMPLING_RATE_CC_OSR64		(12000)		// 12KSPS

/* Sampling rate values in SPS for different OSRs (for Burst Capture Mode) */
#define SAMPLING_RATE_BURST_OSR0	(116000)	// 116KSPS
#define SAMPLING_RATE_BURST_OSR4	(76000)		// 76KSPS
#define SAMPLING_RATE_BURST_OSR16	(44000)		// 44KSPS
#define SAMPLING_RATE_BURST_OSR64	(14000)		// 14KSPS

/******************************************************************************/
/********************** Public/Extern Declarations ****************************/
/******************************************************************************/

extern mbed_uart_init_param mbed_uart_extra_init_params;
extern mbed_spi_init_param mbed_spi_extra_init_params;
extern mbed_irq_init_param mbed_ext_int_extra_init_params;
extern mbed_pwm_init_param mbed_pwm_extra_init_params;
extern mbed_gpio_init_param mbed_ldac_gpio_extra_init_params;
extern mbed_gpio_init_param mbed_reset_gpio_extra_init_params;
extern mbed_gpio_init_param mbed_tgp_gpio_extra_init_params;
extern mbed_gpio_init_param mbed_convst_gpio_extra_init_params;
extern mbed_gpio_init_param mbed_busy_gpio_extra_init_params;
extern mbed_gpio_init_param mbed_conv_int_gpio_extra_init_params;

#endif /* APP_CONFIG_MBED_H_ */
