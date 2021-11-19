/*!
 *****************************************************************************
 * @file: I2cLib.h
 * @brief: source file of I2C library
 *-----------------------------------------------------------------------------
 *
Copyright (c) 2013-2018 Analog Devices, Inc. All Rights Reserved.

This software is proprietary to Analog Devices, Inc. and its licensors.
By using this software you agree to the terms of the associated
Analog Devices Software License Agreement.
 ******************************************************************************/

#include	"I2cLib.h"


//-------------------------- Common functions used for both master and slave-------

/**
   @brief uint32_t I2cRx(ADI_I2C_TypeDef *pI2C,uint32_t Mode)
			========== Reads 8 bits of MRX or SRX
   @param pI2C :{pADI_I2C0,pADI_I2C1,pADI_I2C2}
		- pADI_I2C0 for I2C0.
		- pADI_I2C1 for I2C1 
            - pADI_I2C2 for I2C2 
   @param Mode :{MASTER, SLAVE}
		- 0 or MASTER for I2C Master operation.
		- 1 or SLAVE for I2C Slave operation.
   @return SRX or MRX 
**/
uint32_t I2cRx(ADI_I2C_TypeDef *pI2C,uint32_t Mode)
{
  if (Mode == SLAVE)
  {
    return pI2C->SRX; 
  }
  else
  {
    return pI2C->MRX; 
  }
}

/**
   @brief void I2cTx(ADI_I2C_TypeDef *pI2C,uint32_t Mode, uint32_t Tx)
			========== Write 8 bits of iTx to I2CMTX ro I2CSTX
   @param pI2C :{pADI_I2C0,pADI_I2C1,pADI_I2C2}
		- pADI_I2C0 for I2C0.
		- pADI_I2C1 for I2C1 
            - pADI_I2C2 for I2C2 
   @param iMode :{MASTER, SLAVE}
		- 0 or MASTER for I2C Master operation.
		- 1 or SLAVE for I2C Slave operation.
   @param Tx :{0-255}	\n
		Byte to transmit.
		when mode is SLAVE, SFIFO_ID0|SFIFO_ID1|SFIFO_ID2|SFIFO_ID3 can use combined with Tx byte
   @return none
   //I2C has 2 byte FIFO for Tx
**/
void I2cTx(ADI_I2C_TypeDef *pI2C,uint32_t Mode, uint32_t Tx)
{
  if (Mode == SLAVE)
    pI2C->STX = (uint16_t)Tx; 
  else
    pI2C->MTX = (uint16_t)Tx; 
}

/**
   @brief void I2cFifoTx(ADI_I2C_TypeDef *pI2C,uint32_t fifoID, uint32_t Tx)
			========== Write 8 bits of iTx to I2CMTX ro I2CSTX
   @param pI2C :{pADI_I2C0,pADI_I2C1,pADI_I2C2}
		- pADI_I2C0 for I2C0.
		- pADI_I2C1 for I2C1 
            - pADI_I2C2 for I2C2 
   @param fifoID :{SFIFO_ID0, SFIFO_ID1,SFIFO_ID2,SFIFO_ID3}
   @param Tx :{0-255}	\n
		Byte to transmit.
   @return none
   //I2C has 2 byte FIFO for Tx
**/
void I2cFifoTx(ADI_I2C_TypeDef *pI2C,uint32_t fifoID, uint32_t Tx)
{
    pI2C->STX = (uint16_t)(fifoID|Tx); 
}

