/***************************************************************************//**
*   @file   ad70081z_regs.h
*   @brief  Global declarations for ad70081z_regs module
********************************************************************************
* Copyright (c) 2021 Analog Devices, Inc.
* All rights reserved.
*
* This software is proprietary to Analog Devices, Inc. and its licensors.
* By using this software you agree to the terms of the associated
* Analog Devices Software License Agreement.
*******************************************************************************/
#ifndef _AD70081Z_REGS_H_
#define _AD70081Z_REGS_H_

/******************************************************************************/
/***************************** Include Files **********************************/
/******************************************************************************/

#include <stdint.h>

/******************************************************************************/
/********************** Macros and Constants Definition ***********************/
/******************************************************************************/

/******************************************************************************/
/************************ Public Declarations *********************************/
/******************************************************************************/

/* Get the AD70081z registers count (actual single + multi-byte entity registers
 * available and defined in ad70081z.h file) */
#define AD70081Z_REGISTERS_COUNT	(146)

/* Max register address available (last register address defined in ad70081z.h file) */
#define MAX_REGISTER_ADDRESS	(AD70081Z_ADC_CONFIG)

extern const uint32_t ad70081z_regs[];

#endif /* _AD70081Z_REGS_H_ */
