/*!
 *****************************************************************************
 * @file: I2cLib.h
 * @brief: header file of I2C library
 *-----------------------------------------------------------------------------
 *
Copyright (c) 2013-2018 Analog Devices, Inc. All Rights Reserved.

This software is proprietary to Analog Devices, Inc. and its licensors.
By using this software you agree to the terms of the associated
Analog Devices Software License Agreement.
 ******************************************************************************/
#ifndef __I2C_LIB_H__
#define __I2C_LIB_H__

#include <ADuCM410.h>

#ifndef MASTER
#define MASTER 0
#endif
#ifndef SLAVE
#define SLAVE 1
#endif
#ifndef DISABLE
#define DISABLE 0
#endif
#ifndef ENABLE
#define ENABLE 1
#endif

#define STRETCH_DIS 0
#define STRETCH_EN 1

#define SFIFO_ID0 (0u<<BITP_I2C_STX_ID_SEL)
#define SFIFO_ID1 (1u<<BITP_I2C_STX_ID_SEL)
#define SFIFO_ID2 (2u<<BITP_I2C_STX_ID_SEL)
#define SFIFO_ID3 (3u<<BITP_I2C_STX_ID_SEL)

#define MASTER_TX_FIFO_FULL (2<<BITP_I2C_STAT_MTXSFA)

#define UPDATE_TXFIFO_STATUS_AT_BYTEEND 1
#define UPDATE_TXFIFO_STATUS_AT_BYTESTART 0
#define BUS_CLEAR_SDA_RELEASE 1
#define BUS_CLEAR_9CYCLE 0

/*
  I2C master setup
*/
typedef struct
{
  //Master configuration

  //1 - master enable
  //0 - master mode disabled
  uint32_t MasterEn; 
  //1 - compete for ownership even if another device is currently driving a start condition
  //0 - will not compete
  uint32_t competeEn;
  //1- internal loopback, Master to slave
  //0 - normal mode  
  uint32_t loopBackEn;
  //1 - enabel Rx Dma
  //0 - disable
  uint32_t rxDmaEn;
  //1 - enable Tx Dma
  //0 - disable Tx Dma
  uint32_t txDmaEn;
  //master stretch time. range:0~15
  //strech SCL, time unit is one SCL bit
  //when time out, the stretch will release.
  //2^autoStretchTime time is counted in UCLK/prescale/256, 
  uint32_t autoStretchTime;

//-----------------high speed mode -------------
  //1 - high speed mode
  //0 - fast or standard mode
  uint32_t highSpeedEn;
  //1 - automatically connect current source pull-up
  //0 - user manually write MCS in SHCTL register to control current source pull-up
  //only used in high speed mode
  uint32_t autoMcsEn;
  //delay between SCLOUT and SCLOEN, range:0~15
  uint32_t sclDelay;
  //delay between SDAOUT and SDAOEN, range:0~15
  uint32_t sdaDelay;
  
//-----------Interrupt------------
  //1 - enable interrupt for Rx request
  //0 - disable 
  uint32_t rxIntEn;
  //1 - enable interrupt for Tx request
  //0 - disable
  uint32_t txIntEn;
  //1 - enable interrupt for Arbitration lost to I2C bus
  //0 - disable
  uint32_t ArbitrLostIntEn;
  //1 - enable interrupt for NACK
  //0 - disable interrupt
  uint32_t NACKIntEn;
  //1 - enable interrupt for stop condition detected, tansaction completed.
  //0 - disable interrput
  uint32_t StopIntEn;

//----------- misc------------
  //hold time for SDA into device, counted from falling edge of SCL
  //range:0~63
  uint32_t thdDat;
  //glitch with width that less than glitchfilter will be ignored
  uint32_t glitchFilter;
  //1 or UPDATE_TXFIFO_STATUS_AT_BYTEEND - update Tx FIFO status when tx byte transmitted
  //0 or UPDATE_TXFIFO_STATUS_AT_BYTESTART- update Tx FIFO status at the start of tx byte transmission
  uint32_t txFifoUpdate; 

}I2CM_SETUP_t;  //master setup


