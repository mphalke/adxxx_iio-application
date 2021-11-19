/*!
 *****************************************************************************
 * @file:   CmpLib.c
 * @brief:  source file of Analog Comparator
 *-----------------------------------------------------------------------------
 *
Copyright (c) 2013-2018 Analog Devices, Inc. All Rights Reserved.

This software is proprietary to Analog Devices, Inc. and its licensors.
By using this software you agree to the terms of the associated
Analog Devices Software License Agreement.
 ******************************************************************************/

#include "CmpLib.h"

/**
   @brief uint32_t CmpHysCfg(uint32_t CmpNum,uint32_t iHysType, uint32_t iHysVoltage)	
      ==========Sets hysteresis type and hysteresis.
   @param CmpNum :0~3
      The number of each comparator part
   @param iHysVoltage :{0~0x1F}
      -0x00 : hysteresis disabled 
      -0x01 : 10mv hysteresis enabled 
      -0x02 : 25mv hysteresis 
      -0x03 : 35mv hysteresis 
      -0x06 : 50mv hysteresis 
      -0x07 : 60mv hysteresis 
      -0x0C : 75mv hysteresis 
      -0x0D : 85mv hysteresis 
      -0x0E : 100mv hysteresis 
      -0x11 : 110mv hysteresis 
      -0x12 : 125mv hysteresis 
      -0x13 : 135mv hysteresis 
      -0x16 : 150mv hysteresis 
      -0x17 : 160mv hysteresis 
      -0x1C : 175mv hysteresis 
      -0x1D : 185mv hysteresis 
      -0x1E : 200mv hysteresis 
      -0x1F : 210mv hysteresis 
   @return 1.
**/

uint32_t CmpHysCfg(uint32_t CmpNum, uint32_t iHysVoltage)
{
   uint32_t i1;
   volatile uint32_t *p = (volatile uint32_t *)(&pADI_COMP->COMPCON0);

   i1 = *(p + CmpNum);
   
   i1 &= ~(BITM_COMP_COMPCON_N__HYS);
   i1 |= iHysVoltage & BITM_COMP_COMPCON_N__HYS;
   
   *(p + CmpNum) = i1;

   return 1;
}

/**
   @brief uint32_t CmpEnable(uint32_t CmpNum, uint32_t iEn)
         ==========Powers up and enables comparator
   @param CmpNum :0~3
       The number of each comparator part
   @param iEn :{AFECOMP_EN_DIS, AFECOMP_EN_EN}
      -0 or AFECOMP_EN_DIS to power off comparator.
      -not 0 or AFECOMP_EN_EN to power up and enable comparator.
   @return 1.
**/

uint32_t CmpEnable(uint32_t CmpNum, uint32_t iEn)
{
   uint32_t i1;
   volatile uint32_t *p = (volatile uint32_t *)(&pADI_COMP->COMPCON0);
   
   i1 = *(p + CmpNum);
   i1 &= ~BITM_COMP_COMPCON_N__EN;
   i1 |= (iEn << BITP_COMP_COMPCON_N__EN);

   *(p + CmpNum) = i1;
   return 1;
}

/**
   @brief uint32_t CmpOutputCfg(uint32_t CmpNum, uint32_t iInvert, uint32_t iOut)
         ==========chooses direction and set output.
   @param CmpNum :0~3
       The number of each comparator part
   @param iInvert :{AFECOMP_INV_NO, AFECOMP_INV_YES}
      -0 or AFECOMP_INV_NO for output high if +ve input above -ve input.
      -not 0 or AFECOMP_INV_YES for output high if +ve input below -ve input.
   @param iOut :{0~0x03}
      -0x02 for output to Test Pad Enable.
      -not 0x02 or {0,1,3}: Output to Test Pad Disable
   @return 1.
**/
uint32_t CmpOutputCfg(uint32_t CmpNum, uint32_t iInvert, uint32_t iOut)
{
   uint32_t i1;
   volatile uint32_t *p = (volatile uint32_t *)(&pADI_COMP->COMPCON0);
   
   i1 = *(p + CmpNum);
   i1 &= ~(BITM_COMP_COMPCON_N__INV | BITM_COMP_COMPCON_N__OUT);
   i1 |= ((iInvert << BITP_COMP_COMPCON_N__INNEG) | (iOut << BITP_COMP_COMPCON_N__OUT));

   *(p + CmpNum) = i1;
   return 1;
}

