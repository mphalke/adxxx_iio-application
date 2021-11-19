
#include "DioLib.h"

/**
   @brief void DioCfgPin(ADI_GPIO_TypeDef *pPort, uint32_t PinMsk, uint32_t Mode)
         ========== Configures the mode of 1 GPIO of the specified port.
   @param pPort :{pADI_GPIO0,pADI_GPIO1,pADI_GPIO2,pADI_GPIO3,
                  pADI_GPIO4,pADI_GPIO5,pADI_GPIO6,pADI_GPIO7,pADI_GPIO8}
   @param PinMsk :{PIN0|PIN1|PIN2|PIN3|PIN4|PIN5|PIN6|PIN7|
              PIN8|PIN9|PIN10|PIN11|PIN12|PIN13|PIN14|PIN15}
      - PIN0 to configure Px.0.
      - PIN1 to configure Px.1.
      - PIN2 to configure Px.2.
      - PIN3 to configure Px.3.
      - PIN4 to configure Px.4.
      - PIN5 to configure Px.5.
      - PIN6 to configure Px.6.
      - PIN7 to configure Px.7
      - PIN8 to configure Px.8.
      - PIN9 to configure Px.9.
      - PIN10 to configure Px.10.
      - PIN11 to configure Px.11.
      - PIN12 to configure Px.12.
      - PIN13 to configure Px.13.
      - PIN14 to configure Px.14.
      - PIN15 to configure Px.15.
        use combination of above pins
   @param Mode :{0, 1, 2, 3}
      - Set the mode accoring to the multiplex options required.
   @return none.
**/
void DioCfgPin(ADI_GPIO_TypeDef *pPort, uint32_t PinMsk, uint32_t Mode)
{
   uint32_t reg;
   uint32_t bitPos = 0;
   uint32_t checkMsk = 1;
   reg = pPort->CON;
   for(bitPos=0; bitPos<16; bitPos++)
   {
      if(PinMsk&checkMsk)
      {
         reg &= ~(3u<<(bitPos<<1));  //two bits of CFG register for each pin
         reg |= (Mode<<(bitPos<<1));
      }
      checkMsk = checkMsk<<1;
   }
   pPort->CON = (uint16_t)reg;
}

/**
   @brief uint32_t DioCfg(ADI_GPIO_TypeDef *pPort, uint32_t iMpx)
         ========== Sets Digital IO port multiplexer.
   @param pPort :{pADI_GPIO0,pADI_GPIO1,pADI_GPIO2,pADI_GPIO3,
                  pADI_GPIO4,pADI_GPIO5,pADI_GPIO6,pADI_GPIO7,pADI_GPIO8}
   @param iMpx :{0-0xFFFF}
      - Set iMpx accoring to the multiplex options required.
   @return 1.
**/

uint32_t DioCfg(ADI_GPIO_TypeDef *pPort, uint32_t iMpx)
{  
   pPort->CON = (uint16_t)iMpx;
   return 1;
}

/**
   @brief void DioOenPin(ADI_GPIO_TypeDef *pPort, uint32_t PinMsk, uint32_t Oen)
         ========== Enables the output drive of 1 GPIO of the specified port.
   @param pPort :{pADI_GPIO0,pADI_GPIO1,pADI_GPIO2,pADI_GPIO3,
                  pADI_GPIO4,pADI_GPIO5,pADI_GPIO6,pADI_GPIO7,pADI_GPIO8}
   @param PinMsk :{PIN0|PIN1|PIN2|PIN3|PIN4|PIN5|PIN6|PIN7}
   @param Oen :{0, 1}
      - 0 to disable the output drive
      - 1 to enable the output drive
   @return none.
**/
void DioOenPin(ADI_GPIO_TypeDef *pPort, uint32_t PinMsk, uint32_t Oen)
{
   uint32_t reg = pPort->OE;
   reg &= ~PinMsk;
   if(Oen)
      reg |= PinMsk;
   pPort->OE = (uint8_t)reg;
}

