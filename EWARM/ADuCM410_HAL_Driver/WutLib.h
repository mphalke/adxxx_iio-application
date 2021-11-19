/*!
 *****************************************************************************
 * @file:   WdtLib.h
 * @brief:  header file of watch dog timer
 *-----------------------------------------------------------------------------
 *
Copyright (c) 2013-2018 Analog Devices, Inc. All Rights Reserved.

This software is proprietary to Analog Devices, Inc. and its licensors.
By using this software you agree to the terms of the associated
Analog Devices Software License Agreement.
 ******************************************************************************/


#include "ADuCM410.h"

typedef struct
{
  //ENUM_WUT_T4CON_CLK_PCLK   PCLK: PCLK (default) 
  //ENUM_WUT_T4CON_CLK_LFOSC    LFOSC: 32 KHz Internal Oscillator 
  //ENUM_WUT_T4CON_CLK_LFOSC1   LFOSC: 32kHz Internal Oscillator 
  //ENUM_WUT_T4CON_CLK_ECLKIN   ECLKIN: External Clock from P1.0 
  uint32_t clkSource;

  //ENUM_WUT_T4CON_PRE_PREDIV1    PREDIV1: Source Clock/1 (default). If the Select
  //NUM_WUT_T4CON_PRE_PREDIV16     PREDIV16: Source Clock/16 
  //NUM_WUT_T4CON_PRE_PREDIV256    PREDIV256: Source Clock/256 
  //NUM_WUT_T4CON_PRE_PREDIV32768  PREDIV32768: Source Clock/32,768 
  uint32_t prescaler;

  //1 - enable freeze of the high 16bits after the lower bits have been read
  //0 - disable
  uint32_t freezeEn;


  //ENUM_WUT_T4CON_TMODE_PERIODIC      PERIODIC: Cleared by User to Operate in Periodic Mode.
  //ENUM_WUT_T4CON_TMODE_FREERUN       FREERUN: Set by User to Operate in Free Running Mode (default). 
  uint32_t timerMode;

  //1 - enable wake up
  //0 - disable
  uint32_t wakeupEn;

  //12 bit interval
  uint32_t interval;

  uint32_t fieldA;
  uint32_t fieldB;
  uint32_t fieldC;
  uint32_t fieldD;

  //---------------Interrupt---------
  uint32_t intEnA;
  uint32_t intEnB;
  uint32_t intEnC;
  uint32_t intEnD;
  uint32_t intRollOverEn;


}WUT_SETUP_t;

extern WUT_SETUP_t gWutSetup;

//------------------------------ Function prototypes ------------------------------------------
extern void WakeUpSetup(WUT_SETUP_t const *setup);

extern int32_t WutCfg(int32_t iMode, int32_t iWake, int32_t iPre, int32_t iClkSrc);
extern int32_t WutLdWr(int32_t iField, uint32_t  lTld);
extern uint32_t  WutLdRd(int32_t iField);
extern int32_t WutInc(int32_t iInc);
extern int32_t WutClrInt(int32_t iSource);
extern int32_t WutCfgInt(int32_t iSource, int32_t iEnable);
extern int32_t  WutVal(void);
extern int32_t WutSta(void);
#define  WutGo()       do\
                        {\
                          pADI_WUT->T4CON |= BITM_WUT_T4CON_ENABLE;\
                        }while(0)
#define  WutStop()      do\
                        {\
                          pADI_WUT->T4CON &= ~BITM_WUT_T4CON_ENABLE;\
                        }while(0)

