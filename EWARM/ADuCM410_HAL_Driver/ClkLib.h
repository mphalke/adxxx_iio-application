/*!
 *****************************************************************************
 * @file:   ClkLib.h
 * @brief:  header file of clock
 *-----------------------------------------------------------------------------
 *
Copyright (c) 2013-2018 Analog Devices, Inc. All Rights Reserved.

This software is proprietary to Analog Devices, Inc. and its licensors.
By using this software you agree to the terms of the associated
Analog Devices Software License Agreement.
 ******************************************************************************/
#ifndef CLK_LIB_H
#define CLK_LIB_H

#ifdef __cplusplus
extern "C" {
#endif 

#include "ADuCM410.h"

typedef struct
{
   //1 - enable pll, result in SPLL in 160MHz
   //0 - disable PLL.
   uint32_t pllEn;
   //ENUM_CLOCK_CLKCON0_CLKMUX_HFOSC       /* High Frequency Internal Oscillator (HFOSC) */
   //ENUM_CLOCK_CLKCON0_CLKMUX_SPLL        /* System PLL is Selected (165 MHz) */
   //ENUM_CLOCK_CLKCON0_CLKMUX_EXTCLK      /* External GPIO Port is Selected (ECLKIN) */
   uint32_t rootClkMux;

    //ENUM_CLOCK_CLKCON0_ANACLKMUX_HFOSC    /* Internal Oscillator is Selected (HFOSC) */
   //ENUM_CLOCK_CLKCON0_ANACLKMUX_GPIOCLK  /* GPIO Clock */
   uint32_t analogClkMux;

//---------------Divider-----------
   //ENUM_CLOCK_CLKCON1_CDHCLK_DIV1     /* DIV1. Divide by 1 (HCLK is Equal
   //ENUM_CLOCK_CLKCON1_CDHCLK_DIV2     /* DIV2. Divide by 2 (HCLK is Half 
   //ENUM_CLOCK_CLKCON1_CDHCLK_DIV4     /* DIV4. Divide by 4 (HCLK is Quart
   //ENUM_CLOCK_CLKCON1_CDHCLK_DIV8     /* DIV8. Divide by 8 */
   //ENUM_CLOCK_CLKCON1_CDHCLK_DIV16    /* DIV16.Divide by 16 */
   //ENUM_CLOCK_CLKCON1_CDHCLK_DIV32    /* DIV32.Divide by 32 */
   //ENUM_CLOCK_CLKCON1_CDHCLK_DIV64    /* DIV64.Divide by 64 */
   //ENUM_CLOCK_CLKCON1_CDHCLK_DIV128   /* DIV128. Divide by 128 */
   //spi0,spi1,spi2,cortex core, pwm used hclk
   uint32_t hclkDiv;

   //ENUM_CLOCK_CLKCON1_CDPCLK0_DIV1    /* DIV1. Divide by 1 (PCLK is Equal t
   //ENUM_CLOCK_CLKCON1_CDPCLK0_DIV2    /* DIV2. Divide by 2 (PCLK is Half th
   //ENUM_CLOCK_CLKCON1_CDPCLK0_DIV4    /* DIV4. Divide by 4 (PCLK is Quarter
   //ENUM_CLOCK_CLKCON1_CDPCLK0_DIV8    /* DIV8. Divide by 8 */
   //ENUM_CLOCK_CLKCON1_CDPCLK0_DIV16   /* DIV16. Divide by 16 */
   //ENUM_CLOCK_CLKCON1_CDPCLK0_DIV32   /* DIV32. Divide by 32 */
   //ENUM_CLOCK_CLKCON1_CDPCLK0_DIV64   /* DIV64. Divide by 164 */
   //ENUM_CLOCK_CLKCON1_CDPCLK0_DIV128  /* DIV128. Divide by 128 */
   //wut, pla, gpt used pclk0
   uint32_t pclk0Div;

   //ENUM_CLOCK_CLKCON1_CDPCLK1_DIV1    /* DIV1. Divide by 1 (PCLK is Equal t
   //ENUM_CLOCK_CLKCON1_CDPCLK1_DIV2    /* DIV2. Divide by 2 (PCLK is Half th
   //ENUM_CLOCK_CLKCON1_CDPCLK1_DIV4    /* DIV4. Divide by 4 (PCLK is Quarter
   //ENUM_CLOCK_CLKCON1_CDPCLK1_DIV8    /* DIV8. Divide by 8 */
   //ENUM_CLOCK_CLKCON1_CDPCLK1_DIV16   /* DIV16. Divide by 16 */
   //ENUM_CLOCK_CLKCON1_CDPCLK1_DIV32   /* DIV32. Divide by 32 */
   //ENUM_CLOCK_CLKCON1_CDPCLK1_DIV64   /* DIV64. Divide by 164 */
   //ENUM_CLOCK_CLKCON1_CDPCLK1_DIV128  /* DIV128. Divide by 128 */
   //I2C0,I2C1,I2C2,UART0,UART1,MDIO used pclk1
   uint32_t pclk1Div;
    
   //unused, can be ignored
   uint32_t clockOff;

   //---------Interrupt------------
   //1 - enable interrupt related to PLL
   //0 - disalbe interrrupt related to PLL
   uint32_t pllIntEn;

   //-------TEST CLOCK -------
   //ENUM_CLOCK_CLKCON0_CLKOUT_SPLL_CLK  /* SPLL clock */
   //ENUM_CLOCK_CLKCON0_CLKOUT_HCLKBUS   /* Hclk_bus */
   //ENUM_CLOCK_CLKCON0_CLKOUT_T3        /* Timer 3 Clock */
   //ENUM_CLOCK_CLKCON0_CLKOUT_WUT       /* Wake up Timer Clock */
   //ENUM_CLOCK_CLKCON0_CLKOUT_T0        /* Timer 0 Clock */
   //ENUM_CLOCK_CLKCON0_CLKOUT_ANA_CLK   /* Analog Test Signal */
   //ENUM_CLOCK_CLKCON0_CLKOUT_B1_PCLK   /* Bridge 2 PCLK */
   //ENUM_CLOCK_CLKCON0_CLKOUT_B2_PCLK   /* Bridge 2 PCLK */
   //ENUM_CLOCK_CLKCON0_CLKOUT_B0_PCLK   /* Bridge 1 Pclk */
   //ENUM_CLOCK_CLKCON0_CLKOUT_CORE      /* Core Clock */
   uint32_t clkOutput;
}CLK_SETUP_t;

extern CLK_SETUP_t gClkSetup;


//---------------------function prototype---------------------------------
extern void ClkSetup(const CLK_SETUP_t * pSetup);

extern uint32_t ClkMuxCfg(uint32_t clockSource);
extern uint32_t GPIOClkOutCfg(uint32_t clockSource);
extern uint32_t ANAClkMuxCfg(uint32_t clockSource);
extern uint32_t SPLLIECfg(uint32_t pllIntEnable);
extern uint32_t ClkDivCfg(uint32_t hclkDiv,uint32_t pclk0Div, uint32_t pclk1Div);
extern uint32_t ClkSta(void);
extern void     SPLLLOCKStickyStaCLR(void);
extern void     SPLLUNLOCKStickyStaCLR(void);
#if 0 //removed in s2
extern uint32_t ClkOffCfg(uint32_t ClockOff);
#endif

#ifdef __cplusplus
}
#endif

#endif   //#WDT_LIB_H