/**
   @brief void DioPullCfgPin(ADI_GPIO_TypeDef *pPort, uint32_t PinMsk, uint32_t Opt)
         ========== select CMOS or Schmitt input for specified pin
   @param pPort :{pADI_GPIO0,pADI_GPIO1,pADI_GPIO2,pADI_GPIO3,
                  pADI_GPIO4,pADI_GPIO5,pADI_GPIO6,pADI_GPIO7,pADI_GPIO8}
   @param PinMsk :{PIN0|PIN1|PIN2|PIN3|PIN4|PIN5|PIN6|PIN7}
   @param Opt :{0, 1}
      - 0 to select pull down
      - 1 to select pull up
   @return none.
**/
void DioPullCfgPin(ADI_GPIO_TypeDef *pPort, uint32_t PinMsk, uint32_t Opt)
{
   uint32_t reg = pPort->PS;
   reg &= ~PinMsk;
   if(Opt)
      reg |= PinMsk;
   pPort->PS = (uint8_t)reg;
}

/**
   @brief void DioPulPin(ADI_GPIO_TypeDef *pPort, uint32_t PinMsk, uint32_t Pul)
         ========== Configures the pull-up of 1 GPIO of the specified port.
   @param pPort :{pADI_GPIO0,pADI_GPIO1,pADI_GPIO2,pADI_GPIO3,
                  pADI_GPIO4,pADI_GPIO5,pADI_GPIO6,pADI_GPIO7,pADI_GPIO8}
   @param PinMsk :{PIN0|PIN1|PIN2|PIN3|PIN4|PIN5|PIN6|PIN7}
   @param Pul :{0, 1}
      - 0 to disable the pull-up
      - 1 to enable the pull-up
   @return none.
**/
void DioPulPin(ADI_GPIO_TypeDef *pPort, uint32_t PinMsk, uint32_t Pul)
{
   uint32_t reg = pPort->PE;
   reg &= ~PinMsk;
   if(Pul)
      reg |= PinMsk;
   pPort->PE = (uint8_t)reg;
}

/**
   @brief void DioIenPin(ADI_GPIO_TypeDef *pPort, uint32_t PinMsk, uint32_t Ien)
         ========== Enables the input path of 1 GPIO of the specified port.
   @param pPort :{pADI_GPIO0,pADI_GPIO1,pADI_GPIO2,pADI_GPIO3,
                  pADI_GPIO4,pADI_GPIO5,pADI_GPIO6,pADI_GPIO7,pADI_GPIO8}
   @param PinMsk :{PIN0|PIN1|PIN2|PIN3|PIN4|PIN5|PIN6|PIN7}
   @param Ien :{0, 1}
      - 0 to disable the input path
      - 1 to enable the input path
   @return none.
**/

void DioIenPin(ADI_GPIO_TypeDef *pPort, uint32_t PinMsk, uint32_t Ien)
{
   uint32_t reg = pPort->IE;
   reg &= ~PinMsk;
   if(Ien)
      reg |= PinMsk;
   pPort->IE = (uint8_t)reg;
}

/**
   @brief uint8_t DioRd(ADI_GPIO_TypeDef *pPort)
         ========== Reads values of port pins.
   @param pPort :{pADI_GPIO0,pADI_GPIO1,pADI_GPIO2,pADI_GPIO3,
                  pADI_GPIO4,pADI_GPIO5,pADI_GPIO6,pADI_GPIO7,pADI_GPIO8}
   @return none.
**/
uint8_t DioRd(ADI_GPIO_TypeDef *pPort)
{
   return (pPort->IN);
}

/**
   @brief void DioWr(ADI_GPIO_TypeDef *pPort, uint32_t Val)
         ========== Writes values to outputs.
   @param pPort :{pADI_GPIO0,pADI_GPIO1,pADI_GPIO2,pADI_GPIO3,
                  pADI_GPIO4,pADI_GPIO5,pADI_GPIO6,pADI_GPIO7,pADI_GPIO8}
   @param Val :{0-0xFF}
   @return none.
**/
void DioWr(ADI_GPIO_TypeDef *pPort, uint32_t Val)
{
   pPort->OUT = (uint8_t)Val;
}

