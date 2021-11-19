/***************************************************************************//**
 *   @file    ad70081z_data_capture.c
 *   @brief   ADC data capture interface for AD70081z IIO based applications
 *   @details This module handles the ADC data capturing for IIO client
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
#include <stdbool.h>
#include <string.h>

#include "ad70081z_data_capture.h"
#include "ad70081z_iio.h"
#include "app_config.h"
#include "error.h"
#include "delay.h"

/******************************************************************************/
/********************** Macros and Constants Definition ***********************/
/******************************************************************************/

/* Max available channels for continuous data capture. Actual number of channels
 * to be captured are supplied from an application */
#define MAX_AVAILABLE_CHANNELS		(32)

/* Timeout count to avoid stuck into potential infinite loop while checking
 * for new data into an acquisition buffer. The actual timeout factor is determined
 * through 'sampling_frequency' attribute of IIO app, but this period here makes sure
 * we are not stuck into a forever loop in case data capture is interrupted
 * or failed in between.
 * Note: This timeout factor is dependent upon the MCU clock frequency. Below timeout
 * is tested for SDP-K1 platform @180Mhz default core clock */
#define BUF_READ_TIMEOUT	(100000000)

/* ADC conversion delay in usec for different values of OSR */
#define OSR4_CONV_DELAY_USEC	4
#define OSR16_CONV_DELAY_USEC	14
#define OSR64_CONV_DELAY_USEC	66

/******************************************************************************/
/********************** Variables and User Defined Data Types *****************/
/******************************************************************************/

/* ADC data buffer */
uint8_t adc_data_buffer[DATA_BUFFER_SIZE] = {0};

/*
 *@enum		acq_buffer_state_e
 *@details	Enum holding the data acquisition buffer states
 **/
typedef enum {
	BUF_AVAILABLE,
	BUF_EMPTY,
	BUF_FULL
} acq_buffer_state_e;

/*
 *@struct	acq_buf_t
 *@details	Structure holding the data acquisition buffer parameters
 **/
typedef struct {
	acq_buffer_state_e state;		// Buffer state
	uint32_t wr_indx;				// Buffer write index (incremented per sample read)
	uint8_t sample_size;			// ADC sample/raw data size received from application
	uint8_t chn_indx;				// ADC channel index into acquisition buffer
	uint8_t active_chn[MAX_AVAILABLE_CHANNELS];	// Active channel number sequence
	volatile uint8_t *pdata;					// Pointer to data buffer
} acq_buf_t;

/* ADC data acquisition buffers */
static volatile acq_buf_t acq_buffer;

/* Flag to indicate data capture status */
static volatile bool start_adc_data_capture = false;

/* Number of active channels in any data buffer read request */
static volatile uint8_t num_of_active_channels = 0;

/* Channel data alignment variables */
static volatile bool do_chn_alignment = false;

/* Count to track number of actual samples requested by IIO client */
static volatile uint16_t num_of_requested_samples = 0;

/* Conversion delay for different values of OSR */
static uint8_t osr_delay_us;

/******************************************************************************/
/************************ Functions Declarations ******************************/
/******************************************************************************/

/******************************************************************************/
/************************ Functions Definitions *******************************/
/******************************************************************************/

/*!
 * @brief	Function to read the single ADC sample (raw data) for input channel
 * @param	input_chn[in] - Input channel to sample and read data for
 * @param	raw_data[in, out]- ADC raw data
 * @return	SUCCESS in case of success, negative error code otherwise
 */
int32_t read_single_sample(uint8_t input_chn, uint32_t *raw_data)
{
	int32_t ret;

	/* Enable IADC channel */
	if (input_chn >= AD70081Z_E10_WPD_IS0 && input_chn <= AD70081Z_E21_RTAP_IS) {
		ret = ad70081z_iadc_enable(p_ad70081z_dev_inst,
					   (enum ad70081z_afe_mux_channel)input_chn, true);
		if (IS_ERR_VALUE(ret))
			return ret;
	}

	/* Perform conversion and read the result (in register access mode) */
	ret = ad70081z_adc_read(p_ad70081z_dev_inst, input_chn, (uint16_t *)raw_data);
	if (IS_ERR_VALUE(ret))
		return ret;

	/* Disable back IADC channel */
	if (input_chn >= AD70081Z_E10_WPD_IS0 && input_chn <= AD70081Z_E21_RTAP_IS) {
		ret = ad70081z_iadc_enable(p_ad70081z_dev_inst,
					   (enum ad70081z_afe_mux_channel)input_chn, false);
		if (IS_ERR_VALUE(ret))
			return ret;
	}

	return SUCCESS;
}

