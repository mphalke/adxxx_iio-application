/*!
 *****************************************************************************
 * @file:   UrtLib.h
 * @brief:  Set of UART peripheral functions.
 *-----------------------------------------------------------------------------
 *
Copyright (c) 2013-2018 Analog Devices, Inc. All Rights Reserved.

This software is proprietary to Analog Devices, Inc. and its licensors.
By using this software you agree to the terms of the associated
Analog Devices Software License Agreement.
 ******************************************************************************/

#ifndef URT_LIB_H
#define URT_LIB_H

#include <ADuCM410.h>

// baud rate settings
#define B1200	1200
#define B2200	2200
#define B2400	2400
#define B4800	4800
#define B9600	9600
#define B19200	19200
#define B38400	38400
#define B57600	57600
#define B115200	115200
#define B230400	230400
#define B430800	430800


/*Urt Line Control Register */
#define COMLCR_BRK_EN               1
#define COMLCR_BRK_DIS              0
#define COMLCR_SP_EN                (0x20)
#define COMLCR_EPS_EVEN             (0x10)
#define COMLCR_PEN_EN               (0x08)
#define COMLCR_STOP_MULTIBIT        (0x04)
#define COMLCR_STOP_ONEBIT          (0x00)

/*Urt Interrupt Enable Register*/
#define COMIEN_ERBFI                (0x01)
#define COMIEN_ETBEI                (0x02)
#define COMIEN_ELSI                 (0x04)
#define COMIEN_EDSSI                (0x08)
#define COMIEN_EDMAT                (0x10)    
#define COMIEN_EDMAR                (0x20)

#define DEFAULT_ROOTCLK             (160000000)
#define OSC32M_ROOTCLK              (32000000)
#ifdef FPGA_VALIDATION
   #define OSC16M_ROOTCLK              (32000000)
#else
   #define OSC16M_ROOTCLK              (16000000)
#endif
#define PLL_ROOTCLK                 (160000000)
#define EXT_GPIO_ROOTCLK            (80000000)   //External clock is assumed to be 80MhZ, if different clock speed is used, this should be changed

#define RX_FIFO_1BYTE               (0x00) 
#define RX_FIFO_4BYTE               (0x40)
#define RX_FIFO_8BYTE               (0x80)
#define RX_FIFO_14BYTE              (0xC0)

#define WORD_5BIT                   (0x00)
#define WORD_6BIT                   (0x01)
#define WORD_7BIT                   (0x02)
#define WORD_8BIT                   (0x03)

#define ENUM_UART_STOPBIT1      0
#define ENUM_UART_STOPBIT2      1

#define ENABLE_IRQ                  (1)
#define DISABLE_IRQ                 (0)

typedef struct
{
    //--------- configuration ---------
    //1200,2200,2400,4800,9600,19200,
    //38400,57600,115200,230400,430800,etc.
    uint32_t baudrate;
    //bit length of each frame
    // 0 or ENUM_UART_LCR_WLS_BITS5        /* 5 Bits */
    // 1 or ENUM_UART_LCR_WLS_BITS6       /* 6 Bits */
    // 2 or ENUM_UART_LCR_WLS_BITS7       /* 7 Bits */
    // 3 or ENUM_UART_LCR_WLS_BITS8       /* 8 Bits */
    uint32_t bitLength;
    //nubmer of stop bit
    // 0 or ENUM_UART_STOPBIT1, send one stop bit
    // 1 or ENUM_UART_STOPBIT2, send 1.5 stop bit when bitLength is 5 bit,
    // or send 2 stop bit when bitLength is others
    uint32_t stopBit;
    //parity enable
    // 0 - parity will not transmitted or checked
    // 1 - parity will be transmitted and checked
    uint32_t parityEn;
    //ENUM_UART_LCR_EPS_ODD,  Odd Parity Will Be Transmitted and Checked. 
    //ENUM_UART_LCR_EPS_EVEN,   Even Parity Will Be Transmitted and Checked. 
    uint32_t parityType;
    //set permanent '1' or '0' as parity when transmitting or receiveing data,
    //depending on the state of parityEn and parityType
    //parityEn | parityType | Parity Bit
    //    0         0           1
    //TBC
    uint32_t stickParityEn;
    // 0 - disable loopback mode
    // 1 - enable loopback mode
    uint32_t loopback;

    //---------- FIFO --------------
    // 0 - FIFO enable
    // 1 - FIFO disable
    uint32_t fifoEn;
    //1//4/8/14 byte to trig Rx Interrupt
    //ENUM_UART_FCR_RFTRIG_BYTE1    /* 1 Byte to Trig RX Interrupt */
    //ENUM_UART_FCR_RFTRIG_BYTE4    /* 4 Byte to Trig RX Interrupt */
    //ENUM_UART_FCR_RFTRIG_BYTE8    /* 8 Byte to Trig RX Interrupt */
    //ENUM_UART_FCR_RFTRIG_BYTE14   /* 14 Byte to Trig RX Interrupt */
    uint32_t fifoIntTrigger;
    //
    uint32_t fifoDmaMode;

    //--------- Interrupt -----------
    // 0 - disable
    // 1 - enable
    uint32_t rxBufFullIntEn;
    uint32_t txIntEn;
    uint32_t lineErrIntEn;
    uint32_t modemIntEn;

    //---------- Dma ------------
    // 0 - disable
    // 1 - enable
    uint32_t rxDmaEn;
    uint32_t txDmaEn;
}Urt_SETUP_t;

extern Urt_SETUP_t gUrt0Setup;
extern Urt_SETUP_t gUrt1Setup;

//------------------------------ Function prototypes ------------------------------------------
void UrtSetup(ADI_UART_TypeDef *pPort, const Urt_SETUP_t *pSetup);

uint32_t UrtCfg(ADI_UART_TypeDef *pPort, uint32_t iBaud, uint32_t iBits, uint32_t iFormat);
uint32_t UrtFifoCfg(ADI_UART_TypeDef *pPort, uint32_t iFifoSize, uint32_t iFIFOEn);
uint32_t UrtFifoClr(ADI_UART_TypeDef *pPort, uint32_t iClrEn);
uint32_t UrtBrk(ADI_UART_TypeDef *pPort, uint32_t iBrk);
uint32_t UrtLinSta(ADI_UART_TypeDef *pPort);
uint32_t UrtTx(ADI_UART_TypeDef *pPort, uint32_t iTx);
uint32_t UrtRx(ADI_UART_TypeDef *pPort);
uint32_t UrtMod(ADI_UART_TypeDef *pPort, uint32_t iMcr, uint32_t iWr);
uint32_t UrtModSta(ADI_UART_TypeDef *pPort);
uint32_t UrtIntCfg(ADI_UART_TypeDef *pPort, uint32_t iIrq);
uint32_t UrtIntSta(ADI_UART_TypeDef *pPort);
#endif // URT_LIB_H