/**
   @brief void I2cBaud(ADI_I2C_TypeDef *pI2C,uint32_t Prescale, uint32_t HighPeriod, uint32_t LowPeriod)
	========== Set the I2C clock rate in Master mode - CLKCON1 setting not accounted for

	@brief HighPeriod configures the Master Clock high period               \n
	@brief LowPeriod configures the Master Clock low period            \n
   @param pI2C :{pADI_I2C0,pADI_I2C1,pADI_I2C2}
		- pADI_I2C0 for I2C0.
		- pADI_I2C1 for I2C1 
            - pADI_I2C2 for I2C2
   @param Prescale: {0~7} 
   @param HighPeriod :{0-255}                                       \n
   @param iLowPeriod :{0-255}	                             \n
   @return none
   @note I2C scl clock = PCLK/(Prescale+1)/(highperid+lowPeriod)
**/
void I2cBaud(ADI_I2C_TypeDef *pI2C,uint32_t Prescale, uint32_t HighPeriod, uint32_t LowPeriod)
{
   uint32_t regTCTL,regDiv;

   regTCTL = pI2C->TCTL&(~BITM_I2C_TCTL_PRE_DIV);
   regTCTL |= Prescale<<BITP_I2C_TCTL_PRE_DIV;
   regDiv =  LowPeriod|(HighPeriod<<BITP_I2C_DIV_HIGH);
   pI2C->TCTL = (uint16_t)regTCTL;
   pI2C->DIV = (uint16_t)regDiv;
}

//---------------------------------- Master related functions --------------
/**
   @brief void I2cMCfg(ADI_I2C_TypeDef *pI2C, uint32_t DMACfg, uint32_t IntSources, uint32_t Config)
			========== Configure the I2C master channel.
   @param pI2C :{pADI_I2C0,pADI_I2C1，pADI_I2C2}
		- pADI_I2C0 for I2C0.
		- pADI_I2C1 for I2C1 
            - pADI_I2C2 for I2C2 
   @param DMACfg :{0|BITM_I2C_MCTL_MTXDMA|BITM_I2C_MCTL_MRXDMA} \n
		- 0 by default to disable all DMA operation.
		- BITM_I2C_MCTL_MTXDMA to enable I2C Master Tx DMA requests.
		- BITM_I2C_MCTL_MRXDMA to enable I2C Master Rx DMA requests.
   @param IntSources :{0|BITM_I2C_MCTL_IENCMP|BITM_I2C_MCTL_IENACK|BITM_I2C_MCTL_IENALOST|BITM_I2C_MCTL_IENMTX|BITM_I2C_MCTL_IENMRX} \n		 
		- 0 by default to disable all interrupt sources.
		- BITM_I2C_MCTL_IENCMP to enable interrupts when a Stop condition is detected. 
		- BITM_I2C_MCTL_IENACK to enable interrupts when a NACK is detected. 
		- BITM_I2C_MCTL_IENALOST to enable interrupts when bus arbitration is lost. 
		- BITM_I2C_MCTL_IENMTX to enable Transmit interrupts.
		- BITM_I2C_MCTL_IENMRX to enable Receive interrupts. 
   @param Config :{0|BITM_I2C_MCTL_LOOPBACK|BITM_I2C_MCTL_COMPETE|BITM_I2C_MCTL_MASEN|BITM_I2C_MCTL_HS_MODE_EN}	\n
		- 0 by default.
		- BITM_I2C_MCTL_LOOPBACK to enable I2C loopback mode. I2CMCON_LOOPBACK_DIS by default.
		- BITM_I2C_MCTL_COMPETE to enable I2C Master to compete for control of bus. I2CMCON_COMPETE_DIS by default.
		- BITM_I2C_MCTL_MASEN to enable I2C Master mode. I2CMCON_MASEN_DIS by default.
            - BITM_I2C_MCTL_HS_MODE_EN to enable high speed mode 
**/

void I2cMCfg(ADI_I2C_TypeDef *pI2C, uint32_t DMACfg, uint32_t IntSources, uint32_t Config)
{
  uint32_t i1;
	  
  i1 = DMACfg;
  i1 |= IntSources;
  i1 |= Config;
  pI2C->MCTL = (uint16_t)i1; 
}