/*!
 * @brief	Function to read the converted ADC sample/raw data for previous
 *			channel and also to enable the next channel in CC mode
 * @param	adc_sample[out] - ADC sample/raw data
 * @param	chn[in]- Current ADC channel
 * @return	SUCCESS in case of success, negative error code otherwise
 */
int32_t read_converted_sample(uint32_t *adc_sample, uint8_t chn)
{
	enum ad70081z_afe_mux_channel next_chn;

	/* Select the next ADC channel from the list of active channels */
	if (acq_buffer.chn_indx >= (num_of_active_channels - 1)) {
		next_chn = acq_buffer.active_chn[0];
	} else {
		next_chn = acq_buffer.active_chn[acq_buffer.chn_indx + 1];
	}

	return ad70081z_cc_read(p_ad70081z_dev_inst, &next_chn,
				(uint16_t *)adc_sample);
}

/*!
 * @brief	Function to perform the operations needed before starting a data
 *			capture in CC mode
 * @param	chn_mask[in]- Active channels mask
 * @return	SUCCESS in case of success, negative error code otherwise
 */
int32_t continuous_sample_read_start_ops(uint32_t chn_mask)
{
	int32_t ret;
	enum ad70081z_afe_mux_channel input_chn;

	/* Enable IADC channels from the list of active channels */
	for (uint8_t chn = 0; chn < num_of_active_channels; chn++) {
		input_chn = acq_buffer.active_chn[chn];

		if (input_chn >= AD70081Z_E10_WPD_IS0 && input_chn <= AD70081Z_E21_RTAP_IS) {
			ret = ad70081z_iadc_enable(p_ad70081z_dev_inst,
						   (enum ad70081z_afe_mux_channel)input_chn,
						   true);
			if (IS_ERR_VALUE(ret))
				return ret;
		}
	}

	/* Set the OSR conversion delay to use during burst data capture mode */
	switch (p_ad70081z_dev_inst->osr) {
	case AD70081Z_ADC_CONFIG_OSR_NO_OVERSAMPLING:
		osr_delay_us = 0;
		break;

	case AD70081Z_ADC_CONFIG_OSR_OVERSAMPLING_X_4:
		osr_delay_us = OSR4_CONV_DELAY_USEC;
		break;

	case AD70081Z_ADC_CONFIG_OSR_OVERSAMPLING_X_16:
		osr_delay_us = OSR16_CONV_DELAY_USEC;
		break;

	case AD70081Z_ADC_CONFIG_OSR_OVERSAMPLING_X_64:
		osr_delay_us = OSR64_CONV_DELAY_USEC;
		break;

	default:
		return FAILURE;
	}

	/* Select the first channel from the list of active channels */
	ret = ad70081z_adc_set_config(p_ad70081z_dev_inst, acq_buffer.active_chn[0]);
	if (IS_ERR_VALUE(ret))
		return ret;

	/* Enter into CC mode */
	ret = ad70081z_cc_start(p_ad70081z_dev_inst);
	if (IS_ERR_VALUE(ret))
		return ret;

	/* Start Conversion */
	ret = ad70081z_adc_convst(p_ad70081z_dev_inst);
	if (IS_ERR_VALUE(ret))
		return ret;

	return SUCCESS;
}

/*!
 * @brief	Function to perform the operations needed before stopping a data
 *			capture in CC mode
 * @return	SUCCESS in case of success, negative error code otherwise
 */
