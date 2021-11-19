/*!
 *****************************************************************************
 * @file:   UrtLib.c
 * @brief:  source file of UART interface library
 *-----------------------------------------------------------------------------
 *
Copyright (c) 2013-2018 Analog Devices, Inc. All Rights Reserved.

This software is proprietary to Analog Devices, Inc. and its licensors.
By using this software you agree to the terms of the associated
Analog Devices Software License Agreement.
 ******************************************************************************/

#include "UrtLib.h"


/**
	@brief uint32_t UrtCfg(ADI_UART_TypeDef *pPort, uint32_t iBaud, uint32_t iBits, uint32_t iFormat)
			==========Configure the UART.
	@param pPort :{pADI_UART0, pADI_UART1}	\n
		Set to pADI_UART. Only one channel available.
	@param iBaud :{B1200,B2200,B2400,B4800,B9600,B19200,B38400,B57600,B115200,B230400,B430800}	\n
		Set iBaud to the baudrate required:
		Values usually: 1200, 2200 (for HART), 2400, 4800, 9600, 
		        19200, 38400, 57600, 115200, 230400, 430800, or type in baud-rate directly 
	@param iBits :{COMLCR_WLS_FIVEBITS,COMLCR_WLS_SIXBITS,COMLCR_WLS_SEVENBITS,COMLCR_WLS_EIGHTBITS}	\n
			- 0 = ENUM_UART_LCR_WLS_BITS5 for data length 5bits.
			- 1 = ENUM_UART_LCR_WLS_BITS6 for data length 6bits.
			- 2 = ENUM_UART_LCR_WLS_BITS7 for data length 7bits.
			- 3 = ENUM_UART_LCR_WLS_BITS8 for data length 8bits.
	@param iFormat :{0|COMLCR_STOP_EN|COMLCR_PEN_EN|COMLCR_EPS_EVEN|COMLCR_SP_EN}	\n
		The bitwise or of the data format required:
			- 0x00  = COMLCR_STOP_ONEBIT -> 1.5 stop bits, no parity.
			- 0x04  = COMLCR_STOP_MULTIBIT  -> Set for 2 stop bits.
			- 0x08  = COMLCR_PEN_EN -> Set for Parity enabled
			- 0x10  = COMLCR_EPS_EVEN -> Even parity.
			- 0x20  = COMLCR_SP_EN -> Sticky parity.
	@return Value of COMLSR: See UrtLinSta() function for bit details.
	@note
		- Powers up UART if not powered up.
		- Standard baudrates are accurate to better than 0.1% plus clock error.\n
		- Non standard baudrates are accurate to better than 1% plus clock error.
   @warning - If an external clock is used for the system the ullRtClk must be modified with \n
         the speed of the clock used.
**/

