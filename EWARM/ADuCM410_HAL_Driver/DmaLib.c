/*!
 *****************************************************************************
 * @file: DmaLib.c
 * @brief: library of DMA block
 *-----------------------------------------------------------------------------
 *
Copyright (c) 2013-2018 Analog Devices, Inc. All Rights Reserved.

This software is proprietary to Analog Devices, Inc. and its licensors.
By using this software you agree to the terms of the associated
Analog Devices Software License Agreement.
 ******************************************************************************/

#include <stdio.h>
#include <string.h>
#include "DmaLib.h"

// Define dmaChanDesc as an array of descriptors aligned to the required
// boundary for all supported compilers. It was not possible to do something
// in a macro here because the #pragma for IAR cannot be put in a #define.
//
// Support primary and alternate here
#define DMACHAN_NUM ((INT_NUM_DMA_LAST - INT_NUM_DMA_FIRST) + 1)

#if defined(__ARMCC_VERSION) || defined(__GNUC__)
static DmaDesc dmaChanDesc     [CCD_SIZE * 2] __attribute__ ((aligned (DMACHAN_DSC_ALIGN)));
#endif

#ifdef __ICCARM__
#pragma data_alignment=(DMACHAN_DSC_ALIGN)
static DmaDesc dmaChanDesc     [CCD_SIZE * 2];
#endif


/**
   @brief DmaDesc * Dma_GetDescriptor(uint32_t Chan);
         ========== Returns the Primary or Alternate structure descriptor of the
         specified channel.
   @param Chan :  value of DMA_CHANNEL_t enum;
   @return DmaDesc.
**/

DmaDesc * Dma_GetDescriptor(uint32_t Chan)
{
   if (Chan < (CCD_SIZE*2))
   {
      return &(dmaChanDesc[Chan]);
   }
   else
      return 0x0;
}

/**
	@brief void DmaBase(void)
			========== Sets the Address of DMA Data base pointer.
	@return 1.
**/
void DmaBase(void)
{
   volatile uint32_t uiBasPtr = 0;

   memset(dmaChanDesc,0x0,sizeof(dmaChanDesc));       // Clear all the DMA descriptors (individual blocks will update their  descriptors
   uiBasPtr = (uint32_t)&dmaChanDesc;             // Setup the DMA base pointer.
   pADI_DMA->CFG = 1;                              // Enable DMA controller
   pADI_DMA->PDBPTR = uiBasPtr;
}

/**
   @brief void DmaSet(uint32_t Mask, uint32_t Enable, uint32_t Alt, uint32_t Priority)
         ========== Controls Mask, Primary Enable, Alternate enable and priority enable bits
   @param Mask :{SPI0TX_B|SPI0RX_B|SPI1TX_B|SPI1RX_B|SPI2TX_B|SPI2RX_B|UART0TX_B|UART0RX_B
                  |UART1TX_B|UART1RX_B|I2C0STX_B|I2C0SRX_B|I2C0M_B|I2C1STX_B|I2C1SRX_B|I2C1M_B
                  |I2C2STX_B|I2C2SRX_B|I2C2M_B|MDIOTX_B|MDIORX_B|FLASH_B|ADC_B|LVTX_B|LVRX_B|HVTX_B
                  |HVRX_B}
   @param Enable :{SPI0TX_B|SPI0RX_B|SPI1TX_B|SPI1RX_B|SPI2TX_B|SPI2RX_B|UART0TX_B|UART0RX_B
                  |UART1TX_B|UART1RX_B|I2C0STX_B|I2C0SRX_B|I2C0M_B|I2C1STX_B|I2C1SRX_B|I2C1M_B
                  |I2C2STX_B|I2C2SRX_B|I2C2M_B|MDIOTX_B|MDIORX_B|FLASH_B|ADC_B|LVTX_B|LVRX_B|HVTX_B
                  |HVRX_B}
   @param Alt :{SPI0TX_B|SPI0RX_B|SPI1TX_B|SPI1RX_B|SPI2TX_B|SPI2RX_B|UART0TX_B|UART0RX_B
                  |UART1TX_B|UART1RX_B|I2C0STX_B|I2C0SRX_B|I2C0M_B|I2C1STX_B|I2C1SRX_B|I2C1M_B
                  |I2C2STX_B|I2C2SRX_B|I2C2M_B|MDIOTX_B|MDIORX_B|FLASH_B|ADC_B|LVTX_B|LVRX_B|HVTX_B
                  |HVRX_B}
   @param Priority :{SPI0TX_B|SPI0RX_B|SPI1TX_B|SPI1RX_B|SPI2TX_B|SPI2RX_B|UART0TX_B|UART0RX_B
                  |UART1TX_B|UART1RX_B|I2C0STX_B|I2C0SRX_B|I2C0M_B|I2C1STX_B|I2C1SRX_B|I2C1M_B
                  |I2C2STX_B|I2C2SRX_B|I2C2M_B|MDIOTX_B|MDIORX_B|FLASH_B|ADC_B|LVTX_B|LVRX_B|HVTX_B
                  |HVRX_B}
   @return none.
**/
void DmaSet(uint32_t Mask, uint32_t Enable, uint32_t Alt, uint32_t Priority)
{
   pADI_DMA->RMSKSET = Mask;
   pADI_DMA->ENSET = Enable;
   pADI_DMA->ALTSET = Alt;
   pADI_DMA->PRISET = Priority;
}   

