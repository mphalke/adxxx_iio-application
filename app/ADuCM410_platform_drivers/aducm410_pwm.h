/***************************************************************************//**
 *   @file     aducm410_pwm.h
 *   @brief:   Header containing extra types required for ADuCM410 PWM drivers
********************************************************************************
 * Copyright (c) 2021 Analog Devices, Inc.
 * All rights reserved.
 *
 * This software is proprietary to Analog Devices, Inc. and its licensors.
 * By using this software you agree to the terms of the associated
 * Analog Devices Software License Agreement.
*******************************************************************************/

#ifndef PWM_EXTRA_H
#define PWM_EXTRA_H

/******************************************************************************/
/***************************** Include Files **********************************/
/******************************************************************************/

#include <stdbool.h>

/******************************************************************************/
/********************** Macros and Constants Definitions **********************/
/******************************************************************************/

/******************************************************************************/
/********************** Variables and User Defined Data Types *****************/
/******************************************************************************/

/* ADuCM410 PWM Channel */
enum pwm_chn {
	PWM_CHN0,
	PWM_CHN1,
	PWM_CHN2,
	PWM_CHN3,
	PWM_CHN4,
	PWM_CHN5,
	PWM_CHN6,
	PWM_CHN7
};

enum pwm_clock_divider {
	DIVIDE_BY_2,        // Prescaler 0 (PWM_UCLK / 2)
	DIVIDE_BY_4,        // Prescaler 1 (PWM_UCLK / 4)
	DIVIDE_BY_8,        // Prescaler 2 (PWM_UCLK / 8)
	DIVIDE_BY_16,       // Prescaler 3 (PWM_UCLK / 16)
	DIVIDE_BY_32,       // Prescaler 4 (PWM_UCLK / 32)
	DIVIDE_BY_64,       // Prescaler 5(PWM_UCLK / 64)
	DIVIDE_BY_128,      // Prescaler 6 (PWM_UCLK / 128)
	DIVIDE_BY_256,      // Prescaler 7 (PWM_UCLK / 256)
};

/**
 * @struct aducm410_pwm_init_param
 * @brief Structure holding the extra parameters for PWM initialization.
 */
typedef struct  {
	enum pwm_chn channel;					// PWM channel
	enum pwm_clock_divider clk_divider;		// PWM clock prescaler or divider
	float pwm_clock_freq;					// PWM clock frequency (before prescaling)
	bool pwm_interrupt_enable;				// PWM interrupt enable flag
} aducm410_pwm_init_param;

/**
 * @struct aducm410_pwm_desc
 * @brief Structure holding the platform descriptor for PWM.
 */
typedef struct {
	void *extra;
} aducm410_pwm_desc;

#endif // PWM_EXTRA_H
