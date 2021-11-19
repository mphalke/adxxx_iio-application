/*!
 *****************************************************************************
 * @file:   GptLib.c
 * @brief:  library for general purpose timer
 *-----------------------------------------------------------------------------
 *
Copyright (c) 2013-2018 Analog Devices, Inc. All Rights Reserved.

This software is proprietary to Analog Devices, Inc. and its licensors.
By using this software you agree to the terms of the associated
Analog Devices Software License Agreement.
 ******************************************************************************/

#include "GptLib.h"

/**
	@brief uint32_t GptCfg(ADI_TMR_TypeDef *pTMR, uint32_t iClkSrc, uint32_t iScale, uint32_t iMode)
			==========Configures timer GPTx if not busy. 
	@param pTMR :{pADI_GPT0,pADI_GPT1,pADI_GPT2}
		- pADI_GPT0 for timer 0.
		- pADI_GPT1 for timer 1.
      - pADI_GPT2 for timer 2.
	@param iClkSrc :{ENUM_TMR_CON_CLK_PCLK0,ENUM_TMR_CON_CLK_HCLK,ENUM_TMR_CON_CLK_LFOSC,ENUM_TMR_CON_CLK_HFXTAL}
		- TxCON.5,6
		- ENUM_TMR_CON_CLK_PCLK0   PCLK. 
      - ENUM_TMR_CON_CLK_HCLK   ROOT_CLK 
      - ENUM_TMR_CON_CLK_LFOSC  LFOSC. 32 KHz OSC 
      - ENUM_TMR_CON_CLK_HFXTAL HFXTAL. 16 MHz OSC or XTAL (Dependent on CLKCON0.11) 
	@param iScale :{ENUM_TMR_CON_PRE_DIV1,ENUM_TMR_CON_PRE_DIV16,ENUM_TMR_CON_PRE_DIV256,ENUM_TMR_CON_PRE_DIV32768}
		- TxCON.0,1
      - ENUM_TMR_CON_PRE_DIV1      Source_clock / [1 or 4] 
      - ENUM_TMR_CON_PRE_DIV16     Source_clock / 16 
      - ENUM_TMR_CON_PRE_DIV256    Source_clock / 256 
      - ENUM_TMR_CON_PRE_DIV32768  Source_clock / 32,768 
	@param iMode :{BITM_TMR_CON_MOD|BITM_TMR_CON_UP|BITM_TMR_CON_RLD|BITM_TMR_CON_ENABLE|BITM_TMR_CON_EVENTEN}	
		- TxCON.2-4,7,12	
      - BITM_TMR_CON_MOD   Timer Runs in Periodic Mode (default) 
		- BITM_TMR_CON_UP  Timer is Set to Count up 
		- BITM_TMR_CON_RLD Resets the Up/down Counter When GPTCLRI[0] is Set 
		- BITM_TMR_CON_ENABLE   EN. Timer is Enabled 
		- BITM_TMR_CON_EVENTEN  Events Will Be Captured 
   return 1 if write register successfully
**/

uint32_t GptCfg(ADI_TMR_TypeDef *pTMR, uint32_t iClkSrc, uint32_t iScale, uint32_t iMode)
{
  uint32_t	i1=0;
  if(pTMR->STA & BITM_TMR_STA_BUSY) return 0;
  //i1 = pTMR->CON & BITM_TMR_CON_EVENTS; // to keep the selected event
  i1 |= (iClkSrc<<BITP_TMR_CON_CLK);
  i1 |= (iScale<<BITP_TMR_CON_PRE);
  i1 |= iMode;
  pTMR->CON = (uint16_t)i1;
  return 1;	
}

/**
	@brief void GptLd(ADI_TMR_TypeDef *pTMR, uint32_t iTLd);
			==========Sets timer reload value.
	@param pTMR :{pADI_GPT0,pADI_GPT1,pADI_GPT2}
		- pADI_GPT0 for timer 0.
		- pADI_GPT1 for timer 1.
      - pADI_GPT2 for timer 2.
	@param iTLd :{0-65535}
		- Sets reload value TxLD to iTLd.
	@return 1.
**/

void GptLd(ADI_TMR_TypeDef *pTMR, uint32_t iTLd)
{      
  pTMR->LD= (uint16_t)iTLd;
}


/**
	@brief uint32_t GptVal(ADI_TMR_TypeDef *pTMR);
			==========Reads timer value.
	@param pTMR :{pADI_GPT0,pADI_GPT1,pADI_GPT2}
		- pADI_GPT0 for timer 0.
		- pADI_GPT1 for timer 1.
      - pADI_GPT2 for timer 2.
	@return timer value TxVAL.
**/

uint32_t GptVal(ADI_TMR_TypeDef *pTMR)
{
  return pTMR->VAL;
}

/**
	@brief uint32_t GptCapRd(ADI_TMR_TypeDef *pTMR);
			==========Reads capture value. Allows capture of a new value.
	@param pTMR :{pADI_GPT0,pADI_GPT1,pADI_GPT2}
		- pADI_GPT0 for timer 0.
		- pADI_GPT1 for timer 1.
      - pADI_GPT2 for timer 2.
	@return capture value TxCAP.
**/

