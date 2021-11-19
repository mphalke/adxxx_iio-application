/***************************************************************************//**
 *   @file     spi_extra.h
 *   @brief:   Header containing extra types required for SPI interface
********************************************************************************
 * Copyright (c) 2020 Analog Devices, Inc.
 *
 * All rights reserved.
 *
 * This software is proprietary to Analog Devices, Inc. and its licensors.
 * By using this software you agree to the terms of the associated
 * Analog Devices Software License Agreement.
*******************************************************************************/

#ifndef SPI_EXTRA_H
#define SPI_EXTRA_H

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
 * @struct aducm410_spi_init_param
 * @brief Structure holding the SPI init parameters for aducm410 platform.
 */
typedef struct {
	void *spi_port; 		// SPI port (memory mapped register)
	void *spi_setup;               // SPI default setup
	uint32_t clk_div;              // Divider for SPI clock
} aducm410_spi_init_param;

/**
 * @struct aducm410_spi_desc
 * @brief SPI specific descriptor for the aducm410 platform.
 */
typedef struct {
	void *spi_port; 		// SPI port (memory mapped register)
	void *slave_select; 		// SPI slave select gpio instance (DigitalOut)
} aducm410_spi_desc;

/******************************************************************************/
/************************ Functions Declarations ******************************/
/******************************************************************************/


#endif /* SPI_EXTRA_H */