/*Setup for I2C woking in slave mode*/
typedef struct
{
  //1 - slave enable
  //0 - disable
  uint32_t slaveEn;
  //1 - transmit request generated just after positive edge of SCL pulse for the direction bit
  //0 - transmit request generated after SCL pulse for the direction bit finish
  uint32_t earlyTxReq;
  //1 - enable slave Rx DMA request
  //0 - disable
  uint32_t rxDmaEn;
  //1 - enable slave tx DMA request
  //0 - disable
  uint32_t txDmaEn;
  //1 - each slave device ID has seperate transmit FIFO
  //0 - one slave has one FIFO shared with different ID
  uint32_t idFifoEn;
  //four slave ID, 7bit address mode
  uint32_t slaveID[4];
  //1 - 10bit address
  //0 - 7 bit address
  uint32_t address10BitEn;
  //slave ID , 10 bit address mode
  uint32_t slaveID10bit;

  //----------- Interrupt setup ----
  //1 - stop condition detected interrupt enable
  //0 -disable
  uint32_t stopIntEn;
  //1 - slave receive request interrupt enable
  //0 - disable
  uint32_t rxIntEn;
  //1 - slave transmit request interrupt enable
  //0 - disable
  uint32_t txIntEn;
  //1 - repeated start interrupt enable
  //0 - disable
  uint32_t reStartIntEn;
  //1 -  slave stretch SCL interrupt enable
  //0 - disable
  uint32_t stretchIntEn;
  

//-----------------high speed mode -------------
  //delay between SCLOUT and SCLOEN
  uint32_t sclDelay;
  //delay between SDAOUT and SDAOEN
  uint32_t sdaDelay;

//--------------------- Auto stretch time out --------
  //master stretch time
  //strech SCL, time unit is one SCL bit
  uint32_t autoStretchTime;
  //following 3 parameters define auto stretch time period
  //Tstretch = Tuclk*(preDiv*256+highTime+lowTime)*2^autoStretchTime
  //for instance, if uclk=160Mhz, preDiv=4,highTime=230,lowTime=246,autoStretchTime=5
  //then Tstretch = 300us
  uint32_t highTime;
  uint32_t lowTime;
  uint32_t preDiv;

//------------ General call -------
  //1 - slave support general call
  //0 - general call is not supported
  uint32_t generalCallEn;
  //1 - enable hardware general call
  //0 - hardware general call disabled
  uint32_t HwGeenralCallEn;
  //7 bit master address in general call
  uint32_t masterAddress;

//----------- misc -----
  //1 or UPDATE_TXFIFO_STATUS_AT_BYTEEND - update Tx FIFO status when tx byte transmitted
  //0 or UPDATE_TXFIFO_STATUS_AT_BYTESTART- update Tx FIFO status at the start of tx byte transmission
  uint32_t txFifoUpdate; 
  //hold time for SDA into device, counted from falling edge of SCL
  uint32_t thdDat;
  //glitch with width that less than glitchfilter will be ignored
  uint32_t glitchFilter;

}I2CS_SETUP_t;

extern I2CM_SETUP_t gI2C0MSetup;
extern I2CS_SETUP_t gI2C0SSetup;
extern I2CM_SETUP_t gI2C1MSetup;
extern I2CS_SETUP_t gI2C1SSetup;
extern I2CM_SETUP_t gI2C2MSetup;
extern I2CS_SETUP_t gI2C2SSetup;

