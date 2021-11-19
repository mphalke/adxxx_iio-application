/*!
 *****************************************************************************
 * @file:   AdcLib.c
 * @brief:  source file of ADC library, including ADC,TIA,PGA and temperature sensor module
 *-----------------------------------------------------------------------------
 *
Copyright (c) 2013-2018 Analog Devices, Inc. All Rights Reserved.

This software is proprietary to Analog Devices, Inc. and its licensors.
By using this software you agree to the terms of the associated
Analog Devices Software License Agreement.
 ******************************************************************************/

#include "AdcLib.h"

/*
@brief void AdcPinDiffExt(uint32_t InN, uint32_t InP)
      =========== select ADC channel pin when measuring AIN channel in differential mode
@param InN: {CHAN_N_AIN1,CHAN_N_AIN3,CHAN_N_AIN5,CHAN_N_AIN7,
            CHAN_N_AIN9,CHAN_N_AIN11,CHAN_N_AIN13,CHAN_N_AIN15}
            negtive channel selection
@param InP: {CHAN_P_AIN0,CHAN_P_AIN2,CHAN_P_AIN4,CHAN_P_AIN6,CHAN_P_AIN8,
            CHAN_P_AIN10,CHAN_P_AIN12,CHAN_P_AIN14}
            positive channel selection
@return none
**/
void AdcPinDiffExt(uint32_t InN, uint32_t InP)
{
   uint32_t regAdcChan;
   regAdcChan = (InN<<BITP_ADC_ADCCHA_ADCCN)|(InP<<BITP_ADC_ADCCHA_ADCCP);
   pADI_ADC->ADCCHA = regAdcChan;   
}

/*
@brief void AdcPinSingleExt(uint32_t chanOpt)
      =========== select ADC channel pin when measuring AIN channel in single-ended mode
@param chanOpt: negative channel _ postive channel 
      SING_END_CHAN_REFN_AIN0     
      SING_END_CHAN_AIN1_REFN  
      SING_END_CHAN_REFN_AIN2  
      SING_END_CHAN_AIN3_REFN  
      SING_END_CHAN_REFN_AIN4  
      SING_END_CHAN_AIN5_REFN  
      SING_END_CHAN_REFN_AIN6  
      SING_END_CHAN_AIN7_REFN  
      SING_END_CHAN_REFN_AIN8  
      SING_END_CHAN_AIN9_REFN  
      SING_END_CHAN_REFN_AIN10 
      SING_END_CHAN_AIN11_REFN 
      SING_END_CHAN_REFN_AIN12 
      SING_END_CHAN_AIN13_REFN 
      SING_END_CHAN_REFN_AIN14 
      SING_END_CHAN_AIN15_REFN 
@return none
@note use CHAN_P_REFN/CHAN_P_REFP with CHAN_N_REF_AINx,
      use CHAN_P_AINx with CHAN_N_REFN/CHAN_N_REFP
**/
void AdcPinSingleExt(uint32_t chanOpt)
{
   pADI_ADC->ADCCHA = chanOpt;
}

/*
@brief void AdcPinInt(uint32_t Channel)
      =========== ADC channel for measuring internal channels
@param Channel: {CHAN_PGA0,CHAN_PGA1,CHAN_PGA2,CHAN_PGA3,CHAN_TEMPSNS,
                  CHAN_AVDD_DIV2,CHAN_IOVDD0_DIV2,CHAN_IOVDD1,CHAN_AVSS, CHAN_DVDD_DIV2}
@return none
**/
void AdcPinInt(uint32_t Channel)
{
   uint32_t regAdcChan, regAdcCon;
   regAdcCon = pADI_ADC->ADCCON;
   if(Channel == CHAN_AVSS)
   {
      regAdcCon |=  BITM_ADC_ADCCON_VDDSEL;
      regAdcChan = CHAN_DVDD_DIV2<<BITP_ADC_ADCCHA_ADCCP;
   }
   else if(Channel == CHAN_DVDD_DIV2)
   {
      regAdcCon &=  ~BITM_ADC_ADCCON_VDDSEL;
      regAdcChan = CHAN_DVDD_DIV2<<BITP_ADC_ADCCHA_ADCCP;
   }
   else
   {
      regAdcChan = Channel<<BITP_ADC_ADCCHA_ADCCP;
   }

   pADI_ADC->ADCCHA = regAdcChan; 
   pADI_ADC->ADCCON = regAdcCon;
}

