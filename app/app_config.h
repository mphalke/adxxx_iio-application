/*************************************************************************//**
 *   @file   app_config.h
 *   @brief  Configuration file for AD70081z IIO firmware application
******************************************************************************
* Copyright (c) 2021 Analog Devices, Inc.
*
* All rights reserved.
*
* This software is proprietary to Analog Devices, Inc. and its licensors.
* By using this software you agree to the terms of the associated
* Analog Devices Software License Agreement.
*****************************************************************************/

#ifndef APP_CONFIG_H
#define APP_CONFIG_H

/******************************************************************************/
/***************************** Include Files **********************************/
/******************************************************************************/
#include <stdint.h>

/******************************************************************************/
/********************** Macros and Constants Definition ***********************/
/******************************************************************************/

/* List of supported platforms */
#define	MBED_PLATFORM		1
#define	ADUCM410_PLATFORM	2

/* List of all possible OSRs for AD70081z device (mapped to ad70081z_adc_config_osr enum) */
#define OSR0	0
#define OSR4	1
#define OSR16	2
#define OSR64	3

/* List of data capture modes for AD70081z device */
#define BURST_DATA_CAPTURE			0
#define CONTINUOUS_DATA_CAPTURE		1

/* Select the active platform */
#if !defined(ACTIVE_PLATFORM)
#define ACTIVE_PLATFORM		MBED_PLATFORM
#endif

#if (ACTIVE_PLATFORM == MBED_PLATFORM)
#include "app_config_mbed.h"
#define uart_extra_init_params mbed_uart_extra_init_params
#define spi_extra_init_params mbed_spi_extra_init_params
#define ext_int_extra_init_params mbed_ext_int_extra_init_params
#define pwm_extra_init_params mbed_pwm_extra_init_params
#define ldac_gpio_extra_init_params mbed_ldac_gpio_extra_init_params
#define reset_gpio_extra_init_params mbed_reset_gpio_extra_init_params
#define tgp_gpio_extra_init_params mbed_tgp_gpio_extra_init_params
#define convst_gpio_extra_init_params mbed_convst_gpio_extra_init_params
#define busy_gpio_extra_init_params mbed_busy_gpio_extra_init_params
#define conv_int_gpio_extra_init_params mbed_conv_int_gpio_extra_init_params
#define EXTERNAL_INT_ID EXTERNAL_INT_ID1
#elif (ACTIVE_PLATFORM == ADUCM410_PLATFORM)
#include "app_config_aducm410.h"
#define uart_extra_init_params aducm410_uart_extra_init_params
#define spi_extra_init_params aducm410_spi_extra_init_params
#define ext_int_extra_init_params aducm410_ext_int_extra_init_params
#define pwm_extra_init_params aducm410_pwm_extra_init_params
#define ldac_gpio_extra_init_params aducm410_ldac_gpio_extra_init_params
#define reset_gpio_extra_init_params aducm410_reset_gpio_extra_init_params
#define tgp_gpio_extra_init_params aducm410_tgp_gpio_extra_init_params
#define convst_gpio_extra_init_params aducm410_convst_gpio_extra_init_params
#define busy_gpio_extra_init_params aducm410_busy_gpio_extra_init_params
#define conv_int_gpio_extra_init_params aducm410_conv_int_gpio_extra_init_params
#define EXTERNAL_INT_ID EXTERNAL_INT_ID6 // EXINT5
#else
#error "No/Invalid active platform selected"
#endif

/* IIO device name string */
#define IIO_DEVICE_NAME		"ad70081z"

/* Baud rate for IIO application UART interface */
#define IIO_UART_BAUD_RATE	(230400)

#if (ACTIVE_PLATFORM == MBED_PLATFORM)
/* Enable the VirtualCOM port connection/interface. By default serial comminunication
 * is physical UART */
//#define USE_VIRTUAL_COM_PORT

#if defined(USE_VIRTUAL_COM_PORT)
/* Below USB configurations (VID and PID) are owned and assigned by ADI.
 * If intended to distribute software further, use the VID and PID owned by your
 * organization */
#define VIRTUAL_COM_PORT_VID	0x0456
#define VIRTUAL_COM_PORT_PID	0xb66c
#define VIRTUAL_COM_SERIAL_NUM	"ad70081z_mbed_iio_application_sdp-k1"
#endif
#endif

/* AD70081z OSR default value */
#define DEFAULT_OSR		OSR0

/* Select the ADC data capture mode (default is burst mode) */
#define DATA_CAPTURE_MODE	BURST_DATA_CAPTURE

#if (DATA_CAPTURE_MODE == CONTINUOUS_DATA_CAPTURE)
#if (DEFAULT_OSR == OSR64)
#define SAMPLING_RATE	SAMPLING_RATE_CC_OSR64
#elif (DEFAULT_OSR == OSR16)
#define SAMPLING_RATE	SAMPLING_RATE_CC_OSR16
#elif (DEFAULT_OSR == OSR4)
#define SAMPLING_RATE	SAMPLING_RATE_CC_OSR4
#else
#define SAMPLING_RATE	SAMPLING_RATE_CC_OSR0
#endif
#else
#if (DEFAULT_OSR == OSR64)
#define SAMPLING_RATE	SAMPLING_RATE_BURST_OSR64
#elif (DEFAULT_OSR == OSR16)
#define SAMPLING_RATE	SAMPLING_RATE_BURST_OSR16
#elif (DEFAULT_OSR == OSR4)
#define SAMPLING_RATE	SAMPLING_RATE_BURST_OSR4
#else
#define SAMPLING_RATE	SAMPLING_RATE_BURST_OSR0
#endif
#endif

/* PWM period and duty cycle calculations (cc mode) */
#define CONV_TRIGGER_PERIOD_NSEC		(((float)(1.0 / SAMPLING_RATE) * 1000000) * 1000.0)
#define CONV_TRIGGER_DUTY_CYCLE_NSEC	(CONV_TRIGGER_PERIOD_NSEC / 2)

/******************************************************************************/
/********************** Variables and User Defined Data Types *****************/
/******************************************************************************/

/******************************************************************************/
/************************ Public Declarations *********************************/
/******************************************************************************/

extern struct uart_desc *uart_desc;
extern struct gpio_desc *busy_gpio_desc;

int32_t init_system(void);

#endif	// APP_CONFIG_H