/**
   @brief uint32_t CmpInputCfg(uint32_t CmpNum, uint32_t iInPos, uint32_t iInNeg)
      ==========Sets Comparator Positive input and Negtive input.
   @param CmpNum :0~3
      The number of each comparator part
   @param iInPos
      -Select Comparator Positive Input Source
       -0x00 : All Input Switches Off
       -0x01 : Enable AIN8/10/12/14 for comp 0/1/2/3 
       -0x02 : Enable PGA0/1/2/3 for comp 0/1/2/3
       -0x03 : Enable GPIO0.6/0.7/2.0/2.1 Analog Signal Input for comp 0/1/2/3
   @param iInNeg
      -Select Comparator Positive Input Source
       -0x00 : All Input Switches Off 
       -0x01 : Enable Half Avdd Input 
       -0x02 : Enable AIN9/11/13/15 for Comp 0/1/2/3 
       -0x03 : Enable VDAC8 Input 
       -0x04 : Enable VDAC9 Input 
       -0x05 : Enable VDAC10 Input 
       -0x06 : Enable VDAC11 Input 
       -0x07 : Enable 1.25V Ref Input from AIN15(BUF1) 
   @return 1.
**/
uint32_t CmpInputCfg(uint32_t CmpNum, uint32_t iInPos, uint32_t iInNeg)
{
   uint32_t i1;
   volatile uint32_t *p = (volatile uint32_t *)(&pADI_COMP->COMPCON0);
   
   i1 = *(p + CmpNum);
   i1 &= ~(BITM_COMP_COMPCON_N__INPOS | BITM_COMP_COMPCON_N__INNEG);
   i1 |= ((iInPos << BITP_COMP_COMPCON_N__INPOS) | (iInNeg << BITP_COMP_COMPCON_N__INNEG));
   
   *(p + CmpNum) = i1;
   return 1;
}

/**
   @brief uint32_t CmpIntCfg(uint32_t CmpNum, uint32_t iEn, uint32_t iMode)
         ==========Setup the Comparator interrupt .
   @param CmpNum :0~3
       The number of each comparator part
   @param iEn :
      -0x00 for interrupt disable.
      -0x01 for interrupt enable.
   @param iMode :
      -0x00: Generate Interrupt if Rising Edge Happens.
      -0x01: Generate Interrupt if Falling Edge Happens.
      -0x02: Generate Interrupt if Low Level Happens.
      -0x03: Generate Interrupt if High Level Happens.
   @return 1.
**/
uint32_t CmpIntCfg(uint32_t CmpNum, uint32_t iEn, uint32_t iMode)
{
   uint32_t i1;
   volatile uint32_t *p = (volatile uint32_t *)(&pADI_COMP->COMPCON0);
   
   i1 = *(p + CmpNum);
   i1 &= ~(BITM_COMP_COMPCON_N__INTEN | BITM_COMP_COMPCON_N__INTMODE);
   i1 |= ((iEn << BITP_COMP_COMPCON_N__INTEN) | (iMode << BITP_COMP_COMPCON_N__INTMODE));
   
   *(p + CmpNum) = i1;
   return 1;

}

/*
   @brief void CmpSetup(const CMP_SETUP_t *pSetup)
      =========== write value of Comparator setup structure to device
   @param pSetup: pointer to Comparator setup structure
**/
void CmpSetup(const CMP_SETUP_t *pSetup)
{
   uint32_t i,i1;
   volatile uint32_t *p = (volatile uint32_t *)(&pADI_COMP->COMPCON0);
   for(i=0;i<4;i++)
   {
       i1 = ((pSetup->comp[i].cmp_int_mode << BITP_COMP_COMPCON_N__INTMODE) |\
               (pSetup->comp[i].cmp_int_en << BITP_COMP_COMPCON_N__INTEN) |\
               (pSetup->comp[i].cmp_en << BITP_COMP_COMPCON_N__EN) |\
               (pSetup->comp[i].cmp_input_pos << BITP_COMP_COMPCON_N__INPOS) |\
               (pSetup->comp[i].cmp_input_neg << BITP_COMP_COMPCON_N__INNEG) |\
               (pSetup->comp[i].cmp_out << BITP_COMP_COMPCON_N__OUT) |\
               (pSetup->comp[i].cmp_invert << BITP_COMP_COMPCON_N__INV) |\
                pSetup->comp[i].cmp_hys);

        *(p + i) = i1;
   }
}

