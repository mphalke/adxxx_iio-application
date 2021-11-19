/***************************************************************************//**
 * @file  aducm410_irq.cpp
 * @brief Implementation of Interrupt Controller ADuCM410 Platform drivers
********************************************************************************
 * Copyright (c) 2020-21 Analog Devices, Inc.
 * All rights reserved.
 *
 * This software is proprietary to Analog Devices, Inc. and its licensors.
 * By using this software you agree to the terms of the associated
 * Analog Devices Software License Agreement.
*******************************************************************************/

/******************************************************************************/
/***************************** Include Files **********************************/
/******************************************************************************/

#include <stdio.h>
#include "IntLib.h"
#include "UrtLib.h"

#include "irq.h"
#include "aducm410_irq.h"
#include "aducm410_uart.h"
#include "error.h"

/******************************************************************************/
/********************** Macros and Constants Definition ***********************/
/******************************************************************************/

#define	BIT(x)	(1 << x)

/******************************************************************************/
/*************************** Types Declarations *******************************/
/******************************************************************************/

/**
* @struct aducm410_irq_callback_desc
* @brief Structure holding the callback functions for aducm410 irqs
* @note  The callback functions are mapped with 'irq_id' structure
*/
typedef struct {
	struct callback_desc callback_ext_int_id1;
	struct callback_desc callback_ext_int_id2;
	struct callback_desc callback_ext_int_id3;
	struct callback_desc callback_ext_int_id4;
	struct callback_desc callback_ext_int_id5;
	struct callback_desc callback_ext_int_id6;
	struct callback_desc callback_ext_int_id7;
	struct callback_desc callback_ext_int_id8;
	struct callback_desc callback_ext_int_id9;
} aducm410_irq_callback_desc;

/* ADuCM410 callback function pointer typedef */
typedef void(*aducm410_callback_func)(void);

/* ADuCM410 irq callback structure variable */
static aducm410_irq_callback_desc aducm410_irq_callbacks;

/******************************************************************************/
/************************ Functions Declarations ******************************/
/******************************************************************************/

/******************************************************************************/
/************************ Functions Definitions *******************************/
/******************************************************************************/

/**
 * @brief	ADuCM410 callback function for external interrupt ID1 event (EXTINT0)
 * @return	none
 */
void Ext_Int0_Handler(void)
{
	/* Clear interrupt flag */
	pADI_ALLON->EICLR |= BIT(0);

	if (aducm410_irq_callbacks.callback_ext_int_id1.callback) {
		aducm410_irq_callbacks.callback_ext_int_id1.callback(
			aducm410_irq_callbacks.callback_ext_int_id1.ctx, EXTERNAL_INT_ID1, NULL);
	}
}

/**
 * @brief	ADuCM410 callback function for external interrupt ID2 event (EXTINT1)
 * @return	none
 */
void Ext_Int1_Handler(void)
{
	/* Clear interrupt flag */
	pADI_ALLON->EICLR |= BIT(1);

	if (aducm410_irq_callbacks.callback_ext_int_id2.callback) {
		aducm410_irq_callbacks.callback_ext_int_id2.callback(
			aducm410_irq_callbacks.callback_ext_int_id2.ctx, EXTERNAL_INT_ID2, NULL);
	}
}

/**
 * @brief	ADuCM410 callback function for external interrupt ID3 event (EXTINT2)
 * @return	none
 */
void Ext_Int2_Handler(void)
{
	/* Clear interrupt flag */
	pADI_ALLON->EICLR |= BIT(2);

	if (aducm410_irq_callbacks.callback_ext_int_id3.callback) {
		aducm410_irq_callbacks.callback_ext_int_id3.callback(
			aducm410_irq_callbacks.callback_ext_int_id3.ctx, EXTERNAL_INT_ID3, NULL);
	}
}

/**
 * @brief	ADuCM410 callback function for external interrupt ID4 event (EXTINT3)
 * @return	none
 */
void Ext_Int3_Handler(void)
{
	/* Clear interrupt flag */
	pADI_ALLON->EICLR |= BIT(3);

	if (aducm410_irq_callbacks.callback_ext_int_id4.callback) {
		aducm410_irq_callbacks.callback_ext_int_id4.callback(
			aducm410_irq_callbacks.callback_ext_int_id4.ctx, EXTERNAL_INT_ID4, NULL);
	}
}

/**
 * @brief	ADuCM410 callback function for external interrupt ID5 event (EXTINT4)
 * @return	none
 */
