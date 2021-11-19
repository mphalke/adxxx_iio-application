/*!
 *****************************************************************************
 * @file:   common.c
 * @brief:  Common utilities for testing.
 *-----------------------------------------------------------------------------
 *
Copyright (c) 2010-2018 Analog Devices, Inc. All Rights Reserved.

This software is proprietary to Analog Devices, Inc. and its licensors.
By using this software you agree to the terms of the associated
Analog Devices Software License Agreement.
 ******************************************************************************/

#include "common.h"

char aDebugString[150u];

#if defined(ENABLE_DEBUG_PIN) || defined(REDIRECT_OUTPUT_TO_UART)
#include "DioLib.h"
#endif

#ifdef REDIRECT_OUTPUT_TO_UART

#define USE_UART_1

#ifdef USE_UART_1  
    #define pADI_UART   pADI_UART1
#else
    #define pADI_UART   pADI_UART0
#endif


#include "UrtLib.h"
int UrtWriteStr(char *pStr);
int UrtWriteStr(char *pStr)
{
    uint32_t    i, size;

    size = strlen(pStr);
    for (i = 0; i < size; i++)
    {
        while (!UrtTx(pADI_UART, pStr[i]))
            ;
        while(!(pADI_UART->LSR&BITM_UART_LSR_TEMT))
            ;
    }
    return 1;
}
#define COMMON_PRINT(s)       UrtWriteStr(s)

#else


#define COMMON_PRINT(s)       printf("%s",s)


#endif /* REDIRECT_OUTPUT_TO_UART */

/**
 * Test Initialization
 *
 * @brief  Test initialization
 *
 */
void common_Init(void)
{
#ifdef REDIRECT_OUTPUT_TO_UART
#ifdef USE_UART_1  
    // Configure  UART1 pins
	DioCfgPin(pADI_GPIO1, PIN0, P1_0_UART1_RX);
    DioCfgPin(pADI_GPIO1, PIN1, P1_1_UART1_TX);
    DioPullCfgPin(pADI_GPIO1,PIN0,GPIO_PULLSEL_UP);
    DioPullCfgPin(pADI_GPIO1,PIN1,GPIO_PULLSEL_UP);
    DioPulPin(pADI_GPIO1,PIN0,1);
    DioPulPin(pADI_GPIO1,PIN1,1);
    DioDsPin(pADI_GPIO1,PIN0,3);
    DioDsPin(pADI_GPIO1,PIN1,3);
#else
    // Configure  UART0 pins
	 DioCfgPin(pADI_GPIO0, PIN4, P0_4_UART0_RX);
     DioCfgPin(pADI_GPIO0, PIN5, P0_5_UART0_TX);
     DioPullCfgPin(pADI_GPIO0,PIN4,GPIO_PULLSEL_UP);
     DioPullCfgPin(pADI_GPIO0,PIN5,GPIO_PULLSEL_UP);
     DioPulPin(pADI_GPIO0,PIN4,1);
     DioPulPin(pADI_GPIO0,PIN5,1);
     DioDsPin(pADI_GPIO0,PIN5,3);
     DioDsPin(pADI_GPIO0,PIN4,3);
#endif
    UrtCfg(pADI_UART, B115200, ENUM_UART_LCR_WLS_BITS8, 0);    // Configure UART for 115200 baud rate
#endif
#ifdef ENABLE_DEBUG_PIN
   DioCfgPin(DEBUG_PORT0,DEBUG_PIN0,0);  //gpio
   DioOenPin(DEBUG_PORT0,DEBUG_PIN0,1); //enable output
   DioPulPin(DEBUG_PORT0,DEBUG_PIN0,0); //enable pull up
   DioSetPin(DEBUG_PORT0,DEBUG_PIN0);  //set to 1 as default
   DioCfgPin(DEBUG_PORT0,DEBUG_PIN1,0);  //gpio
   DioOenPin(DEBUG_PORT0,DEBUG_PIN1,1); //enable output
   DioPulPin(DEBUG_PORT0,DEBUG_PIN1,0); //enable pull up
   DioSetPin(DEBUG_PORT0,DEBUG_PIN1);  //set to 1 as default

#endif
}


/**
 * Passing Result
 *
 * @brief  Report a passing test result
 *
 */
void common_Pass(void)
{
    char pass[] = "All done!";
    char term[] = DEBUG_EOL;

    COMMON_PRINT(pass);
    COMMON_PRINT(term);
}


/**
 * Failing Result
 *
 * @brief  Report a failing test result
 *
 * @param  [in] FailureReason : String identifying the failure
 *
 */
void common_Fail(char *FailureReason)
{
    char fail[] = "Failed: ";
    char term[] = DEBUG_EOL;

    COMMON_PRINT(fail);
    COMMON_PRINT(FailureReason);
    COMMON_PRINT(term);
}


/**
 * Info
 *
 * @brief  Report a failing test result
 *
 * @param  [in] InfoString : String with test information
 *
 */
void common_Perf(char *InfoString)
{
    char term[] = DEBUG_EOL;

    COMMON_PRINT(InfoString);
    COMMON_PRINT(term);
}


/**
 * SafetyWait
 *
 * @brief  Blink and wait until KEIL/IAR halt CPU successfully
 *
 */
void SafetyWait(void)
{
    uint32_t i, j;
   //LED setup
    DioOenPin(LED_PORT, LED_PIN, 1);
    DioSetPin(LED_PORT, LED_PIN);
    
    LED_OFF();

    for (i = 0; i < 50; i++)
    {
        LED_TOGGLE();
        for (j = 0; j < LED_TOGGLE_DELAY; j++)
        {
            (void)DioRd(LED_PORT);
        }
    }

}


