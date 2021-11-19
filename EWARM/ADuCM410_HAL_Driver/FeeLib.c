/*!
 *****************************************************************************
 * @file: FeeLib.h
 * @brief: library of flash block
 *-----------------------------------------------------------------------------
 *
Copyright (c) 2013-2018 Analog Devices, Inc. All Rights Reserved.

This software is proprietary to Analog Devices, Inc. and its licensors.
By using this software you agree to the terms of the associated
Analog Devices Software License Agreement.
 ******************************************************************************/

#include "FeeLib.h"

/**
   @brief uint32_t FeeMErs(uint32_t Block);
      ========== Performs a mass erase if the flash controller is not busy.
   @param Block :{0,1}
      - 0 Mass erase block 0
      - 1 Mass erase block 1
   @return 1 if the command was issued, 0 if the the flash controller was busy.
**/
uint32_t FeeMErs(uint32_t Block)
{
   if(pADI_FLASH->FEESTA&BITM_FLASH_FEESTA_CMDBUSY) return 0;
   pADI_FLASH->FEEKEY =  FLASH_USER_KEY;
   if(Block) pADI_FLASH->FEECMD = ENUM_FLASH_FEECMD_CMD_MASSERASE_PASSIVE;
   else       pADI_FLASH->FEECMD = ENUM_FLASH_FEECMD_CMD_MASSERASE_ACTIVE;
   return 1;
}

/**
   @brief uint32_t FeePErs(uint32_t lAddr);
      ========== Performs a page erase if the flash controller is not busy.

   @param lAddr :{0-0x3FFFF}
      - Specifies an address in the page to be erased
   @return 1 if the command was issued, 0 if the the flash controller was busy.
**/
uint32_t FeePErs(uint32_t lAddr)
{
   if(pADI_FLASH->FEESTA&BITM_FLASH_FEESTA_CMDBUSY) return 0;

   pADI_FLASH->FEEKEY =  FLASH_USER_KEY;
   pADI_FLASH->FEEADR0 = lAddr;
   pADI_FLASH->FEECMD = ENUM_FLASH_FEECMD_CMD_ERASEPAGE;
   return 1;
}

/**
   @brief uint32_t FeeWr(uint32_t lAddr, uint64_t udData)
      ========== Performs a 64 bit write if the flash controller is not busy.
   @param lAddr :{0-0x3FFFF}
      - Specifies the address to be written.
   @param udData :{0-0xFFFFFFFFFFFFFFFF}
      - Specifies the 64 bit data to be written.
   @return 1 if the command was issued, 0 if the the flash controller was busy.   
**/
uint32_t FeeWr(uint32_t lAddr, uint64_t udData)
{
   if(pADI_FLASH->FEESTA&BITM_FLASH_FEESTA_CMDBUSY) return 0;

   pADI_FLASH->FEEKEY =  FLASH_USER_KEY;
   pADI_FLASH->FEEFLADR = lAddr;
   pADI_FLASH->FEEFLDATA0 = (uint32_t)udData;
   pADI_FLASH->FEEFLDATA1 = udData>>32;
   pADI_FLASH->FEECMD = ENUM_FLASH_FEECMD_CMD_WRITE;
   return 1;
}

/**
   @brief uint32_t FeeSta(void);
      ========== Returns the status of the flash controller.
   @return value of FEESTA
      See User guide for bit descriptions.
**/
uint32_t FeeSta(void)
{
   return pADI_FLASH->FEESTA;
}

/**
   @brief uint32_t FeeSign(uint32_t ulStartAddr, uint32_t ulEndAddr);
   ========== Perform flash signature check.
   @param ulStartAddr :{0-0x3FFFF}
      - An address in the first page to be checked;
   @param ulEndAddr :{0-0x3FFFF}
      - An address in the last page to be checked;
   @return 1 if the command was issued, 0 if the the flash controller was busy.
**/
uint32_t FeeSign(uint32_t ulStartAddr, uint32_t ulEndAddr)
{
   if(pADI_FLASH->FEESTA&BITM_FLASH_FEESTA_CMDBUSY) return 0;
   
   pADI_FLASH->FEEADR0 = ulStartAddr;
   pADI_FLASH->FEEADR1 = ulEndAddr;
   pADI_FLASH->FEEKEY =  FLASH_USER_KEY;
   
   pADI_FLASH->FEECMD = ENUM_FLASH_FEECMD_CMD_SIGN;
   return 1;
}

