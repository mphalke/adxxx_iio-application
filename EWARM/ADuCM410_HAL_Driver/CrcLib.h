/*!
 *****************************************************************************
 * @file:  CrcLib.h 
 * @brief: header of CRC 
 *-----------------------------------------------------------------------------
 *
Copyright (c) 2013-2018 Analog Devices, Inc. All Rights Reserved.

This software is proprietary to Analog Devices, Inc. and its licensors.
By using this software you agree to the terms of the associated
Analog Devices Software License Agreement.
 ******************************************************************************/
#ifndef CRC_LIB_H
#define CRC_LIB_H

#ifdef __cplusplus
extern "C" {
#endif 

#include "ADuCM410.h"

#define CRC8_POLY 0x07u
#define CRC16_POLY 0x1021u
#define CRC24_POLY 0x800063u
#define CRC32_POLY 0x04C11DB7u


typedef struct
{
   //algorithm polynomial used in crc calculation
   uint32_t poly;
   //initial seed used in crc calculation
   uint32_t seed;
   //0 - MSB first
   //1 - LSB first
   uint32_t LSB_First;
   //0 - no bit mirror
   //1 - each bit within each byte is swapped
   uint32_t bitSwap;
   //0 - no byte mirror
   //1 - byte swapped within each word
   uint32_t byteSwap;
   //0 - no hword swap
   //1 - half word swap within each word
   uint32_t hwordSwap;
}CRC_SETUP_t;

extern CRC_SETUP_t gCrcSetup;

//----------------- Function declarations -------------
extern void CrcSetup(const CRC_SETUP_t * pSetup);
extern uint32_t  hw_crc32(uint32_t inputData);
extern uint32_t  crcDma(uint8_t *startAddr, uint32_t len);

#define CrcEnable()  do{   \
                        pADI_CRC->CTL |= BITM_CRC_CTL_EN;\
                        }while(0)   

#define CrcDisable()  do{   \
                        pADI_CRC->CTL &= ~BITM_CRC_CTL_EN;\
                        }while(0) 

#define hw_crc24(inputdata)   ((pADI_CRC->CTL & BITM_CRC_CTL_LSBFIRST) ? hw_crc32(inputdata)\
                              :(hw_crc32(inputdata)>>8))
                              
#define hw_crc16(inputdata)   ((pADI_CRC->CTL & BITM_CRC_CTL_LSBFIRST) ? hw_crc32(inputdata)\
                              :(hw_crc32(inputdata)>>16))

#define hw_crc8(inputdata)   ((pADI_CRC->CTL & BITM_CRC_CTL_LSBFIRST) ? hw_crc32(inputdata)\
                              :(hw_crc32(inputdata)>>24))

/*
   Functions used to help verify hardware CRC
*/
extern uint8_t sw_crc8(uint8_t *inputBytes, uint32_t len, uint8_t seed, uint8_t poly);
extern uint16_t sw_crc16(uint16_t *inputBytes, uint32_t len, uint16_t seed, uint16_t poly);
extern uint32_t sw_crc32(uint32_t *inputBytes, uint32_t len, uint32_t seed, uint32_t poly);


#ifdef __cplusplus
}
#endif

#endif   //#CRC_LIB_H