int32_t continuous_sample_read_stop_ops(void)
{
	int32_t ret;
	enum ad70081z_afe_mux_channel input_chn;

	/* Exit from CC mode into register mode */
	ret = ad70081z_cc_exit(p_ad70081z_dev_inst);
	if (IS_ERR_VALUE(ret))
		return ret;

	/* Disable previously enabled IADC channels */
	for (uint8_t chn = 0; chn < num_of_active_channels; chn++) {
		input_chn = acq_buffer.active_chn[chn];

		if (input_chn >= AD70081Z_E10_WPD_IS0 && input_chn <= AD70081Z_E21_RTAP_IS) {
			ret = ad70081z_iadc_enable(p_ad70081z_dev_inst,
						   (enum ad70081z_afe_mux_channel)input_chn,
						   false);
			if (IS_ERR_VALUE(ret))
				return ret;
		}
	}

	return SUCCESS;
}

/*!
 * @brief	Reset the data capture specific variables
 * @return	none
 */
static void reset_data_capture(void)
{
	/* Reset data capture flags */
	start_adc_data_capture = false;
	num_of_active_channels = 0;

	/* Reset acquisition buffer states and clear old data */
	acq_buffer.state = BUF_EMPTY;
	acq_buffer.wr_indx = 0;
	acq_buffer.chn_indx = 0;
	acq_buffer.pdata = adc_data_buffer;
	do_chn_alignment = true;
}

/*!
 * @brief	Function to prepare the data ADC capture for new READBUFF
 *			request from IIO client (for active channels)
 * @param	ch_mask[in] - Channels to enable for data capturing
 * @param	num_of_chns[in] - ADC channel count
 * @param	sample_size[in] - Sample size in bytes
 * @return	0 in case of SUCCESS, negative error code otherwise
 */
int32_t prepare_data_transfer(uint32_t ch_mask, uint8_t num_of_chns,
			      uint8_t sample_size)
{
	uint32_t mask = 0x1;
	uint8_t index = 0;

	/* Reset data capture module specific flags and variables */
	reset_data_capture();

	acq_buffer.sample_size = sample_size;

	/* Get the active channels count based on the channel mask set in an IIO
	 * client application (channel mask starts from bit 0, so for 0th ADC
	 * channel in the 'ad70081z_afe_mux_channel' enum table, the mask value
	 * will be 0x1. As 0th ADC channels in not a valid one, the chn count
	 * starts from 1st valid Mux channel in a for loop below) */
	for (uint8_t chn = AD70081Z_E1_CTHRM_VS; chn <= num_of_chns; chn++) {
		if (ch_mask & mask) {
			acq_buffer.active_chn[index++] = chn;
			num_of_active_channels++;
		}

		mask <<= 1;
	}

	/* Start continuous data capture */
	if (continuous_sample_read_start_ops(ch_mask) != SUCCESS) {
		return FAILURE;
	}

	start_adc_data_capture = true;
	return SUCCESS;
}

/*!
 * @brief	Function to stop ADC data capture
 * @return	0 in case of SUCCESS, negative error code otherwise
 */
int32_t end_data_transfer(void)
{
	start_adc_data_capture = false;

	/* Enable operations required post continuous sample read */
	if (continuous_sample_read_stop_ops() != SUCCESS) {
		return FAILURE;
	}

	/* Reset data capture module specific flags and variables */
	reset_data_capture();

	return SUCCESS;
}

/*!
 * @brief	Function to capture ADC data in a burst
 * @param	pbuf[out] - Pointer to ADC data buffer
 * @param	nb_of_samples[in] - Number of samples to be read
 * @return	SUCCESS in case of success, negative error code otherwise
 */
static int32_t capture_burst_data(uint8_t *pbuf, uint32_t nb_of_samples)
{
	uint32_t sample_indx = 0;
	uint32_t adc_sample;

	while (sample_indx < nb_of_samples) {
		if (read_converted_sample(&adc_sample,
					  acq_buffer.active_chn[acq_buffer.chn_indx]) == SUCCESS) {
			/* Track the count for recently sampled channel */
			acq_buffer.chn_indx++;
			if (acq_buffer.chn_indx >= num_of_active_channels) {
				acq_buffer.chn_indx = 0;
			}

			/* Copy adc samples into acquisition buffer to transport over
			 * communication link */
			memcpy((uint8_t *)pbuf, &adc_sample, acq_buffer.sample_size);
			pbuf += acq_buffer.sample_size;

			sample_indx++;
		} else {
			return FAILURE;
		}

		/* Trigger new Conversion */
		ad70081z_adc_convst(p_ad70081z_dev_inst);

		/* Allow for conversion to finish (TBD usec) */
		if (osr_delay_us > 0)
			udelay(osr_delay_us);
	}

	return SUCCESS;
}

