/***************************************************************************//**
 *   @file    app_config_aducm410.c
 *   @brief   Application configurations module for ADuCM410 platform
********************************************************************************
 * Copyright (c) 2021 Analog Devices, Inc.
 * All rights reserved.
 *
 * This software is proprietary to Analog Devices, Inc. and its licensors.
 * By using this software you agree to the terms of the associated
 * Analog Devices Software License Agreement.
*******************************************************************************/

/******************************************************************************/
/***************************** Include Files **********************************/
/******************************************************************************/

#include <stdbool.h>

#include "ADuCM410.h"
#include "DioLib.h"
#include "ClkLib.h"
#include "UrtLib.h"
#include "SpiLib.h"
#include "IntLib.h"
#include "WdtLib.h"

#include "app_config.h"
#include "app_config_aducm410.h"
#include "error.h"
#include "gpio.h"

/******************************************************************************/
/************************ Macros/Constants ************************************/
/******************************************************************************/

/******************************************************************************/
/******************** Variables and User Defined Data Types *******************/
/******************************************************************************/

/* UART ADuCM410 platform specific init parameters */
aducm410_uart_init_param aducm410_uart_extra_init_params  = {
	.uart_tx_pin = UART_TX,
	.uart_rx_pin = UART_RX,
	.uart_port = UART_PORT,
	.uart_setup = &gUrt1Setup
};

/* SPI ADuCM410 platform specific parameters */
/* Define SPI extra init parameters structure (SPI freq = 20Mz) */
aducm410_spi_init_param aducm410_spi_extra_init_params = {
	.spi_port = SPI_PORT,
	.spi_setup = &gSpi1Setup,
	/* fserialclock = SPICLOCK / 2x(clk_div+1)
	    SPICLOCK = 160Mhz (set in clock system init)
	   if clk_div = 3, fserialclock = 20 Mhz */
	.clk_div = 3
};

/* Define external interrupt platform specific parameters structure */
aducm410_irq_init_param aducm410_ext_int_extra_init_params = {
	.int_mode = INT_FALL,
};

/* Define PWM platform specific parameters structure */
aducm410_pwm_init_param aducm410_pwm_extra_init_params = {
	.channel = PWM_CHN0,			// GPIO P1.2
	.clk_divider = DIVIDE_BY_2,		// PWM_UCLK = 160/2 = 80Mhz
	.pwm_clock_freq = 160000000,	// HCLK -> PWM (160Mhz)
	.pwm_interrupt_enable = false
};

/* Define LDACB pin platform specific parameters structure */
aducm410_gpio_init_param aducm410_ldac_gpio_extra_init_params = {
	.pin_mask = LDACB_GPIO_PIN,
	.pin_mode = NULL,
	.gpio_port = LDACB_GPIO_PORT
};

/* Define RESETB pin platform specific parameters structure */
aducm410_gpio_init_param aducm410_reset_gpio_extra_init_params = {
	.pin_mask = RESETB_GPIO_PIN,
	.pin_mode = NULL,
	.gpio_port = RESETB_GPIO_PORT
};

/* Define TGP pin platform specific parameters structure */
aducm410_gpio_init_param aducm410_tgp_gpio_extra_init_params = {
	.pin_mask = TGP_GPIO_PIN,
	.pin_mode = NULL,
	.gpio_port = TGP_GPIO_PORT
};

/* Define CONVSTB pin platform specific parameters structure */
aducm410_gpio_init_param aducm410_convst_gpio_extra_init_params = {
	.pin_mask = CONVST_GPIO_PIN,
	.pin_mode = NULL,
	.gpio_port = CONVST_GPIO_PORT
};

/* Define BUSY pin platform specific parameters structure */
aducm410_gpio_init_param aducm410_busy_gpio_extra_init_params = {
	.pin_mask = BUSY_GPIO_PIN,
	.pin_mode = NULL,
	.gpio_port = BUSY_GPIO_PORT
};

/* Define CONV_INT pin platform specific parameters structure */
aducm410_gpio_init_param aducm410_conv_int_gpio_extra_init_params = {
	.pin_mask = CONV_INT_GPIO_PIN,
	.pin_mode = NULL,
	.gpio_port = CONV_INT_GPIO_PORT
};

