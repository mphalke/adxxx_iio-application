/***************************************************************************//**
 *   @file     gpio_extra.h
 *   @brief:   Header containing extra types required for GPIO interface
********************************************************************************
 * Copyright (c) 2020 Analog Devices, Inc.
 *
 * All rights reserved.
 *
 * This software is proprietary to Analog Devices, Inc. and its licensors.
 * By using this software you agree to the terms of the associated
 * Analog Devices Software License Agreement.
*******************************************************************************/

#ifndef GPIO_EXTRA_H
#define GPIO_EXTRA_H

/******************************************************************************/
/***************************** Include Files **********************************/
/******************************************************************************/
#include <stdio.h>

/******************************************************************************/
/********************** Macros and Constants Definitions **********************/
/******************************************************************************/

/******************************************************************************/
/********************** Variables and User defined data types *****************/
/******************************************************************************/

/**
* @struct aducm410_gpio_init_param
* @brief Structure holding the GPIO init parameters for aducm410 platform.
*/
typedef struct {
	void *gpio_port;        // GPIO port (memory mapped register address)
	uint32_t pin_mask;      // GPIO pin mask
	uint32_t pin_mode;      // GPIO pin mode (Pull-up/down)
} aducm410_gpio_init_param;

/**
* @struct aducm410_gpio_desc
* @brief GPIO specific descriptor for the aducm410 platform.
*/
typedef struct {
	void *gpio_port;       // GPIO port (memory mapped register address)
	uint32_t pin_mask;     // GPIO pin mask
	uint32_t pin_mode;     // Pin mode (Pull-up/down)
	uint8_t direction;     // GPIO direction (input/output)
} aducm410_gpio_desc;

/******************************************************************************/
/************************ Functions Declarations ******************************/
/******************************************************************************/

#endif /* GPIO_EXTRA_H */
