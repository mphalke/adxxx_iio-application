/*!
 *****************************************************************************
 * @file:   WutLib.c
 * @brief:  header file of watch dog timer
 *-----------------------------------------------------------------------------
 *
Copyright (c) 2013-2018 Analog Devices, Inc. All Rights Reserved.

This software is proprietary to Analog Devices, Inc. and its licensors.
By using this software you agree to the terms of the associated
Analog Devices Software License Agreement.
 ******************************************************************************/

#include "WutLib.h"


/**
	@brief int32_t WutCfg(int32_t iMode, int32_t iWake, int32_t iPre, int32_t iClkSrc)
			
	@param iMode :{ENUM_WUT_T4CON_TMODE_PERIODIC,ENUM_WUT_T4CON_TMODE_FREERUN}
		- 0 or ENUM_WUT_T4CON_TMODE_PERIODIC for periodic mode
		- 0x40 or ENUM_WUT_T4CON_TMODE_FREERUN for free running mode
	@param iWake :{ENUM_WUT_T4CON_WUEN_DIS,ENUM_WUT_T4CON_WUEN_EN}
		- 0 or ENUM_WUT_T4CON_WUEN_DIS to use the wake up timer as general purpose timer
		- 0x100 or ENUM_WUT_T4CON_WUEN_EN to allow the wake up timer to wake up the part
	@param iPre :{ENUM_WUT_T4CON_PRE_PREDIV1,ENUM_WUT_T4CON_PRE_PREDIV16,ENUM_WUT_T4CON_PRE_PREDIV256,ENUM_WUT_T4CON_PRE_PREDIV32768}
		- 0 or ENUM_WUT_T4CON_PRE_PREDIV1
		- 1 or ENUM_WUT_T4CON_PRE_PREDIV16
      - 2 or ENUM_WUT_T4CON_PRE_PREDIV256
      - 3 or ENUM_WUT_T4CON_PRE_PREDIV32768
	@param iClkSrc :{ENUM_WUT_T4CON_CLK_PCLK,ENUM_WUT_T4CON_CLK_LFOSC,ENUM_WUT_T4CON_CLK_ECLKIN}
		- 0 for ENUM_WUT_T4CON_CLK_PCLK => Clocked by system clock.
		- 0x200 or ENUM_WUT_T4CON_CLK_LFOSC =>  Clocked by 32kHz internal oscillator.
		- 0x600 or ENUM_WUT_T4CON_CLK_ECLKIN =>  Clocked by external signal on GPIO.
	@return 0 if timer interface busy or 1 if successful.
	
**/

int32_t WutCfg(int32_t iMode, int32_t iWake, int32_t iPre, int32_t iClkSrc)
{
  int	i1 = 0;

  i1 |= iMode;
  i1 |= iWake;
  i1 |= iClkSrc;
  i1 |= iPre;
  pADI_WUT->T4CON = (uint16_t)i1;
  return 1;	
}


/**
	@brief int32_t WutInc(int32_t iInc);
			==========Sets timer increment value.
	@param iInc :{0-0xFFF}
      - Sets increment value TxLD to iInc.
      - if the timer is already running, this function stops WUA during update of increment register
	@return 1
**/
int32_t WutInc(int32_t iInc)
{
  if (pADI_WUT->T4CON & BITM_WUT_T4CON_ENABLE) 
    pADI_WUT->T4CON |= BITM_WUT_T4CON_STOP_WUFA;
  pADI_WUT->T4INC = (uint16_t)iInc;
  pADI_WUT->T4CON &= ~BITM_WUT_T4CON_STOP_WUFA;
  return 1;
}


/**
	@brief int32_t WutLdWr(int32_t iField, uint32_t lTld);
         ==========Sets timer reload value.
	@param iField :{0, 1, 2, 3}
      - 0 for field A
      - 1 for field B
      - 2 for field C
      - 3 for field D. In periodic mode field D is the timeout.
	@param lTld :{0-0xFFFFFFFF}
		- Sets reload value TxLD to lTLd. 
	@return 0 if invalid field or 1 if field is valid
   @note If the timer is already running the corresponding interrupt should be diabled.
**/
int32_t WutLdWr(int32_t iField, uint32_t lTld)
{      
  switch (iField)
  {
  case 0:
    {
      if (pADI_WUT->T4CON & BITM_WUT_T4CON_ENABLE) 
        pADI_WUT->T4CON |= BITM_WUT_T4CON_STOP_WUFA;
      pADI_WUT->T4WUFA0= (uint16_t)(lTld&0x0000FFFF);
      pADI_WUT->T4WUFA1= (uint16_t)(lTld>>16);
      pADI_WUT->T4CON &= ~BITM_WUT_T4CON_STOP_WUFA;
      break;
    }
  
  case 1:
    {
      pADI_WUT->T4WUFB0= (uint16_t)(lTld&0x0000FFFF);
      pADI_WUT->T4WUFB1= (uint16_t)(lTld>>16);
      break;
    }
  case 2:
    {
      pADI_WUT->T4WUFC0= (uint16_t)(lTld&0x0000FFFF);
      pADI_WUT->T4WUFC1= (uint16_t)(lTld>>16);
      break;
    }
  case 3:
    {
      pADI_WUT->T4WUFD0= (uint16_t)(lTld&0x0000FFFF);
      pADI_WUT->T4WUFD1= (uint16_t)(lTld>>16);
      break;
    }  
  default:
    return 0;
 }
 return 1;	
}

