/*!
 *****************************************************************************
 * @file:   WdtLib.c
 * @brief:  source file of watch dog timer
 *-----------------------------------------------------------------------------
 *
Copyright (c) 2013-2018 Analog Devices, Inc. All Rights Reserved.

This software is proprietary to Analog Devices, Inc. and its licensors.
By using this software you agree to the terms of the associated
Analog Devices Software License Agreement.
 ******************************************************************************/

#include "WdtLib.h"


/**
   @brief uint32_t WdtLd(uint16_t Tld);
         ========== Sets timer reload value.
   @param Tld :{0-0xFFFF}
      - Sets reload value to Tld. 
   @return 1.
**/

uint32_t WdtLd(uint16_t Tld)
{      
   pADI_WDT->LD= Tld;
   return 1;
}

/**
   @brief uint32_t WdtVal(void);
         ========== Reads timer value.
   @return Timer value WDTVALS.
**/

uint32_t WdtVal(void)
{
   return pADI_WDT->VALS;
}


/**
   @brief uint32_t WdtCfg(uint32_t Mod, uint32_t Pre, uint32_t Int, uint32_t Pd);
         ========== Configures the watchdog timer.
   @param iMod :{ENUM_WDT_CON_MDE_FREE, ENUM_WDT_CON_MDE_PERIODIC}
      - ENUM_WDT_CON_MDE_FREE, the timer operates in free running mode.
      - ENUM_WDT_CON_MDE_PERIODIC, the timer operates in periodic mode.
   @param iPre :{ENUM_WDT_CON_PRE_DIV1,ENUM_WDT_CON_PRE_DIV16,ENUM_WDT_CON_PRE_DIV256,ENUM_WDT_CON_PRE_DIV4096}

   @param iInt :{ENUM_WDT_CON_IRQ_RESET,ENUM_WDT_CON_IRQ_INTERRUPT}
      - ENUM_WDT_CON_IRQ_RESET, to generate a reset on a timer timeout.
      - ENUM_WDT_CON_IRQ_INTERRUPT, to generate an interrupt on a timer timeout.
   @param iPd :{T3CON_PMD_DIS,T3CON_PMD_EN}
      - ENUM_WDT_CON_PDSTOP_CONTINUE, the timer continues to count when in hibernate mode.
      - ENUM_WDT_CON_PDSTOP_STOP, the timer stops counting when in hibernate mode.
   @return 1.
**/

uint32_t WdtCfg(uint32_t Mod, uint32_t Pre, uint32_t Int, uint32_t Pd)
{
   uint32_t	i1;
   i1 = pADI_WDT->CON & 0x20;  // keep wdt disabled 
   i1 |= Mod<<BITP_WDT_CON_MDE;
   i1 |= Pre<<BITP_WDT_CON_PRE;
   i1 |= Int<<BITP_WDT_CON_IRQ;
   i1 |= Pd;
   pADI_WDT->CON = (uint16_t)i1;
   return 1;	
}

/*
@brief uint32_t WdtClkCfg(uint32_t div2En, uint32_t pre)
      ===========
 
@param div2En: {true, false}
            - 1 or true, clock source for wdt is divided by 2
            - 0 or false, no division
@param pre: {ENUM_WDT_CON_PRE_DIV1,ENUM_WDT_CON_PRE_DIV16,ENUM_WDT_CON_PRE_DIV256,ENUM_WDT_CON_PRE_DIV4096}
      - ENUM_WDT_CON_PRE_DIV1, for a prescaler of 1.
      - ENUM_WDT_CON_PRE_DIV16, for a prescaler of 16.
      - ENUM_WDT_CON_PRE_DIV256, for a prescaler of 256.
      - ENUM_WDT_CON_PRE_DIV4096, for a prescaler of 4096.
@return none
**/
uint32_t WdtClkCfg(uint32_t div2En, uint32_t pre)
{
      uint32_t reg;
      reg = pADI_WDT->CON & (~(BITM_WDT_CON_CLKDIV2|BITM_WDT_CON_PRE));
      if (div2En > 0)
      {
            reg |= BITM_WDT_CON_CLKDIV2;
      }
      else
      {
            reg &= ~BITM_WDT_CON_CLKDIV2;
      }
      reg |= (pre<<BITP_WDT_CON_PRE);
      pADI_WDT->CON = (uint16_t)reg;

      return 1;
}

/**
   @brief uint32_t WdtGo(uint32_t enable);
         ========== Enable or reset the watchdog timer.
   @param enable :{ture,false}
      - 1 or ture, to enable the timer.
      - 0 or false, to reset the timer.
   @return 1.
**/

uint32_t WdtGo(uint32_t enable)
{
  if (enable > 0)
    pADI_WDT->CON |= BITM_WDT_CON_EN;
  else
    pADI_WDT->CON &= ~BITM_WDT_CON_EN;
   return 1;
}

/**
   @brief uint32_t WdtRefresh(void);
         ========== refresh watch dog timer
   @return 1 
**/

uint32_t WdtRefresh(void)
{
   //BITM_WDT_STA_CLRI set means previous Wdt kick in progress, should not give another kick
   if(!(pADI_WDT->STA & BITM_WDT_STA_CLRI))  
   {
      pADI_WDT->CLRI = (uint16_t)WDT_REFRESH_VALUE;
   }
   return 1;
}

/**
   @brief uint32_t WdtSta(void);
         ========== Returns timer Status.
   @return value of STA:
**/

uint32_t WdtSta(void)
{
   return pADI_WDT->STA;
}

/*
@brief uint32_t WdtWindowCfg(uint32_t minLd, uint32_t enable)
      =========== confiure window of wdt
 
@param minLd: minimum value that allows refreshing wdt
@param enable: {true,false}
      - 1 or ture, enable windowed watch dog timer feature
      - 0 or false, enable windowed watch dog timer feature
@return none
**/
uint32_t WdtWindowCfg(uint32_t minLd, uint32_t enable)
{
      if (enable > 0)
      {
            pADI_WDT->MINLD = (uint16_t)minLd;
            pADI_WDT->CON |= BITM_WDT_CON_MINLOADEN;
      }
      else
      {
            pADI_WDT->CON &= ~BITM_WDT_CON_MINLOADEN;
      }
      return 1;
}

/*
@brief void WdtSetup(const WDT_SETUP_t *pSetup)
      =========== setup for watch dog timer
@param pSetup: pointer to WDT_SETUP_t setup structure
@return none
**/
void WdtSetup(const WDT_SETUP_t *pSetup)
{
   uint32_t regCon;
   regCon = (pSetup->stopWhenSleep<<BITP_WDT_CON_PDSTOP)|(pSetup->intEn<<BITP_WDT_CON_IRQ)    \
            |(pSetup->prescale<<BITP_WDT_CON_PRE)|(pSetup->mode<<BITP_WDT_CON_MDE)      \
            |(pSetup->clkDiv2En<<BITP_WDT_CON_CLKDIV2)|(pSetup->windowEn<<BITP_WDT_CON_MINLOADEN);
   if(pSetup->intEn)
   {
      regCon |= BITM_WDT_CON_WDTIRQEN;
   }

   pADI_WDT->LD =  (uint16_t)(pSetup->load);
   if(pSetup->windowEn)
   {
      pADI_WDT->MINLD  =  (uint16_t)(pSetup->windowMinLoad);
   }
   pADI_WDT->CON = (uint16_t)regCon;

}


/**@}*/
