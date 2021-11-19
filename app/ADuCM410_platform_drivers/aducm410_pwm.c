/***************************************************************************//**
 * @file  aducm410_pwm.c
 * @brief Implementation of PWM ADuCM410 Platform drivers
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

#include <stdio.h>
#include "PwmLib.h"

#include "pwm.h"
#include "aducm410_pwm.h"
#include "error.h"

/******************************************************************************/
/********************** Macros and Constants Definition ***********************/
/******************************************************************************/

#define	BIT(x)	(1 << x)

/* For 16-bit pwm timer */
#define	PWM_DEFAULT_PERIOD	0xffff

/******************************************************************************/
/********************** Variables and User Defined Data Types *****************/
/******************************************************************************/

/******************************************************************************/
/************************ Functions Definitions *******************************/
/******************************************************************************/

/**
 * @brief	Initialized the PWM interface
 * @param	desc[in, out] - Pointer where the configured instance is stored
 * @param	param[in] - Configuration information for the instance
 * @return	SUCCESS in case of success, negative error code otherwise.
 */
int32_t pwm_init(struct pwm_desc **desc,
		 const struct pwm_init_param *param)
{
	int pwm_pair;
	unsigned int pwm_clock_divider, divider_val;
	unsigned int pwm_int_enable;
	unsigned int pwm_period;
	unsigned int pwm_pulse_width;
	float pwm_frequency;
	float duty_cycle_percentage;
	aducm410_pwm_init_param *extra_pwm_init_param;

	if (!desc || !param)
		return -EINVAL;

	/* Allocate a dynamic memory for PWM descriptor */
	struct pwm_desc *new_pwm_desc = (struct pwm_desc *)calloc(1,
					sizeof(struct pwm_desc));
	if (!new_pwm_desc)
		return -ENOMEM;

	new_pwm_desc->id = param->id;
	new_pwm_desc->period_ns = param->period_ns;
	new_pwm_desc->duty_cycle_ns = param->duty_cycle_ns;
	new_pwm_desc->phase_ns = param->phase_ns;

	/* Allocate a dynamic memory for ADuCM410 platform PWM descriptor */
	aducm410_pwm_desc *extra_pwm_desc = (aducm410_pwm_desc *)calloc(1,
					    sizeof(aducm410_pwm_desc));
	if (!extra_pwm_desc)
		goto extra_pwm_desc_err;

	extra_pwm_init_param = (aducm410_pwm_init_param *)param->extra;

	/* Get the PWM clock divider */
	switch (extra_pwm_init_param->clk_divider) {
	case DIVIDE_BY_2:
		pwm_clock_divider = PWMUCLK_2;
		break;

	case DIVIDE_BY_4:
		pwm_clock_divider = PWMUCLK_4;
		break;

	case DIVIDE_BY_8:
		pwm_clock_divider = PWMUCLK_8;
		break;

	case DIVIDE_BY_16:
		pwm_clock_divider = PWMUCLK_16;
		break;

	case DIVIDE_BY_32:
		pwm_clock_divider = PWMUCLK_32;
		break;

	case DIVIDE_BY_64:
		pwm_clock_divider = PWMUCLK_64;
		break;

	case DIVIDE_BY_128:
		pwm_clock_divider = PWMUCLK_128;
		break;

	case DIVIDE_BY_256:
		pwm_clock_divider = PWMUCLK_256;
		break;

	default:
		goto extra_pwm_desc_err;
	}

	/* Get the PWM channel pair */
	switch (extra_pwm_init_param->channel) {
	case PWM_CHN0:
	case PWM_CHN1:
		pwm_pair = PWM0_1;
		break;

	case PWM_CHN2:
	case PWM_CHN3:
		pwm_pair = PWM2_3;
		break;

	case PWM_CHN4:
	case PWM_CHN5:
		pwm_pair = PWM4_5;
		break;

	case PWM_CHN6:
	case PWM_CHN7:
		pwm_pair = PWM6_7;
		break;

	default:
		goto extra_pwm_desc_err;
	}

	/* Get the PWM interrupt enable status */
	if (extra_pwm_init_param->pwm_interrupt_enable) {
		pwm_int_enable = BIT(10);
	} else {
		pwm_int_enable = 0;
	}

	/* Calculate the PWM period */
	if (extra_pwm_init_param->pwm_clock_freq > 0) {
		pwm_frequency = extra_pwm_init_param->pwm_clock_freq / (2 <<
				extra_pwm_init_param->clk_divider);
		pwm_period = (uint32_t)(((float)param->period_ns / 1000000000) *
					(pwm_frequency)) - 1;

		if (pwm_period > PWM_DEFAULT_PERIOD)
			pwm_period = PWM_DEFAULT_PERIOD;
	} else {
		pwm_period = PWM_DEFAULT_PERIOD;
	}

	/* Calculate the percentage duty cycle and pwm width */
	duty_cycle_percentage = ((float)param->duty_cycle_ns / param->period_ns) * 100;
	pwm_pulse_width = (uint32_t)((pwm_period * duty_cycle_percentage) / 100);

	/* Initialize the ADuCM410 PWM interface */
	PwmInit(pwm_clock_divider, pwm_int_enable, 0, 0);

	/* Set the PWM period and duty cycle (both low and high inputs have same duty cycle) */
	if (PwmTime(pwm_pair, pwm_period, pwm_pulse_width, pwm_pulse_width) != 0)
		return SUCCESS;

extra_pwm_desc_err:
	free(new_pwm_desc);

	return FAILURE;
}

/**
 * @brief	Free the resources used by the PWM init
 * @param	desc[in, out] - PWM descriptor
 * @return	SUCCESS in case of success, negative error code otherwise.
 */
int32_t pwm_remove(struct pwm_desc *desc)
{
	if (!desc)
		return -EINVAL;

	if ((struct aducm410_pwm_desc *)desc->extra)
		free((struct aducm410_pwm_desc *)desc->extra);

	free(desc);
	return SUCCESS;
}

/**
 * @brief	Enable PWM
 * @param	desc[in, out] - PWM descriptor
 * @return	SUCCESS in case of success, negative error code otherwise.
 */
int32_t pwm_enable(struct pwm_desc *desc)
{
	/* Enable PWM in standard mode */
	PwmGo(1, 0);
	return SUCCESS;
}

/**
 * @brief	Disable PWM
 * @param	desc[in, out] - PWM descriptor
 * @return	SUCCESS in case of success, negative error code otherwise.
 */
int32_t pwm_disable(struct pwm_desc *desc)
{
	/* Disable PWM in standard mode */
	PwmGo(0, 0);
	return SUCCESS;
}
