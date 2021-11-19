/*!
 *****************************************************************************
 * @file:   IntLib.h
 * @brief:  header file for external interrupt 
 *-----------------------------------------------------------------------------
 *
Copyright (c) 2013-2018 Analog Devices, Inc. All Rights Reserved.

This software is proprietary to Analog Devices, Inc. and its licensors.
By using this software you agree to the terms of the associated
Analog Devices Software License Agreement.
 ******************************************************************************/
#include "IntLib.h"

/**
	@brief void  EiClr(uint32_t EiNr)
			==========clear external interrupt flag
	@param iEiNr :{EICLR_IRQ0, EICLR_IRQ1, EXTINT2, EXTINT3, EXTINT4, EXTINT5, EXTINT6, EXTINT7}
		- 0x0: EXTINT0, External Interrupt 0 
		- 0x1: EXTINT1, External Interrupt 1 
		- 0x2: EXTINT2, External Interrupt 2 
		- 0x3: EXTINT3, External Interrupt 3 
		- 0x4: EXTINT4, External Interrupt 4 
		- 0x5: EXTINT5, External Interrupt 5 
		- 0x6: EXTINT6, External Interrupt 6 
		- 0x7: EXTINT7, External Interrupt 7
      - 0x8: EXTINT8, External Interrupt 8    
      - 0x9: EXTINT9, External Interrupt 9 
	@return 1
	@warning
		
**/
void  EiClr(uint32_t EiNr)
{
  pADI_ALLON->EICLR =(uint16_t)(0x1UL << EiNr);
}

/**
	@brief void EiCfg(uint32_t EiNr,uint32_t Enable, uint32_t Mode)
			==========configures external interrupt
	@param EiNr :{EXTINT0, EXTINT1, EXTINT2, EXTINT3, EXTINT4, EXTINT5, EXTINT6, EXTINT7}
		- 0x0: EXTINT0, External Interrupt 0 
		- 0x1: EXTINT1, External Interrupt 1 
		- 0x2: EXTINT2, External Interrupt 2 
		- 0x3: EXTINT3, External Interrupt 3 
		- 0x4: EXTINT4, External Interrupt 4 
		- 0x5: EXTINT5, External Interrupt 5 
		- 0x6: EXTINT6, External Interrupt 6 
		- 0x7: EXTINT7, External Interrupt 7 
      - 0x8: EXTINT8, External Interrupt 8
      - 0x9: EXTINT9, External Interrupt 9 
   @param Enable :{INT_DIS,INT_EN}
            - 0x0: INT_DIS for disabled.
            - 0x1: INT_EN for enabled.
   @param Mode :{INT_RISE, INT_FALL, INT_EDGES, INT_HIGH, INT_LOW}
            - 0x0: INT_RISE Rising edge
            - 0x1: INT_FALL Falling edge
            - 0x2: INT_EDGES Rising or falling edge
            - 0x3: INT_HIGH High level
            - 0x4: INT_LOW Low level
	@return none
	@warning
		the NVIC also needs to be configured
                external interrupts are available regardless of the GPIO configuration
                only ext int 0, 1 and 2 are available in SHUTDOWN mode
**/

void EiCfg(uint32_t EiNr,uint32_t Enable, uint32_t Mode)
{
  volatile uint32_t *pEIxCFG;
  uint32_t EIxCFG_A, EI0CFG_A, ulOffset, ulContent, ulMask; 
  EI0CFG_A = (uint32_t)& pADI_ALLON->EI0CFG;

  EIxCFG_A = EI0CFG_A + ((EiNr/4)*4);    // determine correct EIxCFG register
  pEIxCFG = (volatile uint32_t *)EIxCFG_A;
  ulOffset = (EiNr % 4)*4;    // determine correct offset in register  
    
  if (Enable == INT_DIS) 
  {     
    ulMask = 0xFUL << ulOffset;
    *pEIxCFG = *pEIxCFG & ~ulMask ; // clear the appropriate bit in the correct EIxCFG register 
  }
  else 
  {
    pADI_ALLON->EICLR = (uint16_t)(0x1UL << EiNr); // clears flag first
    ulContent = (0x8UL | Mode) << ulOffset;  // calculate the value to write
    ulMask = 0xFUL << ulOffset;
    *pEIxCFG = (*pEIxCFG & ~ulMask) | ulContent; // set the appropriate bits in the correct EIxCFG register  
  }
}

/*
@brief void ExIntSetup(EXINT_SETUP_Type * const setup)
      =========== setup for external interrupt
 
@param setup: pointer to EXINT_SETUP_Type structure
@return none
**/
void ExIntSetup(EXINT_SETUP_Type * const setup)
{
   uint32_t regEI0CFG, regEI1CFG, regEI2CFG;

   regEI0CFG = (setup->exIntChan[0].irqMode<<BITP_ALWAYS_ON_EI0CFG_IRQ0MDE)   \
               |(setup->exIntChan[0].irqEn<<BITP_ALWAYS_ON_EI0CFG_IRQ0EN)   \
               |(setup->exIntChan[1].irqMode<<BITP_ALWAYS_ON_EI0CFG_IRQ1MDE)   \
               |(setup->exIntChan[1].irqEn<<BITP_ALWAYS_ON_EI0CFG_IRQ1EN)   \
               |(setup->exIntChan[2].irqMode<<BITP_ALWAYS_ON_EI0CFG_IRQ2MDE)   \
               |(setup->exIntChan[2].irqEn<<BITP_ALWAYS_ON_EI0CFG_IRQ2EN)   \
               |(setup->exIntChan[3].irqMode<<BITP_ALWAYS_ON_EI0CFG_IRQ3MDE)   \
               |(setup->exIntChan[3].irqEn<<BITP_ALWAYS_ON_EI0CFG_IRQ3EN);

   regEI1CFG = (setup->exIntChan[4].irqMode<<BITP_ALWAYS_ON_EI1CFG_IRQ4MDE)   \
               |(setup->exIntChan[4].irqEn<<BITP_ALWAYS_ON_EI1CFG_IRQ4EN)   \
               |(setup->exIntChan[5].irqMode<<BITP_ALWAYS_ON_EI1CFG_IRQ5MDE)   \
               |(setup->exIntChan[5].irqEn<<BITP_ALWAYS_ON_EI1CFG_IRQ5EN)   \
               |(setup->exIntChan[6].irqMode<<BITP_ALWAYS_ON_EI1CFG_IRQ6MDE)   \
               |(setup->exIntChan[6].irqEn<<BITP_ALWAYS_ON_EI1CFG_IRQ6EN)   \
               |(setup->exIntChan[7].irqMode<<BITP_ALWAYS_ON_EI1CFG_IRQ7MDE)   \
               |(setup->exIntChan[7].irqEn<<BITP_ALWAYS_ON_EI1CFG_IRQ7EN);   

   regEI2CFG = (setup->exIntChan[8].irqMode<<BITP_ALWAYS_ON_EI2CFG_IRQ8MDE)   \
               |(setup->exIntChan[8].irqEn<<BITP_ALWAYS_ON_EI2CFG_IRQ8EN)   \
               |(setup->exIntChan[9].irqMode<<BITP_ALWAYS_ON_EI2CFG_IRQ9MDE)   \
               |(setup->exIntChan[9].irqEn<<BITP_ALWAYS_ON_EI2CFG_IRQ9EN);

   pADI_ALLON->EI0CFG = (uint16_t)regEI0CFG;
   pADI_ALLON->EI1CFG = (uint16_t)regEI1CFG;
   pADI_ALLON->EI2CFG = (uint16_t)regEI2CFG;
}

