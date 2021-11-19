/*!
 *****************************************************************************
 * @file:   ClkLib.c
 * @brief:  source file of clock
 *-----------------------------------------------------------------------------
 *
Copyright (c) 2013-2018 Analog Devices, Inc. All Rights Reserved.

This software is proprietary to Analog Devices, Inc. and its licensors.
By using this software you agree to the terms of the associated
Analog Devices Software License Agreement.
 ******************************************************************************/

#include "ClkLib.h"

//#define FIRST_SILICON_WORKAROUND

/*
@brief uint32_t ClkMuxCfg(uint32_t clockSource)
      =========== select root clock source
@param clockSource:
    -ENUM_CLOCK_CLKCON0_CLKMUX_HFOSC        �� High Frequency Internal Oscillator (HFOSC) 
   -ENUM_CLOCK_CLKCON0_CLKMUX_SPLL         ��System PLL is Selected (160 MHz) 
   -ENUM_CLOCK_CLKCON0_CLKMUX_EXTCLK       ��External GPIO Port is Selected (ECLKIN) 
@return 1
**/
uint32_t ClkMuxCfg(uint32_t clockSource)
{
   uint32_t reg;
   uint32_t status;
   
   if (clockSource==ENUM_CLOCK_CLKCON0_CLKMUX_SPLL)
   {
      do
      {
         status = pADI_CLK->CLKSTAT0;
      }
      while(!(status&BITM_CLOCK_CLKSTAT0_SPLLSTATUS));   //check PLL ready
   }
   reg = pADI_CLK->CLKCON0;
   reg &= ~BITM_CLOCK_CLKCON0_CLKMUX;
   reg |= (clockSource<<BITP_CLOCK_CLKCON0_CLKMUX);
   pADI_CLK->CLKCON0 = (uint16_t)reg;
   
   return 1;
}


/*
@brief uint32_t GPIOClkOutCfg(uint32_t clockSource)
    =========== select GPIO clock source
@param clockSource:
   -ENUM_CLOCK_CLKCON0_CLKOUT_SPLL_CLK     ��SPLL clock 
   -ENUM_CLOCK_CLKCON0_CLKOUT_HCLKBUS      �� Hclk_bus 
   -ENUM_CLOCK_CLKCON0_CLKOUT_T3           �� Timer 3 Clock 
   -ENUM_CLOCK_CLKCON0_CLKOUT_WUT          �� Wake up Timer Clock 
   -ENUM_CLOCK_CLKCON0_CLKOUT_T0           ��Timer 0 Clock 
   -ENUM_CLOCK_CLKCON0_CLKOUT_ANA_CLK      �� Analog Test Signal 
   -ENUM_CLOCK_CLKCON0_CLKOUT_B1_PCLK      �� Bridge 2 PCLK 
   -ENUM_CLOCK_CLKCON0_CLKOUT_B2_PCLK      �� Bridge 2 PCLK 
   -ENUM_CLOCK_CLKCON0_CLKOUT_B0_PCLK      ��Bridge 1 Pclk 
   -ENUM_CLOCK_CLKCON0_CLKOUT_CORE         ��Core Clock 
   -ENUM_CLOCK_CLKCON0_CLKOUT_LFOSC        �� 32K OSC 
   -ENUM_CLOCK_CLKCON0_CLKOUT_HXTAL        ��Crystal clok 
   -ENUM_CLOCK_CLKCON0_CLKOUT_ROOT         �� Root Clock 
   -ENUM_CLOCK_CLKCON0_CLKOUT_HFOSC        �� HFOSC (16 MHz) 
@return 1
**/


uint32_t GPIOClkOutCfg(uint32_t clockSource)
{
   uint32_t reg;

   reg = pADI_CLK->CLKCON0;
   reg &= ~BITM_CLOCK_CLKCON0_CLKOUT;
   reg |= (clockSource<<BITP_CLOCK_CLKCON0_CLKOUT);
   pADI_CLK->CLKCON0 = (uint16_t)reg;
   return 1;
}
/*

@brief uint32_t ANAClkMuxCfg(uint32_t clockSource)
      =========== select Analog Clock Source
@param clockSource:
   -ENUM_CLOCK_CLKCON0_ANACLKMUX_HFOSC     ��Internal Oscillator is Selected (HFOSC) 
   -ENUM_CLOCK_CLKCON0_ANACLKMUX_GPIOCLK   ��GPIO Clock 
   -ENUM_CLOCK_CLKCON0_ANACLKMUX_HFXTAL    ��External Oscillator is Selected (HFXTAL) 
@return 1
**/

