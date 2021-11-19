/*!
 *****************************************************************************
 * @file:   PwmLib.c
 * @brief:  library for PWM
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

#include "PwmLib.h"

/**
      @brief int PwmInit(unsigned int iPWMCP, unsigned int iPWMIEN, unsigned int iSYNC, unsigned int iTRIP)
			========== Configure the PWM peripheral clock, interrupt, synchronisation and trip.
      
      @param iPWMCP :{PWMUCLK_2,PWMUCLK_4,PWMUCLK_8,PWMUCLK_16,PWMUCLK_32,PWMUCLK_64,PWMUCLK_128,PWMUCLK_256}
		- PWMCON0.8-6. Divides PWMUCLK to the PWM peripheral
		- PWMUCLK_2 or 0 = PWMUCLK/2
		- PWMUCLK_4 or 0x40 = PWMUCLK/4
		- PWMUCLK_8 or 0x80 = PWMUCLK/8
		- PWMUCLK_16 or 0xC0 = PWMUCLK/16
		- PWMUCLK_32 or 0x100 = PWMUCLK/32
		- PWMUCLK_64 or 0x140 = PWMUCLK/64
		- PWMUCLK_128 or 0x180 = PWMUCLK/128
		- PWMUCLK_256 or 0x1C0 = PWMUCLK/256

      @param iPWMIEN :{PWMCON0_PWMIEN_DIS,PWMCON0_PWMIEN_EN}
		- PWMCON0.10
		- PWMCON0_PWMIEN_DIS or 0 for PWM Interupt disable
		- PWMCON0_PWMIEN_EN or 0x400 for PWM Interupt enable

      @param iSYNC :{0,PWMCON0_SYNC}
		- PWMCON0.15
		-  0 to disable PWM Synchronization
		- PWMCON0_SYNC_EN or 0x8000 to enable all PWM counters to reset on the next clock 
           edge after the detection of a falling edge on the SYNC pin.

      @param iTRIP :{0,PWMCON1_TRIP_EN}
		- PWMCON1.6
		-  0 to Disable PWM trip functionality
		- PWMCON1_TRIP_EN or 0x40 to enable PWM trip function

      @return 1 
      @note 
        This function disables HBridge mode and other configurations. 
        It should be called before any other PWM functions.
**/                                             
int PwmInit(unsigned int iPWMCP, unsigned int iPWMIEN, unsigned int iSYNC, unsigned int iTRIP)
{
  unsigned int i1;
  i1= iPWMCP;
  i1|= iPWMIEN;
  i1|= iSYNC;
  pADI_PWM->PWMCON0 = (uint16_t)i1;
  pADI_PWM->PWMCON1 = (uint16_t)iTRIP;

  return 1;
}


/**

      @brief int PwmTime(int iPair, unsigned int uiFreq, unsigned int uiPWMH_High, unsigned int uiPWML_High)
			========== Configure period and duty cycle of a pair.

      @param iPair :{PWM0_1, PWM2_3, PWM4_5, PWM6_7}
		   - PWM0_1 or 0 for PWM Pair0 (PWM0/PWM1 outputs)
		   - PWM2_3 or 1 for PWM Pair1 (PWM2/PWM3 outputs)
		   - PWM4_5 or 2 for PWM Pair2 (PWM4/PWM5 outputs)
         - PWM6_7 or 3 for PWM Pair3 (PWM6/PWM7 outputs)

      @param uiFreq :{0-0xFFFF}                    \n
	            The PWM Period is calculated as follows:  \n
	            tPWMUCLK x (PWMxLEN+1) * Nprescale    
                    where tPWMUCLK is 80MHz/CLKCON1[2:0], Nprescale is PWMCON0[8:6]

      @param uiPWMH_High :{0-0xFFFF}
	           - Pass values between 0-0xFFFF for duty cycle of high and low side	
                   - High Side High period must be greater or equal to Low side High period (iPWM0High>=iPWM1High)
		   - High Side high period must be less than uiFreq
		   - uiPWMH_High/uiFreq gives the duty cycle for ratio for PWMH high      \n
		     For example, uiFreq = 0x50 and uiPWMH_High = 0x30; then duty cycle is 60:40 for high:low on PWMH pin

      @param uiPWML_High :{0-0xFFFF}
		   - Pass values between 0-0xFFFF for duty cycle of high and low side	
                   - Low output High period must be less or equal to High side High period (iPWM0High>=iPWM1High)
		   - Low Side high period must be less than uiFreq
		   - uiPWML_High/uiFreq gives the duty cycle for ratio for PWML high    \n
		     For example, uiFreq = 0x50 and uiPWML_High = 0x10; then duty cycle is 20:80 for high:low on PWML pin

      @return 0	  Failure: uiPWMH_High < uiPWML_High
      @return 1	  Success
      @return 2	  Failure: uiPWML_High > pADI_PWM->PWM0COM1 - this will result in lower than expected duty cycle on PWML output
**/