/**
   @brief void I2cMWrCfg(ADI_I2C_TypeDef *pI2C,uint32_t uiDevAddr)
		========== Configure I2CADR0/I2CADR1 - Device address register.
   @param pI2C :{pADI_I2C0,pADI_I2C1,pADI_I2C2}
		- pADI_I2C0 for I2C0.
		- pADI_I2C1 for I2C1 
            - pADI_I2C2 for I2C2
   @param uiDevAddr :{0-1023}     \n
   @ This function write uiDevAddr to I2CADR0 address, lsb =0
   @return none
**/
void I2cMWrCfg(ADI_I2C_TypeDef *pI2C,uint32_t uiDevAddr)
{
  uiDevAddr &= 0xFFFE;		// Ensure write bit is configured
  if (uiDevAddr > 0xFF)  	// Check for 10-bit address
  {
    pI2C->ADDR1 = (uint16_t)(uiDevAddr & 0xFF);
    pI2C->ADDR0	= (uint16_t)(((uiDevAddr >> 7) & 0x6) | 0xF0);
  }
  else
  {
    pI2C->ADDR0 = (uint16_t)(uiDevAddr & 0xFF);
    pI2C->ADDR1 = (uint16_t)0x00;
  }
}

/**
	@brief void I2cMRdCfg(ADI_I2C_TypeDef *pI2C,uint32_t DevAddr, uint32_t NumBytes, uint32_t Ext)
			========== Configure I2CMRXCNT - Master read control register.
	@param pI2C :{pADI_I2C0,pADI_I2C1,pADI_I2C2}
		- pADI_I2C0 for I2C0.
		- pADI_I2C1 for I2C1 
            - pADI_I2C2 for I2C2
	@param DevAddr :{0-1023}     \n
	@param NumBytes :{0-65535}     \n
	@param Ext :{DISABLE,ENABLE}
		- DISABLE for Master to Read 1 to 256 bytes
		- ENABLE for Master to read more than 256 bytes
	@return none
**/
void I2cMRdCfg(ADI_I2C_TypeDef *pI2C,uint32_t DevAddr, uint32_t NumBytes, uint32_t Ext)
{
  pI2C->MRXCNT = (uint16_t)(NumBytes - 1);
  pI2C->MRXCNT |= Ext<<BITP_I2C_MRXCNT_EXTEND;
  if (DevAddr > 0xFF)  		// Check for 10-bit address
  {
    pI2C->ADDR1	= (uint16_t)(DevAddr & 0xFF);
    pI2C->ADDR0	= (uint16_t)(((DevAddr >> 7) & 0x6) | 0xF0);
  }
  else
  {
    pI2C->ADDR0 = (uint16_t)(DevAddr|0x01);
    pI2C->ADDR1 = (uint16_t)0x00;
  }
  //pI2C->ADDR0 |= 0x1;			// Ensure read bit is set to 1
}

/**
   @brief uint32_t I2cSta(ADI_I2C_TypeDef *pI2C,uint32_t Mode)
			========== Read the status register for the I2C Master or Slave.
   @param pI2C :{pADI_I2C0,pADI_I2C1,pADI_I2C2}
		- pADI_I2C0 for I2C0.
		- pADI_I2C1 for I2C1 
            - pADI_I2C2 for I2C2
   @param Mode :{MASTER, SLAVE}
		- 0 or MASTER for I2C Master operation.
		- 1 or SLAVE for I2C Slave operation.
   @return value of SSTA:
		- I2CSSTA.0 = Tx FIFO status
		- I2CSSTA.1 = I2C Tx FIFO under-run 
		- I2CSSTA.2 = I2C Tx Request
		- I2CSSTA.3 = I2C Rx Request
		- I2CSSTA.4 = I2C Rx FIFO overflow
		- I2CSSTA.5 = I2C Slave NACK of address byte
		- I2CSSTA.6 = I2C Slave busy
		- I2CSSTA.7 = I2C general call interrupt
		- I2CSSTA.9:8 = I2C general call ID
		- I2CSSTA.10 = I2C Stop condition detected
		- I2CSSTA.12:11 = I2C ID Match status
		- I2CSSTA.13 = I2C repeated Start condition detected
		- I2CSSTA.14 = I2C Start + matching address condition detected
	@return value of MSTA:
		- I2CMSTA.1:0 = Tx FIFO status
		- I2CMSTA.2 = I2C Tx Request
		- I2CMSTA.3 = I2C Rx Request
		- I2CMSTA.4 = I2C NACK of address byte from Slave
		- I2CMSTA.5 = I2C Arbitration lost
		- I2CMSTA.6 = I2C Master busy
		- I2CMSTA.7 = I2C NACK of data byte from Slave
		- I2CMSTA.8 = I2C Stop condition detected
		- I2CMSTA.9 = Rx overflow
		- I2CMSTA.10 = I2C Bus busy
		- I2CMSTA.11 = I2C Stop detected
		- I2CMSTA.12 = I2C Tx Under-run condition
            - I2CMSTA.13 = SDA line filtered
            - I2CMSTA.14 = SCL line filtered
            - I2CMSTA.15 = new data writen to address register
**/
uint32_t I2cSta(ADI_I2C_TypeDef *pI2C,uint32_t Mode)
{
  if (Mode == 1)
    return pI2C->SSTAT;
  else
    return pI2C->MSTAT;
}