/**   
   @brief void DmaClr(uint32_t Mask, uint32_t Disable, uint32_t Alt, uint32_t Priority)
			========== Controls Mask, Primary Enable, Alternate enable and priority Clear bits
   @param Mask :{SPI0TX_B|SPI0RX_B|SPI1TX_B|SPI1RX_B|SPI2TX_B|SPI2RX_B|UART0TX_B|UART0RX_B
                  |UART1TX_B|UART1RX_B|I2C0STX_B|I2C0SRX_B|I2C0M_B|I2C1STX_B|I2C1SRX_B|I2C1M_B
                  |I2C2STX_B|I2C2SRX_B|I2C2M_B|MDIOTX_B|MDIORX_B|FLASH_B|ADC_B|LVTX_B|LVRX_B|HVTX_B
                  |HVRX_B}
   @param Enable :{SPI0TX_B|SPI0RX_B|SPI1TX_B|SPI1RX_B|SPI2TX_B|SPI2RX_B|UART0TX_B|UART0RX_B
                  |UART1TX_B|UART1RX_B|I2C0STX_B|I2C0SRX_B|I2C0M_B|I2C1STX_B|I2C1SRX_B|I2C1M_B
                  |I2C2STX_B|I2C2SRX_B|I2C2M_B|MDIOTX_B|MDIORX_B|FLASH_B|ADC_B|LVTX_B|LVRX_B|HVTX_B
                  |HVRX_B}
   @param Alt :{SPI0TX_B|SPI0RX_B|SPI1TX_B|SPI1RX_B|SPI2TX_B|SPI2RX_B|UART0TX_B|UART0RX_B
                  |UART1TX_B|UART1RX_B|I2C0STX_B|I2C0SRX_B|I2C0M_B|I2C1STX_B|I2C1SRX_B|I2C1M_B
                  |I2C2STX_B|I2C2SRX_B|I2C2M_B|MDIOTX_B|MDIORX_B|FLASH_B|ADC_B|LVTX_B|LVRX_B|HVTX_B
                  |HVRX_B}
   @param Priority :{SPI0TX_B|SPI0RX_B|SPI1TX_B|SPI1RX_B|SPI2TX_B|SPI2RX_B|UART0TX_B|UART0RX_B
                  |UART1TX_B|UART1RX_B|I2C0STX_B|I2C0SRX_B|I2C0M_B|I2C1STX_B|I2C1SRX_B|I2C1M_B
                  |I2C2STX_B|I2C2SRX_B|I2C2M_B|MDIOTX_B|MDIORX_B|FLASH_B|ADC_B|LVTX_B|LVRX_B|HVTX_B
                  |HVRX_B}
   @return none.
**/
void DmaClr(uint32_t Mask, uint32_t Disable, uint32_t Alt, uint32_t Priority)
{
   pADI_DMA->RMSKCLR = Mask;
   pADI_DMA->ENCLR = Disable;
   pADI_DMA->ALTCLR = Alt;
   pADI_DMA->PRICLR = Priority;
}

