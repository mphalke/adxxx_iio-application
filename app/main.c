/***************************************************************************//**
 * @file    main.c
 * @brief   Main interface for AD70081z IIO firmware application
 * @details
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

#include <stdint.h>
#include <assert.h>

#include "ad70081z_iio.h"
#include "error.h"

/******************************************************************************/
/********************* Macros and Constants Definition ************************/
/******************************************************************************/

/******************************************************************************/
/******************** Variables and User Defined Data Types *******************/
/******************************************************************************/

/******************************************************************************/
/************************** Functions Declaration *****************************/
/******************************************************************************/

/******************************************************************************/
/************************** Functions Definition ******************************/
/******************************************************************************/

/* @brief	Main function
 * @details	This is a main entry function for firmware application
 */
int main(void)
{
	/* Initialize the AD70081z IIO interface */
	if (ad70081z_iio_initialize() != SUCCESS) {
		assert(false);
	}

	while (1) {
		/* Monitor the IIO client events */
		ad70081z_iio_event_handler();
	}
}
