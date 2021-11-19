/*!
 *****************************************************************************
 * @file:  MdLib.h 
 * @brief: header of MDIO interface
 *-----------------------------------------------------------------------------
 *
Copyright (c) 2013-2018 Analog Devices, Inc. All Rights Reserved.

This software is proprietary to Analog Devices, Inc. and its licensors.
By using this software you agree to the terms of the associated
Analog Devices Software License Agreement.
 ******************************************************************************/
#ifndef MDIO_LIB_H
#define MDIO_LIB_H

#ifdef __cplusplus
extern "C" {
#endif 

#include "ADuCM410.h"

typedef struct
{
   //MDIO Enable
   uint32_t mdEn;
   //Enable Open-drain or Push-pull of MDIO Drive
   //0- ENUM_MDIO_MDCON_MD_DRV_MD_DRV_OD      /* MDIO Drive Open Drain. */
   //1- ENUM_MDIO_MDCON_MD_DRV_MD_DRV_PP      /* MDIO Drive Push-pull. */
   uint32_t mdDrive;
   //Enable PHY Address Bit Width
   //0- ENUM_MDIO_MDCON_MD_PHM_EN_5BIT        /* 5bits PHYADD is active */
   //1- ENUM_MDIO_MDCON_MD_PHM_EN_3BITS       /* 3bits PHYADD is active, two MSBS are ignored */
   uint32_t mdPhyWidth;
   //Expected device address. Normally 01.
   uint32_t mdDevAddr;
   //Selects Expected PHYADR Bits. For each of the 5 bits
   //for 5bit MDIO address, each bit can be configured by hardware pin or software register
   //b'00000: each address bit PHYADR.x = PRTADRx pin. 
   //b'11111: each address bit PHYADR.x = MD_PHYSW.x.
   uint32_t mdPhySel;
   //Software Provided PHYADR. 
   //Chosen according to corresponding MD_PHYSEL.
   uint32_t mdSwAddr;
   //PADDR[4:0] PE Control 
   //default value is 0x1F
   uint32_t mdPaddrPe;

//-----------------Interrupt --------------
   //Interrupt Enable for MD_PHYN.
   //If set, interrupt will be requested when PHY Address is Non-Matching.
   uint32_t mdPhyNonMatchIen;
   //Interrupt Enable for MD_PHYM.
   //If set, interrupt will be requested when PHY Address is Matching.
   uint32_t mdPhyMatchIen;
   //Interrupt Enable for MD_DEVN.
   //If set, interrupt will be requested when Device Address is Non-Matching.
   uint32_t mdDevNonMatchIen;
   //Interrupt Enable for MD_DEVM.
   //If set, interrupt will be requested when Device Address is Matching.
   uint32_t mdDevMatchIen;
   //Interrupt Enable for MD_RDF.
   //If set, interrupt will be requested at end of Read frame.
   uint32_t mdReadIen;
   //Interrupt Enable for MD_INCF.
   //If set, interrupt will be requested at end of PostReadIncAdd frame.
   uint32_t mdIncReadIen;
   //Interrupt Enable for MD_ADRF.
   //If set interrupt will be requested at end of Address frame.
   uint32_t mdAddressIen;
   //Interrupt Enable for MD_WRF.
   //If set, interrupt will be requested at end of write frame.
   uint32_t  mdWriteIen;
   
}MDIO_SETUP_t;

extern MDIO_SETUP_t gMdioSetup;
// =================================== Function API =====================
   
extern uint32_t MdInit(uint32_t iPhySz, uint32_t iRst, uint32_t iDrvPp);
extern uint32_t MdOn(uint32_t iOn, uint32_t iRst, uint32_t iDrvPp);
extern uint32_t MdCfg(uint32_t iPhyAdr, uint32_t iPASel, uint32_t iDevAdd);
extern uint32_t MdRxd(void);
extern uint32_t MdTxd(uint32_t iTxDat);
extern uint32_t MdAdr(void);
extern uint32_t MdPin(void);
extern uint32_t MdSta(void);
extern uint32_t MdRdI(void);
extern uint32_t MdIen(uint32_t iMdIEn);
extern uint32_t MdFrm(void);

extern void MdSetup(const MDIO_SETUP_t *pSetup);




#ifdef __cplusplus
}
#endif

#endif   //#MDIO_LIB_H