uint32_t ANAClkMuxCfg(uint32_t clockSource)
{
   uint32_t reg;

   reg = pADI_CLK->CLKCON0;
   reg &= ~BITM_CLOCK_CLKCON0_ANACLKMUX;
   reg |= (clockSource<<BITP_CLOCK_CLKCON0_ANACLKMUX);
   pADI_CLK->CLKCON0 = (uint16_t)reg;
   return 1;
}

/*
@brief uint32_t SPLLIECfg(uint32_t pllIntEnable)
      =========== PLL Interrupt Enable
@param pllIntEnable:

   -ENUM_CLOCK_CLKCON0_SPLLIE_DIS          ��PLL Interrupt Will Not Be Generated 
   -ENUM_CLOCK_CLKCON0_SPLLIE_EN           ��PLL Interrupt Will Be Generated 
@return 1 
*/
uint32_t SPLLIECfg(uint32_t pllIntEnable)
{
   uint32_t reg;

   reg = pADI_CLK->CLKCON0;
   reg &= ~BITM_CLOCK_CLKCON0_SPLLIE;
   reg |= (pllIntEnable<<BITP_CLOCK_CLKCON0_SPLLIE);
   pADI_CLK->CLKCON0 = (uint16_t)reg;
   return 1;
}

  

/*
@brief uint32_t ClkDivCfg(uint32_t hclkDiv,uint32_t pclk0Div, uint32_t pclk1Div)
      =========== set divider for different clock
@param hclkDiv:
   - ENUM_CLOCK_CLKCON1_CDHCLK_DIV1  , DIV1. Divide by 1 (HCLK is Equal to Root Clock) 
   - ENUM_CLOCK_CLKCON1_CDHCLK_DIV2  , DIV2. Divide by 2 (HCLK is Half the Frequency of Root Clock) 
   - ENUM_CLOCK_CLKCON1_CDHCLK_DIV4  , DIV4. Divide by 4 (HCLK is Quarter the Frequency of Root Clock) 
   - ENUM_CLOCK_CLKCON1_CDHCLK_DIV8  , DIV8. Divide by 8 
   - ENUM_CLOCK_CLKCON1_CDHCLK_DIV16 , DIV16.Divide by 16 
   - ENUM_CLOCK_CLKCON1_CDHCLK_DIV32 , DIV32.Divide by 32 
   - ENUM_CLOCK_CLKCON1_CDHCLK_DIV64 , DIV64.Divide by 64 
   - ENUM_CLOCK_CLKCON1_CDHCLK_DIV128, DIV128. Divide by 128 
@param pclk0Div:
   - ENUM_CLOCK_CLKCON1_CDPCLK0_DIV1  ,Divide by 1 (PCLK is Equal to Root Clock) 
   - ENUM_CLOCK_CLKCON1_CDPCLK0_DIV2  ,Divide by 2 (PCLK is Half the Frequency of Root Clock) 
   - ENUM_CLOCK_CLKCON1_CDPCLK0_DIV4  ,Divide by 4 (PCLK is Quarter the Frequency of Root Clock , 20 MHz)
   - ENUM_CLOCK_CLKCON1_CDPCLK0_DIV8  ,Divide by 8 
   - ENUM_CLOCK_CLKCON1_CDPCLK0_DIV16 , Divide by 16 
   - ENUM_CLOCK_CLKCON1_CDPCLK0_DIV32 , Divide by 32 
   - ENUM_CLOCK_CLKCON1_CDPCLK0_DIV64 , Divide by 164
@param pclk1Div:
   - ENUM_CLOCK_CLKCON1_CDPCLK1_DIV1    DIV1. Divide by 1 (PCLK is Equal to Root Clock) 
   - ENUM_CLOCK_CLKCON1_CDPCLK1_DIV2    DIV2. Divide by 2 (PCLK is Half the Frequency of Root Clock) 
   - ENUM_CLOCK_CLKCON1_CDPCLK1_DIV4    DIV4. Divide by 4 (PCLK is Quarter the Frequency of Root Clock, 20 MHz) 
   - ENUM_CLOCK_CLKCON1_CDPCLK1_DIV8    DIV8. Divide by 8 
   - ENUM_CLOCK_CLKCON1_CDPCLK1_DIV16   DIV16. Divide by 16 
   - ENUM_CLOCK_CLKCON1_CDPCLK1_DIV32   DIV32. Divide by 32 
   - ENUM_CLOCK_CLKCON1_CDPCLK1_DIV64   DIV64. Divide by 64 
   - ENUM_CLOCK_CLKCON1_CDPCLK1_DIV128  DIV128. Divide by 128
@return none
**/
uint32_t ClkDivCfg(uint32_t hclkDiv,uint32_t pclk0Div, uint32_t pclk1Div)
{
#ifdef FIRST_SILICON_WORKAROUND
   //switch to internal osc
   uint32_t preClkSrc = pADI_CLK->CLKCON0;
   pADI_CLK->CLKCON0 = (uint16_t)(preClkSrc&(~BITM_CLOCK_CLKCON0_CLKMUX));  
#endif
   //setup divider
   pADI_CLK->CLKCON1 = (uint16_t)((hclkDiv<<BITP_CLOCK_CLKCON1_CDHCLK) \
                        |(pclk0Div<<BITP_CLOCK_CLKCON1_CDPCLK0) \
                        |(pclk1Div<<BITP_CLOCK_CLKCON1_CDPCLK1));
#ifdef FIRST_SILICON_WORKAROUND
   //switch back to previous clock source
   pADI_CLK->CLKCON0 = (uint16_t)preClkSrc;
#endif
   return 1;
}

