/***************************************************************************//**
 *   @file   gpio.c
 *   @brief  Implementation of GPIO platform drivers
********************************************************************************
 * Copyright (c) 2020 Analog Devices, Inc.
 *
 * All rights reserved.
 *
 * This software is proprietary to Analog Devices, Inc. and its licensors.
 * By using this software you agree to the terms of the associated
 * Analog Devices Software License Agreement.
*******************************************************************************/

/******************************************************************************/
/************************ Includes Files *******************************/
/******************************************************************************/
#include <stdio.h>
#include <stdlib.h>
#include "DioLib.h"

#include "gpio.h"
#include "aducm410_gpio.h"
#include "error.h"

/******************************************************************************/
/************************ Functions Definitions *******************************/
/******************************************************************************/

/**
 * @brief Obtain the GPIO decriptor.
 * @param desc - The GPIO descriptor.
 * @param gpio_number - The number of the GPIO.
 * @return SUCCESS in case of success, FAILURE otherwise.
 */
int32_t gpio_get(struct gpio_desc **desc, const struct gpio_init_param *param)
{
	if (!desc || !param) {
		return FAILURE;
	}

	/* Create a new gpio descriptor */
	gpio_desc *new_gpio = (gpio_desc *)calloc(1, sizeof(gpio_desc)) ;
	if (!new_gpio) {
		return FAILURE;
	}

	/* Create a new aducm410 gpio descriptor for platform specific parameters */
	aducm410_gpio_desc *aducm410_new_desc = (aducm410_gpio_desc *)calloc(1,
						sizeof(aducm410_gpio_desc)) ;
	if (!aducm410_new_desc) {
		return FAILURE;
	}

	/* Get the gpio extra init parameters into extra descriptor */
	aducm410_new_desc->gpio_port = ((aducm410_gpio_init_param *)(
						param->extra))->gpio_port;
	aducm410_new_desc->pin_mask = ((aducm410_gpio_init_param *)(
					       param->extra))->pin_mask;
	aducm410_new_desc->pin_mode = ((aducm410_gpio_init_param *)(
					       param->extra))->pin_mode;
	aducm410_new_desc->direction = GPIO_IN;

	/* Configure the gpio */
	DioCfgPin((ADI_GPIO_TypeDef *)aducm410_new_desc->gpio_port,
		  aducm410_new_desc->pin_mask,
		  param->number);

	new_gpio->number = param->number;
	new_gpio->extra = (aducm410_gpio_desc *)aducm410_new_desc;

	*desc = new_gpio;

	return SUCCESS;
}


/**
 * @brief Get the value of an optional GPIO.
 * @param desc - The GPIO descriptor.
 * @param param - GPIO Initialization parameters.
 * @return SUCCESS in case of success, FAILURE otherwise.
 */
int32_t gpio_get_optional(struct gpio_desc **desc,
			  const struct gpio_init_param *param)
{
	if (param) {
		return gpio_get(desc, param);
	} else {
		*desc = NULL;
		return SUCCESS;
	}
}


/**
 * @brief Free the resources allocated by gpio_get().
 * @param desc - The GPIO descriptor.
 * @return SUCCESS in case of success, FAILURE otherwise.
 */
int32_t gpio_remove(struct gpio_desc *desc)
{
	if (!desc) {
		return FAILURE;
	}

	/* Free the aducm410 gpio descriptor */
	if ((aducm410_gpio_desc *)(desc->extra)) {
		free((aducm410_gpio_desc *)(desc->extra));
	}

	/* Free the gpio descriptor */
	free(desc);

	return SUCCESS;
}


/**
 * @brief Enable the input direction of the specified GPIO.
 * @param desc - The GPIO descriptor.
 * @return SUCCESS in case of success, FAILURE otherwise.
 * @note does not support reconfiguration of already set pin direction
 */
int32_t gpio_direction_input(struct gpio_desc *desc)
{
	aducm410_gpio_desc
	*aducm410_new_desc;   // pointer to gpio desc extra parameters

	if (!desc || !desc->extra) {
		return FAILURE;
	}

	aducm410_new_desc = (aducm410_gpio_desc *)(desc->extra);

	/* Configure GPIO as input */
	DioIenPin((ADI_GPIO_TypeDef *)aducm410_new_desc->gpio_port,
		  aducm410_new_desc->pin_mask, 1);

	/* Set the gpio pull config */
	DioPullCfgPin((ADI_GPIO_TypeDef *)aducm410_new_desc->gpio_port,
		      aducm410_new_desc->pin_mask,
		      aducm410_new_desc->pin_mode);

	/* Enable pull config */
	DioPulPin((ADI_GPIO_TypeDef *)aducm410_new_desc->gpio_port,
		  aducm410_new_desc->pin_mask, 1);

	/* Set GPIO direction as input */
	aducm410_new_desc->direction = GPIO_IN;

	return SUCCESS;
}


