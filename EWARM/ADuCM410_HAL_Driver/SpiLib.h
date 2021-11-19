/*!
 *****************************************************************************
 * @file:  SpiLib.h 
 * @brief: header of SPI interface
 *-----------------------------------------------------------------------------
 *
Copyright (c) 2013-2018 Analog Devices, Inc. All Rights Reserved.

This software is proprietary to Analog Devices, Inc. and its licensors.
By using this software you agree to the terms of the associated
Analog Devices Software License Agreement.
 ******************************************************************************/
#ifndef SPI_LIB_H
#define SPI_LIB_H

#ifdef __cplusplus
extern "C" {
#endif 

#include "ADuCM410.h"

#define FIFOEMPTY_TX_LAST_DATA   0  //send '0' when no valid data in Tx FIFO
#define FIFOEMPTY_TX_0           1  //send last transmitted data wehn no valid data in Tx FIFO  

typedef struct
{
   //1 - enable spi
   //0 - disable spi
   uint32_t spiEn;
   //1 - SPI master mode enable
   //0 - SPI master disabled, when clear to 0 a synchronous reset issued
   uint32_t masterEn;
   //clock pahse
   uint32_t cpha;
   //clock polarity
   uint32_t cpol;
   //1 - SPI wire Or mode enabled
   //0 - SPI wire or mode disabled
   uint32_t wireOrEn;
   //1 - LSB transfered first
   //0 - MSB transfered first
   uint32_t lsbFirst;
   //1 - initiate transfer when write to TX reigster.
   //0 - initiate transfer when read of RX register.
   uint32_t txTrigTransfer;
   //1 - Rx resigter is overwriten by new serial byte received
   //0 - new serial byte is discarded.
   uint32_t rxOverwrite;
   //FIFOEMPTY_TX_LAST_DATA   0  //send '0' when no valid data in Tx FIFO
   //FIFOEMPTY_TX_0           1  //send last transmitted data wehn no valid data in Tx FIFO  
   uint32_t fifoEmtpyTx;
   //1 - enable miso drive in slave mode
   //0 - miso open circuit in slave mode
   uint32_t misoEn;
   //1 - transfer continous until no valid data in Tx register.
   //0 -  disable continous transfer. each SPI frame contains only 8 bit.
   uint32_t continousTx;
   //1 - enable loopback
   //0 - disable loopback
   uint32_t loopback;

   //1 - enable three pin mode, rx/tx data sharing on MOSI pin in different tiem slot.
   //0 - normal mode
   uint32_t threePinMode;

   //----------- Interrupt -------------
   //ENUM_SPI_IEN_IRQMODE_TX1RX1 , Interrupt Occurs After 1 Byte is Transfered or Received 
   //ENUM_SPI_IEN_IRQMODE_TX2RX2 , Interrupt Occurs After 2 Byte is Transfered or Received 
   //ENUM_SPI_IEN_IRQMODE_TX3RX3 , Interrupt Occurs After 3 Byte is Transfered or Received 
   //ENUM_SPI_IEN_IRQMODE_TX4RX4 , Interrupt Occurs After 4 Byte is Transfered or Received 
   //ENUM_SPI_IEN_IRQMODE_TX5RX5 , Interrupt Occurs After 5 Byte is Transfered or Received 
   //ENUM_SPI_IEN_IRQMODE_TX6RX6 , Interrupt Occurs After 6 Byte is Transfered or Received 
   //ENUM_SPI_IEN_IRQMODE_TX7RX7 , Interrupt Occurs After 7 Byte is Transfered or Received 
   //ENUM_SPI_IEN_IRQMODE_TX8RX8 , Interrupt Occurs After 8 Byte is Transfered or Received 
   uint32_t txrxIrqByte;
   uint32_t csIntEn;
   uint32_t txUnderflowIntEn;
   uint32_t rxOverflowIntEn;
   uint32_t readyIntEn;
   uint32_t txDoneIntEn;
   uint32_t frameEndIntEn;
   uint32_t txFifoEmptyIntEn;

   //------------- Dma -----------------
   uint32_t txDmaEn;
   uint32_t rxDmaEn;

   //-------------- Read command mode -----------
   //1 - enable read command mode
   //0 - diable read command mode
   uint32_t readCmdEn;
   //number of bytes to be transmitted before reading data
   uint32_t txByte;
   //
   uint32_t txRxOverlap;

   //------------ Flow control ------------------

}SPI_SETUP_t;

extern SPI_SETUP_t gSpi0Setup;
extern SPI_SETUP_t gSpi1Setup;
extern SPI_SETUP_t gSpi2Setup;
//------------------------------ Function prototypes ------------------------------------------
extern void SpiSetup(ADI_SPI_TypeDef *pSPI,SPI_SETUP_t *pSetup);

extern uint32_t SpiSta(ADI_SPI_TypeDef *pSPI);
extern uint32_t SpiRx(ADI_SPI_TypeDef *pSPI);
extern uint32_t SpiTx(ADI_SPI_TypeDef *pSPI, uint32_t iTx);
extern uint32_t SpiBaud(ADI_SPI_TypeDef *pSPI, uint32_t iClkDiv);
extern uint32_t SpiCfg(ADI_SPI_TypeDef *pSPI, uint32_t iFifoSize, uint32_t iMasterEn, uint32_t iConfig);
extern uint32_t SpiIenEn(ADI_SPI_TypeDef *pSPI,uint32_t iIntType);   
extern uint32_t SpiIenDis(ADI_SPI_TypeDef *pSPI,uint32_t iIntType);
extern uint32_t SpiFifoFlush(ADI_SPI_TypeDef *pSPI, uint32_t iTxFlush, uint32_t iRxFlush);
extern uint32_t SpiTxFifoFlush(ADI_SPI_TypeDef *pSPI, uint32_t iTxFlush);
extern uint32_t SpiRxFifoFlush(ADI_SPI_TypeDef *pSPI, uint32_t iRxFlush);
extern uint32_t SpiFifoSta(ADI_SPI_TypeDef *pSPI);
extern uint32_t SpiDma(ADI_SPI_TypeDef *pSPI, uint32_t iDmaRxSel, uint32_t iDmaTxSel, uint32_t iDmaEn);
extern uint32_t SpiCount(ADI_SPI_TypeDef *pSPI, uint32_t iSpiCnt, uint32_t iWr, uint32_t iFrameContEn);
extern uint32_t SpiRdCmd(ADI_SPI_TypeDef *pSPI, uint32_t iCfg, uint32_t iTxBytes, uint32_t iCmdEn);
extern uint32_t SpiFlowCtl(ADI_SPI_TypeDef *pSPI, uint32_t iCfg, uint32_t iRdBurstSize, uint32_t iWaitTime);
extern uint32_t SpiCsCfg(ADI_SPI_TypeDef *pSPI, uint32_t iCSoverRide);


#define CS0   0x1
#define CS1   0x2
#define CS2   0x4
#define CS3   0x8

#define FORCE_CS_HIGH   0x1
#define FORCE_CS_LOW   0x2


#ifdef __cplusplus
}
#endif

#endif   //#SPI_LIB_H