/*!
 * @brief	Function to read and align the ADC buffered raw data
 * @param	pbuf[out] - Pointer to ADC data buffer
 * @param	nb_of_samples[in] - Number of samples to be read
 * @return	Number of bytes read
 */
int32_t read_buffered_data(void *pbuf, uint32_t nb_of_samples)
{
	uint32_t timeout = BUF_READ_TIMEOUT;	// Buffer new data read timeout count
	num_of_requested_samples = (nb_of_samples * num_of_active_channels);

#if (DATA_CAPTURE_MODE == BURST_DATA_CAPTURE)
	capture_burst_data(pbuf, num_of_requested_samples);
#else
	acq_buffer.wr_indx = 0;
	acq_buffer.pdata = adc_data_buffer;
	acq_buffer.state = BUF_AVAILABLE;

	/* Wait for acquisition buffer to become full */
	do {
		timeout--;
	} while ((acq_buffer.state != BUF_FULL) && (timeout > 0));

	if (timeout == 0) {
		/* This returns the empty buffer */
		return FAILURE;
	}
#endif

	return SUCCESS;
}

/*!
 * @brief	This is an ISR (Interrupt Service Routine) to monitor end of conversion event.
 * @param	*ctx[in] - Callback context (unused)
 * @param	event[in] - Callback event (unused)
 * @param	extra[in] - Callback extra (unused)
 * @return	none
 * @details	This is an Interrupt callback function/ISR invoked in synchronous/asynchronous
 *			manner depending upon the application implementation. The conversion results
 *			are read into acquisition buffer and control continue to sample next channel.
 *			This continues until conversion is stopped (through IIO client command)
 * @note	This function also handles the logic to align the first channel data after
 *			every 'n' sample transmission. This is required to visualize data properly
 *			on IIO client application.
 */
void data_capture_callback(void *ctx, uint32_t event, void *extra)
{
	uint32_t adc_sample;

	if (start_adc_data_capture == true) {
		/* Read the sample(s) for channel(s) which has/have been sampled recently and
		 * get the number of samples read count */
		if (read_converted_sample(&adc_sample,
					  acq_buffer.active_chn[acq_buffer.chn_indx]) != FAILURE) {
			do {
				/* Wait until conversion event for the zeroth channel is triggered */
				if ((do_chn_alignment == true) && (acq_buffer.chn_indx != 0)) {
					/* Track the count for recently sampled channel */
					acq_buffer.chn_indx++;
					if (acq_buffer.chn_indx >= num_of_active_channels) {
						acq_buffer.chn_indx = 0;
					}

					/* If recent sampled channel is not a zeroth enabled channel
					 * in the channels list, return without storing data into buffer */
					break;
				}

				/* Track the count for recently sampled channel */
				acq_buffer.chn_indx++;
				if (acq_buffer.chn_indx >= num_of_active_channels) {
					acq_buffer.chn_indx = 0;
				}

				if (acq_buffer.state == BUF_AVAILABLE) {
					/* Reset channel data alignment flag if control reach here */
					do_chn_alignment = false;

					/* Copy adc samples into acquisition buffer to transport over
					 * communication link */
					memcpy((uint8_t *)acq_buffer.pdata, &adc_sample, acq_buffer.sample_size);
					acq_buffer.pdata += acq_buffer.sample_size;

					/* Check for acquisition buffer full condition */
					acq_buffer.wr_indx++;
					if (acq_buffer.wr_indx >= num_of_requested_samples) {
						acq_buffer.state = BUF_FULL;
						do_chn_alignment = true;
					}
				}
			} while (0);
		}

		/* Trigger next Conversion */
		ad70081z_adc_convst(p_ad70081z_dev_inst);
	}
}