/*
@brief  uint32_t ClkSta()
    ========== Read the status register for the Clk.
@return value of Clk Sta
    - SPLLSTATUS,System PLL Status.
    - SPLLLOCKCLR ,System PLL Lock.
    - SPLLUNLOCKCLR, System PLL Unlock
    - SPLLLOCK ,Sticky System PLL Lock Flag.
    - SPLLUNLOCK ,Sticky System PLL Unlock Flag.
    - [15:5]  RESERVED
*/
 uint32_t ClkSta()
{
   return pADI_CLK->CLKSTAT0;
}


/**
 *  SPLLLOCK Sticky Status CLR
 *
 * @brief  Writing a one to this bit clear sticky status and Lock IRQ source, this bit can be auto-cleared to 0 after writing a 1.
 *
 */

void SPLLLOCKStickyStaCLR(void)
{
   uint32_t reg;

   reg = pADI_CLK->CLKSTAT0;
   reg &= ~BITM_CLOCK_CLKSTAT0_SPLLLOCKCLR;
   reg |= (1 <<BITP_CLOCK_CLKSTAT0_SPLLLOCKCLR);
   pADI_CLK->CLKSTAT0 = (uint16_t)reg;
  
}

/**
 *  SPLLUNLOCK Sticky Status CLR
 *
 * @brief  Writing a one to this bit clear sticky status and Lock IRQ source, this bit can be auto-cleared to 0 after writing a 1.
 *
 */

void SPLLUNLOCKStickyStaCLR(void)
{
   uint32_t reg;

   reg = pADI_CLK->CLKSTAT0;
   reg &= ~BITM_CLOCK_CLKSTAT0_SPLLUNLOCKCLR;
   reg |= (1 <<BITP_CLOCK_CLKSTAT0_SPLLUNLOCKCLR);
   pADI_CLK->CLKSTAT0 = (uint16_t)reg;
  
}

