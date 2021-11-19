/*!
 *****************************************************************************
 * @file:   common.h
 * @brief:  Common utilities for testing.
 *-----------------------------------------------------------------------------
 *
Copyright (c) 2010-2018 Analog Devices, Inc. All Rights Reserved.

This software is proprietary to Analog Devices, Inc. and its licensors.
By using this software you agree to the terms of the associated
Analog Devices Software License Agreement.
 ******************************************************************************/


#ifndef COMMON_H
#define COMMON_H

#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <stddef.h>
#include <string.h>

#ifdef __cplusplus
extern "C" {
#endif
   
#define DEBUG_EOL       "\r\n" 

#define DEBUG_PORT0          (pADI_GPIO2)
#define DEBUG_PIN0           (PIN0) 
#define DEBUG_PIN0_TOGGLE()   DioTglPin(DEBUG_PORT0,DEBUG_PIN0)
#define DEBUG_PIN0_SET()       DioSetPin(DEBUG_PORT0,DEBUG_PIN0)
#define DEBUG_PIN0_CLR()       DioClrPin(DEBUG_PORT0,DEBUG_PIN0)
#define DEBUG_PIN1           (PIN1)
#define DEBUG_PIN1_TOGGLE()   DioTglPin(DEBUG_PORT0,DEBUG_PIN1)
#define DEBUG_PIN1_SET()       DioSetPin(DEBUG_PORT0,DEBUG_PIN1)
#define DEBUG_PIN1_CLR()       DioClrPin(DEBUG_PORT0,DEBUG_PIN1)
   
//LED definition that fit ADuCM410 Evaluation board, EVAL-ADUCM410EBZ
//Note that this pin reused by DEBUG_PIN0
#define LED_PORT            (pADI_GPIO2)
#define LED_PIN             PIN0
#define LED_TOGGLE_DELAY    (400000)

#define LED_ON()        LED_PORT->CLR |= LED_PIN 
#define LED_OFF()        LED_PORT->SET |= LED_PIN 
#define LED_TOGGLE()        LED_PORT->TGL |= LED_PIN 

/* Enable REDIRECT_OUTPUT_TO_UART to send the output to UART terminal */
//#define REDIRECT_OUTPUT_TO_UART  

/* Disable ENABLE_DEBUG_PRINTF to prevent debug printf */
#define ENABLE_DEBUG_PRINTF

/*Disable ENABLE_DEBUG_PIN to prevent debug pin*/
#define ENABLE_DEBUG_PIN

#ifdef  ENABLE_DEBUG_PRINTF
extern  char aDebugString[150];

/* exit() is not implemented in Keil */
#ifdef __ARMCC_VERSION
#define exit(...)
#endif

#define DEBUG_MESSAGE(...) \
  do { \
    sprintf(aDebugString, __VA_ARGS__); \
    common_Perf(aDebugString); \
  } while(0)

#define DEBUG_RESULT(s, result, expected_value) \
  do { \
    if ((result) != (expected_value)) { \
      sprintf(aDebugString, "%s  %d", __FILE__, __LINE__); \
      common_Fail(aDebugString); \
      sprintf(aDebugString, "%s"DEBUG_EOL, (s)); \
      common_Perf(aDebugString); \
      exit(0); \
    } \
  } while (0)

#else

#define DEBUG_MESSAGE(...)
#define DEBUG_RESULT(s, result, expected_value)

#endif

#define INIT()          common_Init()
#define PASS(s)         common_Pass()
#define FAIL(s)         common_Fail(s)

/********************************************************************************
* API function prototypes
*********************************************************************************/
void common_Init(void);
void common_Pass(void);
void common_Fail(char *FailureReason);
void common_Perf(char *InfoString);
void SafetyWait(void);

#ifdef __cplusplus
}
#endif

#endif /* COMMON_H */