/**
   @brief uint32_t FeeSig()
      ========== Return the flash signature calculated by the controller.
   @return FEESIG   
**/
uint32_t FeeSig(void)
{
   return pADI_FLASH->FEESIG;
}
  
/**
   @brief void FeeProTmp(uint64_t udKey, int32_t RdPro);
      ========== Temporarily enables write and/or read protection on the part.
            Write protection is disabled after a reset

   @param udKey :{0-0xFFFFFFFFFFFFFFFF}
      - Block 0 is write protected by clearing bit 0, Block 1 is write protected
      by clearing bit 1 and so forth for all 64 blocks
   @param RdPro : {FEECON1_DBG_EN|FEECON1_DBG_DIS}
      - 1 or FEECON1_DBG_EN to enable JTAG
      - 0 or FEECON1_DBG_DIS to disable JTAG and read protect the part
   @return 1
   @note If you only want to read protect the part udKey should be 0xFFFFFFFFFFFFFFFF
   @warning If you read protect a part you will lose debug access
**/    
void FeeProTmp(uint64_t udKey, int32_t RdPro)
{
   pADI_FLASH->FEEPRO0 = (udKey & 0xFFFFFFFF);
   pADI_FLASH->FEEPRO1 = udKey >> 32;
   pADI_FLASH->FEEKEY = FLASH_USER_KEY;
   if (RdPro)
      pADI_FLASH->FEECON1 |= BITM_FLASH_FEECON1_JTAGDEBUGEN;
   else
      pADI_FLASH->FEECON1 &= (~BITM_FLASH_FEECON1_JTAGDEBUGEN);
   pADI_FLASH->FEEKEY = 0;
}

/**
   @brief uint32_t FeeWrPro(uint64_t udKey)
         ========== Enables write protection on the part.
   @param udKey :{0-0xFFFFFFFFFFFFFFFF}
      - Block 0 is write protected by clearing bit 0, Block 1 is write protected
      by clearing bit 1 and so forth for all 64 blocks
   @return 1
   @note This function should be used for debugging. If protection is required during
         production the protection patterns should be stored within the executable image
   
**/
uint32_t FeeWrPro(uint64_t udKey)
{
   uint32_t i1;
   i1 = FeeWr(0x1FFF0, (udKey & 0xFFFFFFFF) | 0xFFFFFFFF00000000);
   if(!i1) 
      return 0;
   while(FeeSta()&1);
   i1 = FeeWr(0x3FFF0, (udKey>>32) | 0xFFFFFFFF00000000);
   if(!i1) 
      return 0;
   return 1;
}

/**
   @brief uint32_t FeeFAKey(uint64_t udKey);
         ========== Writes the FA key to a specific location.
   @param udKey :{0-0xFFFFFFFFFFFFFFFF}
      - This key is used for failure analysis.
   @return 1
   @note This function should be used for debugging. During production the keys should be stored 
         within the executable image
   
**/
uint32_t FeeFAKey(uint64_t udKey)
{
   uint32_t i1;
   i1 = FeeWr(0x1FFE8, (udKey & 0xFFFFFFFF) | 0xFFFFFFFF00000000);
   if(!i1) 
      return 0;
   while(FeeSta()&1);
   i1 = FeeWr(0x3FFE8, (udKey>>32) | 0xFFFFFFFF00000000);
   if(!i1) 
      return 0;
   return 1;
}

/**
   @brief uint32_t FeeIntCfg(uint32_t Irq);
      ========== Enables/Disables Flash Interrupt sources.

   @param Irq :{0|BITM_FLASH_FEECON0_IENCMD|BITM_FLASH_FEECON0_IWRALCOMP|BITM_FLASH_FEECON0_IENERR}
      - 1 or BITM_FLASH_FEECON0_IENCMD to enable command complete interrupts
      - 2 or BITM_FLASH_FEECON0_IWRALCOMP to enable write almost complete interrupts
      - 4 or BITM_FLASH_FEECON0_IENERR to enable command failed interrupts
   @return 1
   
**/   
void FeeIntCfg(uint32_t Irq)
{
   pADI_FLASH->FEECON0 = Irq;
}

