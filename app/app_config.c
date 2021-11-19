/***************************************************************************//**
 *   @file    app_config.c
 *   @brief   AD70081z IIO application configurations module
 *   @details This module performs the system configurations
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
#include "ad70081z_data_capture.h"
#include "uart.h"
#include "error.h"
#include "irq.h"
#include "gpio.h"
#include "pwm.h"

/******************************************************************************/
/************************ Macros/Constants ************************************/
/******************************************************************************/

/******************************************************************************/
/******************** Variables and User Defined Data Types *******************/
/******************************************************************************/

/* UART init parameters */
struct uart_init_param uart_init_params = {
	.device_id = NULL,
	.baud_rate = IIO_UART_BAUD_RATE,
	.extra = &uart_extra_init_params
};

/* External interrupt init parameters */
static struct irq_init_param ext_int_init_params = {
	.irq_ctrl_id = EXTERNAL_INT_ID,
	.extra = &ext_int_extra_init_params
};

/* External interrupt callback descriptor */
static struct callback_desc ext_int_callback_desc = {
	data_capture_callback,
	NULL,
	NULL
};

/* BUSY GPIO init parameters */
static struct gpio_init_param busy_gpio_init_params = {
	.number = BUSY_GPIO,
	.platform_ops = NULL,
	.extra = &busy_gpio_extra_init_params
};

/* CONV_INT GPIO init parameters */
static struct gpio_init_param conv_int_gpio_init_params = {
	.number = CONV_INT_GPIO,
	.platform_ops = NULL,
	.extra = &conv_int_gpio_extra_init_params
};

/* PWM init parameters */
static struct pwm_init_param pwm_init_params = {
	.id = NULL, 									// PWM ID
	.period_ns = CONV_TRIGGER_PERIOD_NSEC,			// PWM period in nsec
	.duty_cycle_ns = CONV_TRIGGER_DUTY_CYCLE_NSEC,	// PWM duty cycle in nsec
	.extra = &pwm_extra_init_params
};

/* UART descriptor */
struct uart_desc *uart_desc;

/* BUSY gpio descriptor */
struct gpio_desc *busy_gpio_desc;

/* CONV_INT gpio descriptor */
struct gpio_desc *conv_int_gpio_desc;

/* PWM descriptor */
struct pwm_desc *pwm_desc;

/******************************************************************************/
/************************** Functions Declarations ****************************/
/******************************************************************************/

/******************************************************************************/
/************************** Functions Definitions *****************************/
/******************************************************************************/

/**
 * @brief 	Initialize the GPIOs
 * @return	SUCCESS in case of success, FAILURE otherwise
 */
static int32_t init_gpio(void)
{
	/* Configure the BUSY pin */
	if (gpio_get(&busy_gpio_desc, &busy_gpio_init_params) != SUCCESS) {
		return FAILURE;
	}

	/* Set BUSY pin direction as input */
	if (gpio_direction_input(busy_gpio_desc) != SUCCESS) {
		return FAILURE;
	}

#if (DATA_CAPTURE_MODE == CONTINUOUS_DATA_CAPTURE)
	/* Configure the CONV_INT pin */
	if (gpio_get(&conv_int_gpio_desc, &conv_int_gpio_init_params) != SUCCESS) {
		return FAILURE;
	}

	/* Set CONV_INT pin direction as input */
	if (gpio_direction_input(conv_int_gpio_desc) != SUCCESS) {
		return FAILURE;
	}
#endif

	return SUCCESS;
}

/**
 * @brief 	Initialize the UART peripheral
 * @return	SUCCESS in case of success, FAILURE otherwise
 */
static int32_t init_uart(void)
{
	return uart_init(&uart_desc, &uart_init_params);
}

/**
 * @brief 	Initialize the IRQ contoller
 * @return	none
 * @details	This function initialize the interrupt controller
 */
static int32_t init_interrupts(void)
{
	struct irq_ctrl_desc *ext_int_desc;

	/* Initialize the IRQ controller for external interrupt */
	if (irq_ctrl_init(&ext_int_desc, &ext_int_init_params) != SUCCESS) {
		return FAILURE;
	}

	/* Register a callback function for external interrupt */
	if (irq_register_callback(ext_int_desc,
				  EXTERNAL_INT_ID,
				  &ext_int_callback_desc) != SUCCESS) {
		return FAILURE;
	}

	/* Enable external interrupt */
	if (irq_enable(ext_int_desc, EXTERNAL_INT_ID) != SUCCESS) {
		return FAILURE;
	}

	return SUCCESS;
}

/**
 * @brief 	Initialize the PWM contoller
 * @return	SUCCESS in case of success, FAILURE otherwise
 */
static int32_t init_pwm(void)
{
	do {
		/* Initialize the PWM interface to generate PWM signal
		 * on conversion trigger event pin */
		if (pwm_init(&pwm_desc, &pwm_init_params) != SUCCESS) {
			break;
		}

		if (pwm_enable(pwm_desc) != SUCCESS) {
			break;
		}

		return SUCCESS;
	} while (0);

	return FAILURE;
}

/**
 * @brief 	Initialize the system peripherals
 * @return	SUCCESS in case of success, FAILURE otherwise
 */
int32_t init_system(void)
{
#if (ACTIVE_PLATFORM == ADUCM410_PLATFORM)
	if (aducm410_system_init() != SUCCESS) {
		return FAILURE;
	}
#endif

	if (init_uart() != SUCCESS) {
		return FAILURE;
	}

	if (init_gpio() != SUCCESS) {
		return FAILURE;
	}

#if (DATA_CAPTURE_MODE == CONTINUOUS_DATA_CAPTURE)
	if (init_interrupts() != SUCCESS) {
		return FAILURE;
	}

	if (init_pwm() != SUCCESS) {
		return FAILURE;
	}
#endif

#if (ACTIVE_PLATFORM == ADUCM410_PLATFORM)
	aducm410_clear_interrupts();
#endif

	return SUCCESS;
}