#if 0 //removed in S2
/**
 @brief int32_t ClkOffCfg(uint32_t ClockOff)
         ==========Clear the interrupt of DieB.
   @param ClockOff :{BITM_CLOCK_UCLKOFF_GPIOUCLKOFF | BITM_CLOCK_UCLKOFF_PWMUCLKOFF  | BITM_CLOCK_UCLKOFF_SPI0UCLKOFF | BITM_CLOCK_UCLKOFF_SPI1UCLKOFF |\
                        BITM_CLOCK_UCLKOFF_SPI2UCLKOFF | BITM_CLOCK_UCLKOFF_I2C0UCLKOFF | BITM_CLOCK_UCLKOFF_I2C1UCLKOFF | BITM_CLOCK_UCLKOFF_I2C2UCLKOFF |\
                        BITM_CLOCK_UCLKOFF_UART0UCLKOFF | BITM_CLOCK_UCLKOFF_UART1UCLKOFF | BITM_CLOCK_UCLKOFF_MDIOUCLKOFF | BITM_CLOCK_UCLKOFF_SPI3UCLKOFF |\
                        BITM_CLOCK_UCLKOFF_SPI4UCLKOFF | BITM_CLOCK_UCLKOFF_WUTUCLKOFF | BITM_CLOCK_UCLKOFF_WDTUCLKOFF | BITM_CLOCK_UCLKOFF_PLAUCLKOFF |\
                        BITM_CLOCK_UCLKOFF_GPTUCLKOFF  | BITM_CLOCK_UCLKOFF_PLACLKOFF  | BITM_CLOCK_UCLKOFF_CALCLKOFF | BITM_CLOCK_UCLKOFF_GPTCLKOFF |\
                        BITM_CLOCK_UCLKOFF_ANAUCLKOFF | BITM_CLOCK_UCLKOFF_ANAOSCCLKOFF | BITM_CLOCK_UCLKOFF_DIV0OFF | BITM_CLOCK_UCLKOFF_DIV1OFF};
      - CLKOFFSEL
      - BITM_CLOCK_UCLKOFF_GPIOUCLKOFF :   GPIO CLK User Control                              0: Clock on 1: Clock off
      - BITM_CLOCK_UCLKOFF_PWMUCLKOFF :    PWM Clock User Control                             0: Clock on 1: Clock off
      - BITM_CLOCK_UCLKOFF_SPI0UCLKOFF :   SPI0 Clock User Control                            0: Clock on 1: Clock off
      - BITM_CLOCK_UCLKOFF_SPI1UCLKOFF :   SPI1 Clock User Control                            0: Clock on 1: Clock off
      - BITM_CLOCK_UCLKOFF_SPI2UCLKOFF :   SPI2 Clock User Control                            0: Clock on 1: Clock off 
      - BITM_CLOCK_UCLKOFF_I2C0UCLKOFF :   I2C0 Clock User Control                            0: Clock on 1: Clock off 
      - BITM_CLOCK_UCLKOFF_I2C1UCLKOFF :   I2C1 Clock User Control                            0: Clock on 1: Clock off 
      - BITM_CLOCK_UCLKOFF_I2C2UCLKOFF :   I2C1 Clock User Control                            0: Clock on 1: Clock off 
      - BITM_CLOCK_UCLKOFF_UART0UCLKOFF :  UART0 Clock User Control                           0: Clock on 1: Clock off 
      - BITM_CLOCK_UCLKOFF_UART1UCLKOFF :  UART1 Clock User Control                           0: Clock on 1: Clock off 
      - BITM_CLOCK_UCLKOFF_MDIOUCLKOFF :   MDIO Clock User Control                            0: Clock on 1: Clock off
      - BITM_CLOCK_UCLKOFF_SPI3UCLKOFF :   SPI3 Clock User Control                            0: Clock on 1: Clock off
      - BITM_CLOCK_UCLKOFF_SPI4UCLKOFF :   SPI4 Clock User Control                            0: Clock on 1: Clock off
      - BITM_CLOCK_UCLKOFF_WUTUCLKOFF :    WUT Clock User Control                             0: Clock on 1: Clock off
      - BITM_CLOCK_UCLKOFF_WDTUCLKOFF :    WDT Clock User Control                             0: Clock on 1: Clock off 
      - BITM_CLOCK_UCLKOFF_PLAUCLKOFF :    PLA Clock User Control                             0: Clock on 1: Clock off 
      - BITM_CLOCK_UCLKOFF_GPTUCLKOFF :    GPT Clock User Control                             0: Clock on 1: Clock off 
      - BITM_CLOCK_UCLKOFF_PLACLKOFF :     PLA Clock User Control                             0: Clock on 1: Clock off 
      - BITM_CLOCK_UCLKOFF_CALCLKOFF :     CAL Clock User Control                             0: Clock on 1: Clock off 
      - BITM_CLOCK_UCLKOFF_GPTCLKOFF :     GPT Clock User Control                             0: Clock on 1: Clock off 
      - BITM_CLOCK_UCLKOFF_ANAUCLKOFF :    Analog Clock User Control                          0: Clock on 1: Clock off
      - BITM_CLOCK_UCLKOFF_ANAOSCCLKOFF :  Analog Clock User Control                          0: Clock on 1: Clock off
      - BITM_CLOCK_UCLKOFF_DIV0OFF :       Divider 0 Power-down                               0: Clock on 1: Clock off
      - BITM_CLOCK_UCLKOFF_DIV1OFF :       Divider 1 Power-down                               0: Clock on 1: Clock off

   @return 1.
**/
uint32_t ClkOffCfg(uint32_t ClockOff)
{
   uint32_t reg;

   reg = (ClockOff & (BITM_CLOCK_UCLKOFF_GPIOUCLKOFF | BITM_CLOCK_UCLKOFF_PWMUCLKOFF  | BITM_CLOCK_UCLKOFF_SPI0UCLKOFF | BITM_CLOCK_UCLKOFF_SPI1UCLKOFF |\
          BITM_CLOCK_UCLKOFF_SPI2UCLKOFF | BITM_CLOCK_UCLKOFF_I2C0UCLKOFF | BITM_CLOCK_UCLKOFF_I2C1UCLKOFF | BITM_CLOCK_UCLKOFF_I2C2UCLKOFF |\
          BITM_CLOCK_UCLKOFF_UART0UCLKOFF | BITM_CLOCK_UCLKOFF_UART1UCLKOFF | BITM_CLOCK_UCLKOFF_MDIOUCLKOFF | BITM_CLOCK_UCLKOFF_SPI3UCLKOFF |\
          BITM_CLOCK_UCLKOFF_SPI4UCLKOFF | BITM_CLOCK_UCLKOFF_WUTUCLKOFF | BITM_CLOCK_UCLKOFF_WDTUCLKOFF | BITM_CLOCK_UCLKOFF_PLAUCLKOFF |\
          BITM_CLOCK_UCLKOFF_GPTUCLKOFF  | BITM_CLOCK_UCLKOFF_PLACLKOFF  | BITM_CLOCK_UCLKOFF_CALCLKOFF | BITM_CLOCK_UCLKOFF_GPTCLKOFF |\
          BITM_CLOCK_UCLKOFF_ANAUCLKOFF | BITM_CLOCK_UCLKOFF_ANAOSCCLKOFF | BITM_CLOCK_UCLKOFF_DIV0OFF | BITM_CLOCK_UCLKOFF_DIV1OFF));
   pADI_CLK->UCLKOFF = reg;
   return 1;
  
}