uint32_t UrtCfg(ADI_UART_TypeDef *pPort, uint32_t iBaud, uint32_t iBits, uint32_t iFormat)
{
    uint32_t i1,M;
    uint32_t iDiv;
    uint32_t iRtC;
    uint32_t iOSR;
    unsigned long long ullRtClk = DEFAULT_ROOTCLK;            // The root clock speed

    iDiv = (pADI_CLK->CLKCON1 & BITM_CLOCK_CLKCON1_CDPCLK1);       // Read UART clock from APB1 as set by CLKCON1[8:6]
    iDiv = iDiv >> BITP_CLOCK_CLKCON1_CDPCLK1;
    iDiv = 1 << iDiv;                                  // iDiv exponentiation base on 2

   
    iRtC = (pADI_CLK->CLKCON0 & BITM_CLOCK_CLKCON0_CLKMUX);  // Check what is the root clock
    iRtC >>= BITP_CLOCK_CLKCON0_CLKMUX;

    switch (iRtC)
    {
        case ENUM_CLOCK_CLKCON0_CLKMUX_HFOSC:
            ullRtClk = OSC16M_ROOTCLK;
        break;

        case ENUM_CLOCK_CLKCON0_CLKMUX_SPLL:
            ullRtClk = PLL_ROOTCLK;
        break;

        case ENUM_CLOCK_CLKCON0_CLKMUX_EXTCLK:
            ullRtClk = EXT_GPIO_ROOTCLK;            //External clock is assumed to be 80MhZ, if different                              
        break;                                      //clock speed is used, this should be changed
                                       
        default:     
        break;
    }

    pPort->LCR2 = (uint16_t)ENUM_UART_LCR2_OSR_OSR16;
    iOSR = 16;
    i1 = (uint32_t)((ullRtClk / (iOSR * iDiv)) / iBaud - 1);          //for bigger M and N value
    i1 = (i1==0)? 1: i1;   //DIV cannot be 0
    pPort->DIV = (uint16_t)i1;

	 M = (uint32_t)(ullRtClk / (iOSR * iDiv) / iBaud / i1);
    
    pPort->FBR = (uint16_t)(BITM_UART_FBR_FBEN \
                |(M << BITP_UART_FBR_DIVM) \
                |(((((2048/(iOSR*iDiv))*ullRtClk)/i1)/iBaud) - 2048*M));
    pPort->IEN = (uint16_t)0;
    pPort->LCR = (uint16_t)((iFormat & 0x3c) | (iBits & BITM_UART_LCR_WLS));
    
    return pPort->LSR;
}

/**
	@brief uint32_t UrtFifoCfg(ADI_UART_TypeDef *pPort, uint32_t iFifoSize, uint32_t iFIFOEn)
			==========Configure the UART FIFO.
	@param pPort :{pADI_UART,}	\n
		Set to pADI_UART. Only one channel available.
	@param iFifoSize :{0,1,2,3}	\n
			- 0    = RX_FIFO_1BYTE  ->  Rx Trigger interrupt after 1 byte received
			- 0x40 = RX_FIFO_4BYTE  ->  Rx Trigger interrupt after 4 bytes received
			- 0x80 = RX_FIFO_8BYTE  ->  Rx Trigger interrupt after 8 bytes received
			- 0xC0 = RX_FIFO_14BYTE ->  Rx Trigger interrupt after 14 bytes received
	@param iFIFOEn :{0,BITM_UART_COMFCR_FIFOEN}	\n
		The bitwise or of the data format required:
			- BITP_UART_FIFOEN = disable UART FIFO
			- BITL_UART_FIFOEN = BITM_UART_COMFCR_FIFOEN  ->enable FIFOs
	@return Value of COMFCR
**/
uint32_t UrtFifoCfg(ADI_UART_TypeDef *pPort, uint32_t iFifoSize, uint32_t iFIFOEn)
{
   pPort->FCR = (uint16_t)((BITM_UART_FCR_RFTRIG & iFifoSize ) | iFIFOEn);
 
   return  pPort->FCR;
}

/**
	@brief uint32_t UrtFifoClr(ADI_UART_TypeDef *pPort, uint32_t iClrEn)
			==========Clear the UART FIFOs.
	@param pPort :{pADI_UART,}	\n
		Set to pADI_UART. Only one channel available.
	@param iClrEn :{0,BITM_UART_COMFCR_TFCLR|BITM_UART_COMFCR_RFCLR}	\n
		The bitwise or of the data format required:
            - 0   = normal FIFO operation
            - 0x2 = BITM_UART_RFCLR -> clear Rx FIFO
            - 0x4 = BITM_UART_TFCLR -> clear Tx FIFO
	@return Value of COMFCR
**/
uint32_t UrtFifoClr(ADI_UART_TypeDef *pPort, uint32_t iClrEn)
{
   pPort->FCR |= iClrEn;                                   // Clear the UART FIFOs
   pPort->FCR &= ~(iClrEn);                                // Disable clearing mechanism
   
   return pPort->FCR;
}