/**
   @brief uint32_t DmaSta(void)
      ========== Reads the status of the DMA controller.
   @return value of DMASTA	/n
      bit 0 - enabled	/n
      bits [7:4]
      - 0 = Idle
      - 1 = Reading channel controller data
      - 2 = Reading source data end pointer
      - 3 = Reading destination end pointer
      - 4 = Reading source data
      - 5 = Writing destination data
      - 6 = Waiting for DMArequest to clear
      - 7 = Writing channel controller data
      - 8 = Stalled
      - 9 = Done
      - 10 = Scatter gather transition.
      bits [20:16]
      - number of DMA channels available -1
**/
uint32_t DmaSta(void)
{
   return pADI_DMA->STAT;
}

/**
   @brief uint32_t DmaErr(uint32_t ErrClr)
         ========== Reads and optionally clears DMA error bit.
   @param ErrClr :{DMA_ERR_RD,DMA_ERR_CLR}
      - 0 or DMA_ERR_RD only reads error bit.
      - 1 or DMA_ERR_CLR reads then clears error bit.
   @return value of DMAERRCLR
      - 0 - flags no error
      - 1 - flags error.
**/
uint32_t DmaErr(uint32_t ErrClr)
{
   if(ErrClr)
      pADI_DMA->ERRCLR = 1;
   return pADI_DMA->ERRCLR;
}

/**
   @brief void DmaPeripheralStructSetup(uint32_t Chan, uint32_t Cfg)
         ==========Sets up DMA config structure for the required channel

   @param @param Chan :  value of DMA_CHANNEL_t enum;
   @param Cfg :{DMA_DSTINC_BYTE|DMA_DSTINC_HWORD|DMA_DSTINC_WORD|DMA_DSTINC_NO|
                 DMA_SRCINC_BYTE|DMA_SRCINC_HWORD|DMA_SRCINC_WORD|DMA_SRCINC_NO|
                 DMA_SIZE_BYTE|DMA_SIZE_HWORD|DMA_SIZE_WORD}
   - Choose one of DMA_DSTINC_BYTE,DMA_DSTINC_HWORD,DMA_DSTINC_WORD,DMA_DSTINC_NO for destination address increment
   - Choose one of DMA_SRCINC_BYTE,DMA_SRCINC_HWORD,DMA_SRCINC_WORD,DMA_SRCINC_NO for source address increment
   - Choose one of DMA_SIZE_BYTE (byte),DMA_SIZE_HWORD (half-word),DMA_SIZE_WORD(word) for source data size
   @return none

**/
void DmaPeripheralStructSetup(uint32_t Chan, uint32_t Cfg)
{
   DmaDesc Desc;
   Desc.ctrlCfg.ctrlCfgVal = 0;
   Desc.destEndPtr = 0;
   Desc.reserved4Bytes = 0;
   Desc.srcEndPtr = 0;

    // Common configuration of all the descriptors used here
    Desc.ctrlCfg.Bits.cycle_ctrl       = (Cfg & 0x7);
   Desc.ctrlCfg.Bits.r_power          = 0;
   Desc.ctrlCfg.Bits.src_size         = ((Cfg & 0x3000000)>>24);
   Desc.ctrlCfg.Bits.dst_size         = ((Cfg & 0x3000000)>>24);

   Desc.ctrlCfg.Bits.n_minus_1        = 0;
//     Desc.ctrlCfg.Bits.n_minus_1        = 16;
   Desc.ctrlCfg.Bits.src_inc          = ((Cfg & 0xC000000)>>26);
   Desc.ctrlCfg.Bits.dst_inc          = ((Cfg & 0xC0000000)>>30);

//     Desc.ctrlCfg.Bits.src_size         = 1;
//     Desc.ctrlCfg.Bits.dst_size         = 1;

//     Desc.ctrlCfg.Bits.src_inc          = 1;
//     Desc.ctrlCfg.Bits.dst_inc          = 3;

   *Dma_GetDescriptor(Chan) = Desc;     // structure

}
/**
   @brief uint32_t DmaStructPtrOutSetup(uint32_t Chan, uint32_t NumVals, const uint8_t *pucTX_DMA)
            ==========For DMA operations where the destination is fixed (peripheral register is fixed)
   @param @param Chan :  value of DMA_CHANNEL_t enum;
   @param NumVals :{1-1024}
   - 1 to 1024. Number of values to transfer
   @param *pucTX_DMA :{0-0xFFFFFFFF}
   - Pass Source pointer  address for DMA transfers
   @return 1 if suceeded or 0 if it fails
   @warning DmaPeripheralStructSetup() must be called first

**/

