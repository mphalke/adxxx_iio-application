/*!
 *****************************************************************************
 * @file:   
 * @brief:  
 *-----------------------------------------------------------------------------
 *
Copyright (c) 2013-2018 Analog Devices, Inc. All Rights Reserved.

This software is proprietary to Analog Devices, Inc. and its licensors.
By using this software you agree to the terms of the associated
Analog Devices Software License Agreement.
 ******************************************************************************/
#include "ADuCM410.h"


//------------------------ Macros ---------------------------------
#define EXTINT0 0x0 
#define EXTINT1 0x1 
#define EXTINT2 0x2 
#define EXTINT3 0x3 
#define EXTINT4 0x4 
#define EXTINT5 0x5 
#define EXTINT6 0x6 
#define EXTINT7 0x7
#define EXTINT8 0x8

//iEnable in EiCfg()	
#define INT_DIS	0x0	
#define INT_EN    0x1

//iMode in EiCfg()	
#define INT_RISE  0x0	
#define INT_FALL  0x1
#define INT_EDGES 0x2
#define INT_HIGH  0x3
#define INT_LOW	0x4	

#define EXT_INT_CHAN_NUM   10

typedef struct
{
   //ENUM_ALWAYS_ON_EI0CFG_IRQ0MDE_RISE          Rising Edge 
   //ENUM_ALWAYS_ON_EI0CFG_IRQ0MDE_FALL          Falling Edge 
   //ENUM_ALWAYS_ON_EI0CFG_IRQ0MDE_RISEORFALL    Rising or Falling Edge 
   //ENUM_ALWAYS_ON_EI0CFG_IRQ0MDE_HIGHLEVEL     High Level 
   //ENUM_ALWAYS_ON_EI0CFG_IRQ0MDE_LOWLEVEL      Low Level 
   uint32_t irqMode;
   
   //1 - enable external interrupt
   //0 - disable
   uint32_t irqEn;
   
}EXINT_CHAN_SETUP_Type;

typedef struct
{
   EXINT_CHAN_SETUP_Type exIntChan[EXT_INT_CHAN_NUM];
}EXINT_SETUP_Type;

extern EXINT_SETUP_Type gExIntSetup;

//------------------------------ Function API --------------------------
extern void ExIntSetup(EXINT_SETUP_Type * const setup);

extern void EiCfg(uint32_t EiNr,uint32_t Enable, uint32_t Mode);
extern void  EiClr(uint32_t EiNr);
