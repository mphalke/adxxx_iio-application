/*!
 *****************************************************************************
 * @file:   system_ADuCM410.c
 * @brief:  ADuCM410 system init
 *-----------------------------------------------------------------------------
 *
Copyright (c) 2013-2018 Analog Devices, Inc. All Rights Reserved.

This software is proprietary to Analog Devices, Inc. and its licensors.
By using this software you agree to the terms of the associated
Analog Devices Software License Agreement.
 ******************************************************************************/

#include "system_ADuCM410.h"

#define __HFOSC     (16000000)
#define __SPLL      (160000000)
#define __GPIOCLK   (16000000)

/*! checksum placed in 0x1FFC, 
scenario 1, page0_checksum != 0xFFFFFFFF: this address should be placed with calculated CRC of page0,
ADI kernel will check the CRC after reset to determine the integrity of page0. if CRC check fail,
Kernel enters download mode for upgrading user code. otherwise run user code 
scenario 2, page0_checksum == 0xFFFFFFFF, checksum feature is passed. run user code directly if no further
security check required.
*/
const uint32_t page0_checksum = 0xFFFFFFFF;

/*! System Clock Frequency (Core Clock) */
uint32_t SystemCoreClock = 0u;

/*!
 * @brief   Update the clock
 * @details Updates the variable SystemCoreClock and must be called whenever
           the core clock is changed during program execution.
 *
 * @return none
 *
 */
void SystemCoreClockUpdate(void)
{
    /* Update Core Clock sources */
    /* update the HF clock */
    switch ((pADI_CLK->CLKCON0 & BITM_CLOCK_CLKCON0_CLKMUX) >> BITP_CLOCK_CLKCON0_CLKMUX) {

        case ENUM_CLOCK_CLKCON0_CLKMUX_HFOSC:
            SystemCoreClock = __HFOSC;
            break;

        case ENUM_CLOCK_CLKCON0_CLKMUX_SPLL:
            SystemCoreClock = __SPLL;
            break;

        case ENUM_CLOCK_CLKCON0_CLKMUX_EXTCLK:
            SystemCoreClock = __GPIOCLK;
            break;

        default:
            return;
    }
}

void SystemInit()
{
   //all setting are not retain, if user change them
   pADI_ALLON->RSTKEY = 0x2009;
   pADI_ALLON->RSTKEY = 0x0426;
   pADI_ALLON->RSTCFG = 0xF;
   pADI_CACHE->KEY = CACHE_KEY;
   pADI_CACHE->SETUP &= ~BITM_CC_SETUP_CCFLUSHDIS;
   pADI_CACHE->KEY = 0;
   
 #if (__FPU_PRESENT == 1u) && (__FPU_USED == 1u)
    /* the FPU is disabled by default so enable FPU (NEON and VFP)
     * set the System Control Block, Coprocessor Access Control Register bits:
     * CP10 = grant CP10 coprocessor privileges and user mode access (full access)
     * CP11 = grant CP11 coprocessor privileged and user mode access (full access)
     * (CP10 and CP11 MUST be the same or "BEHAVIOR IS UNPREDICTABLE")
     */
    SCB->CPACR |= ((3UL << 10*2)|(3UL << 11*2));  /* set CP10 and CP11 for Full Access */
#endif

    /* Flush instruction and data pipelines to insure assertion of new settings. */
    __ISB();
    __DSB();

    SystemCoreClockUpdate();
}