/**
	@brief uint32_t WutLdRr(int32_t iField);
			==========Sets timer reload value.
	@param iField :{0, 1, 2, 3}
		- 0 for field A
		- 1 for field B
		- 2 for field C
      - 3 for field D. 
	@return TxLD corresponding to iField or 0 if iField is not valid
**/

uint32_t WutLdRd(int32_t iField)
{
  uint32_t uL;
  switch (iField)
  {
  case 0:
    {
      uL = pADI_WUT->T4WUFA1;
      uL = uL<<16;
      uL |= pADI_WUT->T4WUFA0;
      break;
    }  
  case 1:
    {
      uL = pADI_WUT->T4WUFB1;
      uL = uL<<16;
      uL |= pADI_WUT->T4WUFB0;
      break;
    }
  case 2:
    {
      uL = pADI_WUT->T4WUFC1;
      uL = uL<<16;
      uL |= pADI_WUT->T4WUFC0;
      break;
    }
  case 3:
    {
      uL = pADI_WUT->T4WUFD1;
      uL = uL<<16;
      uL |= pADI_WUT->T4WUFD0;
      break;
    }  
  default:
    {
      uL = 0;
      break;
    }
  }  
  return uL;
}

/**
	@brief int32_t WutVal(void);
			==========Reads timer value.

	@return 0 if freeze has not worked...
                 or timer value T4VAL.
**/

int32_t WutVal(void)
{
  int32_t lVal;
  if (!(pADI_WUT->T4CON & BITM_WUT_T4CON_FREEZE) )
        pADI_WUT->T4CON |= BITM_WUT_T4CON_FREEZE;
  lVal = pADI_WUT->T4VAL0;
  if (!(pADI_WUT->T4CON & BITM_WUT_T4CON_FREEZE) ) return 0;  // T4VAL is not frozen
  lVal |= (pADI_WUT->T4VAL1<<16);
  return (lVal);
}


	
/**
	@brief int32_t WutSta(void);
			==========Returns Timer Status.
	@return T4STA.
**/

int32_t WutSta(void)
{
  return (pADI_WUT->T4STA);
}



/**
	@brief int32_t WutClrInt(int32_t iSource);
			==========Clear timer interrupts.
	@param iSource :{BITM_WUT_T4CLRI_WUFA,BITM_WUT_T4CLRI_WUFB,BITM_WUT_T4CLRI_WUFC,BITM_WUT_T4CLRI_WUFD,BITM_WUT_T4CLRI_ROLL}
		- 0x1 or BITM_WUT_T4CLRI_WUFA for wake up field A interrupt
		- 0x2 or BITM_WUT_T4CLRI_WUFB for wake up field B interrupt
      - 0x4 or BITM_WUT_T4CLRI_WUFC for wake up field C interrupt
      - 0x8 or BITM_WUT_T4CLRI_WUFD for wake up field D interrupt
      - 0x10 or BITM_WUT_T4CLRI_ROLL for timer overflow interrupt
	@return 1.
**/
int32_t WutClrInt(int32_t iSource)
{
  (pADI_WUT->T4CLRI) = (uint16_t)iSource;
  return 1;
}


/**
   @brief int32_t WutCfgInt(int32_t iSource, iEnable);
			==========Clear timer interrupts.
   @param iSource :{BITM_WUT_T4IEN_WUFA| BITM_WUT_T4IEN_WUFB| BITM_WUT_T4IEN_WUFC| BITM_WUT_T4IEN_WUFD| BITM_WUT_T4IEN_ROLL}
      - 0x1 or BITM_WUT_T4IEN_WUFA for wake up field A interrupt
      - 0x2 or BITM_WUT_T4IEN_WUFB for wake up field B interrupt
      - 0x4 or BITM_WUT_T4IEN_WUFC for wake up field C interrupt
      - 0x8 or BITM_WUT_T4IEN_WUFD for wake up field D interrupt
      - 0x10 or BITM_WUT_T4IEN_ROLL for timer overflow interrupt
   @param iEnable :{0,1}
      - 0 disable interrupt
      - 1 enable interrupt
   @return 1.
**/
int32_t WutCfgInt(int32_t iSource, int32_t iEnable)
{
	int32_t iInterrupt = 0;

	if (iEnable == 1)				   // Enabling interrupts	
	{
		iInterrupt = (iSource & 0x1F);
		pADI_WUT->T4IEN |= iInterrupt;
	}
	else
	{
		iInterrupt = pADI_WUT->T4IEN;
		iInterrupt = (iSource ^ iInterrupt);
		pADI_WUT->T4IEN = (iInterrupt & 0x1F);		
	}
  	return 1;
}

/*
@brief void WakeUpSetup(WUT_SETUP_t const *setup)
      =========== setup for wake up timer
 
@param setup: pointer to WUT_SETUP_t structrue variable
 
@return none
**/
void WakeUpSetup(WUT_SETUP_t const *setup)
{
  (void)setup;
}


/**@}*/
