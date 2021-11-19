/*!
 *****************************************************************************
 * @file:  CmpLib.h 
 * @brief: header of Analog comparator library
 *-----------------------------------------------------------------------------
 *
Copyright (c) 2013-2018 Analog Devices, Inc. All Rights Reserved.

This software is proprietary to Analog Devices, Inc. and its licensors.
By using this software you agree to the terms of the associated
Analog Devices Software License Agreement.
 ******************************************************************************/
#ifndef CMP_LIB_H
#define CMP_LIB_H

#ifdef __cplusplus
extern "C" {
#endif 

#include "ADuCM410.h"
   
#define ENUM_COMP0_POSIN_OFF        0
#define ENUM_COMP0_POSIN_AIN8       1
#define ENUM_COMP0_POSIN_PGA0       2
#define ENUM_COMP0_POSIN_GPIO0_6    3
#define ENUM_COMP1_POSIN_OFF        0
#define ENUM_COMP1_POSIN_AIN10       1
#define ENUM_COMP1_POSIN_PGA1       2
#define ENUM_COMP1_POSIN_GPIO0_7    3
#define ENUM_COMP2_POSIN_OFF        0
#define ENUM_COMP2_POSIN_AIN12       1
#define ENUM_COMP2_POSIN_PGA2       2
#define ENUM_COMP2_POSIN_GPIO2_0    3
#define ENUM_COMP3_POSIN_OFF        0
#define ENUM_COMP3_POSIN_AIN14       1
#define ENUM_COMP3_POSIN_PGA3       2
#define ENUM_COMP3_POSIN_GPIO2_1    3
   
#define ENUM_COMPx_NEGIN_OFF              0
#define ENUM_COMPx_NEGIN_AVDD_DIV2        1
#define ENUM_COMP0_NEGIN_AIN9            2
#define ENUM_COMP1_NEGIN_AIN11            2
#define ENUM_COMP2_NEGIN_AIN13            2
#define ENUM_COMP3_NEGIN_AIN15            2
#define ENUM_COMPx_NEGIN_VDAC8            3
#define ENUM_COMPx_NEGIN_VDAC9          4
#define ENUM_COMPx_NEGIN_VDAC10              5
#define ENUM_COMPx_NEGIN_VDAC11            6
#define ENUM_COMPx_NEGIN_1V25             7


typedef struct
{
   //Enable Comparator
   //0 - disable
   //1 - enable
   uint32_t cmp_en;
   
   //Comparator Positive Input Source
   //ENUM_COMPX_POSIN_xxx  defined above
   uint32_t cmp_input_pos;
   //Comparator Negative Input Source
   //ENUM_COMPx_NEGIN_OFF, defined above
   uint32_t cmp_input_neg;
   //Select Output Logic State
   //0 - no invert, output high if postive input higher than negtive input
   //1 - invert, output high if positive input lower than negtive input
   uint32_t cmp_invert;
   
   //Hysteresis Voltage
   //ENUM_COMP_COMPCON_N__HYS_DIS      hysteresis disabled 
   //ENUM_COMP_COMPCON_N__HYS_EN10MV   10mv hysteresis enabled 
   //ENUM_COMP_COMPCON_N__HYS_EN25MV   25mv hysteresis 
   //ENUM_COMP_COMPCON_N__HYS_EN35MV   35mv hysteresis 
   //ENUM_COMP_COMPCON_N__HYS_EN50MV   50mv hysteresis 
   //ENUM_COMP_COMPCON_N__HYS_EN60MV   60mv hysteresis 
   //ENUM_COMP_COMPCON_N__HYS_EN75MV   75mv hysteresis 
   //ENUM_COMP_COMPCON_N__HYS_EN85MV   85mv hysteresis 
   //ENUM_COMP_COMPCON_N__HYS_EN100MV  100mv hysteresis
   //ENUM_COMP_COMPCON_N__HYS_EN110MV  110mv hysteresis
   //ENUM_COMP_COMPCON_N__HYS_EN125MV  125mv hysteresis
   //ENUM_COMP_COMPCON_N__HYS_EN135MV  135mv hysteresis
   //ENUM_COMP_COMPCON_N__HYS_EN150MV  150mv hysteresis
   //ENUM_COMP_COMPCON_N__HYS_EN160MV  160mv hysteresis
   //ENUM_COMP_COMPCON_N__HYS_EN175MV  175mv hysteresis
   //ENUM_COMP_COMPCON_N__HYS_EN185MV  185mv hysteresis
   //ENUM_COMP_COMPCON_N__HYS_EN200MV  200mv hysteresis
   //ENUM_COMP_COMPCON_N__HYS_EN210MV  210mv hysteresis
   uint32_t cmp_hys;

//-----------Interrupt ----------
   //Interrupt Mode
   //ENUM_COMP_COMPCON_N__INTMODE_RISEEDGE  Generate Interrupt if Rising Edge Happens 
   //ENUM_COMP_COMPCON_N__INTMODE_FALLEDGE  Generate Interrupt if Falling Edge Happens 
   //ENUM_COMP_COMPCON_N__INTMODE_LOWLEVEL  Generate Interrupt if Low Level Happens 
   //ENUM_COMP_COMPCON_N__INTMODE_HIGHLEVEL Generate Interrupt if High Level Happens 
   uint32_t cmp_int_mode;
   //Interrupt Enable
   //0 - disable
   //1 - enable
   uint32_t cmp_int_en;
   uint32_t cmp_out;
}CMP_CONFIG_BITS_t;

typedef struct{
   CMP_CONFIG_BITS_t comp[4]; 
}CMP_SETUP_t;

extern CMP_SETUP_t gCmpSetup;

extern uint32_t CmpHysCfg(uint32_t CmpNum,uint32_t iHysVoltage);
extern uint32_t CmpEnable(uint32_t CmpNum, uint32_t iEn);
extern uint32_t CmpOutputCfg(uint32_t CmpNum, uint32_t iInvert, uint32_t iOut);
extern uint32_t CmpInputCfg(uint32_t CmpNum, uint32_t iInPos, uint32_t iInNeg);
extern uint32_t CmpIntCfg(uint32_t CmpNum, uint32_t iEn, uint32_t iMode);
extern void CmpSetup(const CMP_SETUP_t *pSetup);

#ifdef __cplusplus
}
#endif

#endif   //#CMP_LIB_H