/**
 * @brief Enable the output direction of the specified GPIO.
 * @param desc - The GPIO descriptor.
 * @param value - The value.
 *                Example: GPIO_HIGH
 *                         GPIO_LOW
 * @return SUCCESS in case of success, FAILURE otherwise.
 * @note does not support reconfiguration of already set pin direction
 */
int32_t gpio_direction_output(struct gpio_desc *desc, uint8_t value)
{
	aducm410_gpio_desc
	*aducm410_new_desc;   // pointer to gpio desc extra parameters

	if (!desc || !desc->extra) {
		return FAILURE;
	}

	aducm410_new_desc = (aducm410_gpio_desc *)(desc->extra);

	/* Configure GPIO as output */
	DioOenPin((ADI_GPIO_TypeDef *)aducm410_new_desc->gpio_port,
		  aducm410_new_desc->pin_mask, 1);

	/* Set GPIO direction as output */
	aducm410_new_desc->direction = GPIO_OUT;

	/* Set/Clear GPIO */
	if (gpio_set_value (desc, value) != SUCCESS) {
		return FAILURE;
	}

	return SUCCESS;
}


/**
 * @brief Get the direction of the specified GPIO.
 * @param desc - The GPIO descriptor.
 * @param direction - The direction.
 *                    Example: GPIO_OUT
 *                             GPIO_IN
 * @return SUCCESS in case of success, FAILURE otherwise.
 */
int32_t gpio_get_direction(struct gpio_desc *desc, uint8_t *direction)
{
	if (!desc || !desc->extra) {
		return FAILURE;
	}

	*direction = ((aducm410_gpio_desc *)(desc->extra))->direction;

	return SUCCESS;
}


/**
 * @brief Set the value of the specified GPIO.
 * @param desc - The GPIO descriptor.
 * @param value - The value.
 *                Example: GPIO_HIGH
 *                         GPIO_LOW
 * @return SUCCESS in case of success, FAILURE otherwise.
 */
int32_t gpio_set_value(struct gpio_desc *desc, uint8_t value)
{
	aducm410_gpio_desc *aducm410_new_desc;    // pointer to aducm410 gpio desc

	if (!desc || !desc->extra) {
		return FAILURE;
	}

	aducm410_new_desc = (aducm410_gpio_desc *)(desc->extra);

	/* Set/Clear GPIO */
	if (value == GPIO_HIGH) {
		DioSetPin((ADI_GPIO_TypeDef *)aducm410_new_desc->gpio_port,
			  aducm410_new_desc->pin_mask);
	} else {
		DioClrPin((ADI_GPIO_TypeDef *)aducm410_new_desc->gpio_port,
			  aducm410_new_desc->pin_mask);
	}

	return SUCCESS;
}


/**
 * @brief Get the value of the specified GPIO.
 * @param desc - The GPIO descriptor.
 * @param value - The value.
 *                Example: GPIO_HIGH
 *                         GPIO_LOW
 * @return SUCCESS in case of success, FAILURE otherwise.
 */
int32_t gpio_get_value(struct gpio_desc *desc, uint8_t *value)
{
	aducm410_gpio_desc *aducm410_new_desc;    // pointer to aducm410 gpio desc
	uint8_t gpio_val;
	uint8_t bit_shift_cnt = 0;
	uint8_t mask;

	if (!desc || !desc->extra) {
		return FAILURE;
	}

	aducm410_new_desc = (aducm410_gpio_desc *)(desc->extra);

	/* Read the GPIO port */
	gpio_val = DioRd((ADI_GPIO_TypeDef *)aducm410_new_desc->gpio_port);

	/* Mask and extract the pin value */
	mask = aducm410_new_desc->pin_mask;
	while (mask != 0x1) {
		bit_shift_cnt++;
		mask >>= 1;
	}

	/* Get the pin value (shifted to LSB) from GPIO port */
	*value = (gpio_val >> bit_shift_cnt) & 0x1;

	return SUCCESS;
}