/**
   @brief void FeeAuto(uint32_t Cfg);
      ========== Configures the amount of automation that the flash
                  flash controller will perform for write operations.

   @param Cfg :{0,FEECON1_KHDMA,FEECON1_INCR}
      - 0 to manually write to flash registers for flash writes
      - 2 or FEECON1_KHDMA to enable DMA support in the flash controller
      - 4 or FEECON1_INCR to automatically increment the destination address
   @return 1
   
**/  
void FeeAuto(uint32_t Cfg)
{
   uint32_t i1 = pADI_FLASH->FEECON1 & (~(BITM_FLASH_FEECON1_KHDMAEN|BITM_FLASH_FEECON1_AUTOINCREN));
   pADI_FLASH->FEEKEY = FLASH_USER_KEY;
   pADI_FLASH->FEECON1 = i1 | Cfg;
   pADI_FLASH->FEEKEY = 0;
}

///**
//   @brief int FeeClrCache();
//      ========== Clears enabled caches.
//
//   @return 1
//   @warning After the flash is modified if a reset isn't performed the
//            cache should be cleared using this function
//   
//**/  
//
//int FeeClrCache(void)
//{
//   unsigned long ulCACHESETUP = pADI_FLASH->CACHESETUP;
//   if ((ulCACHESETUP & 0x2) == 0x2)
//   {
//      pADI_FLASH->CACHEKEY = 0xf123f456;
//      pADI_FLASH->CACHESETUP |= 0x1;
//      while ((pADI_FLASH->CACHESTAT & 0x1) == 0x1)
//      {  }
//   }
//   if ((ulCACHESETUP & 0x20000) == 0x20000)
//   {
//      pADI_FLASH->CACHEKEY = 0xf123f456;
//      pADI_FLASH->CACHESETUP |= 0x10000;
//      while ((pADI_FLASH->CACHESTAT & 0x10000) == 0x10000)
//      {  }
//   }
//   pADI_FLASH->CACHEKEY = 0xf123f456;
//   pADI_FLASH->CACHESETUP = ulCACHESETUP;
//
//   return 1;
//}

/**
   @brief int FeeIntAbt(unsigned int iAEN0, unsigned int iAEN1);
         ========== Choose which interrupts can abort flash commands.

   @param iAEN0 :{}
   @param iAEN1 :{}
   @return 1
   
**/
void FeeIntAbt(uint32_t AEN0,uint32_t AEN1)
{
   pADI_FLASH->FEEAEN0 = AEN0;
   pADI_FLASH->FEEAEN1 = AEN1;
}

/**
   @brief int FeeAbtAdr();
         ========== Return the address of the location written when the write was aborted.
   @return pADI_FLASH->FEEWRADDRA
**/
uint32_t FeeAbtAdr(void)
{
   return pADI_FLASH->FEEWRADDRA;
}

/*
@brief void FeeSetup(FLASH_SETUP_t *setup)
      =========== setup for flash
@param setup: pointer to FLASH_SETUP_t
@return none
**/
void FeeSetup(FLASH_SETUP_t *pFlashSetup)
{
    uint32_t regFlashCon0,regFlashCon1;

    regFlashCon0 = (pFlashSetup->cmdCompleteIntEn<<BITP_FLASH_FEECON0_IENCMD)   \
                   |(pFlashSetup->wrCompleteIntEn<<BITP_FLASH_FEECON0_IWRALCOMP)    \
                   |(pFlashSetup->cmdFailIntEn<<BITP_FLASH_FEECON0_IENERR);

   regFlashCon1 = (pFlashSetup->jtagEn<<BITP_FLASH_FEECON1_JTAGDEBUGEN) \
                  |(pFlashSetup->keyHoleDmaEn<<BITP_FLASH_FEECON1_KHDMAEN)    \
                  |(pFlashSetup->keyHoleAutoInc<<BITP_FLASH_FEECON1_AUTOINCREN)     \
                  |(pFlashSetup->mdioSwapEn<<BITP_FLASH_FEECON1_SWAPPROGRAMCODE)    \
                  |(pFlashSetup->mdioModeEn<<BITP_FLASH_FEECON1_MDIOMODE)     \
                  |(pFlashSetup->SwapFlash0<<BITP_FLASH_FEECON1_SWAPFLASH0)     \
                  |(pFlashSetup->SwapFlash1<<BITP_FLASH_FEECON1_SWAPFLASH1)     \
                  |(pFlashSetup->flashSwapEn<<BITP_FLASH_FEECON1_SWAPINFLASHEN);
   pADI_FLASH->FEECON0 = regFlashCon0;
   pADI_FLASH->FEECON1 = regFlashCon1;
   pADI_FLASH->FEEAEN0 = pFlashSetup->intAbort[0];
   pADI_FLASH->FEEAEN1 = pFlashSetup->intAbort[1];
   pADI_FLASH->FEEAEN2 = pFlashSetup->intAbort[2];
}

/**@}*/