void Ext_Int4_Handler(void)
{
	/* Clear interrupt flag */
	pADI_ALLON->EICLR |= BIT(4);

	if (aducm410_irq_callbacks.callback_ext_int_id5.callback) {
		aducm410_irq_callbacks.callback_ext_int_id5.callback(
			aducm410_irq_callbacks.callback_ext_int_id5.ctx, EXTERNAL_INT_ID5, NULL);
	}
}

/**
 * @brief	ADuCM410 callback function for external interrupt ID6 event (EXTINT5)
 * @return	none
 */
void Ext_Int5_Handler(void)
{
	/* Clear interrupt flag */
	pADI_ALLON->EICLR |= BIT(5);

	if (aducm410_irq_callbacks.callback_ext_int_id6.callback) {
		aducm410_irq_callbacks.callback_ext_int_id6.callback(
			aducm410_irq_callbacks.callback_ext_int_id6.ctx, EXTERNAL_INT_ID6, NULL);
	}
}

/**
 * @brief	ADuCM410 callback function for external interrupt ID7 event (EXTINT6)
 * @return	none
 */
void Ext_Int6_Handler(void)
{
	/* Clear interrupt flag */
	pADI_ALLON->EICLR |= BIT(6);

	if (aducm410_irq_callbacks.callback_ext_int_id7.callback) {
		aducm410_irq_callbacks.callback_ext_int_id7.callback(
			aducm410_irq_callbacks.callback_ext_int_id7.ctx, EXTERNAL_INT_ID7, NULL);
	}
}

/**
 * @brief	ADuCM410 callback function for external interrupt ID8 event (EXTINT7)
 * @return	none
 */
void Ext_Int7_Handler(void)
{
	/* Clear interrupt flag */
	pADI_ALLON->EICLR |= BIT(7);

	if (aducm410_irq_callbacks.callback_ext_int_id8.callback) {
		aducm410_irq_callbacks.callback_ext_int_id8.callback(
			aducm410_irq_callbacks.callback_ext_int_id8.ctx, EXTERNAL_INT_ID8, NULL);
	}
}

/**
 * @brief	ADuCM410 callback function for external interrupt ID9 event (EXTINT8)
 * @return	none
 */
void Ext_Int8_Handler(void)
{
	/* Clear interrupt flag */
	pADI_ALLON->EICLR |= BIT(8);

	if (aducm410_irq_callbacks.callback_ext_int_id9.callback) {
		aducm410_irq_callbacks.callback_ext_int_id9.callback(
			aducm410_irq_callbacks.callback_ext_int_id9.ctx, EXTERNAL_INT_ID9, NULL);
	}
}

/**
 * @brief	Initialized the controller for the peripheral interrupts
 * @param	desc[in, out] - Pointer where the configured instance is stored
 * @param	param[in] - Configuration information for the instance
 * @return	SUCCESS in case of success, FAILURE otherwise.
 */
int32_t irq_ctrl_init(struct irq_ctrl_desc **desc,
		      const struct irq_init_param *param)
{
	uint32_t ext_int_mode;

	if (!desc || !param) {
		return FAILURE;
	}

	/* Create a new descriptor for generic parameters */
	struct irq_ctrl_desc *new_desc = (struct irq_ctrl_desc *)calloc(1,
					 sizeof(struct irq_ctrl_desc));
	if (!new_desc) {
		return FAILURE;
	}

	new_desc->irq_ctrl_id = param->irq_ctrl_id;
	ext_int_mode = ((aducm410_irq_init_param *)(param->extra))->int_mode;

	/* Create a new descriptor for platform specific parameters */
	aducm410_irq_desc *aducm410_new_desc = (aducm410_irq_desc *)calloc(1,
					       sizeof(aducm410_irq_desc));

	new_desc->extra = (aducm410_irq_desc *)aducm410_new_desc;

	switch (new_desc->irq_ctrl_id) {
	case EXTERNAL_INT_ID1:
		EiCfg(EXTINT0, INT_EN, ext_int_mode);
		break;

	case EXTERNAL_INT_ID2:
		EiCfg(EXTINT1, INT_EN, ext_int_mode);
		break;

	case EXTERNAL_INT_ID3:
		EiCfg(EXTINT2, INT_EN, ext_int_mode);
		break;

	case EXTERNAL_INT_ID4:
		EiCfg(EXTINT3, INT_EN, ext_int_mode);
		break;

	case EXTERNAL_INT_ID5:
		EiCfg(EXTINT4, INT_EN, ext_int_mode);
		break;

	case EXTERNAL_INT_ID6:
		EiCfg(EXTINT5, INT_EN, ext_int_mode);
		break;

	case EXTERNAL_INT_ID7:
		EiCfg(EXTINT6, INT_EN, ext_int_mode);
		break;

	case EXTERNAL_INT_ID8:
		EiCfg(EXTINT7, INT_EN, ext_int_mode);
		break;

	case EXTERNAL_INT_ID9:
		EiCfg(EXTINT8, INT_EN, ext_int_mode);
		break;

	default:
		return FAILURE;
	}

	*desc = new_desc;

	return SUCCESS;
}