#endif 

/*
@brief void ClkSetup(const CLK_SETUP_t * pSetup)
      =========== setup clock 
 
@param pSetup: pointer to CLK_SETUP_t structure
@return none
**/
void ClkSetup(const CLK_SETUP_t * pSetup)
{
      uint32_t regCLKCON0,regCLKCON1,status;
      uint32_t preClkSrc = pADI_CLK->CLKCON0;
      pADI_CLK->CLKCON0 = (uint16_t)(preClkSrc&(~BITM_CLOCK_CLKCON0_CLKMUX)); //use internal OSC to configure clock setting
      preClkSrc = pADI_CLK->CLKCON0&(~BITM_CLOCK_CLKCON0_CLKOUT);
      regCLKCON0 = (pSetup->rootClkMux<<BITP_CLOCK_CLKCON0_CLKMUX) \
                  |(pSetup->clkOutput<<BITP_CLOCK_CLKCON0_CLKOUT) \
                  |(pSetup->analogClkMux<<BITP_CLOCK_CLKCON0_ANACLKMUX) \
                  |(pSetup->pllIntEn<<BITP_CLOCK_CLKCON0_SPLLIE)\
                  |preClkSrc;
      regCLKCON1 = (pSetup->hclkDiv<<BITP_CLOCK_CLKCON1_CDHCLK)   \
                  |(pSetup->pclk0Div<<BITP_CLOCK_CLKCON1_CDPCLK0)   \
                  |(pSetup->pclk1Div<<BITP_CLOCK_CLKCON1_CDPCLK1);
      if(pSetup->pllEn)
      {
         pADI_PLL->PLLPDCTRL |= BITM_PLL_MMRS_PLLPDCTRL_TOTPDB;   //enable PLL.
         //for(uint32_t i=0;i<1000;i++);
         do
         {
            status = pADI_CLK->CLKSTAT0;
         }
         while(!(status&BITM_CLOCK_CLKSTAT0_SPLLSTATUS));   //check PLL ready
      }
      else
      {
         pADI_PLL->PLLPDCTRL &= ~BITM_PLL_MMRS_PLLPDCTRL_TOTPDB;   //disable PLL.
      }
      pADI_CLK->CLKCON1 = (uint16_t)regCLKCON1;
      
      pADI_CLK->CLKCON0 = (uint16_t)regCLKCON0;  //PLL running after this line if enabled
      
      
}





/**@}*/
