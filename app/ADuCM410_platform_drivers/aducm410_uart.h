/***************************************************************************//**
 *   @file     uart_extra.h
 *   @brief:   Header containing extra types required for UART interface
********************************************************************************
 * Copyright (c) 2020 Analog Devices, Inc.
 *
 * All rights reserved.
 *
 * This software is proprietary to Analog Devices, Inc. and its licensors.
 * By using this software you agree to the terms of the associated
 * Analog Devices Software License Agreement.
*******************************************************************************/

#ifndef UART_EXTRA_H
#define UART_EXTRA_H

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
 * @struct aducm410_uart_init_param
 * @brief Structure holding the UART init parameters for aducm410 platform.
 */
typedef struct {
	uint8_t uart_tx_pin;		// UART Transmit Pin
	uint8_t uart_rx_pin;  		// UART Receive Pin
	void *uart_port; 		// UART port (memory mapped register address)
	void *uart_setup;              // UART setup
} aducm410_uart_init_param;

/**
 * @struct aducm410_uart_desc
 * @brief UART specific descriptor for the aducm410 platform.
 */
typedef struct {
	void *uart_port; 		// UART port (memory mapped register address)
} aducm410_uart_desc;

/******************************************************************************/
/************************ Functions Declarations ******************************/
/******************************************************************************/


#endif /* UART_EXTRA_H */