/**
 * @brief	Free the resources allocated by irq_ctrl_init()
 * @param	desc[in, out] - Interrupt controller descriptor.
 * @return	SUCCESS in case of success, FAILURE otherwise.
 */
int32_t irq_ctrl_remove(struct irq_ctrl_desc *desc)
{
	if (!desc) {
		return FAILURE;
	}

	if ((aducm410_irq_desc *)desc->extra) {
		free((aducm410_irq_desc *)desc->extra);
	}

	free(desc);

	return SUCCESS;
}


/**
 * @brief	Enable interrupt
 * @param	desc[in, out] - Interrupt controller descriptor.
 * @param	irq_id[in] - Interrupt request ID
 * @return	SUCCESS in case of success, FAILURE otherwise.
 */
int32_t irq_enable(struct irq_ctrl_desc *desc, uint32_t irq_id)
{
	if (!desc) {
		return FAILURE;
	}

	switch (desc->irq_ctrl_id) {
	case EXTERNAL_INT_ID1:
		NVIC_EnableIRQ(EINT0_IRQn);
		break;

	case EXTERNAL_INT_ID2:
		NVIC_EnableIRQ(EINT1_IRQn);
		break;

	case EXTERNAL_INT_ID3:
		NVIC_EnableIRQ(EINT2_IRQn);
		break;

	case EXTERNAL_INT_ID4:
		NVIC_EnableIRQ(EINT3_IRQn);
		break;

	case EXTERNAL_INT_ID5:
		NVIC_EnableIRQ(EINT4_IRQn);
		break;

	case EXTERNAL_INT_ID6:
		NVIC_EnableIRQ(EINT5_IRQn);
		break;

	case EXTERNAL_INT_ID7:
		NVIC_EnableIRQ(EINT6_IRQn);
		break;

	case EXTERNAL_INT_ID8:
		NVIC_EnableIRQ(EINT7_IRQn);
		break;

	case EXTERNAL_INT_ID9:
		NVIC_EnableIRQ(EINT8_IRQn);
		break;

	default:
		return FAILURE;
	}

	return SUCCESS;
}

/**
 * @brief	Disable interrupt
 * @param	desc[in, out] - Interrupt controller descriptor.
 * @param	irq_id[in] - Interrupt request ID
 * @return	SUCCESS in case of success, FAILURE otherwise.
 */
int32_t irq_disable(struct irq_ctrl_desc *desc, uint32_t irq_id)
{
	if (!desc) {
		return FAILURE;
	}

	switch (desc->irq_ctrl_id) {
	case EXTERNAL_INT_ID1:
		NVIC_DisableIRQ(EINT0_IRQn);
		break;

	case EXTERNAL_INT_ID2:
		NVIC_DisableIRQ(EINT1_IRQn);
		break;

	case EXTERNAL_INT_ID3:
		NVIC_DisableIRQ(EINT2_IRQn);
		break;

	case EXTERNAL_INT_ID4:
		NVIC_DisableIRQ(EINT3_IRQn);
		break;

	case EXTERNAL_INT_ID5:
		NVIC_DisableIRQ(EINT4_IRQn);
		break;

	case EXTERNAL_INT_ID6:
		NVIC_DisableIRQ(EINT5_IRQn);
		break;

	case EXTERNAL_INT_ID7:
		NVIC_DisableIRQ(EINT6_IRQn);
		break;

	case EXTERNAL_INT_ID8:
		NVIC_DisableIRQ(EINT7_IRQn);
		break;

	case EXTERNAL_INT_ID9:
		NVIC_DisableIRQ(EINT8_IRQn);
		break;

	default:
		return FAILURE;
	}

	return SUCCESS;
}

/**
 * @brief	Registers a IRQ callback function to irq controller.
 * @param	desc[in] - The IRQ controller descriptor.
 * @param	irq_id[in] - Interrupt identifier.
 * @param	callback_desc - Descriptor of the callback. If it is NULL, the
 *			callback will be unregistered
 * @return	SUCCESS in case of success, FAILURE otherwise.
 */
