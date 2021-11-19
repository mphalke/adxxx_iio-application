/*!
 *****************************************************************************
 * @file:   MdLib.c
 * @brief:  library for MDIO interface
 *-----------------------------------------------------------------------------
 *
Copyright (c) 2013-2018 Analog Devices, Inc. All Rights Reserved.

This software is proprietary to Analog Devices, Inc. and its licensors.
By using this software you agree to the terms of the associated
Analog Devices Software License Agreement.
 ******************************************************************************/

#include "MdLib.h"

/**
   @brief uint32_t MdInit(uint32_t iPhySz, uint32_t iRst, uint32_t iDrvPp)   
      ==========Optionally resets then sets PHYADR size and MDIO pin mode.
   @param iPhySz :{3,5}
      - 3 to set PHYADR size to 3.
      - 5 to set PHYADR size to default of 5.
   @param iRst :{0,1}
      - 0 does not cause a reset.
      - 1 resets the MDIO hardware. Bit clears automatically.
   @param iDrvPp :{0,1}
      - 0 Sets pin to default of open drain.
      - 1 Sets MDIO as push-pull.
   @return 1.
**/

uint32_t MdInit(uint32_t iPhySz, uint32_t iRst, uint32_t iDrvPp)
{
   uint32_t i1;
   i1 = (pADI_MDIO->MDCON &(~(BITM_MDIO_MDCON_MD_RST | BITM_MDIO_MDCON_MD_PHM | BITM_MDIO_MDCON_MD_DRV)));

   i1 |= (iRst!=0);
   i1 |= (iDrvPp << BITP_MDIO_MDCON_MD_DRV);
   i1 |=((uint32_t)(iPhySz==3) << BITP_MDIO_MDCON_MD_PHM);
   
   pADI_MDIO->MDCON = (uint16_t)i1;
   return 1;
}

/**
   @brief uint32_t MdOn(uint32_t iOn, uint32_t iRst, uint32_t iDrvPp)   
      ==========Switches MDIO off/on in selected mode.
   @param iOn :{0,1}
      -0 to switch MDIO off.
      -1 to switch MDIO on.
   @param iRst :{0,1}
      - 0 does not cause a reset.
      - 1 resets the MDIO hardware.
   @param iDrvPp :{0,1}
      - 0 Sets pin to default of open drain.
      - 1 Sets MDIO as push-pull.
   @return iOn.
   @warning Use for revision S1 silicon only. Else use MdInit().
**/

uint32_t MdOn(uint32_t iOn, uint32_t iRst, uint32_t iDrvPp)
{
   uint32_t i1;
   i1 = (pADI_MDIO->MDCON &(~(BITM_MDIO_MDCON_MD_RST | BITM_MDIO_MDCON_MD_DRV | BITM_MDIO_MDCON_MD_EN)));
   


   i1 |= (iRst!=0);
   i1 |= (iDrvPp << BITP_MDIO_MDCON_MD_DRV);
   i1 |= (iOn << BITP_MDIO_MDCON_MD_EN);
   
   pADI_MDIO->MDCON = (uint16_t)i1;
   
   return (uint32_t)!((pADI_MDIO->MDCON & BITM_MDIO_MDCON_MD_EN) >> BITP_MDIO_MDCON_MD_EN);
}

/**
   @brief uint32_t MdCfg(uint32_t iPhyAdr, uint32_t iPASel, uint32_t iDevAdd)   
         ==========Configures MDIO for communications.
   @param iPhyAdr :{0-31}
      - Software supplied PHYADR bits.
   @param iPASel :{0-31}
      - For each of the 5 bits:
      - 0 selects corresponding bit from PRTADR pins for PHYADR.
      - 1 selects corresponding bit from iPhyAdr for PHYADR.
   @param iDevAdd :{0-31}
      - DEVADD that the device will respond to.  
   @return The PHYADR that the device will respond to.
   @warning Changing PRTADR pins will change PHYADR.
          For CFP only 1 is valid for DEVADD.
**/

uint32_t MdCfg(uint32_t iPhyAdr, uint32_t iPASel, uint32_t iDevAdd)
{
   pADI_MDIO->MDPHY = (uint16_t)(iPhyAdr | (iPASel << BITP_MDIO_MDPHY_MD_PHYSEL) | (iDevAdd << BITP_MDIO_MDPHY_MD_DEVADD));
   return (pADI_MDIO->MDPIN & (~iPASel) ) | (iPhyAdr & iPASel);
}

/**
   @brief uint32_t MdRxd(void)   
         ==========Reads data supplied by MDIO frame.
   @return The MDRXD value from the last MDIO data frame.
   @warning None
**/

uint32_t MdRxd(void)
{
   return pADI_MDIO->MDRXD;
}

/**
   @brief uint32_t MdTxd(uint32_t iTxDat)   
         ==========Writes data to transmit by MDIO frame.
   @param iTxDat :{0-65535}
      - Data to send on MDIO.
   @return iTxDat.
   @warning None
**/

uint32_t MdTxd(uint32_t iTxDat)
{
   pADI_MDIO->MDTXD = (uint16_t)iTxDat;
   return iTxDat;
}

/**
   @brief uint32_t MdAdr(void)   
         ==========Reads address supplied by MDIO frame.
   @return The address supplied by the most recent MDIO address frame.
   @warning None.
**/

uint32_t MdAdr(void)
{
   return pADI_MDIO->MDADR;
}

/**
   @brief uint32_t MdPin(void)   
         ==========Reads the PRTADR pins.
   @return The PRTADR pins.
   @warning None
**/

uint32_t MdPin(void)
{
   return pADI_MDIO->MDPIN;
}

