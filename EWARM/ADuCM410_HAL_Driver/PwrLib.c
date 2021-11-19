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
#include	"PwrLib.h"

/**
	@brief void PwrCfg(uint32_t Mode)
			========== Sets MCU power mode.
	@param Mode :{ENUM_PMG_PWRMOD_FLEXI,ENUM_PMG_PWRMOD_HIBERNATE,ENUM_PMG_PWRMOD_SHUTDOWN}
         0 or ENUM_ALWAYS_ON_PWRMOD_PWRMOD_FULLACTIVE          Active Mode 
         1 or ENUM_ALWAYS_ON_PWRMOD_PWRMOD_CORESLEEP         CORE_SLEEP Mode 
         2 or ENUM_ALWAYS_ON_PWRMOD_PWRMOD_SYSSLEEP          SYS_SLEEP Mode 
         3 or ENUM_ALWAYS_ON_PWRMOD_PWRMOD_HIBERNATE         Hibernate Mode 
	@return none.
**/
void PwrCfg(uint32_t Mode)
{
   int32_t index = 0;
   //uint32_t savedWDT;
   //savedWDT = pADI_WDT0->CTL;  //None of the watchdog timer registers are retained in hibernate mode
   if ((Mode == 2) || (Mode == 3))
   {
      SCB->SCR = 0x04;		// sleepdeep mode - write to the Cortex-m3 System Control register bit2
   }
   pADI_ALLON->PWRKEY = (uint16_t)POWER_KEY1;	// key1
   pADI_ALLON->PWRKEY = (uint16_t)POWER_KEY2;	// key2
   pADI_ALLON->PWRMOD = (uint16_t)Mode;

   for (index=0;index<2;index++);
   __WFI();
   for (index=0;index<2;index++);
   //pADI_WDT0->CTL = savedWDT;  //restore WDT control register.
}