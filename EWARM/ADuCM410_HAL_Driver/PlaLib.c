/*!
 *****************************************************************************
 * @file:   PlaLib.c
 * @brief:  library for programmable logic array
 *-----------------------------------------------------------------------------
 *
Copyright (c) 2013-2018 Analog Devices, Inc. All Rights Reserved.

This software is proprietary to Analog Devices, Inc. and its licensors.
By using this software you agree to the terms of the associated
Analog Devices Software License Agreement.
 ******************************************************************************/

#include "PlaLib.h"

uint16_t pla_flipflop_bit = PLA_FLIPFLOP_BIT_DEFAULT_BYPASS;  //default bypass flip-flop



/**
   @brief void PlaConfig(uint32_t Num, uint32_t iCfg)
      ==========Configure the PLA Element #Num.
   @param Num :{0~31}
      - The index of the PLA elements
   @param iCfg :{PLA_ELEM_N__MUX4 | PLA_ELEM_N__TBL | PLA_ELEM_N__MUX3 | PLA_ELEM_N__MUX2 | PLA_ELEM_N__MUX1 | PLA_ELEM_N__MUX0}
      PLA_ELEM_N__MUX4 : Select or Bypass Flip-flop Output
      PLA_ELEM_N__TBL : Configures Output.
         0x00 : 0
         0x01 : NOR
         0x02 : B and Not A
         0x03 : NOT A
         0x04 : A and Not B.
         0x05 : Not B
         0x06 : EXOR
         0x07 : NAND
         0x08 : AND
         0x09 : EXNOR
         0x0A : B
         0x0B : B or Not A
         0x0C : A
         0x0D : A or Not B
         0x0E : OR
         0x0F : 1
      PLA_ELEM_N__MUX3 : For element 0 ~ 15, Configure Mux3 Between GPIO Bus Input or Odd Feedback Input. 
                         For element 16 ~ 31,
      PLA_ELEM_N__MUX2 : For element 0 ~ 15, Configure Mux2 Between PLA_DINx Register or Even Feedback.
                         For element 16 ~ 31,
      PLA_ELEM_N__MUX1 : Configure Mux1 for Odd Element Feedback.
      PLA_ELEM_N__MUX0 : Configure Mux1 for Even Element Feedback.
   @return 1.
**/
void PlaConfig(uint32_t Num, uint32_t iCfg)
{
   uint32_t *p = (uint32_t *)((uint32_t)(&pADI_PLA->PLA_ELEM0));
   if(Num < 32)
   {*(p + Num) = (iCfg & 0xFFFF);}
   return;
}

/**
   @brief void PlaClkCfg(uint32_t Clk1, uint32_t Clk0)
      ==========Configure the Clock source for PLA Element block 0/1.
   @param Clk1 : the clock source for block1
      ENUM_PLA_PLA_CLK_BLOCK1_P03 : GPIO Clock on P0.3
      ENUM_PLA_PLA_CLK_BLOCK1_P11 : GPIO Clock on P1.1 
      ENUM_PLA_PLA_CLK_BLOCK1_P20 : GPIO Clock on P2.0 
      ENUM_PLA_PLA_CLK_BLOCK1_PCLK0 : HCLK 
      ENUM_PLA_PLA_CLK_BLOCK1_MOSC : MOSC (16 MHz) 
      ENUM_PLA_PLA_CLK_BLOCK1_T0 : Timer 0 
      ENUM_PLA_PLA_CLK_BLOCK1_T2 :Timer 2 
      ENUM_PLA_PLA_CLK_BLOCK1_KOSC : KOSC (32 KHz) 
   @param Clk0 : the clock source for block0
      The parameter is the same like the Clk1;

   @return .
**/
void PlaClkCfg(uint32_t Clk1, uint32_t Clk0)
{
   pADI_PLA->PLA_CLK = (uint16_t)(((Clk1 << BITP_PLA_PLA_CLK_BLOCK1) & BITM_PLA_PLA_CLK_BLOCK1) |\
                         (Clk0 & BITM_PLA_PLA_CLK_BLOCK0)) ;
}


/**
   @brief void PlaIntCfg(uint32_t Index, uint32_t En, uint32_t Src)
      ==========Configure the PLA interrupt.
   @param Index : {0~3}
         - the interrupt number of PLA
   @param En : {0,1}
         - IRQ Enable
      0 ��Disable Interrupt
      1 ��Enanle 
   @param Src : {0~31}
      - Element for the  interrupt source;
      For PLA_IRQ0 and PLA_IRQ1, the Src should  in the range {0~15};
      For PLA_IRQ2 and PLA_IRQ3, the Src should  in the range {16~31};
   @return .
**/
void PlaIntCfg(uint32_t Index, uint32_t En, uint32_t Src)
{
   uint32_t i1;
   if(Index == 0)
   {
      i1 = (pADI_PLA->PLA_IRQ0 & (~(BITM_PLA_PLA_IRQ0_IRQ0_SRC | BITM_PLA_PLA_IRQ0_IRQ0_EN) ));
      i1 |= (En << BITP_PLA_PLA_IRQ0_IRQ0_EN ) | Src ;
      pADI_PLA->PLA_IRQ0 =  (uint16_t)i1;
   }
   else if(Index == 1)
   {
      i1 = (pADI_PLA->PLA_IRQ0 & (~(BITM_PLA_PLA_IRQ0_IRQ1_SRC | BITM_PLA_PLA_IRQ0_IRQ1_EN) ));
      i1 |= (En << BITP_PLA_PLA_IRQ0_IRQ1_EN ) | (Src << BITP_PLA_PLA_IRQ0_IRQ1_SRC);
      pADI_PLA->PLA_IRQ0 =  (uint16_t)i1;
   }
   else if(Index == 2)
   {
      i1 = (pADI_PLA->PLA_IRQ1 & (~(BITM_PLA_PLA_IRQ1_IRQ2_SRC | BITM_PLA_PLA_IRQ1_IRQ2_EN) ));
      i1 |= (En << BITP_PLA_PLA_IRQ1_IRQ2_EN ) | (Src - 16);
      pADI_PLA->PLA_IRQ1 =  (uint16_t)i1;
   }
   else if(Index == 3)
   {
      i1 = (pADI_PLA->PLA_IRQ1 & (~(BITM_PLA_PLA_IRQ1_IRQ3_SRC | BITM_PLA_PLA_IRQ1_IRQ3_EN) ));
      i1 |= (En << BITP_PLA_PLA_IRQ1_IRQ3_EN ) | ((Src - 16) << BITP_PLA_PLA_IRQ1_IRQ3_SRC);
      pADI_PLA->PLA_IRQ1 =  (uint16_t)i1;
   }
   
   return;
}