/**
	@brief uint32_t I2cMRdCnt(ADI_I2C_TypeDef *pI2C)
			========== Master Read count register - read by master to keep track of number of bytes received.
	@param pI2C :{pADI_I2C0,pADI_I2C1,pADI_I2C2}
		- pADI_I2C0 for I2C0.
		- pADI_I2C1 for I2C1 
            - pADI_I2C2 for I2C2
	@return value of I2CMCRXCNT.
**/
uint32_t I2cMRdCnt(ADI_I2C_TypeDef *pI2C)
{
  return pI2C->MCRXCNT;
}

/**
	@brief void I2cSGCallCfg(ADI_I2C_TypeDef *pI2C,uint8_t HWGCallAddr)
			========== Configure ID value for Hardware General Calls.
	@param pI2C :{pADI_I2C0,pADI_I2C1,pADI_I2C2}
		- pADI_I2C0 for I2C0.
		- pADI_I2C1 for I2C1 
            - pADI_I2C2 for I2C2
	@param HWGCallAddr :{0-255}
	@return none
**/
void I2cSGCallCfg(ADI_I2C_TypeDef *pI2C,int HWGCallAddr)
{
  pI2C->ALT = (uint16_t)HWGCallAddr;
}

/*
@brief void I2cMasterSetup(ADI_I2C_TypeDef *pI2C, I2CM_SETUP_t *pSetup)
      =========== setup for I2C master
@param pI2C: pointer to I2C instance
   - pADI_I2C0
   - pADI_I2C1
   - pADI_I2C2
@param pSetup: pointer to I2CM_SETUP_t
@return none
**/
void I2cMasterSetup(ADI_I2C_TypeDef *pI2C, I2CM_SETUP_t *pSetup)
{
   uint32_t regMasterCon,regMasterShctl,regAutoStretch,regTctl;
   regMasterCon = (pSetup->MasterEn<<BITP_I2C_MCTL_MASEN)   \
                  |(pSetup->competeEn<<BITP_I2C_MCTL_COMPETE)  \
                  |(pSetup->loopBackEn<<BITP_I2C_MCTL_LOOPBACK)   \
                  |(pSetup->rxIntEn<<BITP_I2C_MCTL_IENMRX)  \
                  |(pSetup->txIntEn<<BITP_I2C_MCTL_IENMTX)  \
                  |(pSetup->ArbitrLostIntEn<<BITP_I2C_MCTL_IENALOST) \
                  |(pSetup->NACKIntEn<<BITP_I2C_MCTL_IENACK)   \
                  |(pSetup->StopIntEn<<BITP_I2C_MCTL_IENCMP)   \
                  |(pSetup->txFifoUpdate<<BITP_I2C_MCTL_MXMITDEC) \
                  |(pSetup->rxDmaEn<<BITP_I2C_MCTL_MRXDMA)  \
                  |(pSetup->txDmaEn<<BITP_I2C_MCTL_MTXDMA);
   regMasterShctl = (pSetup->sclDelay<<BITP_I2C_SHCTL_SCL_DLY) \
                     |(pSetup->sdaDelay<<BITP_I2C_SHCTL_SDA_DLY);
   regAutoStretch = pI2C->ASTRETCH_SCL;
   regAutoStretch &= ~BITM_I2C_ASTRETCH_SCL_STRETCH_MODE_MAS;
   regAutoStretch |= pSetup->autoStretchTime<<BITP_I2C_ASTRETCH_SCL_STRETCH_MODE_MAS;
   regTctl = (pSetup->thdDat<<BITP_I2C_TCTL_THDATIN)  \
            |(pSetup->glitchFilter<<BITP_I2C_TCTL_FILTER_TICKS);
   if(pSetup->glitchFilter <= 0) //disable filter, it's enabled by default
   {
      regTctl |= BITM_I2C_TCTL_FILTEROFF;
   }

   pI2C->MCTL = (uint16_t)regMasterCon;
   pI2C->SHCTL = (uint16_t)regMasterShctl;
   pI2C->ASTRETCH_SCL = (uint16_t)regAutoStretch;
   pI2C->TCTL = (uint16_t)regTctl;
}

