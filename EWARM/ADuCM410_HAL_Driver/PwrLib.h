/*!
 *****************************************************************************
 * @file:   
 * @brief:  
 *-----------------------------------------------------------------------------
 *
Copyright (c) 2013-2018 Analog Devices, Inc. All Rights Reserved.

This software is proprietary to Analog Devices, Inc. and its licensors.
By using this software you agree to the terms of the associated
Analog Devices Software License Agreement.
 ******************************************************************************/
#ifndef PWR_LIB_H
#define PWR_LIB_H

#ifdef __cplusplus
extern "C" {
#endif 

#include "ADuCM410.h"

#define POWER_KEY1   0x4859
#define POWER_KEY2   0xF27B


void PwrCfg(uint32_t Mode);


#ifdef __cplusplus
}
#endif

#endif 