/******************************************************************************/
/************************** Functions Declarations ****************************/
/******************************************************************************/

/******************************************************************************/
/************************** Functions Definitions *****************************/
/******************************************************************************/

/**
 * @brief 	Initialize the UART pins
 * @return	SUCCESS in case of success, FAILURE otherwise
 */
static int32_t init_uart_gpios(void)
{
	/* UART Tx gpio descriptor */
	struct gpio_desc *tx_gpio_desc;

	/* UART Rx gpio descriptor */
	struct gpio_desc *rx_gpio_desc;

	/* Define Tx pin platform specific parameters structure */
	aducm410_gpio_init_param gpio_tx_extra_init_param = {
		.pin_mask = UART_TX_PIN,
		.pin_mode = GPIO_PULLSEL_UP,
		.gpio_port = UART_GPIO_PORT
	};

	/* Define Tx pin generic parameters structure */
	gpio_init_param gpio_tx_init_param = {
		.number = UART_TX,
		.extra = &gpio_tx_extra_init_param
	};

	/* Define Rx pin platform specific parameters structure */
	aducm410_gpio_init_param gpio_rx_extra_init_param = {
		.pin_mask = UART_RX_PIN,
		.pin_mode = GPIO_PULLSEL_UP,
		.gpio_port = UART_GPIO_PORT
	};

	/* Define Rx pin generic parameters structure */
	gpio_init_param gpio_rx_init_param = {
		.number = UART_RX,
		.extra = &gpio_rx_extra_init_param
	};

	/* Configure the Tx pin */
	if (gpio_get(&tx_gpio_desc, &gpio_tx_init_param) != SUCCESS) {
		return FAILURE;
	}

	/* Set Tx pin direction as input (controlled by UART module) */
	if (gpio_direction_input(tx_gpio_desc) != SUCCESS) {
		return FAILURE;
	}

	/* Configure the Rx pin */
	if (gpio_get(&rx_gpio_desc, &gpio_rx_init_param) != SUCCESS) {
		return FAILURE;
	}

	/* Set Rx pin direction as input (controlled by UART module) */
	if (gpio_direction_input(rx_gpio_desc) != SUCCESS) {
		return FAILURE;
	}

	return SUCCESS;
}

/**
 * @brief 	Initialize the SPI pins
 * @return	SUCCESS in case of success, FAILURE otherwise
 */
