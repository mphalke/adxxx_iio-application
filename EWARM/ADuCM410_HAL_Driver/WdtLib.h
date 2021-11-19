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
#ifndef WDT_LIB_H
#define WDT_LIB_H

#ifdef __cplusplus
extern "C" {
#endif 

#include "ADuCM410.h"
#include <stdint.h>

#define WDT_REFRESH_VALUE 0xCCCC

typedef struct
{
  //load value of WDT, WDT will count down from this value.
  //also reload this value when WDT been refreshed(Kicked)
  uint32_t load;  

  //1 - WDT stop counting when MCU in hibernate mode
  //0 - WDT continue counting in hibernate mode
  uint32_t stopWhenSleep;

  //ENUM_WDT_CON_IRQ_INTERRUPT - report intterrupt when counted to 0
  //ENUM_WDT_CON_IRQ_RESET - reset when counted to 0
  uint32_t intEn;

  //ENUM_WDT_CON_MDE_FREE, Free-running Mode
  //ENUM_WDT_CON_MDE_PERIODIC, Periodic Mode (default) 
  uint32_t mode;

  //WDT is based on 32.768KHz internal Osicllator
  //when set to 1, WDT clock is divided by 2
  uint32_t clkDiv2En;

  //ENUM_WDT_CON_PRE_DIV1      Source Clock/1 
  //ENUM_WDT_CON_PRE_DIV16     Source Clock/16. 
  //ENUM_WDT_CON_PRE_DIV256    Source Clock/256 (default). 
  //ENUM_WDT_CON_PRE_DIV4096   Source Clock/4096 
  //WDT counting clock = PCLK/prescale, when clkDiv2En = 0
  //WDT counting clock = PCLK/prescale/2, when clkDiv2En = 1
  uint32_t prescale;

  //window feature: CPU should refresh WDT after WDT count value smaller than windowMinLoad
  //this is to make sure WDT is not refreshed too early and too late.
  //1 -  enable window feature of WDT
  //0 - disable window feature of WDT 
  uint32_t windowEn;
  uint32_t windowMinLoad;
}WDT_SETUP_t;


extern WDT_SETUP_t gWdtSetup;

//------------------------------ Function prototypes ------------------------------------------
//Watch dog timer setup
extern void WdtSetup(const WDT_SETUP_t *pSetup);

extern uint32_t WdtLd(uint16_t Tld);
extern uint32_t WdtVal(void);
extern uint32_t WdtCfg(uint32_t Mod, uint32_t Pre, uint32_t Int, uint32_t Pd);
extern uint32_t WdtClkCfg(uint32_t div2En, uint32_t pre);
extern uint32_t WdtGo(uint32_t enable);
extern uint32_t WdtRefresh(void);
extern uint32_t WdtSta(void);
extern uint32_t WdtWindowCfg(uint32_t minLd, uint32_t enable);

#ifdef __cplusplus
}
#endif

#endif   //#WDT_LIB_H
