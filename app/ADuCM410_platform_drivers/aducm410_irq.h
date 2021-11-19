/***************************************************************************//**
 *   @file     aducm410_irq_extra.h
 *   @brief:   Header containing extra types required for ADuCM410 IRQ drivers
********************************************************************************
 * Copyright (c) 2020-21 Analog Devices, Inc.
 * All rights reserved.
 *
 * This software is proprietary to Analog Devices, Inc. and its licensors.
 * By using this software you agree to the terms of the associated
 * Analog Devices Software License Agreement.
*******************************************************************************/

#ifndef IRQ_EXTRA_H
#define IRQ_EXTRA_H

/******************************************************************************/
/***************************** Include Files **********************************/
/******************************************************************************/

#include <stdint.h>

/******************************************************************************/
/********************** Macros and Constants Definitions **********************/
/******************************************************************************/

/******************************************************************************/
/*************************** Types Declarations *******************************/
/******************************************************************************/

/**
 * @enum irq_id
 * @brief Interrupts IDs supported by the irq driver
 */
enum irq_id {
	/** External interrupt ID1 (EXTINT0) */
	EXTERNAL_INT_ID1,
	/** External interrupt ID2 (EXTINT1) */
	EXTERNAL_INT_ID2,
	/** External interrupt ID3 (EXTINT2) */
	EXTERNAL_INT_ID3,
	/** External interrupt ID4 (EXTINT3)*/
	EXTERNAL_INT_ID4,
	/** External interrupt ID5 (EXTINT4)*/
	EXTERNAL_INT_ID5,
	/** External interrupt ID6 (EXTINT5) */
	EXTERNAL_INT_ID6,
	/** External interrupt ID7 (EXTINT6) */
	EXTERNAL_INT_ID7,
	/** External interrupt ID8 (EXTINT7) */
	EXTERNAL_INT_ID8,
	/** External interrupt ID9 (EXTINT8) */
	EXTERNAL_INT_ID9,
	/** External interrupt ID10 (EXTINT9) */
	EXTERNAL_INT_ID10,
	/* Number of available interrupts */
	NB_INTERRUPTS
};

/**
 * @struct aducm410_irq_init_param
 * @brief Structure holding the extra parameters for Interrupt Request.
 */
typedef struct {
	uint32_t int_mode;          // Interrupt mode (falling/rising etc)
} aducm410_irq_init_param;

/**
 * @struct aducm410_irq_desc
 * @brief Structure holding the platform descriptor for Interrupt Request.
 */
typedef struct {
	void *extra;
} aducm410_irq_desc;

#endif // IRQ_EXTRA_H_
