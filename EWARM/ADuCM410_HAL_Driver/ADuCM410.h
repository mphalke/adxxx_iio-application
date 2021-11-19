/**
 *****************************************************************************
   @file     ADuCM410_Peri.h
   @brief    Header to include all peripheral headers and device header

   @internal   001 @endinternal
   @version  V0.1
   @author   ADI
   @date     May 2018
   @par Revision History:
   - V0.1, May 2018: initial version.


All files provided by ADI, including this file, are
provided as is without warranty of any kind, either expressed or implied.
The user assumes any and all risk from the use of this code.
It is the responsibility of the person integrating this code into an application
to ensure that the resulting application performs as required and is safe.

**/
#ifndef __ADUCM410_PERI_H__
#define __ADUCM410_PERI_H__


#ifdef __cplusplus
extern "C" {
#endif


#define __FPU_PRESENT          1u       /*!< FPU present                           */
#define __FPU_USED             1u       /*!< Enable FPU                           */
#define __NVIC_PRIO_BITS       3u       /*!< Number of Bits for Priority Levels    */
#define __MPU_PRESENT          1u
#define __DSP_PRESENT          1u

#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <stdbool.h>
#include "ADuCM410_device.h"
#include "ADuCM410_addr_rdef.h"
#include <core_cm33.h>
#include "system_ADuCM410.h"

//decalaration for interrupt handler
void NMI_Handler(void);        
void HardFault_Handler(void) __attribute__((noreturn));  
void MemManage_Handler(void) __attribute__((noreturn));  
void BusFault_Handler(void) __attribute__((noreturn));   
void UsageFault_Handler(void); 
void SVC_Handler(void);     
void DebugMon_Handler(void);
void PendSV_Handler(void); 
void SysTick_Handler(void);

void WakeUp_Int_Handler(void);         
void Ext_Int0_Handler(void);           
void Ext_Int1_Handler(void);           
void Ext_Int2_Handler(void);           
void Ext_Int3_Handler(void);           
void Ext_Int4_Handler(void);           
void Ext_Int5_Handler(void);           
void Ext_Int6_Handler(void);           
void Ext_Int7_Handler(void);           
void Ext_Int8_Handler(void);           
void Ext_Int9_Handler(void);           
void WDog_Tmr_Int_Handler(void);       
void GP_Tmr0_Int_Handler(void);         
void GP_Tmr1_Int_Handler(void);         
void GP_Tmr2_Int_Handler(void);         
void GP_Tmr3_Int_Handler(void);         
void GP_Tmr4_Int_Handler(void);         
void MDIO_Int_Handler(void);            
void Flsh_Int_Handler(void);            
void UART0_Int_Handler(void);           
void UART1_Int_Handler(void);           
void SPI0_Int_Handler(void);            
void SPI1_Int_Handler(void);            
void SPI2_Int_Handler(void);            
void I2C0_Slave_Int_Handler(void);      
void I2C0_Master_Int_Handler(void);     
void I2C1_Slave_Int_Handler(void);      
void I2C1_Master_Int_Handler(void);     
void I2C2_Slave_Int_Handler(void);      
void I2C2_Master_Int_Handler(void);     
void PLA0_Int_Handler(void);            
void PLA1_Int_Handler(void);            
void PLA2_Int_Handler(void);            
void PLA3_Int_Handler(void);            
void PWMTrip_Int_Handler(void);         
void PWM0_Int_Handler(void);            
void PWM1_Int_Handler(void);            
void PWM2_Int_Handler(void);            
void PWM3_Int_Handler(void);            
void SRAM_Err_Int_Handler(void);        
void DMA_Err_Int_Handler(void);         
void DMA_SPI0_TX_Int_Handler(void);     
void DMA_SPI0_RX_Int_Handler(void);     
void DMA_SPI1_TX_Int_Handler(void);     
void DMA_SPI1_RX_Int_Handler(void);     
void DMA_SPI2_TX_Int_Handler(void);     
void DMA_SPI2_RX_Int_Handler(void);     
void DMA_UART0_TX_Int_Handler(void);    
void DMA_UART0_RX_Int_Handler(void);    
void DMA_UART1_TX_Int_Handler(void);    
void DMA_UART1_RX_Int_Handler(void);    
void DMA_I2C0_STX_Int_Handler(void);    
void DMA_I2C0_SRX_Int_Handler(void);    
void DMA_I2C0_MTX_Int_Handler(void);    
void DMA_I2C1_STX_Int_Handler(void);    
void DMA_I2C1_SRX_Int_Handler(void);    
void DMA_I2C1_MTX_Int_Handler(void);    
void DMA_I2C2_STX_Int_Handler(void);    
void DMA_I2C2_SRX_Int_Handler(void);    
void DMA_I2C2_MTX_Int_Handler(void);    
void DMA_MDIO_TX_Int_Handler(void);     
void DMA_MDIO_RX_Int_Handler(void);     
void DMA_Flsh_Int_Handler(void);        
void DMA_ADC_Int_Handler(void);         
void PLL_Int_Handler(void);             
void HFOSC_Int_Handler(void);           
void ADC_Int_Handler(void);             
void SEQ_Int_Handler(void);             
void COMP0_Int_Handler(void);           
void COMP1_Int_Handler(void);           
void COMP2_Int_Handler(void);           
void COMP3_Int_Handler(void);           
void VDAC_Int_Handler(void);            
void LVDIE_Int_Handler(void);           
void HVDIE_Int_Handler(void);           
void SPI_LVD2D_Int_Handler(void);       
void SPI_HVD2D_Int_Handler(void);       
void SPI_LV_TX_Int_Handler(void);       
void SPI_LV_RX_Int_Handler(void);       
void SPI_HV_TX_Int_Handler(void);       
void SPI_HV_RX_Int_Handler(void);       
void DMA_TRIG0_Int_Handler(void);   
void DMA_TRIG1_Int_Handler(void);   
void DMA_SW0_Int_Handler(void);     
void DMA_SW1_Int_Handler(void);     
void DMA_CACHE_Int_Handler(void);   
void DMA_DIGCOMP_Int_Handler(void); 
void UnUsed_Handler(void); 


#ifdef __cplusplus
}
#endif

#endif   //#ifndef __ADUCM410_PERI_H__