/*
@brief void AdcGo(uint32_t Start)
      =========== start/stop ADC conversion
@param Start: {ENUM_ADC_ADCCON_CONVTYPE_IDLE ,ENUM_ADC_ADCCON_CONVTYPE_GPIO,
               ENUM_ADC_ADCCON_CONVTYPE_SINGL,ENUM_ADC_ADCCON_CONVTYPE_CONT,
               ENUM_ADC_ADCCON_CONVTYPE_PLA  ,ENUM_ADC_ADCCON_CONVTYPE_GPT}   
               - ENUM_ADC_ADCCON_CONVTYPE_IDLE  No Conversion          
               - ENUM_ADC_ADCCON_CONVTYPE_GPIO  ADC Controlled by GPIO Pin 
               - ENUM_ADC_ADCCON_CONVTYPE_SINGL Software Single Conversion 
               - ENUM_ADC_ADCCON_CONVTYPE_CONT  Software Continue Conversion 
               - ENUM_ADC_ADCCON_CONVTYPE_PLA   PLA Conversion 
               - ENUM_ADC_ADCCON_CONVTYPE_GPT   GPT Triggered Conversion 
@return none
**/
void AdcGo(uint32_t Start)
{
   pADI_ADC->ADCCON &= ~BITM_ADC_ADCCON_CONVTYPE;
   pADI_ADC->ADCCON |= Start;
}


static uint32_t muxDiffBit[16] = {0,4,5,9,10,14,15,19,20,24,25,29,0,4,5,9};

/*
@brief void AdcSeqChan(uint32_t * const pSeqChx, uint32_t num)
      =========== confiuring sequence channel 
@param pSeqChx: pointer to channel table
@return none
**/
void AdcSeqChan(uint32_t * const pSeqChx, uint32_t num)
{
   uint32_t regSeqCh,regSeqChMux0,regSeqChMux1;
   uint32_t i,chanVal,bitPos;
   uint32_t *pChx = pSeqChx;
   regSeqCh = 0;
   regSeqChMux0 = 0;
   regSeqChMux1 = 0;
   for(i=0; i<num; i++)
   {
      chanVal = *pChx;
      bitPos = (chanVal>>4);
      regSeqCh |= 1<<bitPos;
      if(chanVal < SEQ12_AIN12_REFN)
      {
         regSeqChMux0 |= ((chanVal&0x000F)<<muxDiffBit[bitPos]);
      }
      else
      {
         regSeqChMux1 |= ((chanVal&0x000F)<<muxDiffBit[bitPos]);
      }
      pChx++;
   }
   pADI_ADC->ADCSEQCH = regSeqCh;
   pADI_ADC->ADCSEQCHMUX0 = regSeqChMux0;
   pADI_ADC->ADCSEQCHMUX1 = regSeqChMux1;
}



/*
@brief extern void PgaSetup(PGA_SETUP_t *setup)
      =========== setup for PGA
 
@param setup: pointer of PGA_SETUP_t structure
@return none
**/
void PgaSetup(PGA_SETUP_t *pSetup)
{
   uint32_t regPgaCon[4],regPgaBiasCon,regChopCon[4];

   regPgaBiasCon = (pSetup->vcm200BufPwrDown0<<BITP_PGA_PGABIASCON_PD0BUF0P2)   \
                     |(pSetup->vcm200BufPwrDown1<<BITP_PGA_PGABIASCON_PD1BUF0P2) \
                     |(pSetup->pgaChxSetup[0].vcm1_25VBufPwrDown<<BITP_PGA_PGABIASCON_PD0BUF1P25)  \
                     |(pSetup->pgaChxSetup[1].vcm1_25VBufPwrDown<<BITP_PGA_PGABIASCON_PD1BUF1P25)  \
                     |(pSetup->pgaChxSetup[2].vcm1_25VBufPwrDown<<BITP_PGA_PGABIASCON_PD2BUF1P25)  \
                     |(pSetup->pgaChxSetup[3].vcm1_25VBufPwrDown<<BITP_PGA_PGABIASCON_PD3BUF1P25);
   for(uint32_t i=0;i<4;i++)
   {
      regPgaCon[i] = (pSetup->pgaChxSetup[i].pgaPwrDown<<BITP_PGA_PGA0CON_PDPGACORE)   \
                     |(pSetup->pgaChxSetup[i].pgaMode<<BITP_PGA_PGA0CON_PGAMODE)   \
                     |(pSetup->pgaChxSetup[i].pgaGain<<BITP_PGA_PGA0CON_PGAGAIN)   \
                     |(pSetup->pgaChxSetup[i].sinkDriveImprove<<BITP_PGA_PGA0CON_DRVEN)   \
                     |(pSetup->pgaChxSetup[i].workAsTia<<BITP_PGA_PGA0CON_MODE)   \
                     |(pSetup->pgaChxSetup[i].tiaGain<<BITP_PGA_PGA0CON_TIAGAIN)   \
                     |(pSetup->pgaChxSetup[i].tiaBias<<BITP_PGA_PGA0CON_TIAVDACSEL);
      regChopCon[i] = pSetup->pgaChxSetup[i].chopDis<<BITP_PGA_PGA0CHPCON_CHOPOFF;
   }

   pADI_PGA->PGABIASCON = regPgaBiasCon;
   pADI_PGA->PGA0CHPCON = regChopCon[0];
   pADI_PGA->PGA1CHPCON = regChopCon[1];
   pADI_PGA->PGA2CHPCON = regChopCon[2];
   pADI_PGA->PGA3CHPCON = regChopCon[3];
   pADI_PGA->PGA0CON = regPgaCon[0]|(pSetup->bypassExtCap0<<BITP_PGA_PGA0CON_CAPBYPASS);
   pADI_PGA->PGA1CON = regPgaCon[1];
   pADI_PGA->PGA2CON = regPgaCon[2]|(pSetup->bypassExtCap1<<BITP_PGA_PGA0CON_CAPBYPASS);
   pADI_PGA->PGA3CON = regPgaCon[3];
}