/**
   @brief void DioSetPin(ADI_GPIO_TypeDef *pPort, uint32_t PinMsk)
         ========== Sets individual outputs.
   @param pPort :{pADI_GPIO0,pADI_GPIO1,pADI_GPIO2,pADI_GPIO3,
                  pADI_GPIO4,pADI_GPIO5,pADI_GPIO6,pADI_GPIO7,pADI_GPIO8}
   @param PinMsk :{PIN0|PIN1|PIN2|PIN3|PIN4|PIN5|PIN6|PIN7}
   @return none.
**/
void DioSetPin(ADI_GPIO_TypeDef *pPort, uint32_t PinMsk)
{
   pPort->SET = (uint8_t)PinMsk;
}

/**
   @brief void DioClrPin(ADI_GPIO_TypeDef *pPort, uint32_t PinMsk)
         ========== Clears individual outputs.
   @param pPort :{pADI_GPIO0,pADI_GPIO1,pADI_GPIO2,pADI_GPIO3,
                  pADI_GPIO4,pADI_GPIO5,pADI_GPIO6,pADI_GPIO7,pADI_GPIO8}
   @param PinMsk :{PIN0|PIN1|PIN2|PIN3|PIN4|PIN5|PIN6|PIN7}
   @return none.
**/

void DioClrPin(ADI_GPIO_TypeDef *pPort, uint32_t PinMsk)
{
   pPort->CLR = (uint8_t)PinMsk;
}

/**
   @brief void DioTglPin(ADI_GPIO_TypeDef *pPort, uint32_t PinMsk)
         ========== Toggles individual outputs.
   @param pPort :{pADI_GPIO0,pADI_GPIO1,pADI_GPIO2,pADI_GPIO3,
                  pADI_GPIO4,pADI_GPIO5,pADI_GPIO6,pADI_GPIO7,pADI_GPIO8}
   @param PinMsk :{PIN0|PIN1|PIN2|PIN3|PIN4|PIN5|PIN6|PIN7}
   @return none.
**/
void DioTglPin(ADI_GPIO_TypeDef *pPort, uint32_t PinMsk)
{
   pPort->TGL = (uint8_t)PinMsk;
}

/**
   @brief void DioDsPin(ADI_GPIO_TypeDef *pPort, uint32_t PinMsk, uint32_t Ds)
         ========== Controls the drive strength of 1 GPIO of the specified port.
   @param pPort :{pADI_GPIO0,pADI_GPIO1,pADI_GPIO2,pADI_GPIO3,
                  pADI_GPIO4,pADI_GPIO5,pADI_GPIO6,pADI_GPIO7,pADI_GPIO8}
   @param PinMsk :{PIN0|PIN1|PIN2|PIN3|PIN4|PIN5|PIN6|PIN7|
              PIN8|PIN9|PIN10|PIN11|PIN12|PIN13|PIN14|PIN15}
   @param Ds :{0,1,2,3}
      - 0, Drive Strength 1
      - 1, Drive Strength 2
      - 2, Drive Strength 3
      - 3, Drive Strength 4
   @return  1
**/
void DioDsPin(ADI_GPIO_TypeDef *pPort,  uint32_t PinMsk, uint32_t Ds)
{
   uint32_t reg;
   uint32_t bitPos = 0;
   uint32_t checkMsk = 1;
   reg = pPort->DS;
   for(bitPos=0; bitPos<16; bitPos++)
   {
      if(PinMsk&checkMsk)
      {
         reg &= ~(3u<<(bitPos<<1));  //two bits of CFG register for each pin
         reg |= (Ds<<(bitPos<<1));
      }
      checkMsk = checkMsk<<1;
   }
   pPort->DS = (uint16_t)reg;

}

