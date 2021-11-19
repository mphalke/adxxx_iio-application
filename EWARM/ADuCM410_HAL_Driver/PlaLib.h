/*!
 *****************************************************************************
 * @file:  PlaLib.h 
 * @brief: header of programmable logic array
 *-----------------------------------------------------------------------------
 *
Copyright (c) 2013-2018 Analog Devices, Inc. All Rights Reserved.

This software is proprietary to Analog Devices, Inc. and its licensors.
By using this software you agree to the terms of the associated
Analog Devices Software License Agreement.
 ******************************************************************************/
#ifndef PLA_LIB_H
#define PLA_LIB_H

#ifdef __cplusplus
extern "C" {
#endif 

#include "ADuCM410.h"
typedef struct{
   //Mux for Even Element Feedback
   uint32_t mux0;
   //Mux for Odd Element Feedback
   uint32_t mux1;
   //Mux Between INA_PLA_DINx Register or Even Feedback
   uint32_t mux2;
   //Mux Between GPIO Bus Input or Odd Feedback Input
   uint32_t mux3;
   //Select or Bypass Flip-flop Output
   uint32_t mux4;
   //Configures Output
   uint32_t tbl;
}PLA_CONFIG_BITS_t;

typedef struct{
   //pla element configure
    PLA_CONFIG_BITS_t pla_cfg[32];
    //Clock Select for Block 1
    uint32_t pla_clk1;
    //Clock Select for Block 0
    uint32_t pla_clk0;
    //IRQ0 Enable
    uint32_t pla_irq0_en;
    //IRQ0 Source
    uint32_t pla_irq0_src;
    //IRQ1 Enable
    uint32_t pla_irq1_en;
    //IRQ1 Source
    uint32_t pla_irq1_src;
    //IRQ2 Enable
    uint32_t pla_irq2_en;
    //IRQ2 Source
    uint32_t pla_irq2_src;
    //IRQ3 Enable
    uint32_t pla_irq3_en;
    //IRQ3 Source
    uint32_t pla_irq3_src;
    
    //Enable ADC Start Convert from PLA
    uint32_t pla_adc_en;
    //Element for ADC Start Convert Source
    uint32_t pla_adc_src;
    //Input Bit to Element 15 to Element 0
    uint32_t pla_din;
    //Disable Writing to Registers
    uint32_t pla_lock;
}PLA_SETUP_t;
   
   
extern void PlaConfig(uint32_t Num, uint32_t iCfg);
extern void PlaClkCfg(uint32_t Clk1, uint32_t Clk0);
extern void PlaIntCfg(uint32_t Index, uint32_t En, uint32_t Src);
extern void PlaAdc(uint32_t ConvEn, uint32_t Src);
extern void PlaDin(uint32_t iDin);
extern void PlaLock(uint32_t En);
extern void PlaSetup(const PLA_SETUP_t *pSetup);

extern PLA_SETUP_t gPlaSetup;

/*HDL like MACRO for programming PLA*/
enum PLA_LOGIC{
   LOGIC_0 = 0u,
   LOGIC_A_NOR_B,
   LOGIC_NA_AND_B,
   LOGIC_NA,
   LOGIC_A_AND_NB,
   LOGIC_NB,
   LOGIC_A_XOR_B,
   LOGIC_A_NAND_B,
   LOGIC_A_AND_B,
   LOGIC_A_EXNOR_B,
   LOGIC_B,
   LOGIC_NA_OR_B,
   LOGIC_A,
   LOGIC_A_OR_NB,
   LOGIC_A_OR_B,
   LOGIC_1,
};
#define PLA_FLIPFLOP_BIT_DEFAULT_BYPASS ENUM_PLA_PLA_ELEM_N__MUX4_BYPASS //default bypass flip-flop
extern uint16_t pla_flipflop_bit;  

enum PLA_INPUT_A{
   INA_ELEM0 = 0U,
   INA_ELEM2,
   INA_ELEM4,
   INA_ELEM6,
   INA_ELEM8,
   INA_ELEM10,
   INA_ELEM12,
   INA_ELEM14,
   INA_PLA_DIN,
   INA_ELEM0_NOT,
   INA_ELEM2_NOT,
   INA_ELEM4_NOT,
   INA_ELEM6_NOT,
   INA_ELEM8_NOT,
   INA_ELEM10_NOT,
   INA_ELEM12_NOT,
   INA_ELEM14_NOT,
   INA_PLA_DIN_NOT,
};
enum PLA_INPUT_B{
   INB_ELEM1 = 0x80U,
   INB_ELEM3,
   INB_ELEM5,
   INB_ELEM7,
   INB_ELEM9,
   INB_ELEM11,
   INB_ELEM13,
   INB_ELEM15,
   INB_GPIO_INPUT,
   INB_ELEM1_NOT,
   INB_ELEM3_NOT,
   INB_ELEM5_NOT,
   INB_ELEM7_NOT,
   INB_ELEM9_NOT,
   INB_ELEM11_NOT,
   INB_ELEM13_NOT,
   INB_ELEM15_NOT,
   INB_GPIO_INPUT_NOT,
};
#define BLOCK1_INA_ELEM31  INA_ELEM0
#define BLOCK1_INA_ELEM0  INA_ELEM0
#define BLOCK1_INA_ELEM2  INA_ELEM2
#define BLOCK1_INA_ELEM4  INA_ELEM4
#define BLOCK1_INA_ELEM6  INA_ELEM6
#define BLOCK1_INA_ELEM8  INA_ELEM8
#define BLOCK1_INA_ELEM10  INA_ELEM10
#define BLOCK1_INA_ELEM12  INA_ELEM12
#define BLOCK1_INA_ELEM14  INA_ELEM14
#define BLOCK1_INA_ELEM0_NOT  INA_ELEM0_NOT
#define BLOCK1_INA_ELEM2_NOT  INA_ELEM2_NOT
#define BLOCK1_INA_ELEM4_NOT  INA_ELEM4_NOT
#define BLOCK1_INA_ELEM6_NOT  INA_ELEM6_NOT
#define BLOCK1_INA_ELEM8_NOT  INA_ELEM8_NOT
#define BLOCK1_INA_ELEM10_NOT  INA_ELEM10_NOT
#define BLOCK1_INA_ELEM12_NOT  INA_ELEM12_NOT
#define BLOCK1_INA_ELEM14_NOT  INA_ELEM14_NOT

#define BLOCK1_INB_ELEM1        INB_ELEM1
#define BLOCK1_INB_ELEM3        INB_ELEM3
#define BLOCK1_INB_ELEM5        INB_ELEM5
#define BLOCK1_INB_ELEM7        INB_ELEM7
#define BLOCK1_INB_ELEM9        INB_ELEM9
#define BLOCK1_INB_ELEM11       INB_ELEM11
#define BLOCK1_INB_ELEM13       INB_ELEM13
#define BLOCK1_INB_ELEM15       INB_ELEM15
#define BLOCK1_INB_ELEM1_NOT    INB_ELEM1_NOT
#define BLOCK1_INB_ELEM3_NOT    INB_ELEM3_NOT
#define BLOCK1_INB_ELEM5_NOT    INB_ELEM5_NOT
#define BLOCK1_INB_ELEM7_NOT    INB_ELEM7_NOT
#define BLOCK1_INB_ELEM9_NOT    INB_ELEM9_NOT
#define BLOCK1_INB_ELEM11_NOT   INB_ELEM11_NOT
#define BLOCK1_INB_ELEM13_NOT   INB_ELEM13_NOT
#define BLOCK1_INB_ELEM15_NOT   INB_ELEM15_NOT

#define BLOCK1_INA_B0_ELEMx      INA_PLA_DIN
#define BLOCK1_INA_B0_ELEMx_NOT  INA_PLA_DIN_NOT
#define BLOCK1_INB_COMP0  INB_GPIO_INPUT
#define BLOCK1_INB_COMP1  INB_GPIO_INPUT
#define BLOCK1_INB_COMP2  INB_GPIO_INPUT
#define BLOCK1_INB_COMP3  INB_GPIO_INPUT
#define BLOCK1_INB_COMP0_NOT  INB_GPIO_INPUT_NOT
#define BLOCK1_INB_COMP1_NOT  INB_GPIO_INPUT_NOT
#define BLOCK1_INB_COMP2_NOT  INB_GPIO_INPUT_NOT
#define BLOCK1_INB_COMP3_NOT  INB_GPIO_INPUT_NOT
#define BLOCK1_INB_DGND   INB_GPIO_INPUT
#define BLOCK1_INB_ADC     INB_GPIO_INPUT
#define BLOCK1_INB_ADC_NOT     INB_GPIO_INPUT_NOT

enum PLA_CLK{
   PLA_CLK_P0_3 = 0u,
   PLA_CLK_P1_1,
   PLA_CLK_P2_0,
   PLA_CLK_PCLK0,
   PLA_CLK_HFOSC,
   PLA_CLK_T0,
   PLA_CLK_T2,
   PLA_CLK_LFOSC,
};

#define PLA_BEGIN 
#define PLA_END pla_flipflop_bit = PLA_FLIPFLOP_BIT_DEFAULT_BYPASS;
#define BLOCK0_ALWAYS_AT_POSEDGE(clk)  pla_flipflop_bit = ENUM_PLA_PLA_ELEM_N__MUX4_FF;\
                                       pADI_PLA->PLA_CLK &= ~BITM_PLA_PLA_CLK_BLOCK0;\
                                       pADI_PLA->PLA_CLK |= (clk<<BITP_PLA_PLA_CLK_BLOCK0);
#define BLOCK1_ALWAYS_AT_POSEDGE(clk)  pla_flipflop_bit = ENUM_PLA_PLA_ELEM_N__MUX4_FF;\
                                       pADI_PLA->PLA_CLK &= ~BITM_PLA_PLA_CLK_BLOCK1;\
                                       pADI_PLA->PLA_CLK |= (clk<<BITP_PLA_PLA_CLK_BLOCK1);


/*
   possible options for out:
      ELEM0 ~ ELEM31
   possible options for inA:
      BLOCK1_INA_ELEM31
      INA_ELEM0 
      INA_ELEM2
      INA_ELEM4
      INA_ELEM6
      INA_ELEM8
      INA_ELEM10
      INA_ELEM12
      INA_ELEM14
      INA_PLA_DIN
*/
#define PLA_AND(out, inA, inB)   \
   {\
      pADI_PLA->PLA_##out = \
      ((inA>=INA_ELEM0_NOT) ? ((inB>=INB_ELEM1_NOT)?(LOGIC_A_NOR_B<<BITP_PLA_PLA_ELEM_N__TBL):(LOGIC_NA_AND_B<<BITP_PLA_PLA_ELEM_N__TBL)) \
      : ((inB>=INB_ELEM1_NOT)?(LOGIC_A_AND_NB<<BITP_PLA_PLA_ELEM_N__TBL):(LOGIC_A_AND_B<<BITP_PLA_PLA_ELEM_N__TBL)) \
      )|( ((inA==INA_PLA_DIN)||(inA==INA_PLA_DIN_NOT)) ? (0<<BITP_PLA_PLA_ELEM_N__MUX2) : ((1<<BITP_PLA_PLA_ELEM_N__MUX2)|(((inA>=INA_ELEM0_NOT)?(inA-INA_ELEM0_NOT):inA)<<BITP_PLA_PLA_ELEM_N__MUX0)) ) \
      |( ((inB==INB_GPIO_INPUT)||(inB==INB_GPIO_INPUT_NOT)) ? (1<<BITP_PLA_PLA_ELEM_N__MUX3) : ((0<<BITP_PLA_PLA_ELEM_N__MUX3)|(((inB>=INB_ELEM1_NOT)?(inB-INB_ELEM1_NOT):inB)<<BITP_PLA_PLA_ELEM_N__MUX1)))   \
      | pla_flipflop_bit;       \
   }

#define PLA_OR(out, inA, inB)   \
   {\
      pADI_PLA->PLA_##out = \
      ((inA>=INA_ELEM0_NOT) ? ((inB>=INB_ELEM1_NOT)?(LOGIC_A_NAND_B<<BITP_PLA_PLA_ELEM_N__TBL):(LOGIC_NA_OR_B<<BITP_PLA_PLA_ELEM_N__TBL)) \
      : ((inB>=INB_ELEM1_NOT)?(LOGIC_A_OR_NB<<BITP_PLA_PLA_ELEM_N__TBL):(LOGIC_A_OR_B<<BITP_PLA_PLA_ELEM_N__TBL)) \
      )|( ((inA==INA_PLA_DIN)||(inA==INA_PLA_DIN_NOT)) ? (0<<BITP_PLA_PLA_ELEM_N__MUX2) : ((1<<BITP_PLA_PLA_ELEM_N__MUX2)|(((inA>=INA_ELEM0_NOT)?(inA-INA_ELEM0_NOT):inA)<<BITP_PLA_PLA_ELEM_N__MUX0)))   \
      |( ((inB==INB_GPIO_INPUT)||(inB==INB_GPIO_INPUT_NOT)) ? (1<<BITP_PLA_PLA_ELEM_N__MUX3) : ((0<<BITP_PLA_PLA_ELEM_N__MUX3)|(((inB>=INB_ELEM1_NOT)?(inB-INB_ELEM1_NOT):inB)<<BITP_PLA_PLA_ELEM_N__MUX1)) )  \
      | pla_flipflop_bit;       \
   }

#define PLA_NOR(out, inA, inB)   \
   {\
      pADI_PLA->PLA_##out = \
      (LOGIC_A_NOR_B<<BITP_PLA_PLA_ELEM_N__TBL) \
      |( (inA==INA_PLA_DIN) ? (0<<BITP_PLA_PLA_ELEM_N__MUX2) : ((1<<BITP_PLA_PLA_ELEM_N__MUX2)|(inA<<BITP_PLA_PLA_ELEM_N__MUX0)) )  \
      |( (inB==INB_GPIO_INPUT) ? (1<<BITP_PLA_PLA_ELEM_N__MUX3) : ((0<<BITP_PLA_PLA_ELEM_N__MUX3)|(inB<<BITP_PLA_PLA_ELEM_N__MUX1)) )  \
      | pla_flipflop_bit;\
   }
   
#define PLA_NOT(out, in)   \
   {\
      pADI_PLA->PLA_##out = \
      (((enum PLA_INPUT_B)in>=INB_ELEM1)?(LOGIC_NB<<BITP_PLA_PLA_ELEM_N__TBL):(LOGIC_NA<<BITP_PLA_PLA_ELEM_N__TBL)) \
      |( ((enum PLA_INPUT_B)in>=INB_ELEM1)?\
      ( ((enum PLA_INPUT_B)in==INB_GPIO_INPUT) ? (1<<BITP_PLA_PLA_ELEM_N__MUX3) : ((0<<BITP_PLA_PLA_ELEM_N__MUX3)|(in<<BITP_PLA_PLA_ELEM_N__MUX1)) )  \
      :( ((enum PLA_INPUT_A)in==INA_PLA_DIN) ? (0<<BITP_PLA_PLA_ELEM_N__MUX2) : ((1<<BITP_PLA_PLA_ELEM_N__MUX2)|(in<<BITP_PLA_PLA_ELEM_N__MUX0)) )  \
      )| pla_flipflop_bit;\
   }

#define PLA_XOR(out, inA, inB)   \
   {\
      pADI_PLA->PLA_##out = \
      (LOGIC_A_XOR_B<<BITP_PLA_PLA_ELEM_N__TBL) \
      |( (inA==INA_PLA_DIN) ? (0<<BITP_PLA_PLA_ELEM_N__MUX2) : ((1<<BITP_PLA_PLA_ELEM_N__MUX2)|(inA<<BITP_PLA_PLA_ELEM_N__MUX0)) )  \
      |( (inB==INB_GPIO_INPUT) ? (1<<BITP_PLA_PLA_ELEM_N__MUX3) : ((0<<BITP_PLA_PLA_ELEM_N__MUX3)|(inB<<BITP_PLA_PLA_ELEM_N__MUX1)) )  \
      | pla_flipflop_bit;\
   }

#define PLA_NAND(out, inA, inB)   \
   {\
      pADI_PLA->PLA_##out = \
      (LOGIC_A_NAND_B<<BITP_PLA_PLA_ELEM_N__TBL) \
      |( (inA==INA_PLA_DIN) ? (0<<BITP_PLA_PLA_ELEM_N__MUX2) : ((1<<BITP_PLA_PLA_ELEM_N__MUX2)|(inA<<BITP_PLA_PLA_ELEM_N__MUX0)) )  \
      |( (inB==INB_GPIO_INPUT) ? (1<<BITP_PLA_PLA_ELEM_N__MUX3) : ((0<<BITP_PLA_PLA_ELEM_N__MUX3)|(inB<<BITP_PLA_PLA_ELEM_N__MUX1)) )  \
      | pla_flipflop_bit;\
   }

#define PLA_EXNOR(out, inA, inB)   \
   {\
      pADI_PLA->PLA_##out = \
      (LOGIC_A_EXNOR_B<<BITP_PLA_PLA_ELEM_N__TBL) \
      |( (inA==INA_PLA_DIN) ? (0<<BITP_PLA_PLA_ELEM_N__MUX2) : ((1<<BITP_PLA_PLA_ELEM_N__MUX2)|(inA<<BITP_PLA_PLA_ELEM_N__MUX0)) )  \
      |( (inB==INB_GPIO_INPUT) ? (1<<BITP_PLA_PLA_ELEM_N__MUX3) : ((0<<BITP_PLA_PLA_ELEM_N__MUX3)|(inB<<BITP_PLA_PLA_ELEM_N__MUX1)) )  \
      | pla_flipflop_bit;\
   }

#define PLA_OUT_A(out, inA)   \
   {\
      pADI_PLA->PLA_##out = \
      (LOGIC_A<<BITP_PLA_PLA_ELEM_N__TBL) \
      |( (inA==INA_PLA_DIN) ? (0<<BITP_PLA_PLA_ELEM_N__MUX2) : ((1<<BITP_PLA_PLA_ELEM_N__MUX2)|(inA<<BITP_PLA_PLA_ELEM_N__MUX0)) )  \
      | pla_flipflop_bit;\
   }

#define PLA_OUT_B(out, inB)   \
   {\
      pADI_PLA->PLA_##out = \
      (LOGIC_B<<BITP_PLA_PLA_ELEM_N__TBL) \
      |( (inB==INB_GPIO_INPUT) ? (1<<BITP_PLA_PLA_ELEM_N__MUX3) : ((0<<BITP_PLA_PLA_ELEM_N__MUX3)|(inB<<BITP_PLA_PLA_ELEM_N__MUX1)) )  \
      | pla_flipflop_bit;\
   }

#define PLA_LOGIC_1(out)   \
   {\
      pADI_PLA->PLA_##out = \
      (LOGIC_1<<BITP_PLA_PLA_ELEM_N__TBL) \
      | pla_flipflop_bit;\
   }

#define PLA_LOGIC_0(out)   \
   {\
      pADI_PLA->PLA_##out = \
      (LOGIC_0<<BITP_PLA_PLA_ELEM_N__TBL) \
      | pla_flipflop_bit;\
   }



#ifdef __cplusplus
}
#endif

#endif   //#PLA_LIB_H