/**
	@brief uint32_t UrtBrk(ADI_UART_TypeDef *pPort, uint32_t iBrk)
			==========Force SOUT pin to 0
	@param pPort :{pADI_UART0, pADI_UART1}	\n
		Set to pADI_UART. Only one channel available.
	@param iBrk :{COMLCR_BRK_DIS, COMLCR_BRK_EN}	\n
		- 0 = COMLCR_BRK_DIS to disable SOUT break condition (SOUT behaves as normal)
		- 1 = COMLCR_BRK_EN to force SOUT break condition - SOUT remains low until this bit is cleared
	@return Value of LSR: See UrtLinSta() function for bit details.
**/
uint32_t UrtBrk(ADI_UART_TypeDef *pPort, uint32_t iBrk)
{
    if(iBrk == 0)
    {
        pPort->LCR &= ~BITM_UART_LCR_BRK;		//Disable break condition on SOUT pin.
    }
    else
    {
        pPort->LCR |= BITM_UART_LCR_BRK;		//Force break condition on SOUT pin.
    }
    
    return	pPort->LSR;
}
/**
	@brief uint32_t UrtLinSta(ADI_UART_TypeDef *pPort)
			==========Read the status byte of the UART.
	@param pPort :{pADI_UART0, pADI_UART1}	\n
		Set to pADI_UART. Only one channel available.
	@return value of COMLSR:
		- BITM_UART_DR = Data ready.
		- BITM_UART_OE = Overrun error.
		- BITM_UART_PE = Parity error.
		- BITM_UART_FE = Framing error.
		- BITM_UART_BI = Break indicator.
		- BITM_UART_LSR_THRE = COMTX empty status bit.
		- BITM_UART_TEMT = COMTX and shift register empty status bit.
		- BITM_UART_FIFOERR = Data Byte(s) in RX FIFO Have Either Parity Error, Frame Error or Break Indication. 
	@warning	UART must be configured before checking status.
**/

uint32_t UrtLinSta(ADI_UART_TypeDef *pPort)
{
    return	pPort->LSR;
}

/**
	@brief uint32_t UrtTx(ADI_UART_TypeDef *pPort, uint32_t iTx)
			==========Write 8 bits of iTx to the UART.
	@param pPort :{pADI_UART0, pADI_UART1}	\n
		Set to pADI_UART. Only one channel available.
	@param iTx :{0-255}	\n
		Byte to transmit.
	@return 1 if successful or 0 if TX buffer full already:
	@warning
		UART must be configured before writing data.\n
		Character is lost if TX buffer already full.
**/

uint32_t UrtTx(ADI_UART_TypeDef *pPort, uint32_t iTx)
{
    if(pPort->LSR & BITM_UART_LSR_THRE)
    {
        pPort->TX = (uint16_t)iTx;
        return 1;
    }
    
    return 0;
}

/**
	@brief uint32_t UrtRx(ADI_UART_TypeDef *pPort)
			==========Read the UART data.
	@param pPort :{pADI_UART0, pADI_UART1}	\n
		Set to pADI_UART. Only one channel available.
	@return The byte in the Rx buffer (COMRX).
	@note
		- Does not wait if no new character available.
**/

uint32_t UrtRx(ADI_UART_TypeDef *pPort)
{
    return (pPort->RX & 0xff);
}

