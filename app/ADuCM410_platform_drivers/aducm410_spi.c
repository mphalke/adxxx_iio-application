/***************************************************************************//**
 *   @file   spi.cpp
 *   @brief  Implementation of SPI Platform drivers
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
#include "SpiLib.h"

#include "spi.h"
#include "aducm410_spi.h"
#include "error.h"

/******************************************************************************/
/********************** Macros and Constants Definitions **********************/
/******************************************************************************/

#define FIFO_SIZE       8       // Tx/Rx FIFO size

/******************************************************************************/
/********************** Variables and User defined data types *****************/
/******************************************************************************/

/******************************************************************************/
/************************ Functions Declarations ******************************/
/******************************************************************************/

/******************************************************************************/
/************************ Functions Definitions *******************************/
/******************************************************************************/

/**
 * @brief Initialize the SPI communication peripheral.
 * @param desc - The SPI descriptor.
 * @param init_param - The structure that contains the SPI parameters.
 * @return SUCCESS in case of success, FAILURE otherwise.
 */
int32_t spi_init(struct spi_desc **desc,
		 const struct spi_init_param *param)
{
	if (!desc || !param) {
		return FAILURE;
	}

	/* Allocate memory to a new spi descriptor */
	spi_desc *new_desc = (spi_desc *)calloc(1, sizeof(spi_desc));
	if (!new_desc) {
		return FAILURE;
	}

	new_desc->chip_select = param->chip_select;
	new_desc->mode = param->mode;
	new_desc->max_speed_hz = param->max_speed_hz;

	/* Allocate memory to a new aducm410 spi descriptor */
	aducm410_spi_desc *aducm410_new_desc = (aducm410_spi_desc *)calloc(1,
					       sizeof(aducm410_spi_desc));

	if (!aducm410_new_desc) {
		return FAILURE;
	}

	aducm410_new_desc->spi_port = ((aducm410_spi_init_param *)(
					       param->extra))->spi_port;

	/* Setup SPI */
	SpiSetup((ADI_SPI_TypeDef *)(aducm410_new_desc->spi_port),
		 (SPI_SETUP_t *)(((aducm410_spi_init_param *)(param->extra))->spi_setup));

	/* Set SPI clock divider (baud rate) */
	SpiBaud(aducm410_new_desc->spi_port,
		((aducm410_spi_init_param *)(param->extra))->clk_div);

	new_desc->extra = (aducm410_spi_desc *)aducm410_new_desc;

	*desc = new_desc;

	return SUCCESS;
}


/**
 * @brief Free the resources allocated by spi_init().
 * @param desc - The SPI descriptor.
 * @return SUCCESS in case of success, FAILURE otherwise.
 */
int32_t spi_remove(struct spi_desc *desc)
{
	if (!desc) {
		return FAILURE;
	}

	/* Free the aducm410 extra descriptor object */
	if ((aducm410_spi_desc *)(desc->extra)) {
		free((aducm410_spi_desc *)(desc->extra));
	}

	/* Free the SPI descriptor object */
	free(desc);

	return SUCCESS;
}


/**
 * @brief Write and read data to/from SPI.
 * @param desc - The SPI descriptor.
 * @param data - The buffer with the transmitted/received data.
 * @param bytes_number - Number of bytes to write/read.
 * @return SUCCESS in case of success, FAILURE otherwise.
 */
int32_t spi_write_and_read(struct spi_desc *desc,
			   uint8_t *data,
			   uint16_t bytes_number)
{
	uint16_t transmit_loops = bytes_number /
				  FIFO_SIZE; // FIFO is limited to only 8-bytes
	uint16_t odd_bytes = bytes_number % FIFO_SIZE;
	uint16_t byte_indx = 0;
	bool cs_override_done = false;

	ADI_SPI_TypeDef *spi_port = (ADI_SPI_TypeDef *)((aducm410_spi_desc *)(
					    desc->extra))->spi_port;
	if (!desc) {
		return FAILURE;
	}

	spi_port->CSOVERRIDE = ENUM_SPI_CSOVERRIDE_CTL_NOTFORCE;

	while (transmit_loops > 0) {

		/* If bytes are more than FIFO size (8), the CS must be asserted low
		   forcefully during two consecutive FIFO transmission */
		if (!cs_override_done) {
			spi_port->CSOVERRIDE = ENUM_SPI_CSOVERRIDE_CTL_FORCETO0;
			cs_override_done = true;
		}

		spi_port->CNT = FIFO_SIZE;

		/* Fill the FIFO with max size */
		for (size_t byte = 0 ; byte < FIFO_SIZE; byte++) {
			SpiTx(spi_port, data[byte_indx + byte]);
		}

		/* Initiate the transmit by doing dummy Rx buffer read */
		SpiRx(spi_port);

		while(!(SpiSta(spi_port) & BITM_SPI_STAT_XFRDONE));
		spi_port->STAT |= BITM_SPI_STAT_XFRDONE;

		/* Copy from RX FIFO to the supplied data buffer to return to caller */
		for (uint8_t byte = 0; byte < FIFO_SIZE; byte++) {
			data[byte_indx + byte] = SpiRx(spi_port);
		}

		byte_indx += FIFO_SIZE;
		transmit_loops--;
	}

	/* Perform read/write operation for odd bytes (less than FIFO_SIZE) */
	if (odd_bytes) {

		spi_port->CNT = odd_bytes;

		/* Fill the FIFO */
		for (size_t byte = 0 ; byte < odd_bytes ; byte++) {
			SpiTx(spi_port, data[byte_indx + byte]);
		}

		/* Initiate the transmit by doing dummy Rx buffer read */
		SpiRx(spi_port);

		while(!(SpiSta(spi_port) & BITM_SPI_STAT_XFRDONE));
		spi_port->STAT |= BITM_SPI_STAT_XFRDONE;

		/* Copy from RX FIFO to the supplied data buffer to return to caller */
		for(uint8_t byte = 0; byte < odd_bytes; byte++) {
			data[byte_indx + byte] = SpiRx(spi_port);
		}
	}

	return SUCCESS;
}