//uint32_t GptCapRd(ADI_TMR_TypeDef *pTMR)
//{
//  return pTMR->CAP;
//}

/**
	@brief uint32_t GptCapSrc(ADI_TMR_TypeDef *pTMR, uint32_t iTCapSrc);
			==========Sets capture source.
	@param pTMR :{pADI_GPT0,pADI_GPT1,pADI_GPT2}
		- pADI_GPT0 for timer 0.
		- pADI_GPT1 for timer 1.
      - pADI_GPT2 for timer 2.
	@param iTCapSrc :{T0CON_EVENT_WUT, T0CON_EVENT_EXT0, T0CON_EVENT_EXT1, T0CON_EVENT_EXT2, 
        T0CON_EVENT_EXT3, T0CON_EVENT_EXT4, T0CON_EVENT_EXT5, T0CON_EVENT_EXT6,      
        T0CON_EVENT_EXT7,T0CON_EVENT_EXT8,T0CON_EVENT_T3, T0CON_EVENT_LV0, T0CON_EVENT_T1,
        T1CON_EVENT_EXT4, T1CON_EVENT_EXT5, T1CON_EVENT_EXT6, T1CON_EVENT_FLASH,
        T1CON_EVENT_UART, T1CON_EVENT_SPI0, T1CON_EVENT_PLA0, T1CON_EVENT_PLA1,
        T1CON_EVENT_DMAERR, T1CON_EVENT_DMADONE, T1CON_EVENT_I2C1S, T1CON_EVENT_I2C1M,T1CON_EVENT_T2,
        T2CON_EVENT_EXT7, T2CON_EVENT_EXT8, T2CON_EVENT_SPI1, T2CON_EVENT_I2C0S,
        T2CON_EVENT_I2C0M, T2CON_EVENT_PLA2, T2CON_EVENT_PLA3, T2CON_EVENT_PWMT,
        T2CON_EVENT_PWM0, T2CON_EVENT_PWM1, T2CON_EVENT_PWM2, T2CON_EVENT_PWM3,
        T2CON_EVENT_LV1, T2CON_EVENT_EXT0, T2CON_EVENT_EXT1, T2CON_EVENT_T1}
		- TxCON.8-11
                - for timer 0 capture event, select one of the following event:
							   T0CON_EVENT_WUT, T0CON_EVENT_EXT0, T0CON_EVENT_EXT1, T0CON_EVENT_EXT2, 
                               T0CON_EVENT_EXT3, T0CON_EVENT_EXT4, T0CON_EVENT_EXT5, T0CON_EVENT_EXT6,      
        T0CON_EVENT_EXT7,T0CON_EVENT_EXT8,T0CON_EVENT_T3, T0CON_EVENT_LV0, T0CON_EVENT_T1       
                - for timer 1  capture event, select one of the following event: 
							   T1CON_EVENT_EXT4, T1CON_EVENT_EXT5, T1CON_EVENT_EXT6, T1CON_EVENT_FLASH,
							   T1CON_EVENT_UART, T1CON_EVENT_SPI0, T1CON_EVENT_PLA0, T1CON_EVENT_PLA1,
        T1CON_EVENT_DMAERR, T1CON_EVENT_DMADONE, T1CON_EVENT_I2C1S, T1CON_EVENT_I2C1M,T1CON_EVENT_T2
      - for timer 2  capture event, select one of the following event: 
        T2CON_EVENT_EXT7, T2CON_EVENT_EXT8, T2CON_EVENT_SPI1, T2CON_EVENT_I2C0S,
        T2CON_EVENT_I2C0M, T2CON_EVENT_PLA2, T2CON_EVENT_PLA3, T2CON_EVENT_PWMT,
        T2CON_EVENT_PWM0, T2CON_EVENT_PWM1, T2CON_EVENT_PWM2, T2CON_EVENT_PWM3,
        T2CON_EVENT_LV1, T2CON_EVENT_EXT0, T2CON_EVENT_EXT1, T2CON_EVENT_T1
						   
	@return 1.
**/

//uint32_t GptCapSrc(ADI_TMR_TypeDef *pTMR, uint32_t iTCapSrc)
//{
//  uint32_t	i1;
//  if(pTMR->STA & BITM_TMR_STA_BUSY) return 0;
//  i1 = pTMR->CON & (~BITM_TMR_CON_EVENTS);
//  i1 |= iTCapSrc;
//  pTMR->CON = i1;
//  return 1;
//}

	
/**
	@brief uint32_t GptSta(ADI_TMR_TypeDef *pTMR);
			==========Reads timer status register.
	@param pTMR :{pADI_GPT0,pADI_GPT1,pADI_GPT2}
		- pADI_GPT0 for timer 0.
		- pADI_GPT1 for timer 1.
      - pADI_GPT2 for timer 2.
	@return TxSTA.
**/

uint32_t GptSta(ADI_TMR_TypeDef *pTMR)
{
  return pTMR->STA;
}


