/***************************************************************************//**
* @file   ad70081z_iio.h
* @brief  Header file for AD70081z IIO interface
********************************************************************************
* Copyright (c) 2021 Analog Devices, Inc.
* All rights reserved.
*
* This software is proprietary to Analog Devices, Inc. and its licensors.
* By using this software you agree to the terms of the associated
* Analog Devices Software License Agreement.
*******************************************************************************/
#ifndef _AD70081Z_IIO_H_
#define _AD70081Z_IIO_H_

/******************************************************************************/
/***************************** Include Files **********************************/
/******************************************************************************/

#include "iio.h"
#include "iio_types.h"
#include "ad70081z.h"

/******************************************************************************/
/********************** Macros and Constants Definition ***********************/
/******************************************************************************/

/******************************************************************************/
/********************** Public/Extern Declarations ****************************/
/******************************************************************************/

/* AD70081z global device instance for accessing device specific APIs */
extern struct ad70081z_dev *p_ad70081z_dev_inst;

/* Init the IIO interface */
int32_t ad70081z_iio_initialize(void);

/* Run the IIO event handler */
void ad70081z_iio_event_handler(void);

#endif /* _AD70081Z_IIO_H_ */
