/*!
 *****************************************************************************
 * @file:  PwmLib.h 
 * @brief: header of PWM
   @version  V0.2
   @author   ADI
   @date     January 2019
   @par Revision History:
   - V0.1, December 2018: initial version. 
   - V0.2, January 2019: Added library functions
 *-----------------------------------------------------------------------------
 *
Copyright (c) 2013-2019 Analog Devices, Inc. All Rights Reserved.

This software is proprietary to Analog Devices, Inc. and its licensors.
By using this software you agree to the terms of the associated
Analog Devices Software License Agreement.
 ******************************************************************************/
#ifndef PWM_LIB_H
#define PWM_LIB_H

#ifdef __cplusplus
extern "C" {
#endif 

#include "ADuCM410.h"

extern int PwmInit(unsigned int iPWMCP, unsigned int iPWMIEN, unsigned int iSYNC, unsigned int iTRIP);
extern int PwmClrInt(unsigned int iSource);
extern int PwmTime(int iPair, unsigned int uiFreq, unsigned int uiPWMH_High, unsigned int uiPWML_High); 
extern int PwmGo(unsigned int iPWMEN, unsigned int iHMODE);
extern int PwmHBCfg(unsigned int iENA, unsigned int iPOINV, unsigned int iHOFF, unsigned int iDIR);
extern int PwmInvert(int iInv1,int iInv3,int iInv5,int iInv7);
extern int PwmLoad(int iLoad);

#define	PWMUCLK_2 0
#define	PWMUCLK_4 0x40
#define	PWMUCLK_8 0x80
#define	PWMUCLK_16 0xC0
#define	PWMUCLK_32 0x100
#define	PWMUCLK_64 0x140
#define	PWMUCLK_128 0x180
#define	PWMUCLK_256 0x1C0

#define	PWM0_1 0
#define	PWM2_3 1
#define	PWM4_5 2
#define	PWM6_7 3


#ifdef __cplusplus
}
#endif

#endif   //#PWM_LIB_H