int PwmTime(int iPair, unsigned int uiFreq, unsigned int uiPWMH_High,unsigned int uiPWML_High)
{
  if  (uiPWMH_High < uiPWML_High)
    return 0x0; // Error: PWM0 High period must be >= PWM1 High period; PWM2 High period must be >= PWM3 High period; PWM4 High period must be >= PWM5 High period
  
  switch (iPair)
  {
  case 0:
    pADI_PWM->PWM0LEN = (uint16_t)uiFreq;
	pADI_PWM->PWM0COM0 = pADI_PWM->PWM0LEN;
	pADI_PWM->PWM0COM1 = (uint16_t)uiPWMH_High;
	if ( uiPWML_High < pADI_PWM->PWM0COM1)
		pADI_PWM->PWM0COM2 = (uint16_t)uiPWML_High;
	else			   // PWML output is dictated by PWMH. PWML high period will be PWMLEN-PWMH_HIGH
		return 2;    
    break;
  case 1:
    pADI_PWM->PWM1LEN = (uint16_t)uiFreq;
	pADI_PWM->PWM1COM0 = pADI_PWM->PWM1LEN;
	pADI_PWM->PWM1COM1 = (uint16_t)uiPWMH_High;
	if ( uiPWML_High < pADI_PWM->PWM1COM1)
		pADI_PWM->PWM1COM2 = (uint16_t)uiPWML_High;
	else			   // PWML output is dictated by PWMH. PWML high period will be PWMLEN-PWMH_HIGH
		return 2;    
    break;
  case 2:
   pADI_PWM->PWM2LEN = (uint16_t)uiFreq;
	pADI_PWM->PWM2COM0 = pADI_PWM->PWM2LEN;
	pADI_PWM->PWM2COM1 = (uint16_t)uiPWMH_High;
	if ( uiPWML_High < pADI_PWM->PWM2COM1)
		pADI_PWM->PWM2COM2 = (uint16_t)uiPWML_High;
	else			   // PWML output is dictated by PWMH. PWML high period will be PWMLEN-PWMH_HIGH
		return 2;    
    break;
   case 3:
        pADI_PWM->PWM3LEN = (uint16_t)uiFreq;
	pADI_PWM->PWM3COM0 = pADI_PWM->PWM3LEN;
	pADI_PWM->PWM3COM1 = (uint16_t)uiPWMH_High;
	if ( uiPWML_High < pADI_PWM->PWM3COM1)
		pADI_PWM->PWM3COM2 = (uint16_t)uiPWML_High;
	else			   // PWML output is dictated by PWMH. PWML high period will be PWMLEN-PWMH_HIGH
		return 2;    
    break;

  default:
    break;
  }
  return 1;
}


/**
      @brief int PwmClrInt(unsigned int iSource)
			========== Clear PWMs interrupt flags.

      @param iSource :{PWMICLR_TRIP_EN|PWMICLR_PWM3_EN|PWMICLR_PWM2_EN|PWMICLR_PWM1_EN|PWMICLR_PWM0_EN}
		- PWMCLRI.0 - 4
		- NULL do nothing
		- PWMCLRI_x for : clear the latched IRQPWMx interrupt. 

      @return 1  
**/
int PwmClrInt(unsigned int iSource)
{
  pADI_PWM->PWMICLR |= iSource;
  return 1;
}
/**
      @brief int PwmLoad(int iLoad)
			========== Controls how PWM compare registers are loaded.

      @param iLoad :{PWMCON0_LCOMP_DIS,PWMCON0_LCOMP_EN}
		- PWMCON0_LCOMP_DIS or 0 to use previous compare register values
		- PWMCON0_LCOMP_EN or 0x8 to load compare registers on the next PWM timer transition (low to high edge)

      @return 1  
**/
int PwmLoad(int iLoad)
{
  int i1;
  
  i1= (pADI_PWM->PWMCON0 & 0xFFF7); // mask off bit 3
  i1 |= iLoad; 
  pADI_PWM->PWMCON0 = (uint16_t)i1; 
  return 1;
}