/*
@brief void AdcSetup(ADC_SETUP_t *pAdcSetup)
      =========== Setup ADC
 
@param pAdcSetup: pointer to ADC_SETUP_t structure
@return none
**/
void AdcSetup(ADC_SETUP_t *pAdcSetup)
{
   uint32_t regAdcCon,regPreBufCon,regAdcSeq;

   regAdcCon = (pAdcSetup->adcPwrDown<<BITP_ADC_ADCCON_PDADC) \
               |(pAdcSetup->osr<<BITP_ADC_ADCCON_OSR) \
               |(pAdcSetup->CnvIntEn<<BITP_ADC_ADCCON_CNVIRQEN)   \
               |(pAdcSetup->timerTrigConv<<BITP_ADC_ADCCON_GPTEVENTEN)  \
               |(pAdcSetup->refBufPwrDown<<BITP_ADC_ADCCON_PDREFBUF)    \
               |(pAdcSetup->pinMode<<BITP_ADC_ADCCON_PINMOD)   \
               |(pAdcSetup->dmaEnForSeq<<BITP_ADC_ADCCON_SEQDMA)  \
               |(pAdcSetup->dmaEnForNonSeq<<BITP_ADC_ADCCON_CNVDMA);
   regPreBufCon = (pAdcSetup->bypassPChanPreBuf<<BITP_ADC_PREBUFCON_PRGBYPP)  \
                  |(pAdcSetup->bypassNChanPreBuf<<BITP_ADC_PREBUFCON_PRGBYPN);

   regAdcSeq = (pAdcSetup->seqIntEn<<BITP_ADC_ADCSEQ_SEQIRQEN)
                  |(pAdcSetup->seqEn<<BITP_ADC_ADCSEQ_SEQEN);

   pADI_ADC->ADCCNVC = pAdcSetup->cnvFreqHighDiv;
   pADI_ADC->ADCCNVCSLOW = pAdcSetup->cnvFreqLowDiv;
   pADI_ADC->ADCSEQC =  pAdcSetup->seqInterval;
   pADI_ADC->ADCSEQ = regAdcSeq;
   pADI_ADC->PREBUFCON = regPreBufCon;
   pADI_ADC->ADCCON = regAdcCon;

}

/*
@brief void AdcDigCompCfg(int compNum, int iDir, int iThreshold, int channel);
      =========== Setup ADC digital comparator
 
@param compNum: {0,1,2,3}
             0 - comparator 0
             1 - comparator 1
             2 - comparator 2
             3 - comparator 3
@param iDir: {0,1}
             0 - generate interrupt if smaller than or equal to threshold value
             1 - generate interrupt if greater than threshold value
@param iThreshold: 16 bit ADC code to compare
@param channel: index of ADC data register to be compared    

@return none
**/
void AdcDigCompCfg(int compNum, int iDir, int iThreshold, int channel)
{
   uint32_t reg;
   volatile uint32_t * pReg = &(pADI_ADC->ADCCMP);
   switch(compNum)
   {
      case 0: pReg = (&(pADI_ADC->ADCCMP));break;
      case 1: pReg = (&(pADI_ADC->ADCCMP1));break;
      case 2: pReg = (&(pADI_ADC->ADCCMP2));break;
      case 3: pReg = (&(pADI_ADC->ADCCMP3));break;
      default: return ;
   }

   reg = *pReg;
   reg &= ~(BITM_ADC_ADCCMP_CMPDIR|BITM_ADC_ADCCMP_THR|BITM_ADC_ADCCMP_CH);
   reg |= (uint32_t)((iDir<<BITP_ADC_ADCCMP_CMPDIR) | (iThreshold<<BITP_ADC_ADCCMP_THR)\
         | (channel<<BITP_ADC_ADCCMP_CH));
   *pReg = reg;

}