//----------------------- Slave related functions -----------------
/**
	@brief void I2C0SIDCfg(uint32_t ID0, uint32_t ID1,uint32_t ID2,uint32_t ID3)
			========== Configure ID value for Slave address - value betweeen 0-0xFF.

	@param ID0 :{0-255}
	@param ID1 :{0-255}
	@param ID2 :{0-255}
	@param ID3 :{0-255}
      @note address bit ID[7:1]
**/
void I2C0SIDCfg(uint32_t ID0, uint32_t ID1,uint32_t ID2,uint32_t ID3)
{
  pADI_I2C0->ID0 = (uint16_t)ID0;
  pADI_I2C0->ID1 = (uint16_t)ID1;
  pADI_I2C0->ID2 = (uint16_t)ID2;
  pADI_I2C0->ID3 = (uint16_t)ID3;	
}

/**
	@brief void I2C1SIDCfg(uint32_t ID0, uint32_t ID1,uint32_t ID2,uint32_t ID3)
			========== Configure ID value for Slave address - value betweeen 0-0xFF.

	@param ID0 :{0-255}
	@param ID1 :{0-255}
	@param ID2 :{0-255}
	@param ID3 :{0-255}
      @note address bit ID[7:1]
**/
void I2C1SIDCfg(uint32_t ID0, uint32_t ID1,uint32_t ID2,uint32_t ID3)
{
  pADI_I2C1->ID0 = (uint16_t)ID0;
  pADI_I2C1->ID1 = (uint16_t)ID1;
  pADI_I2C1->ID2 = (uint16_t)ID2;
  pADI_I2C1->ID3 = (uint16_t)ID3;	
}

/**
	@brief void I2C2SIDCfg(uint32_t ID0, uint32_t ID1,uint32_t ID2,uint32_t ID3)
			========== Configure ID value for Slave address - value betweeen 0-0xFF.

	@param ID0 :{0-255}
	@param ID1 :{0-255}
	@param ID2 :{0-255}
	@param ID3 :{0-255}
      @note address bit ID[7:1]
**/
void I2C2SIDCfg(uint32_t ID0, uint32_t ID1,uint32_t ID2,uint32_t ID3)
{
  pADI_I2C2->ID0 = (uint16_t)ID0;
  pADI_I2C2->ID1 = (uint16_t)ID1;
  pADI_I2C2->ID2 = (uint16_t)ID2;
  pADI_I2C2->ID3 = (uint16_t)ID3;	
}