/**
   @brief void DioOpenDrainPin(ADI_GPIO_TypeDef *pPort, uint32_t PinMsk, uint32_t En)
         ========== Enables/Disable open drain function of the specified Pin.
   @param pPort :{pADI_GPIO0,pADI_GPIO1,pADI_GPIO2,pADI_GPIO3,
                  pADI_GPIO4,pADI_GPIO5,pADI_GPIO6,pADI_GPIO7,pADI_GPIO8}
   @param PinMsk :{PIN0|PIN1|PIN2|PIN3|PIN4|PIN5|PIN6|PIN7}
   @param En :{0, 1}
      - 0 to disable open drain
      - 1 to enable open drain
   @return none.
**/
void DioOpenDrainPin(ADI_GPIO_TypeDef *pPort, uint32_t PinMsk, uint32_t En)
{
   uint32_t reg = pPort->ODE;
   reg &= ~PinMsk;
   if(En)
      reg |= PinMsk;
   pPort->ODE = (uint8_t)reg;
}

/**
   @brief void DioInputCfgPin(ADI_GPIO_TypeDef *pPort, uint32_t PinMsk, uint32_t Opt)
         ========== select CMOS or Schmitt input for specified pin
   @param pPort :{pADI_GPIO0,pADI_GPIO1,pADI_GPIO2,pADI_GPIO3,
                  pADI_GPIO4,pADI_GPIO5,pADI_GPIO6,pADI_GPIO7,pADI_GPIO8}
   @param PinMsk :{PIN0|PIN1|PIN2|PIN3|PIN4|PIN5|PIN6|PIN7}
   @param Opt :{0, 1}
      - 0 to select CMOS input
      - 1 to select Schmitt input
   @return none.
**/
void DioInputCfgPin(ADI_GPIO_TypeDef *pPort, uint32_t PinMsk, uint32_t Opt)
{
   uint32_t reg = pPort->IS;
   reg &= ~PinMsk;
   if(Opt)
      reg |= PinMsk;
   pPort->IS = (uint8_t)reg;
}

/**
   @brief void DioSlewRateCfgPin(ADI_GPIO_TypeDef *pPort, uint32_t PinMsk, uint32_t Opt)
         ========== select CMOS or Schmitt input for specified pin
   @param pPort :{pADI_GPIO0,pADI_GPIO1,pADI_GPIO2,pADI_GPIO3,
                  pADI_GPIO4,pADI_GPIO5,pADI_GPIO6,pADI_GPIO7,pADI_GPIO8}
   @param PinMsk :{PIN0|PIN1|PIN2|PIN3|PIN4|PIN5|PIN6|PIN7}
   @param Opt :{0, 1}
      - 0 to select fast slew rate
      - 1 to select slow slew rate
   @return none.
**/
void DioSlewRateCfgPin(ADI_GPIO_TypeDef *pPort, uint32_t PinMsk, uint32_t Opt)
{
   uint32_t reg = pPort->SR;
   reg &= ~PinMsk;
   if(Opt)
      reg |= PinMsk;
   pPort->SR = (uint8_t)reg;
}

/**
   @brief void DioPwrCfgPin(ADI_GPIO_TypeDef *pPort, uint32_t PinMsk, uint32_t Opt)
         ========== select CMOS or Schmitt input for specified pin
   @param pPort :{pADI_GPIO0,pADI_GPIO1,pADI_GPIO2,pADI_GPIO3,
                  pADI_GPIO4,pADI_GPIO5,pADI_GPIO6,pADI_GPIO7,pADI_GPIO8}
   @param PinMsk :{PIN0|PIN1|PIN2|PIN3|PIN4|PIN5|PIN6|PIN7}
   @param Opt :{GPIO_PWR_3V3, GPIO_PWR_1VX}
      - 0 or GPIO_PWR_1VX to select low power supply
      - 1 or GPIO_PWR_3V3 to select high power supply
   @return none.
**/
void DioPwrCfgPin(ADI_GPIO_TypeDef *pPort, uint32_t PinMsk, uint32_t Opt)
{
   uint32_t reg = pPort->PWR;
   reg &= ~PinMsk;
   if(Opt)
      reg |= PinMsk;
   pPort->PWR = (uint8_t)reg;
}

//parametric inverted data from PAD to logic 
//TBC







