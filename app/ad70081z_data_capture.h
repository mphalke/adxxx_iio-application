/***************************************************************************//**
 *   @file   ad70081z_data_capture.h
 *   @brief  Header for AD70081z ADC data capture interfaces
********************************************************************************
 * Copyright (c) 2021 Analog Devices, Inc.
 * All rights reserved.
 *
 * This software is proprietary to Analog Devices, Inc. and its licensors.
 * By using this software you agree to the terms of the associated
 * Analog Devices Software License Agreement.
*******************************************************************************/

#ifndef _AD70081Z_DATA_CAPTURE_H_
#define _AD70081Z_DATA_CAPTURE_H_

/******************************************************************************/
/***************************** Include Files **********************************/
/******************************************************************************/

#include <stdint.h>
#include <stdbool.h>
#include <stddef.h>

#include "app_config.h"

/******************************************************************************/
/********************** Macros and Constants Definition ***********************/
/******************************************************************************/

/* Max size of the acquisition buffer (in terms of bytes) */
#if (ACTIVE_PLATFORM == MBED_PLATFORM)
#define DATA_BUFFER_SIZE	(32768)		// 32Kbytes
#else
#define DATA_BUFFER_SIZE	(8192)		// 8Kbytes
#endif

/******************************************************************************/
/************************ Public Declarations *********************************/
/******************************************************************************/

extern uint8_t adc_data_buffer[];

int32_t read_single_sample(uint8_t input_chn, uint32_t *raw_data);
int32_t read_buffered_data(void *pbuf, uint32_t nb_of_samples);
int32_t prepare_data_transfer(uint32_t ch_mask, uint8_t num_of_chns,
			      uint8_t sample_size_in_byte);
int32_t end_data_transfer(void);
void data_capture_callback(void *ctx, uint32_t event, void *extra);

#endif /* _AD70081Z_DATA_CAPTURE_H_ */
