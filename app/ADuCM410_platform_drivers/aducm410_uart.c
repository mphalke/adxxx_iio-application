/***************************************************************************//**
 * @file  uart.cpp
 * @brief Implementation of UART platform drivers
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
/***************************** Include Files **********************************/
/******************************************************************************/
#include <stdio.h>
#include "UrtLib.h"

#include "uart.h"
#include "aducm410_uart.h"
#include "error.h"
#include "gpio.h"
#include "aducm410_gpio.h"

/******************************************************************************/
/************************ Functions Definitions *******************************/
/******************************************************************************/

/**
 * @brief Read data from UART device.
 * @param desc - Instance of UART.
 * @param data - Pointer to buffer containing data.
 * @param bytes_number - Number of bytes to read.
 * @return SUCCESS in case of success, FAILURE otherwise.
 */
int32_t uart_read(struct uart_desc *desc, uint8_t *data, uint32_t bytes_number)
{
	ADI_UART_TypeDef *uart_port;		// pointer to UART port
	uint16_t uart_rx_status;              // UART Rx status

	if (!desc || !data) {
		return FAILURE;
	}

	uart_port = (ADI_UART_TypeDef *)(((aducm410_uart_desc *)(
			desc->extra))->uart_port);

	for (size_t i = 0; i < bytes_number; i++) {
		/* Block until new character is received into Rx buffer */
		do {
			uart_rx_status = uart_port->IIR;
		} while (((uart_rx_status & BITM_UART_IIR_STAT) >> BITP_UART_IIR_STAT) !=
			 ENUM_UART_IIR_STAT_RXFULLINT);

		/* Read the character from Rx buffer */
		data[i] = UrtRx(uart_port);
	}

	return bytes_number;
}


/**
 * @brief Write data to UART device.
 * @param desc - Instance of UART.
 * @param data - Pointer to buffer containing data.
 * @param bytes_number - Number of bytes to read.
 * @return SUCCESS in case of success, FAILURE otherwise.
 */
int32_t uart_write(struct uart_desc *desc, const uint8_t *data,
		   uint32_t bytes_number)
{
	ADI_UART_TypeDef *uart_port;	      // pointer to UART port
	uint16_t uart_tx_status;            // UART Tx status

	if (!desc || !data) {
		return FAILURE;
	}

	uart_port = (ADI_UART_TypeDef *)(((aducm410_uart_desc *)(
			desc->extra))->uart_port);

	for (size_t i = 0; i < bytes_number; i++) {
		/* Block until previous character transfered out of Tx buffer */
		do {
			uart_tx_status = uart_port->LSR;
		} while (!((uart_tx_status >> BITP_UART_LSR_TEMT) & BITL_UART_LSR_TEMT));

		/* Write new character into Tx buffer */
		UrtTx(uart_port, data[i]);
	}

	return bytes_number;
}


/**
 * @brief Submit reading buffer to the UART driver.
 *
 * Buffer is used until bytes_number bytes are read.
 * @param desc:	Descriptor of the UART device
 * @param data:	Buffer where data will be read
 * @param bytes_number:	Number of bytes to be read.
 * @return \ref SUCCESS in case of success, \ref FAILURE otherwise.
 */
int32_t uart_read_nonblocking(struct uart_desc *desc,
			      uint8_t *data,
			      uint32_t bytes_number)
{
	ADI_UART_TypeDef *uart_port;		// pointer to UART port

	if (!desc || !data) {
		return FAILURE;
	}

	uart_port = (ADI_UART_TypeDef *)(((aducm410_uart_desc *)(
			desc->extra))->uart_port);

	for (size_t i = 0; i < bytes_number; i++) {
		/* Read assuming that new character has been received into Rx buffer.
		  *Note: The current implementation is suited to read single
		  charcter only. For more than one characters non-blocking read
		  a FIFO mechanism must to be implemented */
		data[i] = UrtRx(uart_port);
	}

	return bytes_number;
}


/**
 * @brief Initialize the UART communication peripheral.
 * @param desc - The UART descriptor.
 * @param param - The structure that contains the UART parameters.
 * @return SUCCESS in case of success, FAILURE otherwise.
 */
int32_t uart_init(struct uart_desc **desc, struct uart_init_param *param)
{
	aducm410_uart_desc *aducm410_new_desc;  // Pointer to aducm410 uart descriptor

	if (!desc || !param) {
		return FAILURE;
	}

	/* Create a new UART description for the device */
	struct uart_desc *new_desc = (struct uart_desc *)calloc(1,
				     sizeof(struct uart_desc));
	if (!new_desc) {
		return FAILURE;
	}

	new_desc->baud_rate = param->baud_rate;

	/* Create a new aducm410 UART descriptor for platform specific parameters */
	aducm410_new_desc = (aducm410_uart_desc *)calloc(1, sizeof(aducm410_uart_desc));
	if (!aducm410_new_desc) {
		return FAILURE;
	}

	aducm410_new_desc->uart_port = ((aducm410_uart_init_param *)(
						param->extra))->uart_port;

	/* Configure a UART peripheral */
	UrtSetup((ADI_UART_TypeDef *)aducm410_new_desc->uart_port,
		 (Urt_SETUP_t *)(((aducm410_uart_init_param *)(param->extra))->uart_setup));

	new_desc->extra = (aducm410_uart_desc *)aducm410_new_desc;

	*desc = new_desc;

	return SUCCESS;
}


/**
 * @brief Free the resources allocated by uart_init().
 * @param desc - The UART descriptor.
 * @return SUCCESS in case of success, FAILURE otherwise.
 */
int32_t uart_remove(struct uart_desc *desc)
{
	if (!desc) {
		return FAILURE;
	}

	/* Free the aducm410 UART descriptor */
	if ((aducm410_uart_desc *)(desc->extra)) {
		free((aducm410_uart_desc *)(desc->extra));
	}

	/* Free the UART device descriptor */
	free(desc);

	return SUCCESS;
}
