
#ifndef __DIO_H__
#define __DIO_H__

#include "ADuCM410.h"

#ifdef __cplusplus
extern "C" {
#endif


#define PIN0   (1u<<0)
#define PIN1   (1u<<1)
#define PIN2   (1u<<2)
#define PIN3   (1u<<3)
#define PIN4   (1u<<4)
#define PIN5   (1u<<5)
#define PIN6   (1u<<6)
#define PIN7   (1u<<7)
#define PIN8   (1u<<8)
#define PIN9   (1u<<9)
#define PIN10  (1u<<10)
#define PIN11  (1u<<11)
#define PIN12  (1u<<12)
#define PIN13  (1u<<13)
#define PIN14  (1u<<14)
#define PIN15  (1u<<15)

//GPIO Pin mux configuration
#define P0_0_GPIO          0
#define P0_0_SPI0_SCLK     1
#define P0_0_COMP0_OUT     2
#define P0_0_PLA0_IN0        3
#define P0_1_GPIO          0
#define P0_1_SPI0_MISO     1
#define P0_1_COMP_OUT1     2
#define P0_1_PLA1_IN        3
#define P0_2_GPIO          0
#define P0_2_SPI0_MOSI     1
#define P0_2_PLA1_CLK     2
#define P0_2_PLA2_IN        3
#define P0_3_GPIO_IRQ0          0
#define P0_3_SPI0_CS     1
#define P0_3_PLA0_CLK     2
#define P0_3_PLA3_IN        3
#define P0_4_GPIO          0
#define P0_4_I2C0_SCL     1
#define P0_4_UART0_RX     2
#define P0_4_PLA2_OUT        3
#define P0_5_GPIO          0
#define P0_5_I2C0_SDA     1
#define P0_5_UART0_TX     2
#define P0_5_PLA3_OUT        3
#define P0_6_GPIO_IRQ3          0
#define P0_6_I2C2_SCL     1
#define P0_6_COMPD0_IN     2
#define P0_6_PLA4_OUT        3
#define P0_7_GPIO_IRQ4          0
#define P0_7_I2C2_SDA     1
#define P0_7_COMPD1_IN     2
#define P0_7_PLA5_OUT        3

#define P1_0_GPIO          0
#define P1_0_UART1_RX     1
#define P1_0_COMP2_OUT     2
#define P1_0_PLA4_IN        3
#define P1_1_GPIO          0
#define P1_1_UART1_TX     1
#define P1_1_COMP3_OUT     2
#define P1_1_PLA5_IN        3
#define P1_2_GPIO          0
#define P1_2_I2C1_SCL     1
#define P1_2_PWM0     2
#define P1_2_PLA6_IN        3
#define P1_3_GPIO          0
#define P1_3_I2C1_SDA     1
#define P1_3_PWM1     2
#define P1_3_PLA7_IN        3
#define P1_4_GPIO          0
#define P1_4_SPI1_SCLK     1
#define P1_4_PWM2     2
#define P1_4_PLA10_OUT        3
#define P1_5_GPIO          0
#define P1_5_SPI1_MISO     1
#define P1_5_PWM3     2
#define P1_5_PLA11_OUT        3
#define P1_6_GPIO          0
#define P1_6_SPI1_MOSI     1
#define P1_6_PWM4     2
#define P1_6_PLA12_OUT        3
#define P1_7_GPIO_IRQ1          0
#define P1_7_SPI1_CS     1
#define P1_7_PWM5     2
#define P1_7_PLA13_OUT        3

#define P2_0_GPIO          0
#define P2_0_ADCCONV     1
#define P2_0_COMPD2_IN     2
#define P2_0_PLA8_IN        3
#define P2_1_GPIO_IRQ2          0
#define P2_1_CLKIN     1
#define P2_1_COMPD3_IN     2
#define P2_1_PLA9_IN        3
#define P2_2_GPIO          0
#define P2_2_POR     1
#define P2_2_CLKOUT     2
#define P2_2_SWO        3
#define P2_3_GPIO          0
#define P2_3_PLA10_IN        3
#define P2_4_GPIO          0
#define P2_4_SPI2_MOSI     1
#define P2_4_UART1_RX     2
#define P2_4_PLA18_OUT        3
#define P2_5_GPIO          0
#define P2_5_SPI2_MISO     1
#define P2_5_UART1_TX     2
#define P2_5_PLA19_OUT        3
#define P2_6_GPIO_IRQ5          0
#define P2_6_SPI2_SCLK     1
#define P2_6_I2C1_SCL     2
#define P2_6_PLA20_OUT        3
#define P2_7_GPIO_IRQ6          0
#define P2_7_SPI2_CS     1
#define P2_7_I2C1_SDA     2
#define P2_7_PLA21_OUT        3

#define P3_0_GPIO_IRQ8          0
#define P3_0_MDADDR0     1
#define P3_0_SRDY0     2
#define P3_0_PLA12_IN        3
#define P3_1_GPIO          0
#define P3_1_MDADDR1     1
#define P3_1_PWMSYNC     2
#define P3_1_PLA13_IN        3
#define P3_2_GPIO          0
#define P3_2_MDADDR2     1
#define P3_2_PWMTRIP     2
#define P3_2_PLA14_IN        3
#define P3_3_GPIO          0
#define P3_3_MDADDR3          1
#define P3_3_PWM6          2
#define P3_3_PLA15_IN        3
#define P3_4_GPIO_IRQ9          0
#define P3_4_MDADDR4     1
#define P3_4_PWM7     2
#define P3_4_PLA26_OUT        3
#define P3_5_GPIO          0
#define P3_5_MCK     1
#define P3_5_SRDY1     2
#define P3_5_PLA27_OUT        3
#define P3_6_GPIO          0
#define P3_6_MDIO     1
#define P3_6_SRDY2     2
#define P3_6_PLA30_OUT        3
#define P3_7_GPIO          0
#define P3_7_PLA29_OUT        3

#define P4_0_GPIO            0
#define P4_0_VDAC3           1
#define P4_0_PLA11_IN        3
#define P4_1_GPIO            0
#define P4_1_VDAC6           1
#define P4_1_PLA28_OUT       3
#define P4_2_GPIO            0
#define P4_2_VDAC7           1
#define P4_3_GPIO            0
#define P4_4_GPIO            0
#define P4_4_VDAC5           1
#define P4_5_GPIO            0
#define P4_7_GPIO_IRQ7        0
#define P4_7_PLA2_CLK        2

#define P5_0_GPIO            0
#define P5_0_VDAC8           2
#define P5_1_GPIO            0
#define P5_1_VDAC9           2
#define P5_2_GPIO            0
#define P5_2_VDAC10          2
#define P5_3_GPIO            0
#define P5_3_VDAC11          2
#define P5_4_GPIO            0
#define P5_5_GPIO            0
#define P5_6_GPIO            0

#if 0       //not used in s2
#define P5_0_FULLMUX0        1
#define P5_1_FULLMUX1        1
#define P5_2_FULLMUX2        1
#define P5_3_FULLMUX3        1
#define P5_4_FULLMUX4        1
#define P5_5_FULLMUX5        1
#define P5_6_FULLMUX6        1
#endif
   
#define GPIO_PWR_1VX 0
#define GPIO_PWR_3V3 1
#define GPIO_PULLSEL_UP 1
#define GPIO_PULLSEL_DOWN  0


// =================================== Function API =====================

extern void DioCfgPin(ADI_GPIO_TypeDef *pPort, uint32_t PinMsk, uint32_t Mode);
extern void DioOenPin(ADI_GPIO_TypeDef *pPort, uint32_t PinMsk, uint32_t Oen);
extern void DioPullCfgPin(ADI_GPIO_TypeDef *pPort, uint32_t PinMsk, uint32_t Opt);
extern void DioPulPin(ADI_GPIO_TypeDef *pPort, uint32_t PinMsk, uint32_t Pul);
extern void DioIenPin(ADI_GPIO_TypeDef *pPort, uint32_t PinMsk, uint32_t Ien);
extern void DioSetPin(ADI_GPIO_TypeDef *pPort, uint32_t PinMsk);
extern void DioClrPin(ADI_GPIO_TypeDef *pPort, uint32_t PinMsk);
extern void DioTglPin(ADI_GPIO_TypeDef *pPort, uint32_t PinMsk);
extern void DioDsPin(ADI_GPIO_TypeDef *pPort,  uint32_t PinMsk, uint32_t Ds);
extern void DioOpenDrainPin(ADI_GPIO_TypeDef *pPort, uint32_t PinMsk, uint32_t En);
extern void DioInputCfgPin(ADI_GPIO_TypeDef *pPort, uint32_t PinMsk, uint32_t Opt);
extern void DioSlewRateCfgPin(ADI_GPIO_TypeDef *pPort, uint32_t PinMsk, uint32_t Opt);
extern void DioPwrCfgPin(ADI_GPIO_TypeDef *pPort, uint32_t PinMsk, uint32_t Opt);

extern uint8_t DioRd(ADI_GPIO_TypeDef *pPort);
extern void DioWr(ADI_GPIO_TypeDef *pPort, uint32_t Val);
extern uint32_t DioCfg(ADI_GPIO_TypeDef *pPort, uint32_t iMpx);
#ifdef __cplusplus
}
#endif

#endif // __DIO_H__