uint32_t DmaStructPtrOutSetup(uint32_t Chan, uint32_t NumVals, const uint8_t *pucTX_DMA)
{
   uint32_t Byt = 0;  // number of bytes per dma value to be transmitted
   switch(dmaChanDesc[Chan].ctrlCfg.Bits.src_size)
   {
      case  SIZE_BYTE:
         Byt = 1;
         break;
      case SIZE_HWORD:
         Byt = 2;
         break;
      case SIZE_WORD:
         Byt = 4;
         break;
      default:
         return 0;
   }

   switch (Chan)
   {
      case ALT_SPI0TX_C:
      case SPI0TX_C:  // SPI0 Tx
         dmaChanDesc[Chan].srcEndPtr    = (unsigned int)(pucTX_DMA+ Byt*(NumVals - 0x1) );
         dmaChanDesc[Chan].destEndPtr   = (unsigned int)(&pADI_SPI0->TX);
		   break;
      case ALT_SPI1TX_C:
      case SPI1TX_C:  // SPI1 Tx
         dmaChanDesc[Chan].srcEndPtr    = (unsigned int)(pucTX_DMA+ Byt*(NumVals - 0x1) );
         dmaChanDesc[Chan].destEndPtr   = (unsigned int)(&pADI_SPI1->TX);
		   break;
      case ALT_SPI2TX_C:
      case SPI2TX_C:  // SPI2 Tx
         dmaChanDesc[Chan].srcEndPtr    = (unsigned int)(pucTX_DMA+ Byt*(NumVals - 0x1) );
         dmaChanDesc[Chan].destEndPtr   = (unsigned int)(&pADI_SPI2->TX);
		   break;
      case ALT_UART0TX_C:
      case UART0TX_C:  // UART0 Tx
         dmaChanDesc[Chan].srcEndPtr    = (unsigned int)(pucTX_DMA+ Byt*(NumVals - 0x1) );
         dmaChanDesc[Chan].destEndPtr   = (unsigned int)(&pADI_UART0->RX);
         break;
      case ALT_UART1TX_C:
      case UART1TX_C:  // UART1 Tx
         dmaChanDesc[Chan].srcEndPtr    = (unsigned int)(pucTX_DMA+ Byt*(NumVals - 0x1) );
         dmaChanDesc[Chan].destEndPtr   = (unsigned int)(&pADI_UART1->RX);
         break;
      case ALT_I2C0STX_C:
	case I2C0STX_C:  // I2C0 Slave Tx
         dmaChanDesc[Chan].srcEndPtr    = (unsigned int)(pucTX_DMA+ Byt*(NumVals - 0x1) );
         dmaChanDesc[Chan].destEndPtr   = (unsigned int)(&pADI_I2C0->STX);
         break;
      case ALT_I2C0M_C:
      case I2C0M_C:  // I2C0 Master
         dmaChanDesc[Chan].srcEndPtr    = (unsigned int)(pucTX_DMA+ Byt*(NumVals - 0x1) );
         dmaChanDesc[Chan].destEndPtr   = (unsigned int)(&pADI_I2C0->MTX);
         break;
      case ALT_I2C1STX_C:
	case I2C1STX_C:  // I2C1 Slave Tx
         dmaChanDesc[Chan].srcEndPtr    = (unsigned int)(pucTX_DMA+ Byt*(NumVals - 0x1) );
         dmaChanDesc[Chan].destEndPtr   = (unsigned int)(&pADI_I2C1->STX);
         break;
      case ALT_I2C1M_C:
      case I2C1M_C:  // I2C0 Master
         dmaChanDesc[Chan].srcEndPtr    = (unsigned int)(pucTX_DMA+ Byt*(NumVals - 0x1) );
         dmaChanDesc[Chan].destEndPtr   = (unsigned int)(&pADI_I2C1->MTX);
         break;
      case ALT_I2C2STX_C:
	case I2C2STX_C:  // I2C1 Slave Tx
         dmaChanDesc[Chan].srcEndPtr    = (unsigned int)(pucTX_DMA+ Byt*(NumVals - 0x1) );
         dmaChanDesc[Chan].destEndPtr   = (unsigned int)(&pADI_I2C2->STX);
         break;
      case ALT_I2C2M_C:
      case I2C2M_C:  // I2C0 Master
         dmaChanDesc[Chan].srcEndPtr    = (unsigned int)(pucTX_DMA+ Byt*(NumVals - 0x1) );
         dmaChanDesc[Chan].destEndPtr   = (unsigned int)(&pADI_I2C2->MTX);
         break;
      case ALT_MDIOTX_C:
      case MDIOTX_C:  // I2C0 Master
         dmaChanDesc[Chan].srcEndPtr    = (unsigned int)(pucTX_DMA+ Byt*(NumVals - 0x1) );
         dmaChanDesc[Chan].destEndPtr   = (unsigned int)(&pADI_MDIO->MDTXD);
         break;
      case ALT_FLASH_C:
      case FLASH_C:  // Flash
         dmaChanDesc[Chan].srcEndPtr    = (unsigned int)(pucTX_DMA+ Byt*(NumVals - 0x1) );
         dmaChanDesc[Chan].destEndPtr   = (unsigned int)(&pADI_FLASH->FEEFLDATA1);
         dmaChanDesc[Chan].ctrlCfg.Bits.r_power      = 1;   //2 transactions per req
         break;
      //lV,HV, TBC
	default:
	   return 0;
	}
      return 1;
}
/**
   @brief int DmaStructPtrInSetup(int Chan, int NumVals, unsigned char *pucRX_DMA);
	 			==========For DMA operations where the source is fixed (peripheral register is fixed)
   @param @param Chan :  value of DMA_CHANNEL_t enum;
   @param NumVals :{1-1024}
    - 1 to 1024. Number of values to transfer
   @param *pucRX_DMA :{0-0xFFFFFFFF}
    - Pass pointer to destination address for DMA transfers
   @return 1 if suceeded or 0 if it fails
   @warning DmaPeripheralStructSetup() must be called first
**/
uint32_t DmaStructPtrInSetup(uint32_t Chan, uint32_t NumVals, uint8_t *pucRX_DMA)
{
   uint32_t Byt = 0;  // number of bytes per dma value to be transmitted
   switch(dmaChanDesc[Chan].ctrlCfg.Bits.src_size)
   {
      case  SIZE_BYTE:
         Byt = 1;
         break;
      case SIZE_HWORD:
         Byt = 2;
         break;
      case SIZE_WORD:
         Byt = 4;
         break;
      default:
         return 0;
   }

   switch (Chan)
   {
      case ALT_SPI0RX_C:
      case SPI0RX_C:  // SPI0 Rx
         dmaChanDesc[Chan].destEndPtr    = (unsigned int)(pucRX_DMA+ Byt*(NumVals - 0x1) );
         dmaChanDesc[Chan].srcEndPtr   = (unsigned int)(&pADI_SPI0->RX);
		   break;
      case ALT_SPI1RX_C:
      case SPI1RX_C:  // SPI1 Rx
         dmaChanDesc[Chan].destEndPtr    = (unsigned int)(pucRX_DMA+ Byt*(NumVals - 0x1) );
         dmaChanDesc[Chan].srcEndPtr     = (unsigned int)(&pADI_SPI1->RX);
		   break;
      case ALT_SPI2RX_C:
      case SPI2RX_C:  // SPI1 Rx
         dmaChanDesc[Chan].destEndPtr    = (unsigned int)(pucRX_DMA+ Byt*(NumVals - 0x1) );
         dmaChanDesc[Chan].srcEndPtr     = (unsigned int)(&pADI_SPI2->RX);
		   break;
      case ALT_UART0RX_C:
      case UART0RX_C:  // UART Rx
         dmaChanDesc[Chan].destEndPtr    = (unsigned int)(pucRX_DMA+ Byt*(NumVals - 0x1) );
         dmaChanDesc[Chan].srcEndPtr   = (unsigned int)(&pADI_UART0->RX);
         break;
      case ALT_UART1RX_C:
      case UART1RX_C:  // UART Rx
         dmaChanDesc[Chan].destEndPtr    = (unsigned int)(pucRX_DMA+ Byt*(NumVals - 0x1) );
         dmaChanDesc[Chan].srcEndPtr   = (unsigned int)(&pADI_UART1->RX);
         break;
      case ALT_I2C0SRX_C:
      case I2C0SRX_C:  // I2C0 Slave Rx
         dmaChanDesc[Chan].destEndPtr    = (unsigned int)(pucRX_DMA+ Byt*(NumVals - 0x1) );
         dmaChanDesc[Chan].srcEndPtr   = (unsigned int)(&pADI_I2C0->SRX);
         break;
      case ALT_I2C0M_C:
      case I2C0M_C:  // I2C0 Master Rx
         dmaChanDesc[Chan].destEndPtr    = (unsigned int)(pucRX_DMA+ Byt*(NumVals - 0x1) );
         dmaChanDesc[Chan].srcEndPtr   = (unsigned int)(&pADI_I2C0->MRX);
		   break;
      case ALT_I2C1SRX_C:
      case I2C1SRX_C:  // I2C1 Slave Rx
         dmaChanDesc[Chan].destEndPtr    = (unsigned int)(pucRX_DMA+ Byt*(NumVals - 0x1) );
         dmaChanDesc[Chan].srcEndPtr   = (unsigned int)(&pADI_I2C1->SRX);
         break;
      case ALT_I2C1M_C:
      case I2C1M_C:  // I2C1 Master Rx
         dmaChanDesc[Chan].destEndPtr    = (unsigned int)(pucRX_DMA+ Byt*(NumVals - 0x1) );
         dmaChanDesc[Chan].srcEndPtr   = (unsigned int)(&pADI_I2C1->MRX);
		   break;
      case ALT_I2C2SRX_C:
      case I2C2SRX_C:  // I2C1 Slave Rx
         dmaChanDesc[Chan].destEndPtr    = (unsigned int)(pucRX_DMA+ Byt*(NumVals - 0x1) );
         dmaChanDesc[Chan].srcEndPtr   = (unsigned int)(&pADI_I2C2->SRX);
         break;
      case ALT_I2C2M_C:
      case I2C2M_C:  // I2C1 Master Rx
         dmaChanDesc[Chan].destEndPtr    = (unsigned int)(pucRX_DMA+ Byt*(NumVals - 0x1) );
         dmaChanDesc[Chan].srcEndPtr   = (unsigned int)(&pADI_I2C2->MRX);
		   break;
      case ALT_MDIORX_C:
      case MDIORX_C:  // MDIO Rx
         dmaChanDesc[Chan].destEndPtr    = (unsigned int)(pucRX_DMA+ Byt*(NumVals - 0x1) );
         dmaChanDesc[Chan].srcEndPtr   = (unsigned int)(&pADI_MDIO->MDRXD);
		   break;
      //ADC HV,LV TBC
      default:
         return 0;
      }
   return 1;
}
/**
   @brief void DmaGo(uint32_t Chan, uint32_t Numx, uint32_t Cfg)
            ==========Used to re-enable DMA config structure
   @param @param Chan :  value of DMA_CHANNEL_t enum;
   @param Cfg :{DMA_STOP|DMA_BASIC|DMA_AUTO|DMA_PING|DMA_PSG_PRI|DMA_PSG_ALT}
    - Choose one of DMA_STOP,DMA_BASIC,DMA_AUTO,DMA_PING,DMA_PSG_PRI,DMA_PSG_ALT
   @param Numx :{1-1024}
    - Number of values to transfer
 @return 1:

**/
void DmaGo(uint32_t Chan, uint32_t Numx, uint32_t Cfg)
{
//  	Chan--;
	dmaChanDesc[Chan].ctrlCfg.Bits.cycle_ctrl       = (Cfg & 0x7);
	dmaChanDesc[Chan].ctrlCfg.Bits.n_minus_1        = Numx - 0x1;
}