int32_t irq_register_callback(struct irq_ctrl_desc *desc,
			      uint32_t irq_id,
			      struct callback_desc *callback_desc)
{
	if (!desc || !callback_desc) {
		return FAILURE;
	}

	switch (irq_id) {
	case EXTERNAL_INT_ID1:
		aducm410_irq_callbacks.callback_ext_int_id1.callback = callback_desc->callback;
		aducm410_irq_callbacks.callback_ext_int_id1.ctx = callback_desc->ctx;
		break;

	case EXTERNAL_INT_ID2:
		aducm410_irq_callbacks.callback_ext_int_id2.callback = callback_desc->callback;
		aducm410_irq_callbacks.callback_ext_int_id2.ctx = callback_desc->ctx;
		break;

	case EXTERNAL_INT_ID3:
		aducm410_irq_callbacks.callback_ext_int_id3.callback = callback_desc->callback;
		aducm410_irq_callbacks.callback_ext_int_id3.ctx = callback_desc->ctx;
		break;

	case EXTERNAL_INT_ID4:
		aducm410_irq_callbacks.callback_ext_int_id4.callback = callback_desc->callback;
		aducm410_irq_callbacks.callback_ext_int_id4.ctx = callback_desc->ctx;
		break;

	case EXTERNAL_INT_ID5:
		aducm410_irq_callbacks.callback_ext_int_id5.callback = callback_desc->callback;
		aducm410_irq_callbacks.callback_ext_int_id5.ctx = callback_desc->ctx;
		break;

	case EXTERNAL_INT_ID6:
		aducm410_irq_callbacks.callback_ext_int_id6.callback = callback_desc->callback;
		aducm410_irq_callbacks.callback_ext_int_id6.ctx = callback_desc->ctx;
		break;

	case EXTERNAL_INT_ID7:
		aducm410_irq_callbacks.callback_ext_int_id7.callback = callback_desc->callback;
		aducm410_irq_callbacks.callback_ext_int_id7.ctx = callback_desc->ctx;
		break;

	case EXTERNAL_INT_ID8:
		aducm410_irq_callbacks.callback_ext_int_id8.callback = callback_desc->callback;
		aducm410_irq_callbacks.callback_ext_int_id8.ctx = callback_desc->ctx;
		break;

	case EXTERNAL_INT_ID9:
		aducm410_irq_callbacks.callback_ext_int_id9.callback = callback_desc->callback;
		aducm410_irq_callbacks.callback_ext_int_id9.ctx = callback_desc->ctx;
		break;

	default:
		return FAILURE;
	}

	return SUCCESS;
}

/**
 * @brief	Unregister a IRQ callback function.
 * @param	desc[in] - The IRQ controller descriptor.
 * @param	irq_id[in] - Interrupt identifier.
 * @return	SUCCESS in case of success, FAILURE otherwise.
 */
int32_t irq_unregister(struct irq_ctrl_desc *desc, uint32_t irq_id)
{
	if (!desc) {
		return FAILURE;
	}

	switch (irq_id) {
	case  EXTERNAL_INT_ID1:
		aducm410_irq_callbacks.callback_ext_int_id1.callback = NULL;
		break;

	case EXTERNAL_INT_ID2:
		aducm410_irq_callbacks.callback_ext_int_id2.callback = NULL;
		break;

	case EXTERNAL_INT_ID3:
		aducm410_irq_callbacks.callback_ext_int_id3.callback = NULL;
		break;

	case EXTERNAL_INT_ID4:
		aducm410_irq_callbacks.callback_ext_int_id4.callback = NULL;
		break;

	case EXTERNAL_INT_ID5:
		aducm410_irq_callbacks.callback_ext_int_id5.callback = NULL;
		break;

	case EXTERNAL_INT_ID6:
		aducm410_irq_callbacks.callback_ext_int_id6.callback = NULL;
		break;

	case EXTERNAL_INT_ID7:
		aducm410_irq_callbacks.callback_ext_int_id7.callback = NULL;
		break;

	case EXTERNAL_INT_ID8:
		aducm410_irq_callbacks.callback_ext_int_id8.callback = NULL;
		break;

	case EXTERNAL_INT_ID9:
		aducm410_irq_callbacks.callback_ext_int_id9.callback = NULL;
		break;

	default:
		return FAILURE;
	}

	return SUCCESS;
}