/*
@brief void I2cSlaveSetup(ADI_I2C_TypeDef *pI2C, I2CS_SETUP_t *pSetup)
      =========== setup for I2C slave
@param pI2C :{pADI_I2C0,pADI_I2C1,pADI_I2C2}
		- pADI_I2C0 for I2C0.
		- pADI_I2C1 for I2C1 
    - pADI_I2C2 for I2C2
@param pSetup: pointer to I2C slave setup structure
@return none
**/
void I2cSlaveSetup(ADI_I2C_TypeDef *pI2C, I2CS_SETUP_t *pSetup)
{
   uint32_t regSctl,regAstretchScl,regShctl,regTctl,regDiv;
   regSctl = (pSetup->slaveEn<<BITP_I2C_SCTL_SLVEN) \
              |(pSetup->address10BitEn<<BITP_I2C_SCTL_ADR10EN)  \
              |(pSetup->generalCallEn<<BITP_I2C_SCTL_GCEN)  \
              |(pSetup->HwGeenralCallEn<<BITP_I2C_SCTL_HGCEN)  \
              |(pSetup->earlyTxReq<<BITP_I2C_SCTL_EARLYTXR) \
              |(pSetup->stopIntEn<<BITP_I2C_SCTL_IENSTOP) \
              |(pSetup->rxIntEn<<BITP_I2C_SCTL_IENSRX)  \
              |(pSetup->txIntEn<<BITP_I2C_SCTL_IENSTX)  \
              |(pSetup->txFifoUpdate<<BITP_I2C_SCTL_SXMITDEC) \
              |(pSetup->reStartIntEn<<BITP_I2C_SCTL_IENREPST) \
              |(pSetup->rxDmaEn<<BITP_I2C_SCTL_SRXDMA)  \
              |(pSetup->txDmaEn<<BITP_I2C_SCTL_STXDMA)  \
              |(pSetup->idFifoEn<<BITP_I2C_SCTL_ID_FIFO_EN);
   regAstretchScl = pI2C->ASTRETCH_SCL;
   regAstretchScl &= ~BITM_I2C_ASTRETCH_SCL_STRECTH_MODE_SLV;
   regAstretchScl |= (pSetup->autoStretchTime<<BITP_I2C_ASTRETCH_SCL_STRECTH_MODE_SLV)  \
                    |(pSetup->stretchIntEn<<BITP_I2C_ASTRETCH_SCL_SSCL_IRQ_IEN);
   regShctl = (pSetup->sclDelay<<BITP_I2C_SHCTL_SCL_DLY)  \
              |(pSetup->sdaDelay<<BITP_I2C_SHCTL_SDA_DLY);
   regTctl = (pSetup->thdDat<<BITP_I2C_TCTL_THDATIN)  \
              |(pSetup->glitchFilter<<BITP_I2C_TCTL_FILTER_TICKS) \
              |(pSetup->preDiv<<BITP_I2C_TCTL_PRE_DIV);
   regDiv = (pSetup->lowTime<<BITP_I2C_DIV_LOW) \
            |(pSetup->highTime<<BITP_I2C_DIV_HIGH);

   pI2C->ID0 = (uint16_t)(pSetup->slaveID[0]);
   pI2C->ID1 = (uint16_t)(pSetup->slaveID[1]);
   pI2C->ID2 = (uint16_t)(pSetup->slaveID[2]);
   pI2C->ID3 = (uint16_t)(pSetup->slaveID[3]);
   pI2C->SLV_ADDR1 = (uint16_t)(pSetup->slaveID10bit&0xFF);
   pI2C->SLV_ADDR1 = (uint16_t)(pSetup->slaveID10bit>>8);
   pI2C->ALT = (uint16_t)(pSetup->masterAddress);
   pI2C->TCTL = (uint16_t)regTctl;
   pI2C->DIV = (uint16_t)regDiv;
   pI2C->SHCTL = (uint16_t)regShctl;
   pI2C->ASTRETCH_SCL = (uint16_t)regAstretchScl;
   pI2C->SCTL = (uint16_t)regSctl;
}