/**
	@brief uint32_t UrtMod(ADI_UART_TypeDef *pPort, uint32_t iMcr, uint32_t iWr)
			==========Write iMcr to UART Modem Control Register
	@param pPort :{pADI_UART0, pADI_UART1}	\n
		Set to pADI_UART. Only one channel available.
	@param iMcr :{0|COMMCR_DTR|COMMCR_RTS|COMMCR_LOOPBACK}	\n
		Set to the modem control combination required (COMMCR):
		- 0 to not use DTR, RTS ot LOOPBACK.
		Or a combination of the following.
		- BITM_UART_DTR to use Data terminal ready.
		- BITM_UART_RTS to use Request to send.
		- BITM_UART_OUT1 to force NOUT1 to a logic 0
		- BITM_UART_OUT2 to fouce NOUT2 to a logic 0
		- BITM_UART_LOOPBACK for Loop back mode.

	@param iWr :{0,1}
		- 0 to read mode only (ignores iMcr).
		- 1 to write and read mode.
	@return value of COMMSR:	\n
		- COMMSR.0 = DCTS -> CTS changed.
		- COMMSR.1 = DDSR -> DSR changed.
		- COMMSR.2 = TERI -> RI Trailing edge.
		- COMMSR.3 = DDCD -> DCD changed.
		- COMMSR.4 = CTS -> Clear to send.
		- COMMSR.5 = DSR -> Data set ready.
		- COMMSR.6 = RI -> Ring indicator.
		- COMMSR.7 = DCD -> Data carrier detect.
	@note	This function does not change the Port Multiplexers.
**/

uint32_t UrtMod(ADI_UART_TypeDef *pPort, uint32_t iMcr, uint32_t iWr)
{
    if (iWr)
    {
        pPort->MCR = (uint16_t)iMcr;
    }

    return (pPort->MSR & 0x0ff);
}
/**
	@brief uint32_t UrtModSta(ADI_UART_TypeDef *pPort)
			==========Read the Modem status register byte of the UART.
	@param pPort :{pADI_UART0, pADI_UART1}	\n
		Set to pADI_UART. Only one channel available.
	@return value of COMMSR:
		- COMMSR_DCD = Data carrier detect level
		- COMMSR_RI = Ring indicator level
		- COMMSR_DSR = Data set ready status
		- COMMSR_CTS = Clear to Send input level
		- COMMSR_DDCD = Delta DCD status
		- COMMSR_TERI = trailing edge Ring indicator status
		- COMMSR_DDSR = Delta DSR status
		- COMMSR_DCTS = Delta CTS status
	@warning	UART must be configured before checking status
**/

uint32_t UrtModSta(ADI_UART_TypeDef *pPort)
{
    return (pPort->MSR & 0xff);
}


/**
	@brief uint32_t UrtIntCfg(ADI_UART_TypeDef *pPort, uint32_t iIrq)
			==========Enables/Disables UART Interrupt sources.

	@param pPort :{pADI_UART0, pADI_UART1}	\n
		Set to pADI_UART. Only one channel available.
	@param iIrq :{COMIEN_ERBFI| COMIEN_ETBEI| COMIEN_ELSI| COMIEN_EDSSI| COMIEN_EDMAT| COMIEN_EDMAR}
		- 0 to select none of the options.
		Or set to the bitwise or combination of
		- COMIEN_ERBFI to enable UART RX IRQ.
		- COMIEN_ETBEI to enable UART TX IRQ.
		- COMIEN_ELSI to enable UART Status IRQ.
		- COMIEN_EDSSI to enable UART Modem status IRQ.
		- COMIEN_EDMAT to enable UART DMA Tx IRQ.
		- COMIEN_EDMAR to enable UART DMA Rx IRQ.
	@return 1.
**/
uint32_t UrtIntCfg(ADI_UART_TypeDef *pPort, uint32_t iIrq)
{
    pPort->IEN = (uint16_t)iIrq;

    return 1;
}

/**
	@brief uint32_t UrtIntSta(ADI_UART_TypeDef *pPort)
			==========return UART interrupt status.
	@param pPort :{pADI_UART0, pADI_UART1}	\n
		Set to pADI_UART. Only one channel available.

	@return COMIIR.
**/
uint32_t UrtIntSta(ADI_UART_TypeDef *pPort)
{
    return pPort->IIR;
}

