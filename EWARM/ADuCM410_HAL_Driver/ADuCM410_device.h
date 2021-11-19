/* ================================================================================
     Project     :   ADuCM410
     File        :   ADuCM410_device.h
     Description :   C typedef structures for bit-fields and enums for enumerations.

     Copyright (c) 2020 Analog Devices, Inc.  All Rights Reserved.
     This software is proprietary and confidential to Analog Devices, Inc. and
     its licensors.

     This file was auto-generated. Do not make local changes to this file.
   ================================================================================ */

#ifndef __ADUCM410_H__
#define __ADUCM410_H__

#if defined(_LANGUAGE_C) || (defined(__GNUC__) && !defined(__ASSEMBLER__))
#include <stdint.h>
#endif /* _LANGUAGE_C */

#ifdef __cplusplus
extern "C" {
#endif

/*! ========================================================================
 *  \struct ADI_TMR_TypeDef
 *  \brief GPT0
 *  ======================================================================== */
typedef struct _ADI_TMR_TypeDef
{
    volatile       uint16_t LD;                              /**< 0 16-bit Load Value Register */
    volatile const uint8_t RESERVED0[2];                   
    volatile const uint16_t VAL;                             /**< 4 16-bit Timer Value Register */
    volatile const uint8_t RESERVED1[2];                   
    volatile       uint16_t CON;                             /**< 8 Control Register */
    volatile const uint8_t RESERVED2[2];                   
    volatile       uint16_t CLRI;                            /**< C Clear Interrupt Register */
    volatile const uint8_t RESERVED3[14];                  
    volatile const uint16_t STA;                             /**< 1C Status Register */
} ADI_TMR_TypeDef;

/*! ========================================================================
 *  \struct ADI_TIMER_TypeDef
 *  \brief Timer
 *  ======================================================================== */
typedef struct _ADI_TIMER_TypeDef
{
    volatile       uint32_t CTL;                             /**< 0 Timer Control */
    volatile       uint32_t CNT;                             /**< 4 Count Value */
    volatile       uint32_t STATUS;                          /**< 8 Timer Status */
    volatile const uint8_t RESERVED0[4];                   
    volatile       uint32_t CFG0;                            /**< 10 Capture Compare Configuration */
    volatile       uint32_t CFG1;                            /**< 14 Capture Compare Configuration */
    volatile       uint32_t CFG2;                            /**< 18 Capture Compare Configuration */
    volatile       uint32_t CFG3;                            /**< 1C Capture Compare Configuration */
    volatile       uint32_t CC0;                             /**< 20 Compare and Capture Value */
    volatile       uint32_t CC1;                             /**< 24 Compare and Capture Value */
    volatile       uint32_t CC2;                             /**< 28 Compare and Capture Value */
    volatile       uint32_t CC3;                             /**< 2C Compare and Capture Value */
} ADI_TIMER_TypeDef;

/*! ========================================================================
 *  \struct ADI_MISC16_TypeDef
 *  \brief Your module description, here.
 *  ======================================================================== */
typedef struct _ADI_MISC16_TypeDef
{
    volatile const uint8_t RESERVED0[32];                  
    volatile const uint32_t ADIID;                           /**< 20 ADI ID */
    volatile const uint32_t CHIPID;                          /**< 24 Chip ID */
    volatile const uint8_t RESERVED1[268];                 
    volatile       uint32_t USERKEY;                         /**< 134 Open to Customer to Protect Important Registers */
} ADI_MISC16_TypeDef;

/*! ========================================================================
 *  \struct ADI_WUT_TypeDef
 *  \brief WUT
 *  ======================================================================== */
typedef struct _ADI_WUT_TypeDef
{
    volatile const uint16_t T4VAL0;                          /**< 0 Current Count Value - LS 16 Bits */
    volatile const uint8_t RESERVED0[2];                   
    volatile const uint16_t T4VAL1;                          /**< 4 Current Count Value - MS 16 Bits */
    volatile const uint8_t RESERVED1[2];                   
    volatile       uint16_t T4CON;                           /**< 8 Control Register */
    volatile const uint8_t RESERVED2[2];                   
    volatile       uint16_t T4INC;                           /**< C 12-bit Interval for Wakeup Field a */
    volatile const uint8_t RESERVED3[2];                   
    volatile       uint16_t T4WUFB0;                         /**< 10 Wakeup Field B - LS 16 Bits */
    volatile const uint8_t RESERVED4[2];                   
    volatile       uint16_t T4WUFB1;                         /**< 14 Wakeup Field B - MS 16 Bits */
    volatile const uint8_t RESERVED5[2];                   
    volatile       uint16_t T4WUFC0;                         /**< 18 Wakeup Field C - LS 16 Bits */
    volatile const uint8_t RESERVED6[2];                   
    volatile       uint16_t T4WUFC1;                         /**< 1C Wakeup Field C - MS 16 Bits */
    volatile const uint8_t RESERVED7[2];                   
    volatile       uint16_t T4WUFD0;                         /**< 20 Wakeup Field D - LS 16 Bits */
    volatile const uint8_t RESERVED8[2];                   
    volatile       uint16_t T4WUFD1;                         /**< 24 Wakeup Field D - MS 16 Bits */
    volatile const uint8_t RESERVED9[2];                   
    volatile       uint16_t T4IEN;                           /**< 28 Interrupt Enable Register */
    volatile const uint8_t RESERVED10[2];                  
    volatile const uint16_t T4STA;                           /**< 2C Status Register */
    volatile const uint8_t RESERVED11[2];                  
    volatile       uint16_t T4CLRI;                          /**< 30 Clear Interrupt Register */
    volatile const uint8_t RESERVED12[10];                 
    volatile       uint16_t T4WUFA0;                         /**< 3C Wakeup Field a - LS 16 Bits */
    volatile const uint8_t RESERVED13[2];                  
    volatile       uint16_t T4WUFA1;                         /**< 40 Wakeup Field a - MS 16 Bits */
} ADI_WUT_TypeDef;

/*! ========================================================================
 *  \struct ADI_WDT_TypeDef
 *  \brief Watchdog Timer Register Map
 *  ======================================================================== */
typedef struct _ADI_WDT_TypeDef
{
    volatile       uint16_t LD;                              /**< 0 Watchdog Timer Load Value */
    volatile const uint8_t RESERVED0[2];                   
    volatile const uint16_t VALS;                            /**< 4 Current Count Value */
    volatile const uint8_t RESERVED1[2];                   
    volatile       uint16_t CON;                             /**< 8 Watchdog Timer Control Register */
    volatile const uint8_t RESERVED2[2];                   
    volatile       uint16_t CLRI;                            /**< C Refresh Watchdog Register */
    volatile const uint8_t RESERVED3[10];                  
    volatile const uint16_t STA;                             /**< 18 Timer Status */
    volatile const uint8_t RESERVED4[2];                   
    volatile       uint16_t MINLD;                           /**< 1C Minimum Load Value */
} ADI_WDT_TypeDef;

/*! ========================================================================
 *  \struct ADI_ALWAYS_ON_TypeDef
 *  \brief Always on clock, reset, power management and test
 *  ======================================================================== */
typedef struct _ADI_ALWAYS_ON_TypeDef
{
    volatile       uint16_t PWRMOD;                          /**< 0 Power Modes */
    volatile const uint8_t RESERVED0[2];                   
    volatile       uint16_t PWRKEY;                          /**< 4 Key Protection for PWRMOD */
    volatile const uint8_t RESERVED1[2];                   
    volatile       uint16_t RSTCFG;                          /**< 8 Reset Configuration */
    volatile const uint8_t RESERVED2[2];                   
    volatile       uint16_t RSTKEY;                          /**< C Key Protection for RSTCFG */
    volatile const uint8_t RESERVED3[18];                  
    volatile       uint16_t EI0CFG;                          /**< 20 External Interrupt Configuration 0 */
    volatile const uint8_t RESERVED4[2];                   
    volatile       uint16_t EI1CFG;                          /**< 24 External Interrupt Configuration 1 */
    volatile const uint8_t RESERVED5[2];                   
    volatile       uint16_t EI2CFG;                          /**< 28 External Interrupt Configuration 2 */
    volatile const uint8_t RESERVED6[6];                   
    volatile       uint16_t EICLR;                           /**< 30 External Interrupt Clear */
    volatile const uint8_t RESERVED7[14];                  
    volatile       uint16_t RSTSTA;                          /**< 40 Reset Status */
} ADI_ALWAYS_ON_TypeDef;

/*! ========================================================================
 *  \struct ADI_PLA_TypeDef
 *  \brief PLA Register Map
 *  ======================================================================== */
typedef struct _ADI_PLA_TypeDef
{
    volatile       uint16_t PLA_ELEM0;                       /**< 0 ELEMx Configuration Register */
    volatile const uint8_t RESERVED0[2];                   
    volatile       uint16_t PLA_ELEM1;                       /**< 4 ELEMx Configuration Register */
    volatile const uint8_t RESERVED1[2];                   
    volatile       uint16_t PLA_ELEM2;                       /**< 8 ELEMx Configuration Register */
    volatile const uint8_t RESERVED2[2];                   
    volatile       uint16_t PLA_ELEM3;                       /**< C ELEMx Configuration Register */
    volatile const uint8_t RESERVED3[2];                   
    volatile       uint16_t PLA_ELEM4;                       /**< 10 ELEMx Configuration Register */
    volatile const uint8_t RESERVED4[2];                   
    volatile       uint16_t PLA_ELEM5;                       /**< 14 ELEMx Configuration Register */
    volatile const uint8_t RESERVED5[2];                   
    volatile       uint16_t PLA_ELEM6;                       /**< 18 ELEMx Configuration Register */
    volatile const uint8_t RESERVED6[2];                   
    volatile       uint16_t PLA_ELEM7;                       /**< 1C ELEMx Configuration Register */
    volatile const uint8_t RESERVED7[2];                   
    volatile       uint16_t PLA_ELEM8;                       /**< 20 ELEMx Configuration Register */
    volatile const uint8_t RESERVED8[2];                   
    volatile       uint16_t PLA_ELEM9;                       /**< 24 ELEMx Configuration Register */
    volatile const uint8_t RESERVED9[2];                   
    volatile       uint16_t PLA_ELEM10;                      /**< 28 ELEMx Configuration Register */
    volatile const uint8_t RESERVED10[2];                  
    volatile       uint16_t PLA_ELEM11;                      /**< 2C ELEMx Configuration Register */
    volatile const uint8_t RESERVED11[2];                  
    volatile       uint16_t PLA_ELEM12;                      /**< 30 ELEMx Configuration Register */
    volatile const uint8_t RESERVED12[2];                  
    volatile       uint16_t PLA_ELEM13;                      /**< 34 ELEMx Configuration Register */
    volatile const uint8_t RESERVED13[2];                  
    volatile       uint16_t PLA_ELEM14;                      /**< 38 ELEMx Configuration Register */
    volatile const uint8_t RESERVED14[2];                  
    volatile       uint16_t PLA_ELEM15;                      /**< 3C ELEMx Configuration Register */
    volatile const uint8_t RESERVED15[2];                  
    volatile       uint16_t PLA_ELEM16;                      /**< 40 ELEMx Configuration Register */
    volatile const uint8_t RESERVED16[2];                  
    volatile       uint16_t PLA_ELEM17;                      /**< 44 ELEMx Configuration Register */
    volatile const uint8_t RESERVED17[2];                  
    volatile       uint16_t PLA_ELEM18;                      /**< 48 ELEMx Configuration Register */
    volatile const uint8_t RESERVED18[2];                  
    volatile       uint16_t PLA_ELEM19;                      /**< 4C ELEMx Configuration Register */
    volatile const uint8_t RESERVED19[2];                  
    volatile       uint16_t PLA_ELEM20;                      /**< 50 ELEMx Configuration Register */
    volatile const uint8_t RESERVED20[2];                  
    volatile       uint16_t PLA_ELEM21;                      /**< 54 ELEMx Configuration Register */
    volatile const uint8_t RESERVED21[2];                  
    volatile       uint16_t PLA_ELEM22;                      /**< 58 ELEMx Configuration Register */
    volatile const uint8_t RESERVED22[2];                  
    volatile       uint16_t PLA_ELEM23;                      /**< 5C ELEMx Configuration Register */
    volatile const uint8_t RESERVED23[2];                  
    volatile       uint16_t PLA_ELEM24;                      /**< 60 ELEMx Configuration Register */
    volatile const uint8_t RESERVED24[2];                  
    volatile       uint16_t PLA_ELEM25;                      /**< 64 ELEMx Configuration Register */
    volatile const uint8_t RESERVED25[2];                  
    volatile       uint16_t PLA_ELEM26;                      /**< 68 ELEMx Configuration Register */
    volatile const uint8_t RESERVED26[2];                  
    volatile       uint16_t PLA_ELEM27;                      /**< 6C ELEMx Configuration Register */
    volatile const uint8_t RESERVED27[2];                  
    volatile       uint16_t PLA_ELEM28;                      /**< 70 ELEMx Configuration Register */
    volatile const uint8_t RESERVED28[2];                  
    volatile       uint16_t PLA_ELEM29;                      /**< 74 ELEMx Configuration Register */
    volatile const uint8_t RESERVED29[2];                  
    volatile       uint16_t PLA_ELEM30;                      /**< 78 ELEMx Configuration Register */
    volatile const uint8_t RESERVED30[2];                  
    volatile       uint16_t PLA_ELEM31;                      /**< 7C ELEMx Configuration Register */
    volatile const uint8_t RESERVED31[2];                  
    volatile       uint16_t PLA_CLK;                         /**< 80 PLA Clock Select */
    volatile const uint8_t RESERVED32[2];                  
    volatile       uint16_t PLA_IRQ0;                        /**< 84 Interrupt Register for Block 0 */
    volatile const uint8_t RESERVED33[2];                  
    volatile       uint16_t PLA_IRQ1;                        /**< 88 Interrupt Register for Block1 */
    volatile const uint8_t RESERVED34[2];                  
    volatile       uint16_t PLA_ADC;                         /**< 8C ADC Configuration Register */
    volatile const uint8_t RESERVED35[2];                  
    volatile       int16_t PLA_DIN0;                        /**< 90 AMBA Bus Data Input for Block 0 */
    volatile const uint8_t RESERVED36[6];                  
    volatile const uint16_t PLA_DOUT0;                       /**< 98 AMBA Bus Data Output for Block 0 */
    volatile const uint8_t RESERVED37[2];                  
    volatile const uint16_t PLA_DOUT1;                       /**< 9C AMBA Bus Data Output for Block1 */
    volatile const uint8_t RESERVED38[2];                  
    volatile       uint16_t PLA_LCK;                         /**< A0 Write Lock Register. */
    volatile const uint8_t RESERVED39[2];                  
    volatile       uint16_t PLA_IRQTYPE;                     /**< A4 PLA Interrupt Request and DMA Request Type */
} ADI_PLA_TypeDef;

/*! ========================================================================
 *  \struct ADI_DMAREQ_TypeDef
 *  \brief Your module description, here.
 *  ======================================================================== */
typedef struct _ADI_DMAREQ_TypeDef
{
    volatile       uint8_t REQEN;                           /**< 0 GPT/GPT32 and PLA DMA Request Enable */
    volatile const uint8_t RESERVED0[3];                   
    volatile       uint8_t REQ0SEL;                         /**< 4 GPT/GPT32 and PLA DMA Request 0 Select */
    volatile const uint8_t RESERVED1[3];                   
    volatile       uint8_t REQ1SEL;                         /**< 8 GPT/GPT32 and PLA DMA Request 1 Select */
    volatile const uint8_t RESERVED2[3];                   
    volatile       uint8_t PLAREQEN;                        /**< C PLA DMA Requests Enable */
    volatile const uint8_t RESERVED3[3];                   
    volatile       uint8_t GPTREQEN;                        /**< 10 GPT/GPT32 DMA Requests Enable */
    volatile const uint8_t RESERVED4[3];                   
    volatile       uint16_t GPT_REQ_TYPE;                    /**< 14 GPT and GPT32 Require Type */
} ADI_DMAREQ_TypeDef;

/*! ========================================================================
 *  \struct ADI_UART_TypeDef
 *  \brief Universal Asynchronous Receiver/Transmitter
 *  ======================================================================== */
typedef struct _ADI_UART_TypeDef
{
    union {
    volatile const uint16_t   RX;                         /*!< Receive Buffer Register */
    volatile       uint16_t   TX;                         /*!< Transmit Holding Register */
    };
    volatile const uint8_t RESERVED0[2];                   
    volatile       uint16_t IEN;                             /**< 4 Interrupt Enable */
    volatile const uint8_t RESERVED1[2];                   
    volatile const uint16_t IIR;                             /**< 8 Interrupt ID */
    volatile const uint8_t RESERVED2[2];                   
    volatile       uint16_t LCR;                             /**< C Line Control */
    volatile const uint8_t RESERVED3[2];                   
    volatile       uint16_t MCR;                             /**< 10 Modem Control */
    volatile const uint8_t RESERVED4[2];                   
    volatile const uint16_t LSR;                             /**< 14 Line Status */
    volatile const uint8_t RESERVED5[2];                   
    volatile const uint16_t MSR;                             /**< 18 Modem Status */
    volatile const uint8_t RESERVED6[2];                   
    volatile       uint16_t SCR;                             /**< 1C Scratch Buffer */
    volatile const uint8_t RESERVED7[2];                   
    volatile       uint16_t FCR;                             /**< 20 FIFO Control */
    volatile const uint8_t RESERVED8[2];                   
    volatile       uint16_t FBR;                             /**< 24 Fractional Baud Rate */
    volatile const uint8_t RESERVED9[2];                   
    volatile       uint16_t DIV;                             /**< 28 Baudrate Divider */
    volatile const uint8_t RESERVED10[2];                  
    volatile       uint16_t LCR2;                            /**< 2C Second Line Control */
    volatile const uint8_t RESERVED11[2];                  
    volatile       uint16_t CTL;                             /**< 30 UART Control Register */
    volatile const uint8_t RESERVED12[2];                  
    volatile const uint16_t RFC;                             /**< 34 RX FIFO Byte Count */
    volatile const uint8_t RESERVED13[2];                  
    volatile const uint16_t TFC;                             /**< 38 TX FIFO Byte Count */
    volatile const uint8_t RESERVED14[2];                  
    volatile       uint16_t RSC;                             /**< 3C RS485 Half-duplex Control */
    volatile const uint8_t RESERVED15[2];                  
    volatile       uint16_t ACR;                             /**< 40 Auto Baud Control */
    volatile const uint8_t RESERVED16[2];                  
    volatile const uint16_t ASRL;                            /**< 44 Auto Baud Status (Low) */
    volatile const uint8_t RESERVED17[2];                  
    volatile const uint16_t ASRH;                            /**< 48 Auto Baud Status (High) */
} ADI_UART_TypeDef;

/*! ========================================================================
 *  \struct ADI_I2C_TypeDef
 *  \brief I2C Master/Slave
 *  ======================================================================== */
typedef struct _ADI_I2C_TypeDef
{
    volatile       uint16_t MCTL;                            /**< 0 Master Control */
    volatile const uint8_t RESERVED0[2];                   
    volatile       uint16_t MSTAT;                           /**< 4 Master Status */
    volatile const uint8_t RESERVED1[2];                   
    volatile const uint16_t MRX;                             /**< 8 Master Receive Data */
    volatile const uint8_t RESERVED2[2];                   
    volatile       uint16_t MTX;                             /**< C Master Transmit Data */
    volatile const uint8_t RESERVED3[2];                   
    volatile       uint16_t MRXCNT;                          /**< 10 Master Receive Data Count */
    volatile const uint8_t RESERVED4[2];                   
    volatile const uint16_t MCRXCNT;                         /**< 14 Master Current Receive Data Count */
    volatile const uint8_t RESERVED5[2];                   
    volatile       uint16_t ADDR0;                           /**< 18 1st Master Address Byte */
    volatile const uint8_t RESERVED6[2];                   
    volatile       uint16_t ADDR1;                           /**< 1C 2nd Master Address Byte */
    volatile const uint8_t RESERVED7[2];                   
    volatile       uint16_t BYT;                             /**< 20 Start Byte */
    volatile const uint8_t RESERVED8[2];                   
    volatile       uint16_t DIV;                             /**< 24 Serial Clock Period Divisor */
    volatile const uint8_t RESERVED9[2];                   
    volatile       uint16_t SCTL;                            /**< 28 Slave Control */
    volatile const uint8_t RESERVED10[2];                  
    volatile       uint16_t SSTAT;                           /**< 2C Slave I2C Status/Error/IRQ */
    volatile const uint8_t RESERVED11[2];                  
    volatile const uint16_t SRX;                             /**< 30 Slave Receive */
    volatile const uint8_t RESERVED12[2];                  
    volatile       uint16_t STX;                             /**< 34 Slave Transmit */
    volatile const uint8_t RESERVED13[2];                  
    volatile       uint16_t ALT;                             /**< 38 Hardware General Call ID */
    volatile const uint8_t RESERVED14[2];                  
    volatile       uint16_t ID0;                             /**< 3C 1st Slave Address Device ID */
    volatile const uint8_t RESERVED15[2];                  
    volatile       uint16_t ID1;                             /**< 40 2nd Slave Address Device ID */
    volatile const uint8_t RESERVED16[2];                  
    volatile       uint16_t ID2;                             /**< 44 3rd Slave Address Device ID */
    volatile const uint8_t RESERVED17[2];                  
    volatile       uint16_t ID3;                             /**< 48 4th Slave Address Device ID */
    volatile const uint8_t RESERVED18[2];                  
    volatile       uint16_t STAT;                            /**< 4C Master and Slave FIFO Status */
    volatile const uint8_t RESERVED19[2];                  
    volatile       uint16_t SHCTL;                           /**< 50 Shared Control */
    volatile const uint8_t RESERVED20[2];                  
    volatile       uint16_t TCTL;                            /**< 54 Timing Control Register */
    volatile const uint8_t RESERVED21[2];                  
    volatile       uint16_t ASTRETCH_SCL;                    /**< 58 Automatic Stretch SCL Register */
    volatile const uint8_t RESERVED22[2];                  
    volatile       uint16_t IDFSTA;                          /**< 5C ID FIFO Status Register */
    volatile const uint8_t RESERVED23[2];                  
    volatile       uint16_t SLV_ADDR1;                       /**< 60 Slave 10 Bits Address 1st Byte. */
    volatile const uint8_t RESERVED24[2];                  
    volatile       uint16_t SLV_ADDR2;                       /**< 64 Slave 10 Bits Address 2nd Byte. */
    volatile const uint8_t RESERVED25[2];                  
    volatile const uint16_t SSTAT2;                          /**< 68 Slave I2C Status/IRQ 2 */
} ADI_I2C_TypeDef;

/*! ========================================================================
 *  \struct ADI_MDIO_TypeDef
 *  \brief MDIO Interface
 *  ======================================================================== */
typedef struct _ADI_MDIO_TypeDef
{
    volatile       uint16_t MDCON;                           /**< 0 MDIO Block Control */
    volatile const uint8_t RESERVED0[2];                   
    volatile const uint16_t MDFRM;                           /**< 4 MDIO Received Frame Control Information */
    volatile const uint8_t RESERVED1[2];                   
    volatile const uint16_t MDRXD;                           /**< 8 MDIO Received Data */
    volatile const uint8_t RESERVED2[2];                   
    volatile const uint16_t MDADR;                           /**< C MDIO Received Address */
    volatile const uint8_t RESERVED3[2];                   
    volatile       uint16_t MDTXD;                           /**< 10 MDIO Data for Transmission */
    volatile const uint8_t RESERVED4[2];                   
    volatile       uint16_t MDPHY;                           /**< 14 MDIO PHYADDR Software Values and Selection and DEVADD */
    volatile const uint8_t RESERVED5[2];                   
    volatile const uint16_t MDSTA;                           /**< 18 MDIO Progress Signaling Through Frame */
    volatile const uint8_t RESERVED6[2];                   
    volatile       uint16_t MDIEN;                           /**< 1C MDIO Interrupt Enables */
    volatile const uint8_t RESERVED7[2];                   
    volatile const uint16_t MDPIN;                           /**< 20 MDIO Read PHYADDR Pins */
    volatile const uint8_t RESERVED8[6];                   
    volatile       uint16_t DMAEN;                           /**< 28 MDIO DMA Enable */
    volatile const uint8_t RESERVED9[2];                   
    volatile       uint16_t MDTESTCON;                       /**< 2C MDIO Test Controller Protected by Test Key */
} ADI_MDIO_TypeDef;

/*! ========================================================================
 *  \struct ADI_DMA_TypeDef
 *  \brief DMA
 *  ======================================================================== */
typedef struct _ADI_DMA_TypeDef
{
    volatile const uint32_t STAT;                            /**< 0 DMA Status */
    volatile       uint32_t CFG;                             /**< 4 DMA Configuration */
    volatile       uint32_t PDBPTR;                          /**< 8 DMA Channel Primary Control Data Base Pointer */
    volatile const uint32_t ADBPTR;                          /**< C DMA Channel Alternate Control Data Base Pointer */
    volatile const uint8_t RESERVED0[4];                   
    volatile       uint32_t SWREQ;                           /**< 14 DMA Channel Software Request */
    volatile const uint8_t RESERVED1[8];                   
    volatile       uint32_t RMSKSET;                         /**< 20 DMA Channel Request Mask Set */
    volatile       uint32_t RMSKCLR;                         /**< 24 DMA Channel Request Mask Clear */
    volatile       uint32_t ENSET;                           /**< 28 DMA Channel Enable Set */
    volatile       uint32_t ENCLR;                           /**< 2C DMA Channel Enable Clear */
    volatile       uint32_t ALTSET;                          /**< 30 DMA Channel Primary-alternate Set */
    volatile       uint32_t ALTCLR;                          /**< 34 DMA Channel Primary-alternate Clear */
    volatile       uint32_t PRISET;                          /**< 38 DMA Channel Priority Set */
    volatile       uint32_t PRICLR;                          /**< 3C DMA Channel Priority Clear */
    volatile const uint8_t RESERVED2[8];                   
    volatile       uint32_t ERRCHNLCLR;                      /**< 48 DMA per Channel Error Clear */
    volatile       uint32_t ERRCLR;                          /**< 4C DMA Bus Error Clear */
    volatile       uint32_t INVALIDDESCCLR;                  /**< 50 DMA per Channel Invalid Descriptor Clear */
    volatile const uint8_t RESERVED3[1964];                
    volatile       uint32_t BSSET;                           /**< 800 DMA Channel Bytes Swap Enable Set */
    volatile       uint32_t BSCLR;                           /**< 804 DMA Channel Bytes Swap Enable Clear */
    volatile const uint8_t RESERVED4[8];                   
    volatile       uint32_t SRCADDRSET;                      /**< 810 DMA Channel Source Address Decrement Enable Set */
    volatile       uint32_t SRCADDRCLR;                      /**< 814 DMA Channel Source Address Decrement Enable Clear */
    volatile       uint32_t DSTADDRSET;                      /**< 818 DMA Channel Destination Address Decrement Enable Set */
    volatile       uint32_t DSTADDRCLR;                      /**< 81C DMA Channel Destination Address Decrement Enable Clear */
    volatile const uint8_t RESERVED5[1984];                
    volatile const uint32_t REVID;                           /**< FE0 DMA Controller Revision ID */
} ADI_DMA_TypeDef;

/*! ========================================================================
 *  \struct ADI_CC_TypeDef
 *  \brief Cache Controller
 *  ======================================================================== */
typedef struct _ADI_CC_TypeDef
{
    volatile const uint32_t STAT;                            /**< 0 Cache Status Register */
    volatile       uint32_t SETUP;                           /**< 4 Cache Setup Register */
    volatile       uint32_t KEY;                             /**< 8 Cache Key Register */
    volatile       uint32_t PERFSETUP;                       /**< C Cache Performance Monitor Setup Register */
    volatile const uint32_t ACCESSCNTR;                      /**< 10 Cache Miss Counter */
    volatile const uint8_t RESERVED0[16];                  
    volatile       uint32_t MSTRSETUP;                       /**< 24 Cache Master Setup Register */
    volatile const uint8_t RESERVED1[12];                  
    volatile const uint32_t ECCSTAT;                         /**< 34 Cache SRAM ECC Status Register */
    volatile const uint32_t ECCADDR;                         /**< 38 Cache SRAM ECC Address Register */
} ADI_CC_TypeDef;

/*! ========================================================================
 *  \struct ADI_FLASH_TypeDef
 *  \brief Flash Controller
 *  ======================================================================== */
typedef struct _ADI_FLASH_TypeDef
{
    volatile const uint32_t FEESTA;                          /**< 0 Status Register */
    volatile       uint32_t FEECON0;                         /**< 4 Command Control Register – Interrupt Enable Register */
    volatile       uint32_t FEECMD;                          /**< 8 Command Register */
    volatile       uint32_t FEEFLADR;                        /**< C Flash Address Key - Hole Register */
    volatile       uint32_t FEEFLDATA0;                      /**< 10 Flash Data Register - Key - Hole Interface Lower 32 Bits */
    volatile       uint32_t FEEFLDATA1;                      /**< 14 Flash Data Register - Key - Hole Interface Upper 32 Bits */
    volatile       uint32_t FEEADR0;                         /**< 18 Lower Page Address */
    volatile       uint32_t FEEADR1;                         /**< 1C Upper Page Address */
    volatile       uint32_t FEEKEY;                          /**< 20 Flash Key Register. */
    volatile const uint8_t RESERVED0[4];                   
    volatile       uint32_t FEEPRO0;                         /**< 28 Write Protection Register for Flash0 */
    volatile       uint32_t FEEPRO1;                         /**< 2C Write Protection Register for Flash1 */
    volatile const uint8_t RESERVED1[4];                   
    volatile const uint32_t FEESIG;                          /**< 34 Flash Signature */
    volatile       uint32_t FEECON1;                         /**< 38 User Setup Register */
    volatile const uint8_t RESERVED2[4];                   
    volatile const uint32_t FEEWRADDRA;                      /**< 40 Write Abort Address Register */
    volatile const uint8_t RESERVED3[4];                   
    volatile       uint32_t FEEAEN0;                         /**< 48 Lower 32 Bits of the Sys Irq Abort Enable Register. */
    volatile       uint32_t FEEAEN1;                         /**< 4C Middle 32 Bits of the Sys Irq Abort Enable Register. */
    volatile       uint32_t FEEAEN2;                         /**< 50 Upper 32 Bits of the Sys Irq Abort Enable Register. */
    volatile const uint8_t RESERVED4[16];                  
    volatile       uint32_t FEEECCCONFIG;                    /**< 64 Configurable ECC Enable/disable, Error Response */
    volatile const uint8_t RESERVED5[12];                  
    volatile const uint32_t FEEECCADDRC0;                    /**< 74 Flash 0 ECC Error Address via CODE Bus */
    volatile const uint32_t FEEECCADDRC1;                    /**< 78 Flash 1 ECC Error Address via CODE Bus */
    volatile const uint8_t RESERVED6[24];                  
    volatile const uint32_t FEEECCADDRD0;                    /**< 94 Flash 0 ECC Error Address via DMA Bus */
    volatile const uint32_t FEEECCADDRD1;                    /**< 98 Flash 1 ECC Error Address via DMA Bus */
} ADI_FLASH_TypeDef;

/*! ========================================================================
 *  \struct ADI_GPIO_TypeDef
 *  \brief GPIO
 *  ======================================================================== */
typedef struct _ADI_GPIO_TypeDef
{
    volatile       uint16_t CON;                             /**< 0 Port Configuration */
    volatile const uint8_t RESERVED0[2];                   
    volatile       uint8_t OE;                              /**< 4 Port Output Enable */
    volatile const uint8_t RESERVED1[3];                   
    volatile       uint8_t IE;                              /**< 8 Port Input Path Enable */
    volatile const uint8_t RESERVED2[3];                   
    volatile const uint8_t IN;                              /**< C Port Registered Data Input */
    volatile const uint8_t RESERVED3[3];                   
    volatile       uint8_t OUT;                             /**< 10 Port Data Output */
    volatile const uint8_t RESERVED4[3];                   
    volatile       uint8_t SET;                             /**< 14 Port Data Out Set */
    volatile const uint8_t RESERVED5[3];                   
    volatile       uint8_t CLR;                             /**< 18 Port Data Out Clear */
    volatile const uint8_t RESERVED6[3];                   
    volatile       uint8_t TGL;                             /**< 1C Port Pin Toggle */
    volatile const uint8_t RESERVED7[3];                   
    volatile       uint8_t ODE;                             /**< 20 Port Open Drain Enable */
    volatile const uint8_t RESERVED8[3];                   
    volatile       uint8_t IS;                              /**< 24 Port Input Select */
    volatile const uint8_t RESERVED9[3];                   
    volatile       uint8_t PE;                              /**< 28 Port Pull Enable */
    volatile const uint8_t RESERVED10[3];                  
    volatile       uint8_t PS;                              /**< 2C Port Pull Select */
    volatile const uint8_t RESERVED11[3];                  
    volatile       uint8_t SR;                              /**< 30 Port Slew Rate */
    volatile const uint8_t RESERVED12[3];                  
    volatile       uint16_t DS;                              /**< 34 Port Drive Select */
    volatile const uint8_t RESERVED13[2];                  
    volatile       uint8_t PWR;                             /**< 38 Port Power Select */
    volatile const uint8_t RESERVED14[3];                  
    volatile       uint8_t POL;                             /**< 3C GPIO Interrupt Polarity Select */
    volatile const uint8_t RESERVED15[3];                  
    volatile       uint8_t IENA;                            /**< 40 InterruptA Enable */
    volatile const uint8_t RESERVED16[3];                  
    volatile       uint8_t IENB;                            /**< 44 InterruptB Enable */
    volatile const uint8_t RESERVED17[3];                  
    volatile       uint8_t INT;                             /**< 48 Interrupt Status */
    volatile const uint8_t RESERVED18[3];
} ADI_GPIO_TypeDef;

/*! ========================================================================
 *  \struct ADI_SPI_TypeDef
 *  \brief Serial Peripheral Interface
 *  ======================================================================== */
typedef struct _ADI_SPI_TypeDef
{
    volatile       uint16_t STAT;                            /**< 0 Status */
    volatile const uint8_t RESERVED0[2];                   
    volatile const uint16_t RX;                              /**< 4 Receive */
    volatile const uint8_t RESERVED1[2];                   
    volatile       uint16_t TX;                              /**< 8 Transmit */
    volatile const uint8_t RESERVED2[2];                   
    volatile       uint16_t DIV;                             /**< C SPI Baud Rate Selection */
    volatile const uint8_t RESERVED3[2];                   
    volatile       uint16_t CTL;                             /**< 10 SPI Configuration 1 */
    volatile const uint8_t RESERVED4[2];                   
    volatile       uint16_t IEN;                             /**< 14 SPI Configuration 2 */
    volatile const uint8_t RESERVED5[2];                   
    volatile       uint16_t CNT;                             /**< 18 Transfer Byte Count */
    volatile const uint8_t RESERVED6[2];                   
    volatile       uint16_t DMA;                             /**< 1C SPI DMA Enable */
    volatile const uint8_t RESERVED7[2];                   
    volatile const uint16_t FIFOSTAT;                        /**< 20 FIFO Status */
    volatile const uint8_t RESERVED8[2];                   
    volatile       uint16_t RDCTL;                           /**< 24 Read Control */
    volatile const uint8_t RESERVED9[2];                   
    volatile       uint16_t FLOWCTL;                         /**< 28 Flow Control */
    volatile const uint8_t RESERVED10[2];                  
    volatile       uint16_t WAITTMR;                         /**< 2C Wait Timer for Flow Control */
    volatile const uint8_t RESERVED11[6];                  
    volatile       uint16_t CSOVERRIDE;                      /**< 34 Chip-Select Override */
} ADI_SPI_TypeDef;

/*! ========================================================================
 *  \struct ADI_CLOCK_TypeDef
 *  \brief Clock Gating and Other Settings
 *  ======================================================================== */
typedef struct _ADI_CLOCK_TypeDef
{
    volatile       uint16_t CLKCON0;                         /**< 0 Misc Clock Settings Register */
    volatile const uint8_t RESERVED0[2];                   
    volatile       uint16_t CLKCON1;                         /**< 4 Clock Dividers Register */
    volatile const uint8_t RESERVED1[2];                   
    volatile       uint16_t CLKSTAT0;                        /**< 8 Clocking Status */
} ADI_CLOCK_TypeDef;

/*! ========================================================================
 *  \struct ADI_PWM_TypeDef
 *  \brief PWM MMR
 *  ======================================================================== */
typedef struct _ADI_PWM_TypeDef
{
    volatile       uint16_t PWMCON0;                         /**< 0 PWM Control Register */
    volatile const uint8_t RESERVED0[2];                   
    volatile       uint16_t PWMCON1;                         /**< 4 ADC Conversion Start and Trip Control Register */
    volatile const uint8_t RESERVED1[2];                   
    volatile       uint16_t PWMICLR;                         /**< 8 Hardware Trip Configuration Register */
    volatile const uint8_t RESERVED2[6];                   
    volatile       uint16_t PWM0COM0;                        /**< 10 Compare Register 0 for PWM0 and PWM1 */
    volatile const uint8_t RESERVED3[2];                   
    volatile       uint16_t PWM0COM1;                        /**< 14 Compare Register 1 for PWM0 and PWM1 */
    volatile const uint8_t RESERVED4[2];                   
    volatile       uint16_t PWM0COM2;                        /**< 18 Compare Register 2 for PWM0 and PWM1 */
    volatile const uint8_t RESERVED5[2];                   
    volatile       uint16_t PWM0LEN;                         /**< 1C Period Value Register for PWM0 and PWM1 */
    volatile const uint8_t RESERVED6[2];                   
    volatile       uint16_t PWM1COM0;                        /**< 20 Compare Register 0 for PWM2 and PWM3 */
    volatile const uint8_t RESERVED7[2];                   
    volatile       uint16_t PWM1COM1;                        /**< 24 Compare Register 1 for PWM2 and PWM3 */
    volatile const uint8_t RESERVED8[2];                   
    volatile       uint16_t PWM1COM2;                        /**< 28 Compare Register 2 for PWM2 and PWM3 */
    volatile const uint8_t RESERVED9[2];                   
    volatile       uint16_t PWM1LEN;                         /**< 2C Period Value Register for PWM2 and PWM3 */
    volatile const uint8_t RESERVED10[2];                  
    volatile       uint16_t PWM2COM0;                        /**< 30 Compare Register 0 for PWM4 and PWM5 */
    volatile const uint8_t RESERVED11[2];                  
    volatile       uint16_t PWM2COM1;                        /**< 34 Compare Register 1 for PWM4 and PWM5 */
    volatile const uint8_t RESERVED12[2];                  
    volatile       uint16_t PWM2COM2;                        /**< 38 Compare Register 2 for PWM4 and PWM5 */
    volatile const uint8_t RESERVED13[2];                  
    volatile       uint16_t PWM2LEN;                         /**< 3C Period Value Register for PWM4 and PWM5 */
    volatile const uint8_t RESERVED14[2];                  
    volatile       uint16_t PWM3COM0;                        /**< 40 Compare Register 0 for PWM6 and PWM7 */
    volatile const uint8_t RESERVED15[2];                  
    volatile       uint16_t PWM3COM1;                        /**< 44 Compare Register 1 for PWM6 and PWM7 */
    volatile const uint8_t RESERVED16[2];                  
    volatile       uint16_t PWM3COM2;                        /**< 48 Compare Register 2 for PWM6 and PWM7 */
    volatile const uint8_t RESERVED17[2];                  
    volatile       uint16_t PWM3LEN;                         /**< 4C Period Value Register for PWM6 and PWM7 */
} ADI_PWM_TypeDef;

/*! ========================================================================
 *  \struct ADI_SUBSYS_TypeDef
 *  \brief Your module description, here.
 *  ======================================================================== */
typedef struct _ADI_SUBSYS_TypeDef
{
    volatile       uint32_t SRAMCON;                         /**< 0 SRAM Control Register */
    volatile const uint8_t RESERVED0[8];                   
    volatile       uint32_t SRAMECCCON;                      /**< C SRAM ECC Control Register */
    volatile const uint32_t SRAMECCSTA;                      /**< 10 SRAM ECC Status Register */
    volatile const uint32_t SRAMECCA0;                       /**< 14 SRAM0 ECC Error Address Register */
    volatile const uint32_t SRAMECCD0;                       /**< 18 SRAM0 ECC Error Data Register */
    volatile const uint32_t SRAMECCP0;                       /**< 1C SRAM0 ECC Error Parity Register */
    volatile const uint32_t SRAMECCA1;                       /**< 20 SRAM1 ECC Error Address Register */
    volatile const uint32_t SRAMECCD1;                       /**< 24 SRAM1 ECC Error Data Register */
    volatile const uint32_t SRAMECCP1;                       /**< 28 SRAM1 ECC Error Parity Register */
    volatile const uint32_t SRAMECCA2;                       /**< 2C SRAM2 ECC Error Address Register */
    volatile const uint32_t SRAMECCD2;                       /**< 30 SRAM2 ECC Error Data Register */
    volatile const uint32_t SRAMECCP2;                       /**< 34 SRAM2 ECC Error Parity Register */
} ADI_SUBSYS_TypeDef;

/*! ========================================================================
 *  \struct ADI_CRC_TypeDef
 *  \brief CRC Accelerator
 *  ======================================================================== */
typedef struct _ADI_CRC_TypeDef
{
    volatile       uint32_t CTL;                             /**< 0 CRC Control Register */
    volatile       int32_t IPDATA;                          /**< 4 Input Data Word Register */
    volatile       int32_t RESULT;                          /**< 8 CRC Result Register */
    volatile       uint32_t POLY;                            /**< C Programmable CRC Polynomial */
} ADI_CRC_TypeDef;

/*! ========================================================================
 *  \struct ADI_ADC_TypeDef
 *  \brief Your module description, here.
 *  ======================================================================== */
typedef struct _ADI_ADC_TypeDef
{
    volatile const uint32_t ADCDAT0;                         /**< 0 ADCx Data and Flags */
    volatile const uint32_t ADCDAT1;                         /**< 4 ADCx Data and Flags */
    volatile const uint32_t ADCDAT2;                         /**< 8 ADCx Data and Flags */
    volatile const uint32_t ADCDAT3;                         /**< C ADCx Data and Flags */
    volatile const uint32_t ADCDAT4;                         /**< 10 ADCx Data and Flags */
    volatile const uint32_t ADCDAT5;                         /**< 14 ADCx Data and Flags */
    volatile const uint32_t ADCDAT6;                         /**< 18 ADCx Data and Flags */
    volatile const uint32_t ADCDAT7;                         /**< 1C ADCx Data and Flags */
    volatile const uint32_t ADCDAT8;                         /**< 20 ADCx Data and Flags */
    volatile const uint32_t ADCDAT9;                         /**< 24 ADCx Data and Flags */
    volatile const uint32_t ADCDAT10;                        /**< 28 ADCx Data and Flags */
    volatile const uint32_t ADCDAT11;                        /**< 2C ADCx Data and Flags */
    volatile const uint32_t ADCDAT12;                        /**< 30 ADCx Data and Flags */
    volatile const uint32_t ADCDAT13;                        /**< 34 ADCx Data and Flags */
    volatile const uint32_t ADCDAT14;                        /**< 38 ADCx Data and Flags */
    volatile const uint32_t ADCDAT15;                        /**< 3C ADCx Data and Flags */
    volatile const uint32_t ADCDAT16;                        /**< 40 ADCx Data and Flags */
    volatile const uint32_t ADCDAT17;                        /**< 44 ADCx Data and Flags */
    volatile const uint32_t ADCDAT18;                        /**< 48 ADCx Data and Flags */
    volatile const uint32_t ADCDAT19;                        /**< 4C ADCx Data and Flags */
    volatile const uint32_t ADCDAT20;                        /**< 50 ADCx Data and Flags */
    volatile const uint32_t ADCDAT21;                        /**< 54 ADCx Data and Flags */
    volatile const uint32_t ADCDAT22;                        /**< 58 ADCx Data and Flags */
    volatile const uint32_t ADCDAT23;                        /**< 5C ADCx Data and Flags */
    volatile const uint32_t ADCDAT24;                        /**< 60 ADCx Data and Flags */
    volatile const uint32_t ADCDAT25;                        /**< 64 ADCx Data and Flags */
    volatile const uint32_t ADCDAT26;                        /**< 68 ADCx Data and Flags */
    volatile const uint32_t ADCDAT27;                        /**< 6C ADCx Data and Flags */
    volatile const uint32_t ADCDAT28;                        /**< 70 ADCx Data and Flags */
    volatile const uint32_t ADCDAT29;                        /**< 74 ADCx Data and Flags */
    volatile       uint32_t ADCCON;                          /**< 78 ADC Configuration */
    volatile       uint32_t PREBUFCON;                       /**< 7C Pre-charge Buffer Control */
    volatile       uint32_t ADCCNVC;                         /**< 80 ADC Conversion Cycle for Positive Input Channels */
    volatile       uint32_t ADCCNVCSLOW;                     /**< 84 ADC Conversion Cycle for Positive Input Channels */
    volatile       uint32_t ADCCHA;                          /**< 88 ADC Channel Select */
    volatile const uint32_t ADCIRQSTAT;                      /**< 8C ADC Interrupt Status */
    volatile       uint32_t ADCSEQ;                          /**< 90 ADC Sequencer Control */
    volatile       uint32_t ADCSEQC;                         /**< 94 ADC Sequencer Configuration */
    volatile const uint32_t ADCSEQS;                         /**< 98 ADC Sequencer Status */
    volatile       uint32_t ADCSEQCH;                        /**< 9C ADC Sequencer Channel 0 */
    volatile       uint32_t ADCSEQCHMUX0;                    /**< A0 ADC Sequencer Channel 1 */
    volatile       uint32_t ADCSEQCHMUX1;                    /**< A4 ADC Sequencer Channel 1 */
    volatile       uint32_t ADCCMP;                          /**< A8 Digital Comparator 0 Configuration */
    volatile       uint32_t ADCCMPIRQSTAT;                   /**< AC Digital Comparator Interrupt Status */
    volatile       uint32_t ADCOFGNDIFF;                     /**< B0 ADC Offset Gain Differential Channel Error Correction */
    volatile       uint32_t ADCOFTEMP;                       /**< B4 ADC Offset Gain Temp Sensor Channel Error Correction */
    volatile       uint32_t ADCGNTEMP;                       /**< B8 ADC Offset Gain Temp Sensor Channel Error Correction */
    volatile       uint32_t ADCOFGNPGA0;                     /**< BC ADC Offset Gain PGA0 Channel Error Correction */
    volatile       uint32_t ADCOFGNPGA1;                     /**< C0 ADC Offset Gain PGA1 Channel Error Correction */
    volatile       uint32_t ADCOFGNPGA2;                     /**< C4 ADC Offset Gain PGA2 Channel Error Correction */
    volatile       uint32_t ADCOFGNPGA3;                     /**< C8 ADC Offset Gain PGA3 Channel Error Correction */
    volatile const uint8_t RESERVED0[136];                 
    volatile       uint32_t ADCCMP1;                         /**< 154 Digital Comparator 1 Configuration */
    volatile       uint32_t ADCCMP2;                         /**< 158 Digital Comparator 2 Configuration */
    volatile       uint32_t ADCCMP3;                         /**< 15C Digital Comparator 3 Configuration */
} ADI_ADC_TypeDef;

/*! ========================================================================
 *  \struct ADI_COMP_TypeDef
 *  \brief Your module description, here.
 *  ======================================================================== */
typedef struct _ADI_COMP_TypeDef
{
    volatile       uint32_t COMPCON0;                        /**< 0 No description provided */
    volatile       uint32_t COMPCON1;                        /**< 4 No description provided */
    volatile       uint32_t COMPCON2;                        /**< 8 No description provided */
    volatile       uint32_t COMPCON3;                        /**< C No description provided */
    volatile const uint32_t COMPIRQSTAT;                     /**< 10 No description provided */
} ADI_COMP_TypeDef;

/*! ========================================================================
 *  \struct ADI_PGA_TypeDef
 *  \brief Your module description, here.
 *  ======================================================================== */
typedef struct _ADI_PGA_TypeDef
{
    volatile       uint32_t PGABIASCON;                      /**< 0 PGA Bias Circuit Control Signal */
    volatile const uint8_t RESERVED0[28];                  
    volatile       uint32_t PGA0CON;                         /**< 20 PGA0 Control Register */
    volatile       uint32_t PGA0CHPCON;                      /**< 24 PGA0 Chop Function Ctrl */
    volatile       uint32_t PGA3CHPCON;                      /**< 28 PGA3 Chop Function Ctrl */
    volatile const uint8_t RESERVED1[68];                  
    volatile       uint32_t PGA1CON;                         /**< 70 PGA1 Control Register */
    volatile       uint32_t PGA1CHPCON;                      /**< 74 PGA1 Chop Function Ctrl */
    volatile const uint8_t RESERVED2[40];                  
    volatile       uint32_t PGA2CON;                         /**< A0 PGA2 Control Register */
    volatile       uint32_t PGA2CHPCON;                      /**< A4 PGA2 Chop Function Ctrl */
    volatile const uint8_t RESERVED3[40];                  
    volatile       uint32_t PGA3CON;                         /**< D0 PGA3 Control Register */
} ADI_PGA_TypeDef;

/*! ========================================================================
 *  \struct ADI_PLL_MMRS_TypeDef
 *  \brief Your module description, here.
 *  ======================================================================== */
typedef struct _ADI_PLL_MMRS_TypeDef
{
    volatile       uint32_t PLLPDCTRL;                       /**< 0 No description provided */
} ADI_PLL_MMRS_TypeDef;

/*! ========================================================================
 *  \struct ADI_VCM_MMRS_TypeDef
 *  \brief Your module description, here.
 *  ======================================================================== */
typedef struct _ADI_VCM_MMRS_TypeDef
{
    volatile       uint32_t TMPSNSCON;                       /**< 0 No description provided */
    volatile       uint32_t TMPSNSCHPCON;                    /**< 4 No description provided */
    volatile       uint32_t VCMREFCON;                       /**< 8 No description provided */
    volatile const uint8_t RESERVED0[4];                   
    volatile       uint32_t VCMBUFCON;                       /**< 10 No description provided */
} ADI_VCM_MMRS_TypeDef;

/*! ========================================================================
 *  \struct ADI_DAC_TypeDef
 *  \brief Your module description, here.
 *  ======================================================================== */
typedef struct _ADI_DAC_TypeDef
{
    volatile       uint32_t DACCON0;                         /**< 0 DAC Control Register */
    volatile       uint32_t DACCON1;                         /**< 4 DAC Control Register */
    volatile       uint32_t DACCON2;                         /**< 8 DAC Control Register */
    volatile       uint32_t DACCON3;                         /**< C DAC Control Register */
    volatile       uint32_t DACCON4;                         /**< 10 DAC Control Register */
    volatile       uint32_t DACCON5;                         /**< 14 DAC Control Register */
    volatile       uint32_t DACCON6;                         /**< 18 DAC Control Register */
    volatile       uint32_t DACCON7;                         /**< 1C DAC Control Register */
    volatile       uint32_t DACCON8;                         /**< 20 DAC Control Register */
    volatile       uint32_t DACCON9;                         /**< 24 DAC Control Register */
    volatile       uint32_t DACCON10;                        /**< 28 DAC Control Register */
    volatile       uint32_t DACCON11;                        /**< 2C DAC Control Register */
    volatile       uint32_t DACDAT0;                         /**< 30 DAC Data Register */
    volatile       uint32_t DACDAT1;                         /**< 34 DAC Data Register */
    volatile       uint32_t DACDAT2;                         /**< 38 DAC Data Register */
    volatile       uint32_t DACDAT3;                         /**< 3C DAC Data Register */
    volatile       uint32_t DACDAT4;                         /**< 40 DAC Data Register */
    volatile       uint32_t DACDAT5;                         /**< 44 DAC Data Register */
    volatile       uint32_t DACDAT6;                         /**< 48 DAC Data Register */
    volatile       uint32_t DACDAT7;                         /**< 4C DAC Data Register */
    volatile       uint32_t DACDAT8;                         /**< 50 DAC Data Register */
    volatile       uint32_t DACDAT9;                         /**< 54 DAC Data Register */
    volatile       uint32_t DACDAT10;                        /**< 58 DAC Data Register */
    volatile       uint32_t DACDAT11;                        /**< 5C DAC Data Register */
} ADI_DAC_TypeDef;


/*  =========================================================================
 * Peripheral Memory Map Declarations
 *  ========================================================================= */

#define ADI_GPT0_BASE                       (0x40000000U)    /* Base address of gpt0: */
#define ADI_GPT1_BASE                       (0x40000400U)    /* Base address of gpt1: */
#define ADI_GPT2_BASE                       (0x40000800U)    /* Base address of gpt2: */
#define ADI_GPTH0_BASE                      (0x40000C00U)    /* Base address of gpth0: */
#define ADI_GPTH1_BASE                      (0x40001000U)    /* Base address of gpth1: */
#define ADI_MISC_BASE                       (0x40002000U)    /* Base address of misc: */
#define ADI_WUT_BASE                        (0x40003000U)    /* Base address of wut: */
#define ADI_WDT_BASE                        (0x40004000U)    /* Base address of wdt: */
#define ADI_ALLON_BASE                      (0x40005000U)    /* Base address of allon: */
#define ADI_PLA_BASE                        (0x40006000U)    /* Base address of pla: */
#define ADI_DMAREQ_BASE                     (0x40007000U)    /* Base address of dmareq: */
#define ADI_UART0_BASE                      (0x40020000U)    /* Base address of uart0: */
#define ADI_UART1_BASE                      (0x40020400U)    /* Base address of uart1: */
#define ADI_I2C0_BASE                       (0x40020800U)    /* Base address of i2c0: */
#define ADI_I2C1_BASE                       (0x40020C00U)    /* Base address of i2c1: */
#define ADI_I2C2_BASE                       (0x40021000U)    /* Base address of i2c2: */
#define ADI_MDIO_BASE                       (0x40022000U)    /* Base address of mdio: */
#define ADI_DMA_BASE                        (0x40040000U)    /* Base address of dma: */
#define ADI_CACHE_BASE                      (0x40044000U)    /* Base address of cache: */
#define ADI_FLASH_BASE                      (0x40048000U)    /* Base address of flash: */
#define ADI_GPIO0_BASE                      (0x40050000U)    /* Base address of gpio0: */
#define ADI_GPIO1_BASE                      (0x40050050U)    /* Base address of gpio1: */
#define ADI_GPIO2_BASE                      (0x400500A0U)    /* Base address of gpio2: */
#define ADI_GPIO3_BASE                      (0x400500F0U)    /* Base address of gpio3: */
#define ADI_GPIO4_BASE                      (0x40050140U)    /* Base address of gpio4: */
#define ADI_GPIO5_BASE                      (0x40050190U)    /* Base address of gpio5: */
#define ADI_GPIO6_BASE                      (0x400501E0U)    /* Base address of gpio6: */
#define ADI_GPIO7_BASE                      (0x40050230U)    /* Base address of gpio7: */
#define ADI_GPIO8_BASE                      (0x40050280U)    /* Base address of gpio8: */
#define ADI_SPI0_BASE                       (0x40054000U)    /* Base address of spi0: */
#define ADI_SPI1_BASE                       (0x40058000U)    /* Base address of spi1: */
#define ADI_SPI2_BASE                       (0x4005C000U)    /* Base address of spi2: */
#define ADI_CLK_BASE                        (0x40060000U)    /* Base address of clk: */
#define ADI_PWM_BASE                        (0x40064000U)    /* Base address of pwm: */
#define ADI_SRAM_BASE                       (0x40065000U)    /* Base address of sram: */
#define ADI_CRC_BASE                        (0x40066000U)    /* Base address of crc: */
#define ADI_ADC_BASE                        (0x40068000U)    /* Base address of adc: */
#define ADI_COMP_BASE                       (0x40068A00U)    /* Base address of comp: */
#define ADI_PGA_BASE                        (0x40069000U)    /* Base address of pga: */
#define ADI_PLL_BASE                        (0x40069200U)    /* Base address of pll: */
#define ADI_TMPSNS_BASE                     (0x40069600U)    /* Base address of tmpsns: */
#define ADI_VDAC_BASE                       (0x40069800U)    /* Base address of vdac: */


/*  =========================================================================
 * Peripheral Pointer Declarations
 *  ========================================================================= */

#define pADI_GPT0                           ((ADI_TMR_TypeDef *) ADI_GPT0_BASE)                   /* Pointer to  (gpt0)*/
#define pADI_GPT1                           ((ADI_TMR_TypeDef *) ADI_GPT1_BASE)                   /* Pointer to  (gpt1)*/
#define pADI_GPT2                           ((ADI_TMR_TypeDef *) ADI_GPT2_BASE)                   /* Pointer to  (gpt2)*/
#define pADI_GPTH0                          ((ADI_TIMER_TypeDef *) ADI_GPTH0_BASE)                /* Pointer to  (gpth0)*/
#define pADI_GPTH1                          ((ADI_TIMER_TypeDef *) ADI_GPTH1_BASE)                /* Pointer to  (gpth1)*/
#define pADI_MISC                           ((ADI_MISC16_TypeDef *) ADI_MISC_BASE)                /* Pointer to  (misc)*/
#define pADI_WUT                            ((ADI_WUT_TypeDef *) ADI_WUT_BASE)                    /* Pointer to  (wut)*/
#define pADI_WDT                            ((ADI_WDT_TypeDef *) ADI_WDT_BASE)                    /* Pointer to  (wdt)*/
#define pADI_ALLON                          ((ADI_ALWAYS_ON_TypeDef *) ADI_ALLON_BASE)            /* Pointer to  (allon)*/
#define pADI_PLA                            ((ADI_PLA_TypeDef *) ADI_PLA_BASE)                    /* Pointer to  (pla)*/
#define pADI_DMAREQ                         ((ADI_DMAREQ_TypeDef *) ADI_DMAREQ_BASE)              /* Pointer to  (dmareq)*/
#define pADI_UART0                          ((ADI_UART_TypeDef *) ADI_UART0_BASE)                 /* Pointer to  (uart0)*/
#define pADI_UART1                          ((ADI_UART_TypeDef *) ADI_UART1_BASE)                 /* Pointer to  (uart1)*/
#define pADI_I2C0                           ((ADI_I2C_TypeDef *) ADI_I2C0_BASE)                   /* Pointer to  (i2c0)*/
#define pADI_I2C1                           ((ADI_I2C_TypeDef *) ADI_I2C1_BASE)                   /* Pointer to  (i2c1)*/
#define pADI_I2C2                           ((ADI_I2C_TypeDef *) ADI_I2C2_BASE)                   /* Pointer to  (i2c2)*/
#define pADI_MDIO                           ((ADI_MDIO_TypeDef *) ADI_MDIO_BASE)                  /* Pointer to  (mdio)*/
#define pADI_DMA                            ((ADI_DMA_TypeDef *) ADI_DMA_BASE)                    /* Pointer to  (dma)*/
#define pADI_CACHE                          ((ADI_CC_TypeDef *) ADI_CACHE_BASE)                   /* Pointer to  (cache)*/
#define pADI_FLASH                          ((ADI_FLASH_TypeDef *) ADI_FLASH_BASE)                /* Pointer to  (flash)*/
#define pADI_GPIO0                          ((ADI_GPIO_TypeDef *) ADI_GPIO0_BASE)                 /* Pointer to  (gpio0)*/
#define pADI_GPIO1                          ((ADI_GPIO_TypeDef *) ADI_GPIO1_BASE)                 /* Pointer to  (gpio1)*/
#define pADI_GPIO2                          ((ADI_GPIO_TypeDef *) ADI_GPIO2_BASE)                 /* Pointer to  (gpio2)*/
#define pADI_GPIO3                          ((ADI_GPIO_TypeDef *) ADI_GPIO3_BASE)                 /* Pointer to  (gpio3)*/
#define pADI_GPIO4                          ((ADI_GPIO_TypeDef *) ADI_GPIO4_BASE)                 /* Pointer to  (gpio4)*/
#define pADI_GPIO5                          ((ADI_GPIO_TypeDef *) ADI_GPIO5_BASE)                 /* Pointer to  (gpio5)*/
#define pADI_GPIO6                          ((ADI_GPIO_TypeDef *) ADI_GPIO6_BASE)                 /* Pointer to  (gpio6)*/
#define pADI_GPIO7                          ((ADI_GPIO_TypeDef *) ADI_GPIO7_BASE)                 /* Pointer to  (gpio7)*/
#define pADI_GPIO8                          ((ADI_GPIO_TypeDef *) ADI_GPIO8_BASE)                 /* Pointer to  (gpio8)*/
#define pADI_SPI0                           ((ADI_SPI_TypeDef *) ADI_SPI0_BASE)                   /* Pointer to  (spi0)*/
#define pADI_SPI1                           ((ADI_SPI_TypeDef *) ADI_SPI1_BASE)                   /* Pointer to  (spi1)*/
#define pADI_SPI2                           ((ADI_SPI_TypeDef *) ADI_SPI2_BASE)                   /* Pointer to  (spi2)*/
#define pADI_CLK                            ((ADI_CLOCK_TypeDef *) ADI_CLK_BASE)                  /* Pointer to  (clk)*/
#define pADI_PWM                            ((ADI_PWM_TypeDef *) ADI_PWM_BASE)                    /* Pointer to  (pwm)*/
#define pADI_SRAM                           ((ADI_SUBSYS_TypeDef *) ADI_SRAM_BASE)                /* Pointer to  (sram)*/
#define pADI_CRC                            ((ADI_CRC_TypeDef *) ADI_CRC_BASE)                    /* Pointer to  (crc)*/
#define pADI_ADC                            ((ADI_ADC_TypeDef *) ADI_ADC_BASE)                    /* Pointer to  (adc)*/
#define pADI_COMP                           ((ADI_COMP_TypeDef *) ADI_COMP_BASE)                  /* Pointer to  (comp)*/
#define pADI_PGA                            ((ADI_PGA_TypeDef *) ADI_PGA_BASE)                    /* Pointer to  (pga)*/
#define pADI_PLL                            ((ADI_PLL_MMRS_TypeDef *) ADI_PLL_BASE)               /* Pointer to  (pll)*/
#define pADI_TMPSNS                         ((ADI_VCM_MMRS_TypeDef *) ADI_TMPSNS_BASE)            /* Pointer to  (tmpsns)*/
#define pADI_VDAC                           ((ADI_DAC_TypeDef *) ADI_VDAC_BASE)                   /* Pointer to  (vdac)*/


/*  =========================================================================
 *! \enum   IRQn_Type
 *! \brief  Interrupt Number Assignments
 *  ========================================================================= */

typedef enum
{
    RESET_IRQn                                  =   -15,    /*!<* RESET */
    NonMaskableInt_IRQn                         =   -14,    /*!<* NonMaskableInt */
    HardFault_IRQn                              =   -13,    /*!<* HardFault */
    MemoryManagement_IRQn                       =   -12,    /*!<* MemoryManagement */
    BusFault_IRQn                               =   -11,    /*!<* BusFault */
    UsageFault_IRQn                             =   -10,    /*!<* UsageFault */
    SVCall_IRQn                                 =    -5,    /*!<* SVCall */
    DebugMonitor_IRQn                           =    -4,    /*!<* DebugMonitor */
    PendSV_IRQn                                 =    -2,    /*!<* PendSV */
    SysTick_IRQn                                =    -1,    /*!<* SysTick */
    WUT_IRQn                                    =     0,    /*!<* WUT */
    EINT0_IRQn                                  =     1,    /*!<* EINT0 */
    EINT1_IRQn                                  =     2,    /*!<* EINT1 */
    EINT2_IRQn                                  =     3,    /*!<* EINT2 */
    EINT3_IRQn                                  =     4,    /*!<* EINT3 */
    EINT4_IRQn                                  =     5,    /*!<* EINT4 */
    EINT5_IRQn                                  =     6,    /*!<* EINT5 */
    EINT6_IRQn                                  =     7,    /*!<* EINT6 */
    EINT7_IRQn                                  =     8,    /*!<* EINT7 */
    EINT8_IRQn                                  =     9,    /*!<* EINT8 */
    EINT9_IRQn                                  =    10,    /*!<* EINT9 */
    WDT_IRQn                                    =    11,    /*!<* WDT */
    GPT0_IRQn                                   =    12,    /*!<* GPT0 */
    GPT1_IRQn                                   =    13,    /*!<* GPT1 */
    GPT2_IRQn                                   =    14,    /*!<* GPT2 */
    GPT3_IRQn                                   =    15,    /*!<* GPT3 */
    GPT4_IRQn                                   =    16,    /*!<* GPT4 */
    MDIO_IRQn                                   =    17,    /*!<* MDIO */
    FLASH_IRQn                                  =    18,    /*!<* FLASH */
    UART0_IRQn                                  =    19,    /*!<* UART0 */
    UART1_IRQn                                  =    20,    /*!<* UART1 */
    SPI0_IRQn                                   =    21,    /*!<* SPI0 */
    SPI1_IRQn                                   =    22,    /*!<* SPI1 */
    SPI2_IRQn                                   =    23,    /*!<* SPI2 */
    I2C0S_IRQn                                  =    24,    /*!<* I2C0S */
    I2C0M_IRQn                                  =    25,    /*!<* I2C0M */
    I2C1S_IRQn                                  =    26,    /*!<* I2C1S */
    I2C1M_IRQn                                  =    27,    /*!<* I2C1M */
    I2C2S_IRQn                                  =    28,    /*!<* I2C2S */
    I2C2M_IRQn                                  =    29,    /*!<* I2C2M */
    PLA0_IRQn                                   =    30,    /*!<* PLA0 */
    PLA1_IRQn                                   =    31,    /*!<* PLA1 */
    PLA2_IRQn                                   =    32,    /*!<* PLA2 */
    PLA3_IRQn                                   =    33,    /*!<* PLA3 */
    PWM_TRIP_IRQn                               =    34,    /*!<* PWM_TRIP */
    PWM0_IRQn                                   =    35,    /*!<* PWM0 */
    PWM1_IRQn                                   =    36,    /*!<* PWM1 */
    PWM2_IRQn                                   =    37,    /*!<* PWM2 */
    PWM3_IRQn                                   =    38,    /*!<* PWM3 */
    SRAM_ERR_IRQn                               =    39,    /*!<* SRAM_ERR */
    DMA_ERR_IRQn                                =    40,    /*!<* DMA_ERR */
    DMA_SPI0_TX_IRQn                            =    41,    /*!<* DMA_SPI0_TX */
    DMA_SPI0_RX_IRQn                            =    42,    /*!<* DMA_SPI0_RX */
    DMA_SPI1_TX_IRQn                            =    43,    /*!<* DMA_SPI1_TX */
    DMA_SPI1_RX_IRQn                            =    44,    /*!<* DMA_SPI1_RX */
    DMA_SPI2_TX_IRQn                            =    45,    /*!<* DMA_SPI2_TX */
    DMA_SPI2_RX_IRQn                            =    46,    /*!<* DMA_SPI2_RX */
    DMA_UART0_TX_IRQn                           =    47,    /*!<* DMA_UART0_TX */
    DMA_UART0_RX_IRQn                           =    48,    /*!<* DMA_UART0_RX */
    DMA_UART1_TX_IRQn                           =    49,    /*!<* DMA_UART1_TX */
    DMA_UART1_RX_IRQn                           =    50,    /*!<* DMA_UART1_RX */
    DMA_I2C0S_TX_IRQn                           =    51,    /*!<* DMA_I2C0S_TX */
    DMA_I2C0S_RX_IRQn                           =    52,    /*!<* DMA_I2C0S_RX */
    DMA_I2C0M_IRQn                              =    53,    /*!<* DMA_I2C0M */
    DMA_I2C1S_TX_IRQn                           =    54,    /*!<* DMA_I2C1S_TX */
    DMA_I2C1S_RX_IRQn                           =    55,    /*!<* DMA_I2C1S_RX */
    DMA_I2C1M_IRQn                              =    56,    /*!<* DMA_I2C1M */
    DMA_I2C2S_TX_IRQn                           =    57,    /*!<* DMA_I2C2S_TX */
    DMA_I2C2S_RX_IRQn                           =    58,    /*!<* DMA_I2C2S_RX */
    DMA_I2C2M_IRQn                              =    59,    /*!<* DMA_I2C2M */
    DMA_MDIO_TX_IRQn                            =    60,    /*!<* DMA_MDIO_TX */
    DMA_MDIO_RX_IRQn                            =    61,    /*!<* DMA_MDIO_RX */
    DMA_FLASH_IRQn                              =    62,    /*!<* DMA_FLASH */
    DMA_ADC_IRQn                                =    63,    /*!<* DMA_ADC */
    PLL_IRQn                                    =    64,    /*!<* PLL */
    HFOSC_IRQn                                  =    65,    /*!<* HFOSC */
    ADC_IRQn                                    =    66,    /*!<* ADC */
    SEQ_IRQn                                    =    67,    /*!<* SEQ */
    COMP0_IRQn                                  =    68,    /*!<* COMP0 */
    COMP1_IRQn                                  =    69,    /*!<* COMP1 */
    COMP2_IRQn                                  =    70,    /*!<* COMP2 */
    COMP3_IRQn                                  =    71,    /*!<* COMP3 */
    VDAC_IRQn                                   =    72,    /*!<* VDAC */
    DMA_TRIG0_IRQn                              =    81,    /*!<* DMA_TRIG0 */
    DMA_TRIG1_IRQn                              =    82,    /*!<* DMA_TRIG1 */
    DMA_SW0_IRQn                                =    83,    /*!<* DMA_SW0 */
    DMA_SW1_IRQn                                =    84,    /*!<* DMA_SW1 */
    CACHE_IRQn                                  =    85,    /*!<* CACHE */
    DIG_COMP_IRQn                               =    86,    /*!<* DIG_COMP */
    GPIO_INTA_IRQn                              =    87,    /*!<* GPIO_INTA */
    GPIO_INTB_IRQn                              =    88,    /*!<* GPIO_INTB */
} IRQn_Type;  /* typedef name for fixed interrupt numbers */




/*  =========================================================================
 *! \enum   DMA_CHANn_TypeDef
 *! \brief  DMAChannel Number Assignments
 *  ========================================================================= */

typedef enum
{
    SPI0_TX_CHANn                               =     0,    /*!<* SPI0_TX */
    SPI0_RX_CHANn                               =     1,    /*!<* SPI0_RX */
    SPI1_TX_CHANn                               =     2,    /*!<* SPI1_TX */
    SPI1_RX_CHANn                               =     3,    /*!<* SPI1_RX */
    SPI2_TX_CHANn                               =     4,    /*!<* SPI2_TX */
    SPI2_RX_CHANn                               =     5,    /*!<* SPI2_RX */
    UART0_TX_CHANn                              =     6,    /*!<* UART0_TX */
    UART0_RX_CHANn                              =     7,    /*!<* UART0_RX */
    UART1_TX_CHANn                              =     8,    /*!<* UART1_TX */
    UART1_RX_CHANn                              =     9,    /*!<* UART1_RX */
    I2C0S_TX_CHANn                              =    10,    /*!<* I2C0S_TX */
    I2C0S_RX_CHANn                              =    11,    /*!<* I2C0S_RX */
    I2C0M_CHANn                                 =    12,    /*!<* I2C0M */
    I2C1S_TX_CHANn                              =    13,    /*!<* I2C1S_TX */
    I2C1S_RX_CHANn                              =    14,    /*!<* I2C1S_RX */
    I2C1M_CHANn                                 =    15,    /*!<* I2C1M */
    I2C2S_TX_CHANn                              =    16,    /*!<* I2C2S_TX */
    I2C2S_RX_CHANn                              =    17,    /*!<* I2C2S_RX */
    I2C2M_CHANn                                 =    18,    /*!<* I2C2M */
    MDIO_TX_CHANn                               =    19,    /*!<* MDIO_TX */
    MDIO_RX_CHANn                               =    20,    /*!<* MDIO_RX */
    FLASH_KHWR_CHANn                            =    21,    /*!<* FLASH_KHWR */
    ADC_RD_CHANn                                =    22,    /*!<* ADC_RD */
    sys_Trig0_CHANn                             =    27,    /*!<* sys_Trig0 */
    sys_Trig1_CHANn                             =    28,    /*!<* sys_Trig1 */
    sys_SW0_CHANn                               =    29,    /*!<* sys_SW0 */
    sys_SW1_CHANn                               =    30,    /*!<* sys_SW1 */
} DMA_CHANn_TypeDef;  /* typedef name for fixed DMA channel assignment */


#ifdef __cplusplus
}
#endif

#endif // __ADUCM410_H__

