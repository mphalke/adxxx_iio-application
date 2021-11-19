/*!
 *****************************************************************************
 * @file:   CrcLib.c
 * @brief:  source file of CRC library
 *-----------------------------------------------------------------------------
 *
Copyright (c) 2013-2018 Analog Devices, Inc. All Rights Reserved.

This software is proprietary to Analog Devices, Inc. and its licensors.
By using this software you agree to the terms of the associated
Analog Devices Software License Agreement.
 ******************************************************************************/

#include "CrcLib.h"

/*
@brief void CrcSetup(const CRC_SETUP_t * pSetup)
      =========== setup for CRC calcalation
 
@param pSetup: pointer to crc setup configuration
@return none
**/
void CrcSetup(const CRC_SETUP_t * pSetup)
{
   uint32_t reg_poly,reg_seed,reg_ctl;
   uint32_t shiftBits;
   
   shiftBits = (pSetup->poly>>8) ? ((pSetup->poly>>16)? ((pSetup->poly>>24)?0:8) :16 ):24;
   if(pSetup->LSB_First)
   {
      reg_poly = pSetup->poly;
      reg_seed = pSetup->seed;
   }
   else
   {
      reg_poly = (pSetup->poly)<<shiftBits;
      reg_seed = (pSetup->seed)<<shiftBits;
   }
   reg_ctl  = (pSetup->LSB_First<<BITP_CRC_CTL_LSBFIRST)|\
               (pSetup->bitSwap<<BITP_CRC_CTL_BITMIRR)|\
               (pSetup->byteSwap<<BITP_CRC_CTL_BYTMIRR)|\
               (pSetup->hwordSwap<<BITP_CRC_CTL_W16SWP);

   pADI_CRC->POLY = reg_poly;
   pADI_CRC->RESULT = (int32_t)reg_seed;
   pADI_CRC->CTL = reg_ctl;
}

/*
@brief uint32_t  hw_crc32(uint32_t inputData)
      =========== do single cra32 and get result, requires setup CRC first
@param inputData: input data used for crc32 calculation
@return calculated result
**/
uint32_t  hw_crc32(uint32_t inputData)
{
   pADI_CRC->IPDATA = (int32_t)inputData;
   return (uint32_t)(pADI_CRC->RESULT);
}




//--------------- software crc used for verification ---------------------------
/*
@brief uint8_t sw_crc8(uint8_t inputByte, uint8_t seed, uint8_t poly)
      =========== software crc8 generator
 
@param inputByte: input data to crc
@param seed: seed used to initialize crc. normally set to 0
@param poly: crc algorithom used for calculation
@return none
**/
uint8_t sw_crc8(uint8_t *inputBytes, uint32_t len, uint8_t seed, uint8_t poly)
{
   uint8_t crc;
   uint32_t i,j;
   uint8_t *p = inputBytes;

   crc = seed;
   for(j=0;j<len;j++)
   {
      crc = crc ^ (*p++);
      for(i=0;i<8;i++)
      {
         if(crc & 0x80)
         {
            crc = (uint8_t)((crc<<1) ^ poly);
         }
         else
         {
            crc <<= 1;
         }
      }
   }
   return crc;
}

uint16_t sw_crc16(uint16_t *inputBytes, uint32_t len, uint16_t seed, uint16_t poly)
{
   uint16_t crc;
   uint32_t i,j;
   uint16_t *p = inputBytes;

   crc = seed;
   for(j=0;j<len;j++)
   {
      crc = crc ^ (*p++);
      for(i=0;i<16;i++)
      {
         if(crc & 0x8000)
         {
            crc = (uint16_t)((crc<<1) ^ poly);
         }
         else
         {
            crc <<= 1;
         }
      }
   }
   return crc;
}

uint32_t sw_crc32(uint32_t *inputBytes, uint32_t len, uint32_t seed, uint32_t poly)
{
   uint32_t crc;
   uint32_t i,j;
   uint32_t *p = inputBytes;

   crc = seed;
   for(j=0;j<len;j++)
   {
      crc = crc ^ (*p++);
      for(i=0;i<32;i++)
      {
         if(crc & 0x80000000)
         {
            crc = (uint32_t)((crc<<1) ^ poly);
         }
         else
         {
            crc <<= 1;
         }
      }
   }
   return crc;

}

