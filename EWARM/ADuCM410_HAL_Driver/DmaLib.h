/*!
 *****************************************************************************
 * @file: DmaLib.h
 * @brief: header file of DMA library
 *-----------------------------------------------------------------------------
 *
Copyright (c) 2013-2018 Analog Devices, Inc. All Rights Reserved.

This software is proprietary to Analog Devices, Inc. and its licensors.
By using this software you agree to the terms of the associated
Analog Devices Software License Agreement.
 ******************************************************************************/

#ifndef DMA_LIB_H
#define DMA_LIB_H

#ifdef __cplusplus
extern "C" {
#endif

#include "ADuCM410.h"

//DMA type (Cycl_ctrl)
#define	DMA_STOP		0
#define	DMA_BASIC		1
#define	DMA_AUTO		2
#define	DMA_PING		3
#define	DMA_MSG_PRI		4
#define	DMA_MSG_ALT		5
#define	DMA_PSG_PRI		6
#define	DMA_PSG_ALT		7
//Bytes per transfer.
#define	DMA_SIZE_BYTE		 0
#define	DMA_SIZE_HWORD	 0x1000000
#define	DMA_SIZE_WORD		 0x2000000
//Destination Increment per transfer.
#define	DMA_DSTINC_BYTE		0
#define	DMA_DSTINC_HWORD	0x40000000
#define	DMA_DSTINC_WORD		0x80000000
#define	DMA_DSTINC_NO		  0xC0000000
//Source Increment per transfer.
#define	DMA_SRCINC_BYTE		0
#define	DMA_SRCINC_HWORD	0x4000000
#define	DMA_SRCINC_WORD		0x8000000
#define	DMA_SRCINC_NO		  0xC000000
#define  SIZE_BYTE    0
#define  SIZE_HWORD   1
#define  SIZE_WORD    2
   
#define  ENUM_DMA_INC_BYTE    0
#define  ENUM_DMA_INC_HWORD   1
#define  ENUM_DMA_INC_WORD    2
#define  ENUM_DMA_INC_NO      3

typedef struct
{
   unsigned int cycle_ctrl    :3;
   unsigned int reserved0     :1;
   unsigned int n_minus_1     :10;
   unsigned int r_power       :4;
   unsigned int reserved1     :3;
   unsigned int reserved2     :3;
   unsigned int src_size      :2;
   unsigned int src_inc       :2;
   unsigned int dst_size      :2;
   unsigned int dst_inc       :2;
} CtrlCfgBits;

// Define the structure of a DMA descriptor.
typedef struct dmaDesc
{
   uint32_t srcEndPtr;
   uint32_t destEndPtr;
   union
   {
      uint32_t   ctrlCfgVal;
      CtrlCfgBits    Bits;
   } ctrlCfg ;
   uint32_t reserved4Bytes;
} DmaDesc;
//typedef enum {false = 0, true = !false} boolean;
// Suitable aLignment for the DMA descriptors
#define DMACHAN_DSC_ALIGN 0x800
/* CCD allocation must be an integral power of two, i.e., 12 channels is allocated as 16 */
#define CCD_SIZE                       (32)

//DMA channel numbers.
typedef enum
{
   SPI0TX_C = 0u, //0
   SPI0RX_C	,     //1
   SPI1TX_C	,
   SPI1RX_C	,     //3
   SPI2TX_C	,
   SPI2RX_C	,     //5
   UART0TX_C,
   UART0RX_C,     //7
   UART1TX_C,
   UART1RX_C,     //9
   I2C0STX_C,
   I2C0SRX_C,     //11
   I2C0M_C	,
   I2C1STX_C,     //13
   I2C1SRX_C,
   I2C1M_C	,     //15
   I2C2STX_C,
   I2C2SRX_C,     //17
   I2C2M_C	,
   MDIOTX_C ,     //19
   MDIORX_C ,
   FLASH_C	,     //21
   ADC_C	   ,     //22
   LVTX_C	,     //23
   LVRX_C	,
   HVTX_C	,     //25
   HVRX_C	,     //26
   TIMERPLA0_C    , //27
   TIMERPLA1_C    , //28
   SWTRIG0_C   ,    //29
   SWTRIG1_C   ,    //30
   //position for alternative description
   ALT_SPI0TX_C = 32,
   ALT_SPI0RX_C	,
   ALT_SPI1TX_C	,
   ALT_SPI1RX_C	,
   ALT_SPI2TX_C	,
   ALT_SPI2RX_C	,
   ALT_UART0TX_C,
   ALT_UART0RX_C,
   ALT_UART1TX_C,
   ALT_UART1RX_C,
   ALT_I2C0STX_C,
   ALT_I2C0SRX_C,
   ALT_I2C0M_C	,
   ALT_I2C1STX_C,
   ALT_I2C1SRX_C,
   ALT_I2C1M_C	,
   ALT_I2C2STX_C,
   ALT_I2C2SRX_C,
   ALT_I2C2M_C	,
   ALT_MDIOTX_C ,
   ALT_MDIORX_C ,
   ALT_FLASH_C	,
   ALT_ADC_C	   ,
   ALT_LVTX_C	,
   ALT_LVRX_C	,
   ALT_HVTX_C	,
   ALT_HVRX_C	,
   ALT_TIMERPLA0_C    , 
   ALT_TIMERPLA1_C    , 
   ALT_SWTRIG0_C   ,    
   ALT_SWTRIG1_C   ,    
}DMA_CHANNEL_t;

#define DMA_CHAN_BIT(chx)  (1u<<chx)

#define SPI0TX_B        DMA_CHAN_BIT(SPI0TX_C )                            
#define SPI0RX_B        DMA_CHAN_BIT(SPI0RX_C)                
#define SPI1TX_B        DMA_CHAN_BIT(SPI1TX_C)                
#define SPI1RX_B        DMA_CHAN_BIT(SPI1RX_C)                
#define SPI2TX_B        DMA_CHAN_BIT(SPI2TX_C)                
#define SPI2RX_B        DMA_CHAN_BIT(SPI2RX_C)                
#define UART0TX_B       DMA_CHAN_BIT(UART0TX_C)                         
#define UART0RX_B       DMA_CHAN_BIT(UART0RX_C)                         
#define UART1TX_B       DMA_CHAN_BIT(UART1TX_C)                         
#define UART1RX_B       DMA_CHAN_BIT(UART1RX_C)                         
#define I2C0STX_B       DMA_CHAN_BIT(I2C0STX_C)                         
#define I2C0SRX_B       DMA_CHAN_BIT(I2C0SRX_C)             
#define I2C0M_B         DMA_CHAN_BIT(I2C0M_C)      
#define I2C1STX_B       DMA_CHAN_BIT(I2C1STX_C)             
#define I2C1SRX_B       DMA_CHAN_BIT(I2C1SRX_C)             
#define I2C1M_B         DMA_CHAN_BIT(I2C1M_C)      
#define I2C2STX_B       DMA_CHAN_BIT(I2C2STX_C)             
#define I2C2SRX_B       DMA_CHAN_BIT(I2C2SRX_C)             
#define I2C2M_B         DMA_CHAN_BIT(I2C2M_C)      
#define MDIOTX_B        DMA_CHAN_BIT(MDIOTX_C)      
#define MDIORX_B        DMA_CHAN_BIT(MDIORX_C)      
#define FLASH_B         DMA_CHAN_BIT(FLASH_C)   
#define ADC_B           DMA_CHAN_BIT(ADC_C)      
#define LVTX_B          DMA_CHAN_BIT(LVTX_C)      
#define LVRX_B          DMA_CHAN_BIT(LVRX_C)      
#define HVTX_B          DMA_CHAN_BIT(HVTX_C)      
#define HVRX_B          DMA_CHAN_BIT(HVRX_C) 
#define TIMERPLA0_B     DMA_CHAN_BIT(TIMERPLA0_C)      
#define TIMERPLA1_B     DMA_CHAN_BIT(TIMERPLA1_C)      
#define SWTRIG0_B       DMA_CHAN_BIT(SWTRIG0_C)      
#define SWTRIG1_B       DMA_CHAN_BIT(SWTRIG1_C)

//DMA channel bit value.
//#define	NONE		   0
//#define	SPI0TX_B	   0x1
//#define	SPI0RX_B	   0x2
//#define	SPI1TX_B	   0x4
//#define	SPI1RX_B	   0x8
//#define	UARTTX_B	   0x10
//#define	UARTRX_B	   0x20
//#define	I2C0STX_B	0x40
//#define	I2C0SRX_B	0x80
//#define	I2C0M_B	   0x100
//#define	I2C1STX_B	0x200
//#define	I2C1SRX_B	0x400
//#define	I2C1M_B	   0x800
//#define	ADC_B	      0x1000
//#define	Flash_B	   0x2000

#define ADC0DMAWRITE 0
#define ADC0DMAREAD  1
#define ADC1DMAWRITE 2
#define ADC1DMAREAD  3
#define SINC2DMAREAD 4

//DMA error bit.
#define	DMA_ERR_RD		0
#define	DMA_ERR_CLR		1

#define iPrimary        0
#define ALTERNATE      CCD_SIZE

typedef struct
{
   //enable specified DMA channel, each bit per channel
   //Besides prepheral dma enable, dma channel also needs to be re-enable when re-run DMA
   //e.x. pADI_DMA->ENSET |= DMA_SPI_RX_CHANNEL_BIT;
   uint32_t chanEn;
   //DMA channel  mask, mask request of specified channel, e.x. bit0=1,mask Channel 0
   uint32_t chanMask;
   //DMA channel select alternate control data structure
   uint32_t useAlt;
   //DMA channel has higher priority when corresponding bit set
   uint32_t priority;
   //DMA channel data to be sent will swap byte when corresponding bit set
   uint32_t byteSwap;
   //DMA channel decrease source data address when corresponding bit set
   uint32_t srcAddrDec;
   //DMA channel decrease destination data address when corresponding bit set
   uint32_t dstAddrDec;

   //pointer to DMA channel description of first channel
   DmaDesc *pDmaChxDesc;

}DMA_SETUP_t;

extern DMA_SETUP_t gDmaSetup;
//---------------------function prototype---------------------------------
extern void DmaSetup(DMA_SETUP_t * pSetup);

extern void DmaBase(void);
extern DmaDesc * Dma_GetDescriptor(uint32_t Chan);
extern void DmaSet(uint32_t Mask, uint32_t Enable, uint32_t Alt, uint32_t Priority);
extern void DmaClr(uint32_t Mask, uint32_t Disable, uint32_t Alt, uint32_t Priority);
extern uint32_t DmaSta(void);
extern uint32_t DmaErr(uint32_t ErrClr);

extern uint32_t AdcDmaReadSetup(uint32_t Chan, uint32_t NumVals, uint32_t Ain, uint32_t *pucRX_DMA);
extern void DmaPeripheralStructSetup(uint32_t Chan, uint32_t Cfg);
extern uint32_t DmaStructPtrOutSetup(uint32_t Chan, uint32_t NumVals, const uint8_t *pucTX_DMA);
extern uint32_t DmaStructPtrInSetup(uint32_t Chan, uint32_t NumVals, uint8_t *pucRX_DMA);
extern void DmaGo(uint32_t Chan, uint32_t Numx, uint32_t Cfg);

#ifdef __cplusplus
}
#endif

#endif // DMA_LIB_H


