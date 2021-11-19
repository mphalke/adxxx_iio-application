/*!
 *****************************************************************************
 * @file:   ADuCM410_Setup.c
 * @brief:  setup for ADuCM410
 *-----------------------------------------------------------------------------
 *
Copyright (c) 2020 Analog Devices, Inc. All Rights Reserved.

This software is proprietary to Analog Devices, Inc. and its licensors.
By using this software you agree to the terms of the associated
Analog Devices Software License Agreement.
 ******************************************************************************/

#include "UrtLib.h"
#include "ClkLib.h"
#include "IntLib.h"
#include "SpiLib.h"

#include "app_config.h"

/*
   System Clock Default Setup for User
*/
CLK_SETUP_t gClkSetup = {
	//--------- configuration ---------
	.pllEn = 1,
	.rootClkMux = ENUM_CLOCK_CLKCON0_CLKMUX_SPLL,
	.analogClkMux = ENUM_CLOCK_CLKCON0_ANACLKMUX_HFOSC,

//-----------------Clock Divider -------------
	.hclkDiv = ENUM_CLOCK_CLKCON1_CDHCLK_DIV1,
	.pclk0Div = ENUM_CLOCK_CLKCON1_CDPCLK0_DIV8,
	.pclk1Div = ENUM_CLOCK_CLKCON1_CDPCLK1_DIV8,
	.clockOff = 0x00000000,  //all clock on

	//---------Interrupt------------
	.pllIntEn = 0,    //0 - disable interrrupt related to PLL

	//-------TEST CLOCK -------
	.clkOutput = ENUM_CLOCK_CLKCON0_CLKOUT_B1_PCLK,
};


/*
   UART1 Default Setup for User
*/
Urt_SETUP_t gUrt1Setup = {
	//--------- configuration ---------
	//230400-8-1
	.baudrate = IIO_UART_BAUD_RATE,
	.bitLength = ENUM_UART_LCR_WLS_BITS8,
	.stopBit = ENUM_UART_STOPBIT1,
	.parityEn = 0,
	.parityType = ENUM_UART_LCR_EPS_ODD,
	.stickParityEn = 0,
	.loopback = 0,
	//----------- FIFO ------------
	.fifoEn = 0,
	.fifoIntTrigger = ENUM_UART_FCR_RFTRIG_BYTE8,
	.fifoDmaMode = 0,
	//--------- Interrupt -----------
	.rxBufFullIntEn = 1, // Enabled
	.txIntEn = 0,
	.lineErrIntEn = 0,
	.modemIntEn = 0,
	//---------- Dma ------------
	.rxDmaEn = 0,
	.txDmaEn = 0,
};


/*
 * SPI1 Default Setup for User:
 * Mode 3, Master Mode, CS asserts/deasserts automatically
 * */
SPI_SETUP_t gSpi1Setup = {
	.spiEn = 1,  // SPI enabled
	.masterEn = 1, // master mode enabled
	.cpha = 1,   // clock phase
	.cpol = 1,      // clock polarity
	.wireOrEn = 0,//0 - SPI wire or mode disabled
	.lsbFirst = 0,   //0 - MSB transfered first
	.txTrigTransfer = 0, // Read RX data register to trigger transfer
	.rxOverwrite = 0,//0 - Rx register is overwriten by new serial byte received
	.fifoEmtpyTx = FIFOEMPTY_TX_0,   //0 - send '0' when no valid data in Tx FIFO
	.misoEn = 0,  //0 - disable miso drive in slave mode
	.continousTx = 1,   //1 - transfer continuous until no valid data in Tx register.
	.loopback = 0,   //0 - disable loopback
	.threePinMode = 0,  //0 - normal mode

	//----------- Interrupt -------------
	.txrxIrqByte = 0,//Interrupt Occurs After 4 Byte is Transfered or Received
	.csIntEn = 0,
	.txUnderflowIntEn = 0,
	.rxOverflowIntEn = 0,
	.readyIntEn = 0,
	.txDoneIntEn = 0,
	.frameEndIntEn = 0,
	.txFifoEmptyIntEn = 0,

	//------------- Dma -----------------
	.txDmaEn = 0,
	.rxDmaEn = 0,

	//-------------- Read command mode -----------
	.readCmdEn = 0, //0 - disable read command mode
	.txByte = 0,    //number of bytes to be transmitted before reading data
	.txRxOverlap = 0,
};


/*
 * External Interrupt Default Setup for User
 * */
EXINT_SETUP_Type gExIntSetup = {
	.exIntChan[0] = {
		.irqMode = ENUM_ALWAYS_ON_EI0CFG_IRQ0MDE_RISE,
		.irqEn = 0
	}, //disable irq0
	.exIntChan[1] = {
		.irqMode = ENUM_ALWAYS_ON_EI0CFG_IRQ0MDE_RISE,
		.irqEn = 0
	}, //disable irq1
	.exIntChan[2] = {
		.irqMode = ENUM_ALWAYS_ON_EI0CFG_IRQ0MDE_RISE,
		.irqEn = 0
	}, //disable irq2
	.exIntChan[3] = {
		.irqMode = ENUM_ALWAYS_ON_EI0CFG_IRQ0MDE_RISE,
		.irqEn = 0
	}, //disable irq3
	.exIntChan[4] = {
		.irqMode = ENUM_ALWAYS_ON_EI0CFG_IRQ0MDE_RISE,
		.irqEn = 0
	}, //disable irq4
	.exIntChan[5] = {
		.irqMode = ENUM_ALWAYS_ON_EI0CFG_IRQ0MDE_FALL,
		.irqEn = 1
	}, //enable irq5
	.exIntChan[6] = {
		.irqMode = ENUM_ALWAYS_ON_EI0CFG_IRQ0MDE_RISE,
		.irqEn = 0
	}, //disable irq6
	.exIntChan[7] = {
		.irqMode = ENUM_ALWAYS_ON_EI0CFG_IRQ0MDE_RISE,
		.irqEn = 0
	}, //disable irq7
	.exIntChan[8] = {
		.irqMode = ENUM_ALWAYS_ON_EI0CFG_IRQ0MDE_RISE,
		.irqEn = 0
	}, //disable irq8
	.exIntChan[9] = {
		.irqMode = ENUM_ALWAYS_ON_EI0CFG_IRQ0MDE_RISE,
		.irqEn = 0
	}, //disable irq9
};
