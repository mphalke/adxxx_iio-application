/*!
 *****************************************************************************
 * @file: FeeLib.h
 * @brief: header file of flash library
 *-----------------------------------------------------------------------------
 *
Copyright (c) 2013-2018 Analog Devices, Inc. All Rights Reserved.

This software is proprietary to Analog Devices, Inc. and its licensors.
By using this software you agree to the terms of the associated
Analog Devices Software License Agreement.
 ******************************************************************************/
#ifndef FEE_LIB_H
#define FEE_LIB_H

#ifdef __cplusplus
extern "C" {
#endif 

#include "ADuCM410.h"

#define FLASH_USER_KEY  0xF123F456

#define FLASH_ACCESS_PRIO_CPU 1
#define FLASH_ACCESS_PRIO_DMA 0

#define CACHE_KEY 0xF123F456

typedef struct
{
   //1 - JTAG debug enable
   //0 - disable
   uint32_t jtagEn;

   //1 -  Key hole DMA enable, also need to setup DMA controller
   //0 -  disable
   uint32_t keyHoleDmaEn;

   //1 - auto address increment for key hole access
   //0 - no increment
   uint32_t keyHoleAutoInc;

   //1 - enable mdio mode
   //0 - disable
   uint32_t mdioModeEn;

   //1 - swap program code for MDIO mode
   //0 - disable
   uint32_t mdioSwapEn;

   //1 - swap inside flash enable
   //0 - no swap
   uint32_t flashSwapEn;

   //require flashSwapEn==1
   //1 - swap top and bottom image inside flash 0
   //0 - no swap
   uint32_t SwapFlash0;

   //require flashSwapEn==1
   //1 - swap top and bottom image inside flash 1
   //0 - no swap
   uint32_t SwapFlash1;

//-------- Interrupt Enable -------
   //1 - command complete interrupt enable
   //0 - disable
   uint32_t cmdCompleteIntEn;

   //1- write almost complete interrupt enable
   //0- disable
   uint32_t wrCompleteIntEn;

   //1 - command fail interrupt enable
   //0 - disable
   uint32_t cmdFailIntEn;

   //sytem interrupt abort flash command
   //each bit corresponding to each system interrupt
   //ex. bit 0 of intAbort[0] set to 1 means wake up interrupt will abort flash command. 
   //bit 0 of intAbort[1] set to 1 means ...
   uint32_t intAbort[3];
}FLASH_SETUP_t;



extern FLASH_SETUP_t gFlashSetup;

//-------------------------------- Function declaration -------------
extern void FeeSetup(FLASH_SETUP_t *pFlashSetup);

extern uint32_t FeeMErs(uint32_t Block);
extern uint32_t FeePErs(uint32_t lAddr);
extern uint32_t FeeWr(uint32_t lAddr, uint64_t udData);   
extern uint32_t FeeSta(void);
extern uint32_t FeeSign(uint32_t ulStartAddr, uint32_t ulEndAddr);
extern uint32_t FeeSig(void);
extern void FeeProTmp(uint64_t udKey, int32_t RdPro);
extern uint32_t FeeWrPro(uint64_t udKey);
extern uint32_t FeeFAKey(uint64_t udKey);
extern void FeeIntCfg(uint32_t Irq);
extern void FeeAuto(uint32_t Cfg);
extern int FeeClrCache(void);
extern void FeeIntAbt(uint32_t AEN0,uint32_t AEN1);
extern uint32_t FeeAbtAdr(void);


#ifdef __cplusplus
}
#endif

#endif   //#FEE_LIB_H