// =================================== Function API =====================
//---------- Master API -------
extern void I2cMasterSetup(ADI_I2C_TypeDef *pI2C, I2CM_SETUP_t *pSetup);
extern void I2cMCfg(ADI_I2C_TypeDef *pI2C, uint32_t DMACfg, uint32_t IntSources, uint32_t Config);
extern void I2cMWrCfg(ADI_I2C_TypeDef *pI2C,uint32_t uiDevAddr);
extern void I2cMRdCfg(ADI_I2C_TypeDef *pI2C,uint32_t DevAddr, uint32_t NumBytes, uint32_t Ext);
extern uint32_t I2cMRdCnt(ADI_I2C_TypeDef *pI2C);		
//---------- Slave API --------
extern void I2cSlaveSetup(ADI_I2C_TypeDef *pI2C, I2CS_SETUP_t *pSetup);
extern void I2cSCfg(ADI_I2C_TypeDef *pI2C,uint32_t DMACfg, uint32_t IntSources, uint32_t Config);
extern void I2cSGCallCfg(ADI_I2C_TypeDef *pI2C,int HWGCallAddr);
extern void I2C0SIDCfg(uint32_t SlaveID0, uint32_t SlaveID1,uint32_t SlaveID2,uint32_t SlaveID3);	
extern void I2C1SIDCfg(uint32_t SlaveID0, uint32_t SlaveID1,uint32_t SlaveID2,uint32_t SlaveID3);	
extern void I2C2SIDCfg(uint32_t ID0, uint32_t ID1,uint32_t ID2,uint32_t ID3);
//--------- common ----------
extern uint32_t I2cRx(ADI_I2C_TypeDef *pI2C,uint32_t Mode);
extern void I2cTx(ADI_I2C_TypeDef *pI2C,uint32_t Mode, uint32_t Tx);
extern void I2cFifoTx(ADI_I2C_TypeDef *pI2C,uint32_t fifoID, uint32_t Tx);
extern void I2cBaud(ADI_I2C_TypeDef *pI2C,uint32_t Prescale, uint32_t HighPeriod, uint32_t LowPeriod);
extern uint32_t I2cSta(ADI_I2C_TypeDef *pI2C,uint32_t Mode);
extern void I2c0SIDCfg(uint32_t ID0, uint32_t ID1,uint32_t ID2,uint32_t ID3);
extern void I2c1SIDCfg(uint32_t ID0, uint32_t ID1,uint32_t ID2,uint32_t ID3);
extern void I2c2SIDCfg(uint32_t ID0, uint32_t ID1,uint32_t ID2,uint32_t ID3);
/**
   @brief void I2cMBusClr(ADI_I2C_TypeDef *pI2C)
			========== send extral SCL cycles 
   @param pI2C :{pADI_I2C0,pADI_I2C1,pADI_I2C2}
		- pADI_I2C0 for I2C0.
		- pADI_I2C1 for I2C1 
    - pADI_I2C2 for I2C2 
   @return none;
**/
#define I2cMBusClr(pI2C)  do{   \
                            pI2C->MCTL |= BITM_I2C_MCTL_BUS_CLR_EN; \
                            }while(0)        //Master mode: send bus clear pulse                   

/**
   @brief void I2cMBusClr(ADI_I2C_TypeDef *pI2C)
			========== stop sending extral SCL cycles 
   @param pI2C :{pADI_I2C0,pADI_I2C1,pADI_I2C2}
		- pADI_I2C0 for I2C0.
		- pADI_I2C1 for I2C1 
    - pADI_I2C2 for I2C2 
   @return none;
**/
#define I2cMBusClrStop(pI2C)  do{ \
                                pI2C->MCTL &= ~BITM_I2C_MCTL_BUS_CLR_EN;  \
                                }while(0)   //Master mode: stop sending bus clear pulse
/**
   @brief void I2cMFifoFlush(ADI_I2C_TypeDef *pI2C)
			========== Flush Master Tx FIFO
   @param pI2C :{pADI_I2C0,pADI_I2C1,pADI_I2C2}
		- pADI_I2C0 for I2C0.
		- pADI_I2C1 for I2C1 
    - pADI_I2C2 for I2C2 
   @return none;
**/
#define I2cMFifoFlush(pI2C)   do{ \
                                pI2C->STAT |= BITM_I2C_STAT_MFLUSH; \
                                }while(0) //flush Master transmit FIFO0    

/**
   @brief void I2cSFifoFlush(ADI_I2C_TypeDef *pI2C,uint32_t FifoId)
			========== Flush Slave Tx FIFO
   @param pI2C :{pADI_I2C0,pADI_I2C1,pADI_I2C2}
		- pADI_I2C0 for I2C0.
		- pADI_I2C1 for I2C1 
    - pADI_I2C2 for I2C2 
   @param FifoId:{BITM_I2C_IDFSTA_SFLUSH0|BITM_I2C_IDFSTA_SFLUSH1
                  |BITM_I2C_IDFSTA_SFLUSH2|BITM_I2C_IDFSTA_SFLUSH3}
   @return none;
**/
#define I2cSFifoFlush(pI2C) do{ \
                                pI2C->IDFSTA |= FifoId; \
                              }while(0)

/*
@brief void I2cSlaveNack(ADI_I2C_TypeDef *pI2C)
      =========== NACK next communication
@param pI2C :{pADI_I2C0,pADI_I2C1,pADI_I2C2}
		- pADI_I2C0 for I2C0.
		- pADI_I2C1 for I2C1 
    - pADI_I2C2 for I2C2 
@return none
**/
#define I2cSlaveNack(pI2C)  do{ \
                                pI2C->SCTL |= BITM_I2C_SCTL_NACK; \
                              }while(0)



#endif //__I2C_LIB_H__


