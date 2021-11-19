/*!
 *****************************************************************************
 * @file:   DacLib.c
 * @brief:  source file of Digital to Analog Voltage convertor
 *-----------------------------------------------------------------------------
 *
Copyright (c) 2013-2018 Analog Devices, Inc. All Rights Reserved.

This software is proprietary to Analog Devices, Inc. and its licensors.
By using this software you agree to the terms of the associated
Analog Devices Software License Agreement.
 ******************************************************************************/

#include "DacLib.h"

/**
	@brief uint32_t DacWr(ADI_DACx_TypeDef *pPort, int uiData)
			==========Writes the DAC value.
	@param pPort :{pADI_DAC0,pADI_DAC1,pADI_DAC2,pADI_DAC3,pADI_DAC4,pADI_DAC5,pADI_DAC6,pADI_DAC7}
      - pADI_DAC0 for DAC0.
      - pADI_DAC1 for DAC1.
      - pADI_DAC2 for DAC2.
      - pADI_DAC3 for DAC3.
      - pADI_DAC4 for DAC4.
      - pADI_DAC5 for DAC5.
      - pADI_DAC6 for DAC6.
      - pADI_DAC7 for DAC7.
      - pADI_DAC8 for DAC8.
      - pADI_DAC9 for DAC9.
      - pADI_DAC10 for DAC10.
      - pADI_DAC11 for DAC11.
	@param uiData : {0x00 ~ 0xFFF}
		- DAC DATAIN ---- DATAIN[27:16]
		- 12-bit digital data to output to DAC.
	@return DAC data.
**/
uint32_t DacWr(ADI_DACx_TypeDef *pPort, uint32_t uiData)
{
    uint32_t dacData = (uiData << (BITP_DAC_DACDAT_N__DATAIN+4));

    pPort->DACDAT = dacData;
    
    return  pPort->DACDAT;
}

/**
	@brief uint32_t DacCfg(ADI_DACx_TypeDef *pPort, uint32_t uiPD, uint32_t uiDrv, uint32_t uiFullScale)
			==========Sets the output range of a DAC.
	@param pPort :{pADI_DAC0,pADI_DAC1,pADI_DAC2,pADI_DAC3,pADI_DAC4,pADI_DAC5,pADI_DAC6,pADI_DAC7}
      - pADI_DAC0 for DAC0.
      - pADI_DAC1 for DAC1.
      - pADI_DAC2 for DAC2.
      - pADI_DAC3 for DAC3.
      - pADI_DAC4 for DAC4.
      - pADI_DAC5 for DAC5.
      - pADI_DAC6 for DAC6.
      - pADI_DAC7 for DAC7.
      - pADI_DAC8 for DAC8.
      - pADI_DAC9 for DAC9.
      - pADI_DAC10 for DAC10.
      - pADI_DAC11 for DAC11.
	@param uiPD :
		- DACCON.8
		- ENUM_DAC_DACCON_N__PD_DACON
		- ENUM_DAC_DACCON_N__PD_DACOFF
	@param uiDrv :
        - DACCON.9
        - ENUM_DAC_DACCON_N__DRV_NORMAL for dive normal.
        - ENUM_DAC_DACCON_N__DRV_DRIVEBOOST for drive boost mode
	@param uiFullScale :
	    - DACCON.5
	    - ENUM_DAC_DACCON_N__FSLVL_OUT2P5
	    - ENUM_DAC_DACCON_N__FSLVL_OUT3V3
	@return new DACCON.
**/	
uint32_t DacCfg(ADI_DACx_TypeDef *pPort, uint32_t uiPD, uint32_t uiDrv, uint32_t uiFullScale)
{
    pPort->DACCON = (uiPD << BITP_DAC_DACCON_N__PD) \
                  + (uiDrv << BITP_DAC_DACCON_N__DRV) \
                  + (uiFullScale << BITP_DAC_DACCON_N__FSLVL) \
                  + (ENUM_DAC_DACCON_N__EN_CLEAROFF << BITP_DAC_DACCON_N__EN);
    
    return  pPort->DACCON; 
}

