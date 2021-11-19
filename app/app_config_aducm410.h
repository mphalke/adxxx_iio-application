/***************************************************************************//**
 *   @file    app_config_maducm410.h
 *   @brief   Header file for ADuCM410 platform configurations
********************************************************************************
 * Copyright (c) 2021 Analog Devices, Inc.
 * All rights reserved.
 *
 * This software is proprietary to Analog Devices, Inc. and its licensors.
 * By using this software you agree to the terms of the associated
 * Analog Devices Software License Agreement.
*******************************************************************************/

#ifndef APP_CONFIG_ADUCM410_H_
#define APP_CONFIG_ADUCM410_H_

/******************************************************************************/
/***************************** Include Files **********************************/
/******************************************************************************/

#include <stdint.h>

#include "DioLib.h"
#include "aducm410_uart.h"
#include "aducm410_spi.h"
#include "aducm410_gpio.h"
#include "aducm410_irq.h"
#include "aducm410_pwm.h"

/******************************************************************************/
/********************** Macros and Constants Definition ***********************/
/******************************************************************************/

/* Pin mapping of EVAL-AD77081z w.r.t ADuCM410 Controller board */

/* SPI is used in 3-wire mode. CS is tied to GND in hardware and pulled low
   as output pin in software */
#define SPI_HOST_SDI	P0_1_SPI0_MISO
#define SPI_HOST_SDO	P0_2_SPI0_MOSI
#define SPI_CSB			P0_3_SPI0_CS
#define SPI_SCK			P0_0_SPI0_SCLK

#define SPI_HOST_SDI_PIN	PIN1
#define SPI_HOST_SDO_PIN	PIN2
#define SPI_CSB_PIN			PIN3
#define SPI_SCK_PIN			PIN0

#define SPI_GPIO_PORT	pADI_GPIO0
#define SPI_PORT		pADI_SPI0

#define LDACB_GPIO		P2_0_GPIO
#define RESETB_GPIO		P2_1_GPIO_IRQ2
#define TGP_GPIO		P1_7_GPIO_IRQ1
#define CONVST_GPIO		P1_6_GPIO
#define BUSY_GPIO		P1_5_GPIO
#define CONV_INT_GPIO	P2_6_GPIO_IRQ5
#define CONV_PWM_GPIO	P1_2_PWM0

#define LDACB_GPIO_PIN		PIN0
#define RESETB_GPIO_PIN		PIN1
#define TGP_GPIO_PIN		PIN7
#define CONVST_GPIO_PIN		PIN6
#define BUSY_GPIO_PIN		PIN5
#define CONV_INT_GPIO_PIN	PIN6
#define CONV_PWM_GPIO_PIN	PIN2

#define LDACB_GPIO_PORT		pADI_GPIO2
#define RESETB_GPIO_PORT	pADI_GPIO2
#define TGP_GPIO_PORT		pADI_GPIO1
#define CONVST_GPIO_PORT	pADI_GPIO1
#define BUSY_GPIO_PORT		pADI_GPIO1
#define CONV_INT_GPIO_PORT	pADI_GPIO2
#define CONV_PWM_GPIO_PORT	pADI_GPIO1

/* USB port connecting ADuCM410 board to PC is used for UART communication */
#define UART_TX		P1_1_UART1_TX
#define	UART_RX		P1_0_UART1_RX

#define UART_TX_PIN		PIN1
#define UART_RX_PIN		PIN0

#define UART_GPIO_PORT	pADI_GPIO1
#define UART_PORT		pADI_UART1

/* Define the max possible sampling (or output data) rates for a given platform.
 * This are not an actual sampling rates of a device but rather a max approximate
 * sampling rates achieved in the firmware for a given platform.
 * This is also used to find the time period to trigger a periodic conversion in CC mode.
 * Note: Max possible ODR is 140KSPS per channel for continuous data capture on
 * IIO client. This is derived by testing the firmware on ADuCM410 controller board
 * @20Mhz SPI clock. The max possible ODR can vary from board to board and
 * data continuity is not guaranteed above this ODR on IIO oscilloscope */
#define SAMPLING_RATE_CC_OSR0		(140000)	// 140KSPS
#define SAMPLING_RATE_CC_OSR4		(96000)		// 96KSPS
#define SAMPLING_RATE_CC_OSR16		(56000)		// 56KSPS
#define SAMPLING_RATE_CC_OSR64		(12000)		// 12KSPS

/* Sampling rate values in SPS for different OSRs (for Burst Capture Mode) */
#define SAMPLING_RATE_BURST_OSR0	(160000)	// 160KSPS
#define SAMPLING_RATE_BURST_OSR4	(100000)	// 100KSPS
#define SAMPLING_RATE_BURST_OSR16	(58000)		// 58KSPS
#define SAMPLING_RATE_BURST_OSR64	(16000)		// 16KSPS

/******************************************************************************/
/********************** Public/Extern Declarations ****************************/
/******************************************************************************/

extern aducm410_uart_init_param aducm410_uart_extra_init_params ;
extern aducm410_spi_init_param aducm410_spi_extra_init_params ;
extern aducm410_irq_init_param aducm410_ext_int_extra_init_params;
extern aducm410_pwm_init_param aducm410_pwm_extra_init_params ;
extern aducm410_gpio_init_param aducm410_ldac_gpio_extra_init_params;
extern aducm410_gpio_init_param aducm410_reset_gpio_extra_init_params;
extern aducm410_gpio_init_param aducm410_tgp_gpio_extra_init_params;
extern aducm410_gpio_init_param aducm410_convst_gpio_extra_init_params;
extern aducm410_gpio_init_param aducm410_busy_gpio_extra_init_params;
extern aducm410_gpio_init_param aducm410_conv_int_gpio_extra_init_params ;

int32_t aducm410_system_init(void);
void aducm410_clear_interrupts(void);

#endif /* APP_CONFIG_ADUCM410_H_ */