/**
   @brief uint32_t AdcDmaReadSetup(uint32_t Chan, uint32_t NumVals, uint32_t Ain, uint32_t *pucRX_DMA)
         ==========Sets up DMA config structure when moving ADC results direct to memory
   @param Chan :{ADC_C,ALT_ADC_C}
    - 20 or ADC_C     for the ADC output channel          - primary structure
    - 42 or ALT_ADC_C      for the ADC output channel          - ALTERNATE structure
  @param NumVals :{1-1024}
    - 1 to 1024. Number of values to transfer
  @param Ain :{AIN0,AIN1,AIN2,AIN3,AIN4,AIN5,AIN6,AIN7,AIN8,AIN9,AIN_IDAC4,
               AIN_IDAC5,AIN_IDAC3,AIN_IDAC0,AIN_IDAC1,AIN_IDAC2,TEMP_SENSOR,VREFP_PADC,PVDD_GAIN,IOVDD_2,
               AVDD_2,VREFN_PADC}
		- ADCCHA.[4:0]
   @param *pucRX_DMA :{0-0xFFFFFFFF}
    - Pass pointer to destination address for DMA transfers
   @return 1 if suceeded or 0 if it fails
   @warning DmaPeripheralStructSetup() must be called first

**/
uint32_t AdcDmaReadSetup(uint32_t Chan, uint32_t NumVals, uint32_t Ain, uint32_t *pucRX_DMA)
 {
   uint32_t Byt = 4;  // number of bytes per dma value to be transmitted

   switch (Chan)
   {
       case ADC_C: // ADC write to control registers
       case ALT_ADC_C:
          dmaChanDesc[Chan].destEndPtr    = (uint32_t)(pucRX_DMA) + Byt*(NumVals - 0x1);
          dmaChanDesc[Chan].srcEndPtr   = ((uint32_t)(&pADI_ADC->ADCDAT0))+Ain;
 		   break;
      default:
         return 0;
      }
   return 1;
 }

