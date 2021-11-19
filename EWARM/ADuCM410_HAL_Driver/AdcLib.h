/*!
 *****************************************************************************
 * @file:  AdcLib.h 
 * @brief: header of Analog to Digital Convertor 
 *-----------------------------------------------------------------------------
 *
Copyright (c) 2013-2018 Analog Devices, Inc. All Rights Reserved.

This software is proprietary to Analog Devices, Inc. and its licensors.
By using this software you agree to the terms of the associated
Analog Devices Software License Agreement.
 ******************************************************************************/
#ifndef ADC_LIB_H
#define ADC_LIB_H

#ifdef __cplusplus
extern "C" {
#endif 

#include "ADuCM410.h"

/*
  ADC non-sequence mode channel selection
*/
//External AIN channels
//ADC Positive Channel numbers
#define	CHAN_P_AIN0		0
#define	CHAN_P_AIN2		2
#define	CHAN_P_AIN4		4
#define	CHAN_P_AIN6		6
#define	CHAN_P_AIN8		8
#define	CHAN_P_AIN10	10
#define	CHAN_P_AIN12	12
#define	CHAN_P_AIN14	14
#define CHAN_N_AIN1 2
#define CHAN_N_AIN3 3
#define CHAN_N_AIN5 4
#define CHAN_N_AIN7 5
#define CHAN_N_AIN9 6
#define CHAN_N_AIN11 7
#define CHAN_N_AIN13 8
#define CHAN_N_AIN15 9 

#define SING_END_CHAN_REFN_AIN0  ((0<<BITP_ADC_ADCCHA_ADCCN)|(0<<BITP_ADC_ADCCHA_ADCCP))
#define SING_END_CHAN_AIN1_REFN  ((0<<BITP_ADC_ADCCHA_ADCCN)|(1<<BITP_ADC_ADCCHA_ADCCP))
#define SING_END_CHAN_REFN_AIN2  ((0<<BITP_ADC_ADCCHA_ADCCN)|(2<<BITP_ADC_ADCCHA_ADCCP))
#define SING_END_CHAN_AIN3_REFN  ((0<<BITP_ADC_ADCCHA_ADCCN)|(3<<BITP_ADC_ADCCHA_ADCCP))
#define SING_END_CHAN_REFN_AIN4  ((0<<BITP_ADC_ADCCHA_ADCCN)|(4<<BITP_ADC_ADCCHA_ADCCP))
#define SING_END_CHAN_AIN5_REFN  ((0<<BITP_ADC_ADCCHA_ADCCN)|(5<<BITP_ADC_ADCCHA_ADCCP))
#define SING_END_CHAN_REFN_AIN6  ((0<<BITP_ADC_ADCCHA_ADCCN)|(6<<BITP_ADC_ADCCHA_ADCCP))
#define SING_END_CHAN_AIN7_REFN  ((0<<BITP_ADC_ADCCHA_ADCCN)|(7<<BITP_ADC_ADCCHA_ADCCP))
#define SING_END_CHAN_REFN_AIN8  ((0<<BITP_ADC_ADCCHA_ADCCN)|(8<<BITP_ADC_ADCCHA_ADCCP))
#define SING_END_CHAN_AIN9_REFN  ((0<<BITP_ADC_ADCCHA_ADCCN)|(9<<BITP_ADC_ADCCHA_ADCCP))
#define SING_END_CHAN_REFN_AIN10  ((0<<BITP_ADC_ADCCHA_ADCCN)|(10<<BITP_ADC_ADCCHA_ADCCP))
#define SING_END_CHAN_AIN11_REFN  ((0<<BITP_ADC_ADCCHA_ADCCN)|(11<<BITP_ADC_ADCCHA_ADCCP))
#define SING_END_CHAN_REFN_AIN12  ((0<<BITP_ADC_ADCCHA_ADCCN)|(12<<BITP_ADC_ADCCHA_ADCCP))
#define SING_END_CHAN_AIN13_REFN  ((0<<BITP_ADC_ADCCHA_ADCCN)|(13<<BITP_ADC_ADCCHA_ADCCP))
#define SING_END_CHAN_REFN_AIN14  ((0<<BITP_ADC_ADCCHA_ADCCN)|(14<<BITP_ADC_ADCCHA_ADCCP))
#define SING_END_CHAN_AIN15_REFN  ((0<<BITP_ADC_ADCCHA_ADCCN)|(15<<BITP_ADC_ADCCHA_ADCCP))


//interanl measurement channels
#define CHAN_PGA0 16
#define CHAN_PGA1 17
#define CHAN_PGA2 18
#define CHAN_PGA3 19
#define CHAN_TEMPSNS  20
#define CHAN_AVDD_DIV2  21
#define CHAN_IOVDD0_DIV2  22
#define CHAN_IOVDD1  23
#define CHAN_DVDD_DIV2  29
//DVDD_DIV2 and VSS(AGND) shared the same adc channel.
//it's determined by ADCCON[8] for which actually measured.
//use an unused value as MACRO for VSS channel. it's configured in AdcPinInt function when using VSS channel
#define CHAN_AVSS     (CHAN_DVDD_DIV2<<2)


/*
  ADC sequence mode channel selection
*/
//ADC sequencer Channel numbers
//#define SEQx_PositiveChan_NegtivaChan
#define SEQ0_AIN0_REFN  0x00
#define SEQ0_AIN0_REFP  0x01
#define SEQ0_AIN0_AIN1  0x02
#define SEQ0_AIN0_AIN3  0x03
#define SEQ0_AIN0_AIN5  0x04
#define SEQ0_AIN0_AIN7  0x05
#define SEQ0_AIN0_AIN9  0x06
#define SEQ0_AIN0_AIN11 0x07
#define SEQ0_AIN0_AIN13 0x08
#define SEQ0_AIN0_AIN15 0x09
#define SEQ1_REFN_AIN1  0x10
#define SEQ1_REFP_AIN1  0x11
#define SEQ2_AIN2_REFN  0x20
#define SEQ2_AIN2_REFP  0x21
#define SEQ2_AIN2_AIN1  0x22
#define SEQ2_AIN2_AIN3  0x23
#define SEQ2_AIN2_AIN1  0x22
#define SEQ2_AIN2_AIN3  0x23
#define SEQ2_AIN2_AIN5  0x24
#define SEQ2_AIN2_AIN7  0x25
#define SEQ2_AIN2_AIN9  0x26
#define SEQ2_AIN2_AIN11 0x27
#define SEQ2_AIN2_AIN13 0x28
#define SEQ2_AIN2_AIN15 0x29
#define SEQ3_REFN_AIN3  0x30
#define SEQ3_REFP_AIN3  0x31
#define SEQ4_AIN4_REFN  0x40
#define SEQ4_AIN4_REFP  0x41
#define SEQ4_AIN4_AIN1  0x42
#define SEQ4_AIN4_AIN3  0x43
#define SEQ4_AIN4_AIN5  0x44
#define SEQ4_AIN4_AIN7  0x45
#define SEQ4_AIN4_AIN9  0x46
#define SEQ4_AIN4_AIN11 0x47
#define SEQ4_AIN4_AIN13 0x48
#define SEQ4_AIN4_AIN15 0x49
#define SEQ5_REFN_AIN5  0x50
#define SEQ5_REFP_AIN5  0x51
#define SEQ6_AIN6_REFN  0x60
#define SEQ6_AIN6_REFP  0x61
#define SEQ6_AIN6_AIN1  0x62
#define SEQ6_AIN6_AIN3  0x63
#define SEQ6_AIN6_AIN5  0x64
#define SEQ6_AIN6_AIN7  0x65
#define SEQ6_AIN6_AIN9  0x66
#define SEQ6_AIN6_AIN11 0x67
#define SEQ6_AIN6_AIN13 0x68
#define SEQ6_AIN6_AIN15 0x69
#define SEQ7_REFN_AIN7  0x70
#define SEQ7_REFP_AIN7  0x71
#define SEQ8_AIN8_REFN  0x80
#define SEQ8_AIN8_REFP  0x81
#define SEQ8_AIN8_AIN1  0x82
#define SEQ8_AIN8_AIN3  0x83
#define SEQ8_AIN8_AIN5  0x84
#define SEQ8_AIN8_AIN7  0x85
#define SEQ8_AIN8_AIN9  0x86
#define SEQ8_AIN8_AIN11 0x87
#define SEQ8_AIN8_AIN13 0x88
#define SEQ8_AIN8_AIN15 0x89
#define SEQ9_REFN_AIN9  0x90
#define SEQ9_REFP_AIN9  0x91
#define SEQ10_AIN10_REFN  0xA0
#define SEQ10_AIN10_REFP  0xA1
#define SEQ10_AIN10_AIN1  0xA2
#define SEQ10_AIN10_AIN3  0xA3
#define SEQ10_AIN10_AIN5  0xA4
#define SEQ10_AIN10_AIN7  0xA5
#define SEQ10_AIN10_AIN9  0xA6
#define SEQ10_AIN10_AIN11 0xA7
#define SEQ10_AIN10_AIN13 0xA8
#define SEQ10_AIN10_AIN15 0xA9
#define SEQ11_REFN_AIN11  0xB0
#define SEQ11_REFP_AIN11  0xB1
#define SEQ12_AIN12_REFN  0xC0
#define SEQ12_AIN12_REFP  0xC1
#define SEQ12_AIN12_AIN1  0xC2
#define SEQ12_AIN12_AIN3  0xC3
#define SEQ12_AIN12_AIN5  0xC4
#define SEQ12_AIN12_AIN7  0xC5
#define SEQ12_AIN12_AIN9  0xC6
#define SEQ12_AIN12_AIN11 0xC7
#define SEQ12_AIN12_AIN13 0xC8
#define SEQ12_AIN12_AIN15 0xC9
#define SEQ13_REFN_AIN13  0xD0
#define SEQ13_REFP_AIN13  0xD1
#define SEQ14_AIN14_REFN  0xE0
#define SEQ14_AIN14_REFP  0xE1
#define SEQ14_AIN14_AIN1  0xE2
#define SEQ14_AIN14_AIN3  0xE3
#define SEQ14_AIN14_AIN5  0xE4
#define SEQ14_AIN14_AIN7  0xE5
#define SEQ14_AIN14_AIN9  0xE6
#define SEQ14_AIN14_AIN11 0xE7
#define SEQ14_AIN14_AIN13 0xE8
#define SEQ14_AIN14_AIN15 0xE9
#define SEQ15_REFN_AIN15  0xF0
#define SEQ15_REFP_AIN15  0xF1
#define SEQ16_PGA0        0x100
#define SEQ17_PGA1        0x110
#define SEQ18_PGA2        0x120
#define SEQ19_PGA3        0x130
#define SEQ20_TEMP        0x140
#define SEQ21_AVDD_DIV2   0x150
#define SEQ22_IOVDD0_DIV2 0x160
#define SEQ23_IOVDD1      0x170
#define SEQ29_AVSS        0x1D0



//REG_ADC_POSTIVECHANEL_NEGTIVECHANNEL_DATNUMBER
#define REG_ADC_AIN0_N_DAT0       (pADI_ADC->ADCDAT0)
#define REG_ADC_REF_AIN1_DAT1     (pADI_ADC->ADCDAT1)
#define REG_ADC_AIN2_N_DAT2       (pADI_ADC->ADCDAT2)
#define REG_ADC_REF_AIN3_DAT3     (pADI_ADC->ADCDAT3)
#define REG_ADC_AIN4_N_DAT4       (pADI_ADC->ADCDAT4)
#define REG_ADC_REF_AIN5_DAT5     (pADI_ADC->ADCDAT5)
#define REG_ADC_AIN6_N_DAT6       (pADI_ADC->ADCDAT6)
#define REG_ADC_REF_AIN7_DAT7     (pADI_ADC->ADCDAT7)
#define REG_ADC_AIN8_N_DAT8       (pADI_ADC->ADCDAT8)
#define REG_ADC_REF_AIN9_DAT9     (pADI_ADC->ADCDAT9)
#define REG_ADC_AIN10_N_DAT10     (pADI_ADC->ADCDAT10)
#define REG_ADC_REF_AIN11_DAT11   (pADI_ADC->ADCDAT11)
#define REG_ADC_AIN12_N_DAT12     (pADI_ADC->ADCDAT12)
#define REG_ADC_REF_AIN13_DAT13   (pADI_ADC->ADCDAT13)
#define REG_ADC_AIN14_N_DAT14     (pADI_ADC->ADCDAT14)
#define REG_ADC_REF_AIN15_DAT15   (pADI_ADC->ADCDAT15)
#define REG_ADC_PGA0_DAT16        (pADI_ADC->ADCDAT16)
#define REG_ADC_PGA1_DAT17        (pADI_ADC->ADCDAT17)
#define REG_ADC_PGA2_DAT18        (pADI_ADC->ADCDAT18)
#define REG_ADC_PGA3_DAT19        (pADI_ADC->ADCDAT19)
#define REG_ADC_TEMP_DAT20        (pADI_ADC->ADCDAT20)
#define REG_ADC_AVDD_DIV2_DAT21   (pADI_ADC->ADCDAT21)
#define REG_ADC_IOVDD0_DIV2_DAT22 (pADI_ADC->ADCDAT22)
#define REG_ADC_IOVDD1_DAT23      (pADI_ADC->ADCDAT23)
 
#define REG_ADC_AVSS_DAT29        (pADI_ADC->ADCDAT29)
  

typedef struct
{
   //1 - power down ADC
   //0 - power up ADC
   uint32_t adcPwrDown;

   uint32_t dmaEnForNonSeq;

   uint32_t dmaEnForSeq;

   //ENUM_ADC_ADCCON_PINMOD_PIN_LVL    CNV is Controlled by PIN Level 
   //ENUM_ADC_ADCCON_PINMOD_PIN_EDGE   CNV is Controlled by PIN Edge 
   uint32_t pinMode;

   //1 - enable timer event to trigger converion
   //0 - disable timer event to trigger conversion
   uint32_t timerTrigConv;

   //oversampling ratio
   //ENUM_ADC_ADCCON_OSR_OSR_NS1  Oversampling Disable 
   //ENUM_ADC_ADCCON_OSR_OSR2     Oversampling X2 
   //ENUM_ADC_ADCCON_OSR_OSR4     Oversampling X4 
   //ENUM_ADC_ADCCON_OSR_OSR8     Oversampling X8 
   //ENUM_ADC_ADCCON_OSR_OSR16    Oversampling X16 
   //ENUM_ADC_ADCCON_OSR_OSR_NS32 Oversampling X32 
   //ENUM_ADC_ADCCON_OSR_OSR_NS64 Oversampling Disable 
   //ENUM_ADC_ADCCON_OSR_OSR_NS128Oversampling Disable 
   uint32_t osr;

   //conversion frequency for positive channel
   //conversion frequency = ADC root clock/cnvFreqHighDiv
   //max 2MHz
   uint32_t cnvFreqHighDiv;
   //conversion frequency for positive channel
   //conversion frequency = ADC root clock/cnvFreqHighDiv
   //max 100KHz
   uint32_t cnvFreqLowDiv;

   uint32_t bypassPChanPreBuf;
   uint32_t bypassNChanPreBuf;

//------------ sequnce ---------
  //seqInterval<255, repeated sequence and insert delay with seqInterval*ADC sample rate
  //seqInterval==255, sequence only run once.
  uint32_t seqInterval;
  //1 - sequence enable 
  //0 - disable
  uint32_t seqEn;

//---------- Interrupt setup -------
   //1 -  enable conversion interrupt
   //0 - disable conversion interrupt 
   uint32_t CnvIntEn;

   uint32_t seqIntEn;

   //1 - power down ADC reference buffer
   //0 - power up ADC reference buffer
   uint32_t refBufPwrDown;

}ADC_SETUP_t;

#define PGA_AC_HP_FILTER_RES_IN_OHM     256000  //256K
#define PGA_AC_LP_FILTER_RES_IN_OHM     1000    //1K

typedef struct
{
  //0 -  enable PGA core
  //1 - disable PGA core
  uint32_t pgaPwrDown;

  //ENUM_PGA_PGA0CON_PGAMODE_DCCOUPLE  PGA DC Mode Enable 
  //ENUM_PGA_PGA0CON_PGAMODE_ACCOUPLE  PGA AC Coupling Mode Enable 
  uint32_t pgaMode;

  //ENUM_PGA_PGA0CON_PGAGAIN_GAIN1  Gain=1 
  //ENUM_PGA_PGA0CON_PGAGAIN_GAIN2  GAIN=2 
  //ENUM_PGA_PGA0CON_PGAGAIN_GAIN4  GAIN=4 
  //ENUM_PGA_PGA0CON_PGAGAIN_GAIN6  GAIN=6 
  //ENUM_PGA_PGA0CON_PGAGAIN_GAIN8  GAIN=8 
  //ENUM_PGA_PGA0CON_PGAGAIN_GAIN10 GAIN=10 
  uint32_t pgaGain;

  //0 - enable 1.25V buffer at postive input of PGA
  //1 - disable
  uint32_t vcm1_25VBufPwrDown;

  //1 - current sink ability improved 5mA
  //0 - normal: <1mA
  uint32_t sinkDriveImprove;

  //1 - enable Chop function
  //0 - disable chop
  uint32_t chopDis;

//---------- TIA mode -------
  //following configuration only useful when workAsTia set to 1
  //1 - working as TIA mode
  //0 - working as PGA mode
  uint32_t workAsTia;

  //ENUM_PGA_PGA0CON_TIAGAIN_RES250   TIARES=250ohm 
  //ENUM_PGA_PGA0CON_TIAGAIN_RES750   TIARES=750ohm 
  //ENUM_PGA_PGA0CON_TIAGAIN_RES2K    TIARES=2kohm 
  //ENUM_PGA_PGA0CON_TIAGAIN_RES5K    TIARES=5kohm 
  //ENUM_PGA_PGA0CON_TIAGAIN_RES10K   TIARES=10kohm 
  //ENUM_PGA_PGA0CON_TIAGAIN_RES20K   TIARES=20kohm 
  //ENUM_PGA_PGA0CON_TIAGAIN_RES100K  TIARES=100kohm 
  uint32_t tiaGain;

  //ENUM_PGA_PGA0CON_TIAVDACSEL_VDAC8SEL    Select VDAC8 as TIA Vbias
  //ENUM_PGA_PGA0CON_TIAVDACSEL_VDAC9SEL    Select VDAC9 as TIA Vbias
  //ENUM_PGA_PGA0CON_TIAVDACSEL_VDAC10SEL   Select VDAC10 as TIA Vbias
  //ENUM_PGA_PGA0CON_TIAVDACSEL_VDAC11SEL   Select VDAC11 as TIA Vbias
  uint32_t tiaBias;

}PGA_CHAN_SETUP_t;

typedef struct
{
   //200 mV VCM buffer, totally two for four PGAs,
   //0 - enable 200 mv VCM buffer0
   //1 - disable buffer
   uint32_t vcm200BufPwrDown0; 

   //0 - enable 200 mv VCM buffer0
   //1 - disable buffer
   uint32_t vcm200BufPwrDown1;

  //external cap is used as Low pass filter at PGA output
  //1 - bypass, no LPF
  //0 - enable LPF
  uint32_t bypassExtCap0;

    //external cap is used as Low pass filter at PGA output
  //1 - bypass, no LPF
  //0 - enable LPF
   uint32_t bypassExtCap1;

   //setup for each pga channel
   PGA_CHAN_SETUP_t pgaChxSetup[4];
}PGA_SETUP_t;


extern PGA_SETUP_t gPgaSetup;
extern ADC_SETUP_t gAdcSetup;


//------------------------ Function Declaration ---------------------
extern void PgaSetup(PGA_SETUP_t *pSetup);
extern void AdcSetup(ADC_SETUP_t *pAdcSetup);

extern void AdcPinSingleExt(uint32_t chanOpt);
extern void AdcPinDiffExt(uint32_t InN, uint32_t InP);
extern void AdcPinInt(uint32_t Channel);
extern void AdcSeqChan(uint32_t * const pSeqChx, uint32_t num);
extern void AdcGo(uint32_t Start);

extern int AdcRd(int iChan);
extern int AdcBuf( int iBufPDn, int iBufByp, int iRBufCfg);
extern int AdcSpeed(int iDiv);
extern int AdcCal( int iGain, int iOffset);
extern int AdcSeqCfg( int iEnable, int iChP, int iDelay);
extern int AdcSeqDiffCfg(int iDiff0,int iDiff2,int iDiff4,int iDiff6);
extern int AdcSeqStart( unsigned long iStart);


extern void AdcDigCompCfg(int compNum, int iDir, int iThreshold, int channel);
extern void AdcDigCompEn(int compNum, int compEn, int irqEn);

extern void Pga0GainSet(uint32_t gain);
extern void Pga1GainSet(uint32_t gain);
extern void Pga2GainSet(uint32_t gain);

#ifdef __cplusplus
}
#endif

#endif   //#ADC_LIB_H