/**
	@brief uint32_t DacInputDataClear(ADI_DACx_TypeDef *pPort, uint32_t uiDatClr)
			==========
	@param pPort :{pADI_DAC0,pADI_DAC1,pADI_DAC2,pADI_DAC3,pADI_DAC4,pADI_DAC5,pADI_DAC6,pADI_DAC7}
      - pADI_DAC0 for DAC0.
      - pADI_DAC1 for DAC1.
      - pADI_DAC2 for DAC2.
      - pADI_DAC3 for DAC3.
      - pADI_DAC4 for DAC4.
      - pADI_DAC5 for DAC5.
      - pADI_DAC6 for DAC6.
      - pADI_DAC7 for DAC7.
      - pADI_DAC8 for DAC8.
      - pADI_DAC9 for DAC9.
      - pADI_DAC10 for DAC10.
      - pADI_DAC11 for DAC11.
	@param uiDatClr :
      - ENUM_DAC_DACCON_N__EN_CLEAR
      - ENUM_DAC_DACCON_N__EN_CLEAROFF
	@return new DACCON.
**/

uint32_t DacInputDataClear(ADI_DACx_TypeDef *pPort, uint32_t uiDatClr)
{
    uint32_t dacCon = pPort->DACCON & (~BITM_DAC_DACCON_N__EN);

    dacCon |= (uiDatClr << BITP_DAC_DACCON_N__EN);

    return (pPort->DACCON = dacCon); 
}

 /**
	@brief uint32_t DacPwrDwn(ADI_DACx_TypeDef *pPort, int uiPdCfg)
           DAC Top Power Down. If PDDAC=1, Daccore/ref_buf/dac_buf will all be power down.
	@param pPort :{pADI_DAC0,pADI_DAC1,pADI_DAC2,pADI_DAC3,pADI_DAC4,pADI_DAC5,pADI_DAC6,pADI_DAC7}
      - pADI_DAC0 for DAC0.
      - pADI_DAC1 for DAC1.
      - pADI_DAC2 for DAC2.
      - pADI_DAC3 for DAC3.
      - pADI_DAC4 for DAC4.
      - pADI_DAC5 for DAC5.
      - pADI_DAC6 for DAC6.
      - pADI_DAC7 for DAC7.
      - pADI_DAC8 for DAC8.
      - pADI_DAC9 for DAC9.
      - pADI_DAC10 for DAC10.
      - pADI_DAC11 for DAC11.
	@param uiPdCfg :
		- ENUM_DAC_DACCON_N__PD_DACON to Enable DAT Top
		- ENUM_DAC_DACCON_N__PD_DACOFF to Power down DAC Top
	@return new DACCON.
**/  
   
uint32_t DacPwrDwn(ADI_DACx_TypeDef *pPort, uint32_t uiPdCfg)
{
    uint32_t dacCon = pPort->DACCON; 

    dacCon &= (~BITM_DAC_DACCON_N__PD);
    dacCon |= uiPdCfg << BITP_DAC_DACCON_N__PD;  
    pPort->DACCON = dacCon;
    
    return  pPort->DACCON; 
}


/**
@brief void DACSetup(const DAC_SETUP_t *pSetup)
      =========== setup for DAC
@param pSetup: pointer to DAC_SETUP_t setup structure
@return none
**/
#define ADuCM410_VDAC_CHAN_NUM 12
void DACSetup(DAC_SETUP_t *pSetup)
{
    uint32_t uiDACConf; 
    volatile uint32_t *addr;
    DAC_CHAN_SETUP_t *pChanSetup = pSetup->dacChan;
    
    addr = (volatile uint32_t  *)(&(pADI_VDAC->DACCON0));
    
    for(uint32_t i=0; i<12; i++)
    {
       uiDACConf = (pChanSetup->driveAblityEn << BITP_DAC_DACCON_N__DRV) \
                        | (pChanSetup->powerDown << BITP_DAC_DACCON_N__PD) \
                        | (pChanSetup->fullScale << BITP_DAC_DACCON_N__FSLVL) \
                        | (pChanSetup->dataClear << BITP_DAC_DACCON_N__EN);
       *addr = uiDACConf;
       *(addr+ADuCM410_VDAC_CHAN_NUM) = pChanSetup->data;
       
       addr++;
       pChanSetup++;
    }
}

/**@}*/