/*
@brief void DmaSetup(DMA_SETUP_t * pSetup)
      ===========setup function for DMA block
 
@param pSetup: pointer of setup structure
@return none
**/
void DmaSetup(DMA_SETUP_t * pSetup)
{
   pADI_DMA->CFG = 1;
   pADI_DMA->ENCLR = ~(pSetup->chanEn);
   pADI_DMA->RMSKSET = pSetup->chanMask;
   pADI_DMA->RMSKCLR = ~(pSetup->chanMask);
   pADI_DMA->ALTSET = pSetup->useAlt;
   pADI_DMA->ALTCLR = ~(pSetup->useAlt);
   pADI_DMA->PRISET = pSetup->priority;
   pADI_DMA->PRICLR = ~(pSetup->priority);
   pADI_DMA->BSSET = pSetup->byteSwap;
   pADI_DMA->BSCLR = ~(pSetup->byteSwap);
   pADI_DMA->SRCADDRSET = pSetup->srcAddrDec;
   pADI_DMA->SRCADDRCLR = ~(pSetup->srcAddrDec);
   pADI_DMA->DSTADDRSET = pSetup->srcAddrDec;
   pADI_DMA->DSTADDRCLR = ~(pSetup->srcAddrDec);

   if(pSetup->pDmaChxDesc==NULL)
   {
      pSetup->pDmaChxDesc = dmaChanDesc;
      pADI_DMA->PDBPTR = (uint32_t)&dmaChanDesc[0];
   }

   pADI_DMA->ENSET = pSetup->chanEn;
}


/**@}*/