/**
@brief void UrtSetup(ADI_UART_TypeDef *pPort, const Urt_SETUP_t *pSetup);
      =========== setup for UART
@param pPort: {pADI_UART0,pADI_UART1}
@param pSetup: pointer to Urt_SETUP_t setup structure
@return none
**/
void UrtSetup(ADI_UART_TypeDef *pPort, const Urt_SETUP_t *pSetup)
{
    uint32_t usUrtIEN = (pSetup->rxDmaEn << BITP_UART_IEN_EDMAR) | (pSetup->txDmaEn << BITP_UART_IEN_EDMAT) \
                       |(pSetup->modemIntEn << BITP_UART_IEN_EDSSI) | (pSetup->lineErrIntEn << BITP_UART_IEN_ELSI) \
                       |(pSetup->txIntEn << BITP_UART_IEN_ETBEI) | (pSetup->rxBufFullIntEn << BITP_UART_IEN_ERBFI); 

    uint32_t usUrtLCR = (pSetup->stickParityEn << BITP_UART_LCR_SP) | (pSetup->parityType << BITP_UART_LCR_EPS) \
                       |(pSetup->parityEn << BITP_UART_LCR_PEN) | (pSetup->stopBit << BITP_UART_LCR_STOPPED) \
                       |(pSetup->bitLength << BITP_UART_LCR_WLS); 

    uint32_t i1,M;
    uint32_t iDiv;
    uint32_t iRtC;
    uint32_t iOSR;
	 uint32_t iBaud = pSetup->baudrate;
    unsigned long long ullRtClk = DEFAULT_ROOTCLK;            // The root clock speed

    iDiv = (pADI_CLK->CLKCON1 & BITM_CLOCK_CLKCON1_CDPCLK1);       // Read UART clock from APB1 as set by CLKCON1[8:6]
    iDiv = iDiv >> BITP_CLOCK_CLKCON1_CDPCLK1;
    iDiv = 1 << iDiv;                                  // iDiv exponentiation base on 2
   
    iRtC = (pADI_CLK->CLKCON0 & BITM_CLOCK_CLKCON0_CLKMUX);  // Check what is the root clock
    iRtC >>= BITP_CLOCK_CLKCON0_CLKMUX;

    switch (iRtC)
    {
        case ENUM_CLOCK_CLKCON0_CLKMUX_HFOSC:
            ullRtClk = OSC16M_ROOTCLK;
        break;

        case ENUM_CLOCK_CLKCON0_CLKMUX_SPLL:
            ullRtClk = PLL_ROOTCLK;
        break;

        case ENUM_CLOCK_CLKCON0_CLKMUX_EXTCLK:
            ullRtClk = EXT_GPIO_ROOTCLK;            //External clock is assumed to be 80MhZ, if different                              
        break;                                      //clock speed is used, this should be changed
                                       
        default:     
        break;
    }

    pPort->LCR2 = ENUM_UART_LCR2_OSR_OSR32;
    iOSR = 32;
    i1 = (uint32_t)((ullRtClk / (iOSR * iDiv)) / iBaud - 1);          //for bigger M and N value
    i1 = (i1==0)? 1: i1;   //DIV cannot be 0
    pPort->DIV = (uint16_t)i1;

    M = (uint32_t)(ullRtClk / (iOSR * iDiv) / iBaud / i1);

    pPort->FBR = (uint16_t)(BITM_UART_FBR_FBEN \
                |(M << BITP_UART_FBR_DIVM) \
                |(((((2048/(iOSR*iDiv))*ullRtClk)/i1)/iBaud) - 2048*M));
    
    pPort->IEN = (uint16_t)usUrtIEN;
    pPort->LCR = (uint16_t)usUrtLCR;
    pPort->MCR = (uint16_t)(pSetup->loopback<<BITP_UART_MCR_LOOPBACK);
    pPort->FCR = (uint16_t)((pSetup->fifoEn<<BITP_UART_FCR_FIFOEN)|(pSetup->fifoIntTrigger<<BITP_UART_FCR_RFTRIG)|	\
    					(pSetup->fifoDmaMode<<BITP_UART_FCR_FDMAMD));	 

}

/**@}*/




