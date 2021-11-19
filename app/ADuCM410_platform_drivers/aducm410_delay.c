/***************************************************************************//**
 *   @file   delay.c
 *   @brief  Implementation of AdDuCM410 delay functions
********************************************************************************
 * Copyright (c) 2020-21 Analog Devices, Inc.
 * All rights reserved.
 *
 * This software is proprietary to Analog Devices, Inc. and its licensors.
 * By using this software you agree to the terms of the associated
 * Analog Devices Software License Agreement.
*******************************************************************************/

/******************************************************************************/
/***************************** Include Files **********************************/
/******************************************************************************/

#include "delay.h"
#include "GptLib.h"

/******************************************************************************/
/********************** Macros and Constants Definitions **********************/
/******************************************************************************/

/* Default system clock frequency in Hz */
#define SYSTEM_CLOCK	160000000

/* Clock prescaler used for generating timer based usec delay */
#define CLOCK_PRESCALER	16

/******************************************************************************/
/************************ Functions Definitions *******************************/
/******************************************************************************/

/**
 * @brief Generate microseconds delay using general timer0
 * @param usecs - Delay in microseconds.
 * @return None.
 * @note  The delay is based on the default system clock frequency of 160Mhz
 *        The delay may not be correct if using system frequenct other than
 *        160Mhz
 */
void udelay(uint32_t usecs)
{
	uint16_t reload;

	reload = usecs * (SYSTEM_CLOCK  / 1000000 / CLOCK_PRESCALER);

	pADI_GPT0->CON &= (~BITM_TMR_CON_ENABLE);	// disable timer0
	pADI_GPT0->LD = reload;						// reload the timer0value

	/* config and enable timer0 */
	pADI_GPT0->CON = ((ENUM_TMR_CON_CLK_HCLK << BITP_TMR_CON_CLK) | \
			  ENUM_TMR_CON_PRE_DIV16 |\
			  BITM_TMR_CON_ENABLE |\
			  (ENUM_TMR_CON_MOD_PERIODIC << BITP_TMR_CON_MOD));

	while (!(pADI_GPT0->STA & BITM_TMR_STA_TMOUT));
	pADI_GPT0->CLRI = 1;	// clear timeout status flag
}

/**
 * @brief Generate miliseconds delay.
 * @param msecs - Delay in miliseconds.
 * @return None.
 */
void mdelay(uint32_t msecs)
{
	if (msecs) {
		// NOTE: using a for loop, to limit hardware usage requirements
		// The value X * msecs is based on default eval board clock/config
		for(volatile uint32_t i = 0; i < (13400 * msecs); i++);
	}
}