/**
	@brief void GptClrInt(ADI_TMR_TypeDef *pTMR, uint32_t iSource);
			==========clears current Timer interrupt by writing to TxCLRI.
	@param pTMR :{pADI_GPT0,pADI_GPT1,pADI_GPT2}
		- pADI_GPT0 for timer 0.
		- pADI_GPT1 for timer 1.
      - pADI_GPT2 for timer 2.
	@param iSource :{BITM_TMR_CLRI_TMOUT,BITM_TMR_CLRI_CAP}
		- BITM_TMR_CLRI_TMOUT for time out.
		- BITM_TMR_CLRI_CAP for capture event.
	@return none.
**/

void GptClrInt(ADI_TMR_TypeDef *pTMR, uint32_t iSource)
{
  pTMR->CLRI = (uint16_t)iSource;
}
               
/**
	@brief uint32_t GptBsy(ADI_TMR_TypeDef *pTMR);
			==========Checks the busy bit.
	@param pTMR :{pADI_GPT0,pADI_GPT1,pADI_GPT2}
		- pADI_GPT0 for timer 0.
		- pADI_GPT1 for timer 1.
      - pADI_GPT2 for timer 2.
   @return busy bit: 0 is not busy, 1 is busy.
**/
uint32_t GptBsy(ADI_TMR_TypeDef *pTMR)
{
  if(pTMR->STA & BITM_TMR_STA_BUSY)
  {
     return 1;
  } 
  else 
  {
     return 0;
  }
}

/*
@brief void GptSetup(ADI_TMR_TypeDef *pTMR, GPT_SETUP_t * pSetup)
      ===========setup for 16 bit general purpose timer
 
@param pTMR :{pADI_GPT0,pADI_GPT1,pADI_GPT2}
		- pADI_GPT0 for timer 0.
		- pADI_GPT1 for timer 1.
      - pADI_GPT2 for timer 2.
@param pSetup: pointer to timer setup structure
@return none
**/
void GptSetup(ADI_TMR_TypeDef *pTMR, GPT_SETUP_t * pSetup)
{
   uint32_t regCon;

   regCon = (pSetup->prescaler<<BITP_TMR_CON_PRE)| \
            (pSetup->countUp<<BITP_TMR_CON_UP)| \
            (pSetup->periodicMode<<BITP_TMR_CON_MOD)| \
            (pSetup->clockSource<<BITP_TMR_CON_CLK)|  \
            (pSetup->reload<<BITP_TMR_CON_RLD);
   pTMR->CON = (uint16_t)regCon;
   pTMR->LD = (uint16_t)(pSetup->loadValue);
}


//=====================================
//   32BIT GPT FUNCTION
//=====================================
/*
@brief void Gpt32Setup(ADI_TMER_TypeDef *pTMR, GPTH_SETUP_t * pSetup)
      ===========setup for 32 bit general purpose timer
 
@param pTMR :{pADI_GPTH0,pADI_GPTH1}
		- pADI_GPTH0 for 32 bit timer 0.
		- pADI_GPTH1 for 32 bit timer 1.
@param pSetup: pointer to timer setup structure
@return none
**/
void Gpt32Setup(ADI_TIMER_TypeDef *pTMR, GPTH_SETUP_t * pSetup)
{
   uint32_t regCon,regCfg0,regCfg1,regCfg2,regCfg3;

   regCon = (pSetup->prescaler<<BITP_TIMER_CTL_PRE)|\
            (pSetup->clock_source<<BITP_TIMER_CTL_SEL);
   regCfg0 = (pSetup->mode0<<BITP_TIMER_CFG_N__MODE)|\
            (pSetup->event0<<BITP_TIMER_CFG_N__EVENT_SEL)|\
            (pSetup->ccEn0<<BITP_TIMER_CFG_N__CC_EN);		
   regCfg1 = (pSetup->mode1<<BITP_TIMER_CFG_N__MODE)|\
            (pSetup->event1<<BITP_TIMER_CFG_N__EVENT_SEL)|\
            (pSetup->ccEn1<<BITP_TIMER_CFG_N__CC_EN);			
   regCfg2 = (pSetup->mode2<<BITP_TIMER_CFG_N__MODE)|\
            (pSetup->event2<<BITP_TIMER_CFG_N__EVENT_SEL)|\
            (pSetup->ccEn2<<BITP_TIMER_CFG_N__CC_EN);		
   regCfg3 = (pSetup->mode3<<BITP_TIMER_CFG_N__MODE)|\
            (pSetup->event3<<BITP_TIMER_CFG_N__EVENT_SEL)|\
            (pSetup->ccEn3<<BITP_TIMER_CFG_N__CC_EN);	
   
   pTMR->CNT = pSetup->count;
   pTMR->CC0 = pSetup->cc0_value;
   pTMR->CC1 = pSetup->cc1_value;
   pTMR->CC2 = pSetup->cc2_value;
   pTMR->CC3 = pSetup->cc3_value;
   pTMR->CFG0 = regCfg0;
   pTMR->CFG1 = regCfg1;
   pTMR->CFG2 = regCfg2;
   pTMR->CFG3 = regCfg3;
   pTMR->CTL = regCon;
}