/**
   @brief uint32_t MdSta(void)   
         ==========Reads the MDIO frame status.
   @return Frame status bits.
      - Bit0 Set at end of Write frame.
      - Bit1 Set at end of Address frame.
      - Bit2 Set at end of PostReadIncAdd frame.
      - Bit3 Set at end of Read frame.
      - Bit4 Set at end of matching PHYADR.
      - Bit5 Set at end of non-matching PHYADR.
      - Bit6 Set at end of DEVADD if PHYADR and DEVADD matching.
      - Bit7 Set at end of DEVADD if PHYADR or DEVADD non-matching.
   @warning All status bit are reset by this function.
**/

uint32_t MdSta(void)
{
   return pADI_MDIO->MDSTA;
}

/**
   @brief uint32_t MdRdI(void)   
         ==========Reads interupt enable bits.
   @return Interrupt enable bits.
      - Bit0 Enables Write frame interrupt.
      - Bit1 Enables Address interrupt.
      - Bit2 Enables PostReadIncAdd interrupt.
      - Bit3 Enables Read interrupt.
      - Bit4 Enables matching PHYADR interrupt.
      - Bit5 Enables non-matching PHYADR interrupt.
      - Bit6 Enables PHYADR and DEVADD matching interrupt.
      - Bit7 Enables PHYADR or DEVADD non-matching interrupt.
   @warning None.
**/

uint32_t MdRdI(void)
{
   return pADI_MDIO->MDIEN;
}

/**
   @brief uint32_t MdIen(uint32_t iMdIEn)   
         ==========Writes interupt enable bits.
   @param iMdIEn :{0|BITM_MDIO_MDIEN_MD_WRFI|BITM_MDIO_MDIEN_MD_ADRI|BITM_MDIO_MDIEN_MD_INCFI|BITM_MDIO_MDIEN_MD_RDFI
                   |BITM_MDIO_MDIEN_MD_PHYMI|BITM_MDIO_MDIEN_MD_PHYNI|BITM_MDIO_MDIEN_MD_DEVMI|BITM_MDIO_MDIEN_MD_DEVNI}
      - Set bits to enable sources as listed below:
        - 0 for no interrupt.
      - 1 or BITM_MDIO_MDIEN_MD_WRFI Enables Write frame interrupt.
      - 2 or BITM_MDIO_MDIEN_MD_ADRI Enables Address interrupt.
      - 4 or BITM_MDIO_MDIEN_MD_INCFI Enables PostReadIncAdd interrupt.
      - 8 or BITM_MDIO_MDIEN_MD_RDFI Enables Read interrupt.
      - 0x10 or BITM_MDIO_MDIEN_MD_DEVMI Enables PHYADR and DEVADD matching interrupt.
      - 0x20 or BITM_MDIO_MDIEN_MD_DEVNI Enables PHYADR or DEVADD non-matching interrupt.
      - 0x40 or BITM_MDIO_MDIEN_MD_PHYMI Enables matching PHYADR interrupt.
      - 0x80 or BITM_MDIO_MDIEN_MD_PHYNI Enables non-matching PHYADR interrupt.
   @return MDIEN.
   @warning None.
**/

uint32_t MdIen(uint32_t iMdIEn)
{
   pADI_MDIO->MDIEN = (uint16_t)iMdIEn;
   return pADI_MDIO->MDIEN;
}

/**
   @brief uint32_t MdFrm(void)   
         ==========Gets details of last frame received.
   @return Received frame details as follows:
      - Bit0 and 1 Give OP of frame.
            - 0 or MD_OP_ADF = Address frame
            - 1 or MD_OP_WRF = Write frame
            - 2 or MD_OP_RDF = Read frame
            - 3 or MD_OP_INCF = PostReadIncAdd frame
      - Bits 2 to 6 give received PHYADR.
      - Bit7 to 11 give received DEVADD.
   @warning None.
**/

uint32_t MdFrm(void)
{
   return pADI_MDIO->MDFRM;
}

/*
   @brief void MdSetup(const MD_SETUP_t *pSetup)
      =========== write value of MDIO setup structure to device
   @param pSetup: pointer to MDIO setup structure
**/
void MdSetup(const MDIO_SETUP_t *pSetup)
{
   pADI_MDIO->MDCON = 0;
   pADI_MDIO->MDCON |= (uint16_t)((pSetup->mdPhyWidth << BITP_MDIO_MDCON_MD_PHM) | (pSetup->mdDrive << BITP_MDIO_MDCON_MD_DRV));
   pADI_MDIO->MDPHY = (uint16_t)((pSetup->mdDevAddr << BITP_MDIO_MDPHY_MD_DEVADD) |\
                           (pSetup->mdPhySel << BITP_MDIO_MDPHY_MD_PHYSEL) | pSetup->mdSwAddr);
   
   pADI_MDIO->MDIEN = (uint16_t)((pSetup->mdPhyNonMatchIen << BITP_MDIO_MDIEN_MD_PHYNI) |\
                           (pSetup->mdPhyMatchIen << BITP_MDIO_MDIEN_MD_PHYMI) |\
                           (pSetup->mdDevNonMatchIen << BITP_MDIO_MDIEN_MD_DEVNI) |\
                           (pSetup->mdDevMatchIen << BITP_MDIO_MDIEN_MD_DEVMI) |\
                           (pSetup->mdReadIen << BITP_MDIO_MDIEN_MD_RDFI) | \
                           (pSetup->mdIncReadIen << BITP_MDIO_MDIEN_MD_INCFI) |\
                           (pSetup->mdAddressIen << BITP_MDIO_MDIEN_MD_ADRI) | pSetup->mdWriteIen );

   pADI_MDIO->MDCON |= (pSetup->mdEn << BITP_MDIO_MDCON_MD_EN);
}


/**@}*/