/**
   @brief void PlaAdc(uint32_t ConvEn, uint32_t Src)
      ==========Configure the PLA as a source to start an ADC .
   @param ConvEn : {0,1}
         - Enable ADC Start Convert from PLA
   0 : Disable;
   1 : Enable;
   @param Src : {0~31}
      - Element for ADC Start Convert Source;
   @return .
**/
void PlaAdc(uint32_t ConvEn, uint32_t Src)
{
   uint32_t i1;
   i1 =  ((ConvEn << BITP_PLA_PLA_ADC_CONVST_EN ) & BITM_PLA_PLA_ADC_CONVST_EN ) | \
         (Src & BITM_PLA_PLA_ADC_CONVST_SRC);
   pADI_PLA->PLA_ADC = (uint16_t)i1;
   return;
}


/**
   @brief PlaDin(uint32_t iDin)
      ==========Input Bit to Element 15 to Element 0 .
   @param iDin : {0~0xFFFF}
         - Each bit represent the MUX2 input of the element 0~15
   @return .
**/
void PlaDin(uint32_t iDin)
{
   pADI_PLA->PLA_DIN0 = (int16_t)(iDin &  BITM_PLA_PLA_DIN0_DIN);
   return;
}

/**
   @brief PlaLock(uint32_t En)
      ==========Set to Disable Writing to Registers .
   @param En : {0,1}
   0 : wirting to registers allowed.
   1 : wirting to registers disabled
   @return .
**/
void PlaLock(uint32_t En)
{
   pADI_PLA->PLA_LCK = (uint16_t)(En & BITM_PLA_PLA_LCK_LOCKED);
   return;
}

/*
   @brief void PlaSetup(const MDIO_SETUP_t *pSetup)
      =========== write value of PLA setup structure to device
   @param pSetup: pointer to PLA setup structure
**/
void PlaSetup(const PLA_SETUP_t *pSetup)
{
   uint32_t i1;
   uint32_t i;
   uint32_t *p = (uint32_t *)(uint32_t)(&pADI_PLA->PLA_ELEM0);
   for(i=0; i<32; i++)
   {
      i1 = ((pSetup->pla_cfg[i].mux0 << BITP_PLA_PLA_ELEM_N__MUX0) | \
            (pSetup->pla_cfg[i].mux1 << BITP_PLA_PLA_ELEM_N__MUX1) | \
            (pSetup->pla_cfg[i].mux2 << BITP_PLA_PLA_ELEM_N__MUX2) | \
            (pSetup->pla_cfg[i].mux3 << BITP_PLA_PLA_ELEM_N__MUX3) | \
            (pSetup->pla_cfg[i].tbl << BITP_PLA_PLA_ELEM_N__TBL) | \
             pSetup->pla_cfg[i].mux4);
      
      *(p + i) = i1;
   }
   pADI_PLA->PLA_CLK = (uint16_t)((pSetup->pla_clk1 << BITP_PLA_PLA_CLK_BLOCK1) |  pSetup->pla_clk0);
   pADI_PLA->PLA_IRQ0 = (uint16_t)((pSetup->pla_irq1_en << BITP_PLA_PLA_IRQ0_IRQ1_EN) | (pSetup->pla_irq1_src << BITP_PLA_PLA_IRQ0_IRQ1_SRC) | \
                        (pSetup->pla_irq0_en << BITP_PLA_PLA_IRQ0_IRQ0_EN) | pSetup->pla_irq0_src);
   pADI_PLA->PLA_IRQ1 = (uint16_t)((pSetup->pla_irq3_en << BITP_PLA_PLA_IRQ1_IRQ3_EN) | (pSetup->pla_irq3_src << BITP_PLA_PLA_IRQ1_IRQ3_SRC) | \
                        (pSetup->pla_irq2_en << BITP_PLA_PLA_IRQ1_IRQ2_EN) | pSetup->pla_irq2_src);
   
   pADI_PLA->PLA_ADC = (uint16_t)((pSetup->pla_adc_en << BITP_PLA_PLA_ADC_CONVST_EN) | pSetup->pla_adc_src);
   pADI_PLA->PLA_DIN0 = (int16_t)(pSetup ->pla_din) ;
   pADI_PLA->PLA_LCK = (uint16_t)(pSetup->pla_lock);

   return;
}