/**
      @brief int PwmGo(unsigned int iPWMEN, unsigned int iHMODE)
			========== Starts/Stops the PWM in standard or H-Bridge mode.

      @param iPWMEN :{PWMCON0_PWMEN_DIS,PWMCON0_PWMEN_EN}
		- PWMCON0_PWMEN_DIS or 0x0  to disable the PWM peripheral.
		- BITM_PWM_PWMCON0_PWMEN or 0x1 to enable/start the PWM peripheral.
      @param iHMODE :{PWMCON0_HMODE_DIS,PWMCON0_HMODE_EN}
		- PWMCON0_HMODE_DIS or 0 to operate in standard mode.
		- PWMCON0_HMODE_EN or 0x2 to operate in H-Bridge mode. 

      @return 1  

**/
int PwmGo(unsigned int iPWMEN, unsigned int iHMODE)
{
  if (iHMODE == 0)
    pADI_PWM->PWMCON0 &=0xFFFD;               			 // Standard mode
   else
     pADI_PWM->PWMCON0 |= BITM_PWM_PWMCON0_HMODE;   			 // H-Bridge mode

  if (iPWMEN == 0)
    pADI_PWM->PWMCON0 &=0xFFFE;			                // Disable PWM 
  else
    pADI_PWM->PWMCON0 |= BITM_PWM_PWMCON0_PWMEN;			    // Enable PWM 
  return 1;
}

/**
      @brief int PwmInvert(int iInv1,int iInv3,int iInv5,int iInv7)
			========== Selects PWM outputs for inversion.

      @param iInv1 :{PWMCON0_PWM1INV_DIS, PWMCON0_PWM1INV_EN}
		- PWMCON0_PWM1INV_DIS or 0 to Disable PWM1 output inversion.
		- PWMCON0_PWM1INV_EN or 0x800 to Enable PWM1 output inversion.
	  @param iInv3 :{PWMCON0_PWM3INV_DIS,PWMCON0_PWM3INV_EN}
		- PWMCON0_PWM3INV_DIS or 0 to Disable PWM3 output inversion.
		- PWMCON0_PWM3INV_EN or 0x1000 to Enable PWM3 output inversion.
	  @param iInv5 :{PWMCON0_PWM5INV_DIS,PWMCON0_PWM5INV_EN}
		- PWMCON0_PWM5INV_DIS or 0 to Disable PWM5 output inversion.
		- PWMCON0_PWM5INV_EN or 0x2000 to Enable PWM5 output inversion.
      @return 1  

**/
int PwmInvert(int iInv1,int iInv3,int iInv5,int iInv7)
{
  int i1;
  
  i1= (pADI_PWM->PWMCON0 & 0x87FF); // mask off bits  11, 12, 13
  i1 |= (iInv1 +iInv3+iInv5+iInv7); 
  pADI_PWM->PWMCON0 = (uint16_t)i1; 
  return 1;
}

/**
      @brief int PwmHBCfg(unsigned int iENA, unsigned int iPOINV, unsigned int iHOFF, unsigned int iDIR)
			========== HBridge mode - configure PWMs.

      @param iENA :{PWMCON0_ENA_DIS,PWMCON0_ENA_EN}
		- PWMCON0_ENA_DIS or 0 to use the values previously stored in the internal compare registers.
		- PWMCON0_ENA_EN or 0x200 enable HBridge outputs 

      @param iPOINV :{PWMCON0_POINV_DIS,PWMCON0_POINV_EN}
		- PWMCON0_POINV_DIS or 0 for PWM outputs as normal in H-Bridge mode
		- PWMCON0_POINV_EN for invert all PWM outputs in H-bridge mode

      @param iHOFF :{PWMCON0_HOFF_DIS,PWMCON0_HOFF_EN}
		- PWMCON0_HOFF_DIS 0 for PWM outputs as normal in H-Bridge mode
		- PWMCON0_HOFF_EN for Forces PWM0 and PWM2 outputs high and PWM1 and PWM3 low (default). 

      @param iDIR :{PWMCON0_DIR_DIS,PWMCON0_DIR_EN}
		- PWMCON0_DIR_DIS for Enable PWM2 and PWM3 as the output signals while PWM0 and PWM1 are held low.
		- PWMCON0_DIR_EN for Enables PWM0 and PWM1 as the output signals while PWM2 and PWM3 are held low.

      @return 1    
**/          
int PwmHBCfg(unsigned int iENA, unsigned int iPOINV, unsigned int iHOFF, unsigned int iDIR)
{
  unsigned int i1;

  i1= (pADI_PWM->PWMCON0 & 0xFDCB);	   // Mask bits 9,5,4,2
  i1|=iENA;
  i1|=iPOINV;
  i1|=iHOFF;
  i1|=iDIR;
  pADI_PWM->PWMCON0 = (uint16_t)i1; 
  return 1;
}

/**@}*/