static int32_t init_spi_gpios(void)
{
	struct gpio_desc *sclk_gpio_desc;     // SPI SCLK gpio descriptor
	struct gpio_desc *miso_gpio_desc;     // SPI MISO gpio descriptor
	struct gpio_desc *mosi_gpio_desc;     // SPI MOSI gpio descriptor
	struct gpio_desc *cs_gpio_desc;       // SPI CS gpio descriptor

	/* Define SCLK pin platform specific parameters structure */
	aducm410_gpio_init_param gpio_sclk_extra_init_param = {
		.pin_mask = SPI_SCK_PIN,
		.pin_mode = NULL,
		.gpio_port = SPI_GPIO_PORT
	};

	/* Define SCLK pin generic parameters structure */
	struct gpio_init_param gpio_sclk_init_param = {
		.number = SPI_SCK,
		.extra = &gpio_sclk_extra_init_param
	};

	/* Define MISO pin platform specific parameters structure */
	aducm410_gpio_init_param gpio_miso_extra_init_param = {
		.pin_mask = SPI_HOST_SDI_PIN,
		.pin_mode = GPIO_PULLSEL_UP,
		.gpio_port = SPI_GPIO_PORT
	};

	/* Define MISO pin generic parameters structure */
	struct gpio_init_param gpio_miso_init_param = {
		.number = SPI_HOST_SDI,
		.extra = &gpio_miso_extra_init_param
	};

	/* Define MOSI pin platform specific parameters structure */
	aducm410_gpio_init_param gpio_mosi_extra_init_param = {
		.pin_mask = SPI_HOST_SDO_PIN,
		.pin_mode = NULL,
		.gpio_port = SPI_GPIO_PORT
	};

	/* Define MOSI pin generic parameters structure */
	struct gpio_init_param gpio_mosi_init_param = {
		.number = SPI_HOST_SDO,
		.extra = &gpio_mosi_extra_init_param
	};

	/* Define CS pin platform specific parameters structure */
	aducm410_gpio_init_param gpio_cs_extra_init_param = {
		.pin_mask = SPI_CSB_PIN,
		.pin_mode = NULL,
		.gpio_port = SPI_GPIO_PORT
	};

	/* Define CS pin generic parameters structure */
	struct gpio_init_param gpio_cs_init_param = {
		.number = SPI_CSB,
		.extra = &gpio_cs_extra_init_param
	};

	/* Configure the SCLK pin */
	if (gpio_get(&sclk_gpio_desc, &gpio_sclk_init_param) != SUCCESS) {
		return FAILURE;
	}

	/* Set SCLK pin direction as output */
	if (gpio_direction_output(sclk_gpio_desc, GPIO_HIGH) != SUCCESS) {
		return FAILURE;
	}

	/* Configure the MISO pin */
	if (gpio_get(&miso_gpio_desc, &gpio_miso_init_param) != SUCCESS) {
		return FAILURE;
	}

	/* Set MISO pin direction as input */
	if (gpio_direction_input(miso_gpio_desc) != SUCCESS) {
		return FAILURE;
	}

	/* Configure the MOSI pin */
	if (gpio_get(&mosi_gpio_desc, &gpio_mosi_init_param) != SUCCESS) {
		return FAILURE;
	}

	/* Set MOSI pin direction as output */
	if (gpio_direction_output(mosi_gpio_desc, GPIO_HIGH) != SUCCESS) {
		return FAILURE;
	}

	/* Configure the CS pin */
	if (gpio_get(&cs_gpio_desc, &gpio_cs_init_param) != SUCCESS) {
		return FAILURE;
	}

	/* Set CS pin direction as output */
	if (gpio_direction_output(cs_gpio_desc, GPIO_HIGH) != SUCCESS) {
		return FAILURE;
	}

	return SUCCESS;
}

/**
 * @brief 	Initialize the PWM pins
 * @return	SUCCESS in case of success, FAILURE otherwise
 */
int32_t init_pwm_gpios(void)
{
	struct gpio_desc *pwm_gpio_desc;       // PWM gpio descriptor

	/* Define PWM pin platform specific parameters structure */
	aducm410_gpio_init_param gpio_pwm_extra_init_param = {
		.pin_mask = CONV_PWM_GPIO_PIN,
		.pin_mode = NULL,
		.gpio_port = CONV_PWM_GPIO_PORT
	};

	/* Define CS pin generic parameters structure */
	struct gpio_init_param gpio_pwm_init_param = {
		.number = CONV_PWM_GPIO,
		.extra = &gpio_pwm_extra_init_param
	};

	/* Configure the PWM pin */
	if (gpio_get(&pwm_gpio_desc, &gpio_pwm_init_param) != SUCCESS) {
		return FAILURE;
	}

	/* Set PWM pin direction as output */
	if (gpio_direction_output(pwm_gpio_desc, GPIO_HIGH) != SUCCESS) {
		return FAILURE;
	}

	return SUCCESS;
}

/**
 * @brief 	Clear the ADuCM410 interrupts
 * @return	none
 */
void aducm410_clear_interrupts(void)
{
	NVIC_ClearPendingIRQ(EINT5_IRQn);

	/* Enable global interrupts */
	__enable_irq();

	EiClr(EXTINT5);
}

/**
 * @brief 	Initialize the ADuCM410 system peripherals
 * @return	SUCCESS in case of success, FAILURE otherwise
 */
int32_t aducm410_system_init(void)
{
	/* Disable global interrupts */
	__disable_irq();

	WdtGo(false);

	/* Initialize the system clock */
	ClkSetup(&gClkSetup);

	/* Init external interrupt */
	ExIntSetup(&gExIntSetup);

	/* Init the UART GPIOs */
	if (init_uart_gpios() != SUCCESS) {
		return FAILURE;
	}

	/* Init the SPI GPIOs */
	if (init_spi_gpios() != SUCCESS) {
		return FAILURE;
	}

	/* Init the PWM GPIOs */
	if (init_pwm_gpios() != SUCCESS) {
		return FAILURE;
	}

	return SUCCESS;
}