/*
@brief void AdcDigCompEn(int compNum, int compEn, int irqEn);
      =========== Enable/Disable comparator and IRQ
 
@param irqEn: {0,1,2,3}
             0 - comparator 0
             1 - comparator 1
             2 - comparator 2
             3 - comparator 3
@param compEn: {0,1}
             0 - Disable comparator
             1 - Enable comparator
@param irqEn: {0,1}
             0 - Do not generate interrupt
             1 - Generate interrupt
@return none
**/
void AdcDigCompEn(int compNum, int compEn, int irqEn)
{
   uint32_t reg;
   volatile uint32_t * pReg = (&(pADI_ADC->ADCCMP));
   switch(compNum)
   {
      case 0: pReg = (&(pADI_ADC->ADCCMP));break;
      case 1: pReg = (&(pADI_ADC->ADCCMP1));break;
      case 2: pReg = (&(pADI_ADC->ADCCMP2));break;
      case 3: pReg = (&(pADI_ADC->ADCCMP3));break;
      default: return ;
   }

   reg = *pReg;
   reg &= ~(BITM_ADC_ADCCMP_EN|BITM_ADC_ADCCMP_IRQEN);
   reg |= (uint32_t)((compEn<<BITP_ADC_ADCCMP_EN) | (irqEn<<BITP_ADC_ADCCMP_IRQEN));
   *pReg = reg;
}


/*
@brief void Pga0GainSet(uint32_t gain)
      =========== set gain for pga
 
@param gain: 
            - ENUM_PGA_PGA0CON_PGAGAIN_GAIN1   , Gain=1 
            - ENUM_PGA_PGA0CON_PGAGAIN_GAIN2   , GAIN=2 
            - ENUM_PGA_PGA0CON_PGAGAIN_GAIN4   , GAIN=4 
            - ENUM_PGA_PGA0CON_PGAGAIN_GAIN6   , GAIN=6 
            - ENUM_PGA_PGA0CON_PGAGAIN_GAIN8   , GAIN=8 
            - ENUM_PGA_PGA0CON_PGAGAIN_GAIN10  , GAIN=10
@return none
**/
void Pga0GainSet(uint32_t gain)
{
    uint32_t regPgaCon;
    regPgaCon = pADI_PGA->PGA0CON;
    regPgaCon &= ~BITM_PGA_PGA0CON_PGAGAIN;
    regPgaCon |= (gain<<BITP_PGA_PGA0CON_PGAGAIN);
    pADI_PGA->PGA0CON = regPgaCon;
}

/*
@brief void Pga1GainSet(uint32_t gain)
      =========== set gain for pga
 
@param gain: 
            - ENUM_PGA_PGA0CON_PGAGAIN_GAIN1   , Gain=1 
            - ENUM_PGA_PGA0CON_PGAGAIN_GAIN2   , GAIN=2 
            - ENUM_PGA_PGA0CON_PGAGAIN_GAIN4   , GAIN=4 
            - ENUM_PGA_PGA0CON_PGAGAIN_GAIN6   , GAIN=6 
            - ENUM_PGA_PGA0CON_PGAGAIN_GAIN8   , GAIN=8 
            - ENUM_PGA_PGA0CON_PGAGAIN_GAIN10  , GAIN=10
@return none
**/
void Pga1GainSet(uint32_t gain)
{
    uint32_t regPgaCon;
    regPgaCon = pADI_PGA->PGA1CON;
    regPgaCon &= ~BITM_PGA_PGA0CON_PGAGAIN;
    regPgaCon |= (gain<<BITP_PGA_PGA0CON_PGAGAIN);
    pADI_PGA->PGA1CON = regPgaCon;
}

/*
@brief void Pga2GainSet(uint32_t gain)
      =========== set gain for pga
 
@param gain: 
            - ENUM_PGA_PGA0CON_PGAGAIN_GAIN1   , Gain=1 
            - ENUM_PGA_PGA0CON_PGAGAIN_GAIN2   , GAIN=2 
            - ENUM_PGA_PGA0CON_PGAGAIN_GAIN4   , GAIN=4 
            - ENUM_PGA_PGA0CON_PGAGAIN_GAIN6   , GAIN=6 
            - ENUM_PGA_PGA0CON_PGAGAIN_GAIN8   , GAIN=8 
            - ENUM_PGA_PGA0CON_PGAGAIN_GAIN10  , GAIN=10
@return none
**/
void Pga2GainSet(uint32_t gain)
{
    uint32_t regPgaCon;
    regPgaCon = pADI_PGA->PGA2CON;
    regPgaCon &= ~BITM_PGA_PGA0CON_PGAGAIN;
    regPgaCon |= (gain<<BITP_PGA_PGA0CON_PGAGAIN);
    pADI_PGA->PGA2CON = regPgaCon;
}



