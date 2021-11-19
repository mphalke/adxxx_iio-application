/***************************************************************************//**
 *   @file    ad70081z_iio.c
 *   @brief   Implementation of AD70081z IIO application interfaces
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

#include <stdint.h>
#include <stdio.h>
#include <errno.h>

#include "ad70081z_iio.h"
#include "ad70081z.h"
#include "ad70081z_user_config.h"
#include "ad70081z_regs.h"
#include "app_config.h"
#include "ad70081z_data_capture.h"
#include "error.h"
#include "util.h"

/******************************************************************************/
/********************* Macros and Constants Definition ************************/
/******************************************************************************/

/******** Forward declaration of getter/setter functions ********/
static ssize_t iio_ad70081z_attr_get(void *device, char *buf, size_t len,
				     const struct iio_ch_info *channel, intptr_t priv);

static ssize_t iio_ad70081z_attr_set(void *device, char *buf, size_t len,
				     const struct iio_ch_info *channel, intptr_t priv);

static ssize_t iio_ad70081z_attr_available_get(void *device, char *buf,
		size_t len,
		const struct iio_ch_info *channel, intptr_t priv);

static ssize_t iio_ad70081z_attr_available_set(void *device, char *buf,
		size_t len,
		const struct iio_ch_info *channel, intptr_t priv);

#define STR(x) #x
#define XSTR(x) STR(x)

#define AD70081Z_CHN_ATTR(_name, _priv) {\
	.name = _name,\
	.priv = _priv,\
	.show = iio_ad70081z_attr_get,\
	.store = iio_ad70081z_attr_set\
}

#define AD70081Z_CHN_AVAIL_ATTR(_name, _priv) {\
	.name = _name,\
	.priv = _priv,\
	.show = iio_ad70081z_attr_available_get,\
	.store = iio_ad70081z_attr_available_set\
}

#define AD70081Z_DAC_CH(_name, _idx) {\
	.name = _name # _idx, \
	.ch_type = IIO_VOLTAGE,\
	.ch_out = 1,\
	.indexed = true,\
	.channel = _idx,\
	.scan_index = _idx,\
	.scan_type = NULL,\
	.attributes = iio_ad700081z_dac_ch_attributes\
}

#define AD70081Z_VADC_CH(_idx) {\
	.name = "vadc_" # _idx, \
	.ch_type = IIO_VOLTAGE,\
	.ch_out = 0,\
	.indexed = true,\
	.channel = _idx,\
	.scan_index = _idx,\
	.scan_type = &ad70081z_adc_scan_type,\
	.attributes = iio_ad700081z_vadc_ch_attributes\
}

#define AD70081Z_IADC_CH(_idx) {\
	.name = "iadc_" # _idx, \
	.ch_type = IIO_VOLTAGE,\
	.ch_out = 0,\
	.indexed = true,\
	.channel = _idx,\
	.scan_index = _idx,\
	.scan_type = &ad70081z_adc_scan_type,\
	.attributes = iio_ad700081z_iadc_ch_attributes\
}

#define		BYTE_SIZE		(uint32_t)8
#define		BYTE_MASK		(uint32_t)0xff

#define REFERENCE_VOLTAGE	2.5

#define IDAC_MAX_DATA_COUNT		(1 << 10)
#define VDAC16_MAX_DATA_COUNT	(1 << 16)
#define VDAC12_MAX_DATA_COUNT	(1 << 12)
#define ADC_MAX_DATA_COUNT		(1 << 16)

#define ADC_CHN_COUNT		23

/* ADC Raw to Voltage conversion default scale factor for IIO client */
#define ADC_DEFAULT_SCALE		((REFERENCE_VOLTAGE / ADC_MAX_DATA_COUNT) * 1000)

/* Scale attribute value per channel */
static float attr_scale_val[ADC_CHN_COUNT] = {
	ADC_DEFAULT_SCALE, ADC_DEFAULT_SCALE, ADC_DEFAULT_SCALE, ADC_DEFAULT_SCALE,
	ADC_DEFAULT_SCALE, ADC_DEFAULT_SCALE, ADC_DEFAULT_SCALE, ADC_DEFAULT_SCALE,
	ADC_DEFAULT_SCALE, ADC_DEFAULT_SCALE, ADC_DEFAULT_SCALE, ADC_DEFAULT_SCALE,
	ADC_DEFAULT_SCALE, ADC_DEFAULT_SCALE, ADC_DEFAULT_SCALE, ADC_DEFAULT_SCALE,
	ADC_DEFAULT_SCALE, ADC_DEFAULT_SCALE, ADC_DEFAULT_SCALE, ADC_DEFAULT_SCALE,
	ADC_DEFAULT_SCALE, ADC_DEFAULT_SCALE, ADC_DEFAULT_SCALE
};

/* Bytes per sample. This count should divide the total 256 bytes into 'n' equivalent
 * ADC samples as IIO library requests only 256bytes of data at a time in a given
 * data read query.
 * For 1 to 8-bit ADC, bytes per sample = 1 (2^0)
 * For 9 to 16-bit ADC, bytes per sample = 2 (2^1)
 * For 17 to 32-bit ADC, bytes per sample = 4 (2^2)
 **/
#define	BYTES_PER_SAMPLE	sizeof(uint16_t)	// For ADC resolution of 16-bits

/* Number of data storage bits (needed for IIO client to plot ADC data) */
#define CHN_STORAGE_BITS	(BYTES_PER_SAMPLE * 8)

/******************************************************************************/
/******************** Variables and User Defined Data Types *******************/
/******************************************************************************/

/* IIO interface descriptor */
static struct iio_desc *p_ad70081z_iio_desc;

/* IIO Device name */
static const char dev_name[] = IIO_DEVICE_NAME;

/* Pointer to the struct representing the IIO device */
struct ad70081z_dev *p_ad70081z_dev_inst = NULL;

/* AD70081z device types */
enum ad70081z_dev_type {
	AD70081Z_ADC,
	AD70081Z_DAC
};

/* AD70081z device names */
static const char *ad70081z_dev_name[] = {
	"ad70081z_adc",
	"ad70081z_dac"
};

/* AD70081z attribute unique IDs */
enum ad70081z_attribute_ids {
	DAC_DATA,
	DAC_VOLTAGE,

	DAC_INPUTA_DATA,
	DAC_INPUTB_DATA,

	DAC_TOGGLE_MODE,
	DAC_TOGGLE_ENABLE,
	DAC_SW_TOGGLE_CNTRL,
	DAC_HW_TOGGLE_CNTRL,

	DAC_HW_LDAC_CNTRL,
	DAC_SW_LDAC_CNTRL,
	DAC_SW_LDAC_MASK,
	DAC_HW_LDAC_MASK,

	DAC_COMPARE_ENABLE,
	DAC_COMPARE_MASK,

	IDAC_SHUTDOWN_ENABLE,
	REFERENCE_SOURCE,

	ADC_RAW,
	ADC_SCALE,
	ADC_OFFSET,
	ADC_SAMPLING_FREQUENCY,

	IADC_INPUT_CURRENT_RANGE,
	IADC_INPUT_CURRENT,
	IADC_RSENSE,
};

/* ADC channel scan structure */
static struct scan_type ad70081z_adc_scan_type = {
	.realbits = 16,
	.storagebits = 16,
	.shift = 0,
	.sign = 'u',
	.is_big_endian = false
};

/* DAC channel attributes structure */
static struct iio_attribute iio_ad700081z_dac_ch_attributes[] = {
	/* DAC data, voltage and current attributes */
	AD70081Z_CHN_ATTR("dac_data", DAC_DATA),
	AD70081Z_CHN_ATTR("voltage", DAC_VOLTAGE),

	/* DAC Input data attributes */
	AD70081Z_CHN_ATTR("inputA_data", DAC_INPUTA_DATA),
	AD70081Z_CHN_ATTR("inputB_data", DAC_INPUTB_DATA),

	/* DAC Toggle channel attributes */
	AD70081Z_CHN_ATTR("toggle_mode", DAC_TOGGLE_MODE),
	AD70081Z_CHN_ATTR("toggle_enable", DAC_TOGGLE_ENABLE),
	AD70081Z_CHN_ATTR("toggle_sw_cntrl", DAC_SW_TOGGLE_CNTRL),
	AD70081Z_CHN_AVAIL_ATTR("toggle_mode_available", DAC_TOGGLE_MODE),
	AD70081Z_CHN_AVAIL_ATTR("toggle_enable_available", DAC_TOGGLE_ENABLE),

	/* DAC LDAC channel attributes */
	AD70081Z_CHN_ATTR("ldac_sw_cntrl", DAC_SW_LDAC_CNTRL),
	AD70081Z_CHN_ATTR("ldac_sw_mask", DAC_SW_LDAC_MASK),
	AD70081Z_CHN_ATTR("ldac_hw_mask", DAC_HW_LDAC_MASK),

	/* DAC Compare channel attributes */
	AD70081Z_CHN_ATTR("compare_mask", DAC_COMPARE_MASK),

	/* IDAC channel enable channel attributes */
	AD70081Z_CHN_ATTR("shutdown_enable", IDAC_SHUTDOWN_ENABLE),

	END_ATTRIBUTES_ARRAY,
};

/* VADC channel attributes structure */
static struct iio_attribute iio_ad700081z_vadc_ch_attributes[] = {
	AD70081Z_CHN_ATTR("raw", ADC_RAW),
	AD70081Z_CHN_ATTR("scale", ADC_SCALE),
	AD70081Z_CHN_ATTR("offset", ADC_OFFSET),
	END_ATTRIBUTES_ARRAY,
};

/* IADC channel attributes structure */
static struct iio_attribute iio_ad700081z_iadc_ch_attributes[] = {
	AD70081Z_CHN_ATTR("raw", ADC_RAW),
	AD70081Z_CHN_ATTR("scale", ADC_SCALE),
	AD70081Z_CHN_ATTR("offset", ADC_OFFSET),

	AD70081Z_CHN_ATTR("input_current_range", IADC_INPUT_CURRENT_RANGE),
	AD70081Z_CHN_AVAIL_ATTR("input_current_range_available", IADC_INPUT_CURRENT_RANGE),
	AD70081Z_CHN_ATTR("input_current", IADC_INPUT_CURRENT),
	AD70081Z_CHN_ATTR("rsense", IADC_RSENSE),

	END_ATTRIBUTES_ARRAY,
};

/* DAC device (global) attributes list */
static struct iio_attribute dac_global_attributes[] = {
	AD70081Z_CHN_ATTR("toggle_hw_cntrl(tgp)", DAC_HW_TOGGLE_CNTRL),
	AD70081Z_CHN_ATTR("ldac_hw_cntrl(ldacb)", DAC_HW_LDAC_CNTRL),
	AD70081Z_CHN_ATTR("compare_enable", DAC_COMPARE_ENABLE),
	AD70081Z_CHN_AVAIL_ATTR("compare_enable_available", DAC_COMPARE_ENABLE),
	AD70081Z_CHN_ATTR("reference_source", REFERENCE_SOURCE),
	AD70081Z_CHN_AVAIL_ATTR("reference_source_available", REFERENCE_SOURCE),
	END_ATTRIBUTES_ARRAY,
};

/* ADC device (global) attributes list */
static struct iio_attribute adc_global_attributes[] = {
	AD70081Z_CHN_ATTR("reference_source", REFERENCE_SOURCE),
	AD70081Z_CHN_AVAIL_ATTR("reference_source_available", REFERENCE_SOURCE),
	AD70081Z_CHN_ATTR("sampling_frequency", ADC_SAMPLING_FREQUENCY),
	END_ATTRIBUTES_ARRAY,
};

/* IIOD debug attributes list */
static struct iio_attribute debug_attributes[] = {
	END_ATTRIBUTES_ARRAY
};

struct iio_data_buffer adc_data_buff = {
	.size = DATA_BUFFER_SIZE,
	.buff = adc_data_buffer
};

/******************************************************************************/
/************************** Functions Declarations ****************************/
/******************************************************************************/

/******************************************************************************/
/************************ Functions Definitions *******************************/
/******************************************************************************/

/*!
 * @brief	Attribute available getter function for DAC attributes
 * @param	device[in]- Pointer to IIO device instance
 * @param	buf[in]- IIO input data buffer
 * @param	len[in]- Number of input bytes
 * @param	channel[in] - DAC input channel
 * @param	priv[in] - Attribute private ID
 * @return	len in case of SUCCESS, negative error code otherwise
 */
static ssize_t iio_ad70081z_attr_available_get(void *device, char *buf,
		size_t len,
		const struct iio_ch_info *channel, intptr_t priv)
{
	switch (priv) {
	case DAC_TOGGLE_MODE:
		return sprintf(buf, "%s", "Software Hardware");

	case DAC_TOGGLE_ENABLE:
	case DAC_COMPARE_ENABLE:
		return sprintf(buf, "%s", "Disable Enable");

	case IADC_INPUT_CURRENT_RANGE:
		return sprintf(buf, "%s", "6.25-50uA 1.25-10uA 5-40uA NA");

	case REFERENCE_SOURCE:
		return sprintf(buf, "%s", "External Internal");

	default:
		break;
	}

	return len;
}

/*!
 * @brief	Attribute available setter function for DAC attributes
 * @param	device[in]- Pointer to IIO device instance
 * @param	buf[in]- IIO input data buffer
 * @param	len[in]- Number of input bytes
 * @param	channel[in] - DAC input channel
 * @param	priv[in] - Attribute private ID
 * @return	len in case of SUCCESS, negative error code otherwise
 */
static ssize_t iio_ad70081z_attr_available_set(void *device, char *buf,
		size_t len,
		const struct iio_ch_info *channel, intptr_t priv)
{
	return len;
}

/*!
 * @brief	Getter function for DAC attributes
 * @param	device[in]- Pointer to IIO device instance
 * @param	chn[in] - DAC input channel
 * @param	base_reg[in]- Base register address
 * @param	val[in, out]- Register value
 * @param	mask[in, out] - Multibyte register mask
 * @return	0 in case of SUCCESS, negative error code otherwise
 */
static int32_t get_dac_multibyte_reg_and_mask(void *device, uint8_t chn,
		uint32_t base_reg,
		uint32_t *val, uint8_t *mask)
{
	uint32_t dac_reg;

	if (!val || !mask)
		return -EINVAL;

	dac_reg = base_reg + (chn / BYTE_SIZE);
	*mask = (chn % BYTE_SIZE);

	return ad70081z_spi_reg_read(device, dac_reg, val);
}

/*!
 * @brief	Getter function for DAC attributes
 * @param	device[in]- Pointer to IIO device instance
 * @param	buf[in]- IIO input data buffer
 * @param	len[in]- Number of input bytes
 * @param	channel[in] - DAC input channel
 * @param	priv[in] - Attribute private ID
 * @return	len in case of SUCCESS, negative error code otherwise
 */
static ssize_t iio_ad70081z_attr_get(void *device, char *buf, size_t len,
				     const struct iio_ch_info *channel, intptr_t priv)
{
	uint32_t val;
	int32_t	 ret;
	uint8_t dac_chn_msk;
	float voltage;
	float iadc_input_current;
	enum ad70081z_iadc_range range;

	val = srt_to_uint32(buf);

	switch (priv) {
	/****************** DAC Direct and InputA/B Data getters ******************/
	case DAC_DATA:
		ret = ad70081z_spi_reg_read(device, AD70081Z_DAC(channel->ch_num), &val);
		if (IS_ERR_VALUE(ret))
			return ret;

		return snprintf(buf, len, "%d", val);

	case DAC_INPUTA_DATA:
		ret = ad70081z_spi_reg_read(device, AD70081Z_INPUT_A(channel->ch_num), &val);
		if (IS_ERR_VALUE(ret))
			return ret;

		return snprintf(buf, len, "%d", val);

	case DAC_INPUTB_DATA:
		ret = ad70081z_spi_reg_read(device, AD70081Z_INPUT_B(channel->ch_num), &val);
		if (IS_ERR_VALUE(ret))
			return ret;

		return snprintf(buf, len, "%d", val);

	case DAC_VOLTAGE:
		ret = ad70081z_spi_reg_read(device, AD70081Z_DAC(channel->ch_num), &val);
		if (IS_ERR_VALUE(ret))
			return ret;

		if (channel->ch_num < AD70081Z_IDAC_CH_LIMIT) {
			voltage = (val * REFERENCE_VOLTAGE) / IDAC_MAX_DATA_COUNT;
		} else {
			if ((channel->ch_num == AD70081Z_E8_MZDB)
			    || (channel->ch_num == AD70081Z_E0_TECC)) {
				voltage = (val * REFERENCE_VOLTAGE) / VDAC12_MAX_DATA_COUNT;
			} else {
				voltage = (val * REFERENCE_VOLTAGE) / VDAC16_MAX_DATA_COUNT;
			}
		}

		return snprintf(buf, len, "%.4f", voltage);

	/****************** DAC Toggle SW/HW getters ******************/
	case DAC_TOGGLE_ENABLE:
		ret = get_dac_multibyte_reg_and_mask(device,
						     (enum ad70081z_channel)channel->ch_num,
						     AD70081Z_TOGGLE_ENABLE0, &val,
						     &dac_chn_msk);
		if (IS_ERR_VALUE(ret))
			return ret;

		if ((val >> dac_chn_msk) & 0x1) {
			return snprintf(buf, len, "%s", "Enable");
		} else {
			return snprintf(buf, len, "%s", "Disable");
		}

	case DAC_TOGGLE_MODE:
		ret = get_dac_multibyte_reg_and_mask(device,
						     (enum ad70081z_channel)channel->ch_num,
						     AD70081Z_TOGGLE_MODE0, &val,
						     &dac_chn_msk);
		if (IS_ERR_VALUE(ret))
			return ret;

		if ((val >> dac_chn_msk) & 0x1) {
			return snprintf(buf, len, "%s", "Software");
		} else {
			return snprintf(buf, len, "%s", "Hardware");
		}

	case DAC_SW_TOGGLE_CNTRL:
		ret = get_dac_multibyte_reg_and_mask(device,
						     (enum ad70081z_channel)channel->ch_num,
						     AD70081Z_TOGGLE_CONTROL0, &val,
						     &dac_chn_msk);
		if (IS_ERR_VALUE(ret))
			return ret;

		if ((val >> dac_chn_msk) & 0x1) {
			return snprintf(buf, len, "%d", 1);
		} else {
			return snprintf(buf, len, "%d", 0);
		}

	case DAC_HW_TOGGLE_CNTRL:
		if (p_ad70081z_dev_inst->gpio_tgp_state) {
			return snprintf(buf, len, "%d", 1);
		} else {
			return snprintf(buf, len, "%d", 0);
		}

	/****************** DAC LDAC SW/HW getters ******************/
	case DAC_HW_LDAC_CNTRL:
		return snprintf(buf, len, "%d", 1);

	case DAC_SW_LDAC_CNTRL:
		return snprintf(buf, len, "%d", 0);

	case DAC_SW_LDAC_MASK:
		ret = get_dac_multibyte_reg_and_mask(device,
						     (enum ad70081z_channel)channel->ch_num,
						     AD70081Z_SW_LDAC0_MASK, &val,
						     &dac_chn_msk);
		if (IS_ERR_VALUE(ret))
			return ret;

		if ((val >> dac_chn_msk) & 0x1) {
			return snprintf(buf, len, "%d", 1);
		} else {
			return snprintf(buf, len, "%d", 0);
		}

	case DAC_HW_LDAC_MASK:
		ret = get_dac_multibyte_reg_and_mask(device,
						     (enum ad70081z_channel)channel->ch_num,
						     AD70081Z_HW_LDAC_MASK0, &val,
						     &dac_chn_msk);
		if (IS_ERR_VALUE(ret))
			return ret;

		if ((val >> dac_chn_msk) & 0x1) {
			return snprintf(buf, len, "%d", 1);
		} else {
			return snprintf(buf, len, "%d", 0);
		}

	/****************** DAC Compare getters ******************/
	case DAC_COMPARE_ENABLE:
		ret = ad70081z_spi_reg_read(device, AD70081Z_CMP_EN, &val);
		if (IS_ERR_VALUE(ret))
			return ret;

		if (val & 0x1) {
			return snprintf(buf, len, "%s", "Enable");
		} else {
			return snprintf(buf, len, "%s", "Disable");
		}

	case DAC_COMPARE_MASK:
		ret = get_dac_multibyte_reg_and_mask(device,
						     (enum ad70081z_channel)channel->ch_num,
						     AD70081Z_CMP_MASK0, &val,
						     &dac_chn_msk);
		if (IS_ERR_VALUE(ret))
			return ret;

		if ((val >> dac_chn_msk) & 0x1) {
			return snprintf(buf, len, "%d", 1);
		} else {
			return snprintf(buf, len, "%d", 0);
		}

	/****************** IDAC getters ******************/
	case IDAC_SHUTDOWN_ENABLE:
		if ((enum ad70081z_channel)channel->ch_num >= AD70081Z_IDAC_CH_LIMIT)
			return snprintf(buf, len, "%s", "NA");

		ret = ad70081z_spi_reg_read(device, AD70081Z_IDAC_OUT_SHDN, &val);
		if (IS_ERR_VALUE(ret))
			return ret;

		if ((val >> channel->ch_num) & 0x1) {
			return snprintf(buf, len, "%d", 1);
		} else {
			return snprintf(buf, len, "%d", 0);
		}

	/****************** ADC channel getters ******************/
	case ADC_RAW:
		ret = read_single_sample((uint8_t)channel->ch_num, &val);
		if (IS_ERR_VALUE(ret))
			return ret;

		return snprintf(buf, len, "%u", (uint16_t)val);

	case ADC_SCALE:
		return sprintf(buf, "%f", attr_scale_val[channel->ch_num]);

	case ADC_OFFSET:
		return snprintf(buf, len, "%d", 0);

	case ADC_SAMPLING_FREQUENCY:
		return snprintf(buf, len, "%d", SAMPLING_RATE);

	case IADC_INPUT_CURRENT_RANGE:
		if (channel->ch_num >= AD70081Z_E19_TOND_IS0
		    && channel->ch_num <= AD70081Z_E19_TOND_IS3) {
			range = p_ad70081z_dev_inst->idac_current_range[channel->ch_num -
							AD70081Z_E19_TOND_IS0];

			if (range == AD70081Z_IADC_RANGE_6p25_50uA) {
				return snprintf(buf, len, "%s", "6.25-50uA");
			} else if (range == AD70081Z_IADC_RANGE_1p25_10uA) {
				return snprintf(buf, len, "%s", "1.25-10uA");
			} else if (range == AD70081Z_IADC_RANGE_5_40uA) {
				return snprintf(buf, len, "%s", "5-40uA");
			} else {
				return -EINVAL;
			}
		} else {
			return snprintf(buf, len, "%s", "NA");
		}

	case IADC_INPUT_CURRENT:
		ret = read_single_sample((uint8_t)channel->ch_num, &val);
		if (IS_ERR_VALUE(ret))
			return ret;

		iadc_input_current = (REFERENCE_VOLTAGE / ADC_MAX_DATA_COUNT) *
				     ((float)val / p_ad70081z_dev_inst->iadc_rsense[channel->ch_num -
								     AD70081Z_E10_WPD_IS0]);
		return snprintf(buf, len, "%f", iadc_input_current);

	case IADC_RSENSE:
		val = p_ad70081z_dev_inst->iadc_rsense[channel->ch_num - AD70081Z_E10_WPD_IS0];
		return snprintf(buf, len, "%u", (uint16_t)val);

	/****************** DAC/ADC common (global) getters ******************/
	case REFERENCE_SOURCE:
		ret = ad70081z_spi_reg_read(device, AD70081Z_REF_CONFIG, &val);
		if (IS_ERR_VALUE(ret))
			return ret;

		if (val & 0x1) {
			return snprintf(buf, len, "%s", "Internal");
		} else {
			return snprintf(buf, len, "%s", "External");
		}

	default:
		break;
	}

	return len;
}

/*!
 * @brief	Setter function for DAC attributes
 * @param	device[in]- Pointer to IIO device instance
 * @param	buf[in]- IIO input data buffer
 * @param	len[in]- Number of expected bytes
 * @param	channel[in] - DAC input channel
 * @param	priv[in] - Attribute private ID
 * @return	len in case of SUCCESS, negative error code otherwise
 */
static ssize_t iio_ad70081z_attr_set(void *device, char *buf, size_t len,
				     const struct iio_ch_info *channel, intptr_t priv)
{
	uint32_t val;
	int32_t	 ret = SUCCESS;
	enum ad70081z_iadc_range range;

	val = srt_to_uint32(buf);

	switch (priv) {
	/****************** DAC Direct and InputA/B Data setters ******************/
	case DAC_DATA:
		ret = ad70081z_set_dac_value(device, val,
					     (enum ad70081z_channel)channel->ch_num);
		if (IS_ERR_VALUE(ret))
			return ret;

		return len;

	case DAC_INPUTA_DATA:
		ret = ad70081z_set_dac_input(device, val, AD70081Z_INPUT_A,
					     (enum ad70081z_channel)channel->ch_num);
		if (IS_ERR_VALUE(ret))
			return ret;

		return len;

	case DAC_INPUTB_DATA:
		ret = ad70081z_set_dac_input(device, val, AD70081Z_INPUT_B,
					     (enum ad70081z_channel)channel->ch_num);
		if (IS_ERR_VALUE(ret))
			return ret;

		return len;

	case DAC_VOLTAGE:
		return len;

	/****************** DAC Toggle SW/HW setters ******************/
	case DAC_TOGGLE_ENABLE:
		if (!strncmp(buf, "Enable", strlen(buf))) {
			ret = ad70081z_set_toggle_enable(device, (enum ad70081z_channel)channel->ch_num,
							 true);
		} else {
			ret = ad70081z_set_toggle_enable(device, (enum ad70081z_channel)channel->ch_num,
							 false);
		}

		if (IS_ERR_VALUE(ret))
			return ret;

		return len;

	case DAC_TOGGLE_MODE:
		if (!strncmp(buf, "Software", strlen(buf))) {
			ret = ad70081z_set_toggle_mode(device, (enum ad70081z_channel)channel->ch_num,
						       true);
		} else {
			ret = ad70081z_set_toggle_mode(device, (enum ad70081z_channel)channel->ch_num,
						       false);
		}

		if (IS_ERR_VALUE(ret))
			return ret;

		return len;

	case DAC_SW_TOGGLE_CNTRL:
	case DAC_HW_TOGGLE_CNTRL:
		if (val > 1U)
			return -EINVAL;

		if (channel) {
			/* Perform software toggle */
			ret = ad70081z_set_toggle_control(device,
							  (enum ad70081z_channel)channel->ch_num, val);
			if (IS_ERR_VALUE(ret))
				return ret;
		} else {
			if (val != p_ad70081z_dev_inst->gpio_tgp_state) {
				/* Perform hardware toggle using TGP pin */
				ret = ad70081z_toggle(device);
				if (IS_ERR_VALUE(ret))
					return ret;
			}
		}

		return len;

	/****************** DAC LDAC SW/HW setters ******************/
	case DAC_SW_LDAC_CNTRL:
		if (val > 1U)
			return -EINVAL;

		ret = ad70081z_set_sw_ldac(device, true);
		if (IS_ERR_VALUE(ret))
			return ret;

		return len;

	case DAC_HW_LDAC_CNTRL:
		if (val > 1U)
			return -EINVAL;

		ret = ad70081z_ldac(device);
		if (IS_ERR_VALUE(ret))
			return ret;

		return len;

	case DAC_SW_LDAC_MASK:
		if (val > 1U)
			return -EINVAL;

		if (!val) {
			ret = ad70081z_set_sw_ldac_mask(device, (enum ad70081z_channel)channel->ch_num,
							false);
		} else {
			ret = ad70081z_set_sw_ldac_mask(device, (enum ad70081z_channel)channel->ch_num,
							true);
		}

		if (IS_ERR_VALUE(ret))
			return ret;

		return len;

	case DAC_HW_LDAC_MASK:
		if (val > 1U)
			return -EINVAL;

		if (!val) {
			ret = ad70081z_set_hw_ldac_mask(device, (enum ad70081z_channel)channel->ch_num,
							false);
		} else {
			ret = ad70081z_set_hw_ldac_mask(device, (enum ad70081z_channel)channel->ch_num,
							true);
		}

		if (IS_ERR_VALUE(ret))
			return ret;

		return len;

	/****************** DAC Compare setters ******************/
	case DAC_COMPARE_ENABLE:
		if (!strncmp(buf, "Enable", strlen(buf))) {
			ret = ad70081z_set_compare(device, true);
		} else {
			ret = ad70081z_set_compare(device, false);
		}

		if (IS_ERR_VALUE(ret))
			return ret;

		return len;

	case DAC_COMPARE_MASK:
		if (val > 1U)
			return -EINVAL;

		if (!val) {
			/* Disable compare mask on channel */
			ret = ad70081z_set_compare_mask(device, (enum ad70081z_channel)channel->ch_num,
							false);
		} else {
			/* Enable compare mask on channel */
			ret = ad70081z_set_compare_mask(device, (enum ad70081z_channel)channel->ch_num,
							true);
		}

		if (IS_ERR_VALUE(ret))
			return ret;

		return len;

	/****************** IDAC setters ******************/
	case IDAC_SHUTDOWN_ENABLE:
		if ((channel->ch_num >= AD70081Z_IDAC_CH_LIMIT) || (val > 1U))
			return -EINVAL;

		if (!val) {
			ret = ad70081z_set_idac_shutdown(device, (enum ad70081z_channel)channel->ch_num,
							 false);
		} else {
			ret = ad70081z_set_idac_shutdown(device, (enum ad70081z_channel)channel->ch_num,
							 true);
		}

		if (IS_ERR_VALUE(ret))
			return ret;

		return len;

	/****************** ADC channel setters ******************/
	case ADC_RAW:
	case ADC_OFFSET:
	case ADC_SCALE:
	case ADC_SAMPLING_FREQUENCY:
	case IADC_INPUT_CURRENT:
		/* These attributes are read only */
		return len;

	case IADC_INPUT_CURRENT_RANGE:
		if (!strncmp(buf, "6.25-50uA", strlen(buf))) {
			range = AD70081Z_IADC_RANGE_6p25_50uA;
		} else if (!strncmp(buf, "1.25-10uA", strlen(buf))) {
			range = AD70081Z_IADC_RANGE_1p25_10uA;
		} else if (!strncmp(buf, "5-40uA", strlen(buf))) {
			range = AD70081Z_IADC_RANGE_5_40uA;
		} else {
			return -EINVAL;
		}

		ret = ad70081z_iadc_config(device,
					   (enum ad70081z_afe_mux_channel)channel->ch_num, range);
		if (IS_ERR_VALUE(ret))
			return ret;

		return len;

	case IADC_RSENSE:
		ret = ad70081z_iadc_rsense_config(device,
						  (enum ad70081z_afe_mux_channel)channel->ch_num, (uint16_t)val);
		if (IS_ERR_VALUE(ret))
			return ret;

		return len;

	/****************** DAC/ADC common getters ******************/
	case REFERENCE_SOURCE:
		if (!strncmp(buf, "Internal", strlen(buf))) {
			ret = ad70081z_set_reference(device, true);
		} else {
			ret = ad70081z_set_reference(device, false);
		}

		if (IS_ERR_VALUE(ret))
			return ret;

		return len;

	default:
		break;
	}

	return len;
}

/**
 * @brief	Read buffer data corresponding to AD70081z ADC IIO device
 * @param	dev_instance[in] - IIO device instance
 * @param	pbuf[out] - Pointer to output data buffer
 * @param	nb_of_samples[in] - Number of samples to read
 * @return	SUCCESS in case of success or negative value otherwise
 */
static int32_t iio_ad77081z_read_data(void *dev_instance,
				      void *pbuf,
				      uint32_t nb_of_samples)
{
	/* Read the data stored into acquisition buffers */
	return read_buffered_data(pbuf, nb_of_samples);
}

/**
 * @brief	Transfer the device data into memory (optional)
 * @param	dev_instance[in] - IIO device instance
 * @param	ch_mask[in] - Channels select mask
 * @return	SUCCESS in case of success or negative value otherwise
 */
static int32_t iio_ad77081z_prepare_transfer(void *dev_instance,
		uint32_t ch_mask)
{
	return prepare_data_transfer(ch_mask, ADC_CHN_COUNT, BYTES_PER_SAMPLE);
}

/**
 * @brief	Perform tasks before end of current data transfer
 * @param	dev_instance[in] - IIO device instance
 * @return	SUCCESS in case of success or negative value otherwise
 */
static int32_t iio_ad77081z_end_transfer(void *dev)
{
	return end_data_transfer();
}

/*!
 * @brief	Search the debug register address in look-up table Or registers array
 * @param	addr- Register address to search for
 * @param	reg_addr_offset - Offset of register address from its base address for
 *			multi-byte register entity
 * @return	Index to register address from look-up detect
 */
static uint32_t debug_reg_search(uint32_t addr, uint32_t *reg_addr_offset)
{
	uint32_t curr_indx;		// Indexing to registers array (look-up table)
	uint32_t reg_base_add;	// Base register address
	bool found = false;		// Address found status flag

	/* Search for valid input register address in registers array */
	for (curr_indx = 0; curr_indx < AD70081Z_REGISTERS_COUNT; curr_indx++) {
		if (addr == AD70081Z_ADDR(ad70081z_regs[curr_indx])) {
			*reg_addr_offset = 0;
			found = true;
			break;
		} else if (addr < AD70081Z_ADDR(ad70081z_regs[curr_indx])) {
			/* Get the input address offset from its base address for
			 * multi-byte register entity and break the loop indicating input
			 * address is located somewhere in the previous indexed register */
			if (AD70081Z_TRANSF_LEN(ad70081z_regs[curr_indx - 1]) > 1) {
				*reg_addr_offset = addr - AD70081Z_ADDR(ad70081z_regs[curr_indx - 1]);
				found = true;
			}
			break;
		}
	}

	/* Get the base address of register entity (single or multi byte) */
	if (found) {
		if (*reg_addr_offset > 0) {
			reg_base_add = ad70081z_regs[curr_indx - 1];
		} else {
			reg_base_add = ad70081z_regs[curr_indx];
		}
	} else {
		reg_base_add = addr | AD70081Z_R1B;
	}

	return reg_base_add;
}

/*!
 * @brief	Read the debug register value
 * @param	dev- Pointer to IIO device instance
 * @param	reg- Register address to read from
 * @param	readval- Pointer to variable to read data into
 * @return	SUCCESS in case of success, negative value otherwise
 */
int32_t debug_reg_read(void *dev, uint32_t reg, uint32_t *readval)
{
	uint32_t reg_base_add;		// Base register address
	uint32_t reg_addr_offset;	// Offset of input register address from its base

	if (reg <= MAX_REGISTER_ADDRESS) {
		reg_base_add = debug_reg_search(reg, &reg_addr_offset);

		/* Read data from device register */
		if ((ad70081z_spi_reg_read(dev, reg_base_add, readval) != SUCCESS)) {
			return FAILURE;
		}

		/* Extract the specific byte location for register entity */
		*readval = (*readval >> (reg_addr_offset * BYTE_SIZE)) & BYTE_MASK;

		return SUCCESS;
	}

	return FAILURE;
}

/*!
 * @brief	Write into the debug register
 * @param	dev- Pointer to IIO device instance
 * @param	reg- Register address to write into
 * @param	writeval- Register value to write
 * @return	SUCCESS in case of success, negative value otherwise
 */
int32_t debug_reg_write(void *dev, uint32_t reg, uint32_t writeval)
{
	uint32_t reg_base_add;		// Base register address
	uint32_t reg_addr_offset;	// Offset of input register address from its base
	uint32_t data;				// Register data

	if(reg <= MAX_REGISTER_ADDRESS) {
		reg_base_add = debug_reg_search(reg, &reg_addr_offset);

		/* Read the register contents */
		if ((ad70081z_spi_reg_read(dev, reg_base_add, &data) != SUCCESS)) {
			return FAILURE;
		}

		/* Modify the register contents to write user data at specific
		 * reister entity location */
		data &= ~(BYTE_MASK << (reg_addr_offset * BYTE_SIZE));
		data |= (uint32_t)((writeval & BYTE_MASK) << (reg_addr_offset * BYTE_SIZE));

		/* Write data into device register */
		if (ad70081z_spi_reg_write(dev, reg_base_add, data) != SUCCESS) {
			return FAILURE;
		}

		return SUCCESS;
	}

	return FAILURE;
}

/*********************************************************
 *               IIO Attributes and Structures
 ********************************************************/

/* IIOD channels configurations */
static struct iio_channel ad70081z_dac_iio_channels[] = {
	/* 10-bit DAC Current Channels (Count= 3) */
	AD70081Z_DAC_CH("idac_", AD70081Z_E24_GAIN),
	AD70081Z_DAC_CH("idac_", AD70081Z_E25_SOA(0)),
	AD70081Z_DAC_CH("idac_", AD70081Z_E25_SOA(1)),

	/* 16-bit DAC Voltage Channels (Count= 25) */
	AD70081Z_DAC_CH("vdac16_", AD70081Z_E4_MIR(0)),
	AD70081Z_DAC_CH("vdac16_", AD70081Z_E4_MIR(1)),
	AD70081Z_DAC_CH("vdac16_", AD70081Z_E6_PHTR(0)),
	AD70081Z_DAC_CH("vdac16_", AD70081Z_E6_PHTR(1)),
	AD70081Z_DAC_CH("vdac16_", AD70081Z_E6_PHTR(2)),
	AD70081Z_DAC_CH("vdac16_", AD70081Z_E6_PHTR(3)),
	AD70081Z_DAC_CH("vdac16_", AD70081Z_E6_PHTR(4)),
	AD70081Z_DAC_CH("vdac16_", AD70081Z_E6_PHTR(5)),
	AD70081Z_DAC_CH("vdac16_", AD70081Z_E6_PHTR(6)),
	AD70081Z_DAC_CH("vdac16_", AD70081Z_E6_PHTR(7)),
	AD70081Z_DAC_CH("vdac16_", AD70081Z_E5_SPH),
	AD70081Z_DAC_CH("vdac16_", AD70081Z_E17_SPVOA(0)),
	AD70081Z_DAC_CH("vdac16_", AD70081Z_E17_SPVOA(1)),
	AD70081Z_DAC_CH("vdac16_", AD70081Z_E17_SPVOA(2)),
	AD70081Z_DAC_CH("vdac16_", AD70081Z_E17_SPVOA(3)),
	AD70081Z_DAC_CH("vdac16_", AD70081Z_E18_TPVOA(0)),
	AD70081Z_DAC_CH("vdac16_", AD70081Z_E18_TPVOA(1)),
	AD70081Z_DAC_CH("vdac16_", AD70081Z_E16_RPVOA(0)),
	AD70081Z_DAC_CH("vdac16_", AD70081Z_E16_RPVOA(1)),
	AD70081Z_DAC_CH("vdac16_", AD70081Z_E12_WHTR),
	AD70081Z_DAC_CH("vdac16_", AD70081Z_E9_RFPD),
	AD70081Z_DAC_CH("vdac16_", AD70081Z_E19_TOND),
	AD70081Z_DAC_CH("vdac16_", AD70081Z_E26_TONF(0)),
	AD70081Z_DAC_CH("vdac16_", AD70081Z_E26_TONF(1)),
	AD70081Z_DAC_CH("vdac16_", AD70081Z_E22_FSOPD),

	/* 12-bit DAC Voltage Channels (Count= 2) */
	AD70081Z_DAC_CH("vdac12_", AD70081Z_E8_MZDB),
	AD70081Z_DAC_CH("vdac12_", AD70081Z_E0_TECC),
};

/* IIOD channels configurations */
static struct iio_channel ad70081z_adc_iio_channels[] = {
	/* 16-bit ADC External Current Sense Input Channels (Count= 8) */
	AD70081Z_IADC_CH(AD70081Z_E10_WPD_IS0),
	AD70081Z_IADC_CH(AD70081Z_E10_WPD_IS1),
	AD70081Z_IADC_CH(AD70081Z_E19_TOND_IS0),
	AD70081Z_IADC_CH(AD70081Z_E19_TOND_IS1),
	AD70081Z_IADC_CH(AD70081Z_E19_TOND_IS2),
	AD70081Z_IADC_CH(AD70081Z_E19_TOND_IS3),
	AD70081Z_IADC_CH(AD70081Z_E20_TTAP_IS),
	AD70081Z_IADC_CH(AD70081Z_E21_RTAP_IS),

	/* 16-bit ADC External Voltage Channels (Count= 12) */
	AD70081Z_VADC_CH(AD70081Z_E1_CTHRM_VS),
	AD70081Z_VADC_CH(AD70081Z_E2_TECC_VS),
	AD70081Z_VADC_CH(AD70081Z_E3_TECC_VS),
	AD70081Z_VADC_CH(AD70081Z_E4_MIRS_VS0),
	AD70081Z_VADC_CH(AD70081Z_E4_MIRS_VS1),
	AD70081Z_VADC_CH(AD70081Z_E5_SPHS_VS),
	AD70081Z_VADC_CH(AD70081Z_E7_LHGS_VS),
	AD70081Z_VADC_CH(AD70081Z_E13_WTHRM_VS),
	AD70081Z_VADC_CH(AD70081Z_E27_ASIG_VS0),
	AD70081Z_VADC_CH(AD70081Z_E27_ASIG_VS1),
	AD70081Z_VADC_CH(AD70081Z_E27_ASIG_VS2),
	AD70081Z_VADC_CH(AD70081Z_E27_ASIG_VS3),

	/* 16-bit ADC Voltage Internal Channels (Count= 3) */
	AD70081Z_VADC_CH(AD70081Z_E24_GAINS_VS),
	AD70081Z_VADC_CH(AD70081Z_E25_SOA_VS0),
	AD70081Z_VADC_CH(AD70081Z_E25_SOA_VS1),
};


/**
 * @brief	Init for reading/writing and parameterization of a
 * 			ad70081z IIO device
 * @param 	desc[in,out] - IIO device descriptor
 * @return	SUCCESS in case of success, FAILURE otherwise
 */
static int32_t iio_ad70081z_init(struct iio_device **desc,
				 enum ad70081z_dev_type dev_type)
{
	struct iio_device *iio_ad70081z_inst;

	iio_ad70081z_inst = calloc(1, sizeof(struct iio_device));
	if (!iio_ad70081z_inst) {
		return FAILURE;
	}

	switch (dev_type) {
	case AD70081Z_DAC:
		iio_ad70081z_inst->num_ch = sizeof(ad70081z_dac_iio_channels) / sizeof(
						    ad70081z_dac_iio_channels[0]);
		iio_ad70081z_inst->channels = ad70081z_dac_iio_channels;
		iio_ad70081z_inst->attributes = dac_global_attributes;
		iio_ad70081z_inst->debug_attributes = debug_attributes;

		iio_ad70081z_inst->prepare_transfer = NULL;
		iio_ad70081z_inst->end_transfer = NULL;
		iio_ad70081z_inst->read_dev = NULL;
		iio_ad70081z_inst->write_dev = NULL;
		iio_ad70081z_inst->debug_reg_read = debug_reg_read;
		iio_ad70081z_inst->debug_reg_write = debug_reg_write;
		break;

	case AD70081Z_ADC:
		iio_ad70081z_inst->num_ch = sizeof(ad70081z_adc_iio_channels) / sizeof(
						    ad70081z_adc_iio_channels[0]);
		iio_ad70081z_inst->channels = ad70081z_adc_iio_channels;
		iio_ad70081z_inst->attributes = adc_global_attributes;
		iio_ad70081z_inst->debug_attributes = debug_attributes;

		iio_ad70081z_inst->prepare_transfer = iio_ad77081z_prepare_transfer;
		iio_ad70081z_inst->end_transfer = iio_ad77081z_end_transfer;
		iio_ad70081z_inst->read_dev = iio_ad77081z_read_data;
		iio_ad70081z_inst->write_dev = NULL;
		iio_ad70081z_inst->debug_reg_read = debug_reg_read;
		iio_ad70081z_inst->debug_reg_write = debug_reg_write;
		break;

	default:
		return FAILURE;
	}

	*desc = iio_ad70081z_inst;

	return SUCCESS;
}

/**
 * @brief Release resources allocated for IIO device
 * @param desc[in] - IIO device descriptor
 * @return SUCCESS in case of success, FAILURE otherwise
 */
static int32_t iio_ad70081z_remove(struct iio_desc *desc)
{
	int32_t status;

	if (!desc) {
		return FAILURE;
	}

	status = iio_unregister(desc, (char *)dev_name);
	if (status != SUCCESS) {
		return FAILURE;
	}

	return SUCCESS;
}

/**
 * @brief	Initialize the IIO interface for AD70081z IIO device
 * @return	none
 * @return	SUCCESS in case of success, FAILURE otherwise
 */
int32_t ad70081z_iio_initialize(void)
{
	int32_t init_status;

	/* IIO device descriptors */
	struct iio_device *p_iio_ad70081z_adc_dev;
	struct iio_device *p_iio_ad70081z_dac_dev;

	/* IIO interface init parameters */
	struct iio_init_param iio_init_params;

	/* Init the system peripherals */
	init_status = init_system();
	if (init_status != SUCCESS) {
		return init_status;
	}

	/* Initialize AD70081z device and peripheral interface */
	init_status = ad70081z_init(&p_ad70081z_dev_inst, &ad70081z_init_params);
	if (init_status != SUCCESS) {
		return init_status;
	}

	/* Initialize the IIO interface */
	iio_init_params.phy_type = USE_UART;
	iio_init_params.uart_desc = uart_desc;
	init_status = iio_init(&p_ad70081z_iio_desc, &iio_init_params);
	if (init_status != SUCCESS) {
		return init_status;
	}

	/* Initialize the ad70081z ADC IIO device interface */
	init_status = iio_ad70081z_init(&p_iio_ad70081z_adc_dev, AD70081Z_ADC);
	if (init_status != SUCCESS) {
		return init_status;
	}

	/* Initialize the ad70081z DAC IIO device interface */
	init_status = iio_ad70081z_init(&p_iio_ad70081z_dac_dev, AD70081Z_DAC);
	if (init_status != SUCCESS) {
		return init_status;
	}

	/* Register ad70081z ADC device */
	init_status = iio_register(p_ad70081z_iio_desc,
				   p_iio_ad70081z_adc_dev,
				   (char *)ad70081z_dev_name[0],
				   p_ad70081z_dev_inst,
				   &adc_data_buff,
				   NULL);
	if (init_status != SUCCESS) {
		return iio_ad70081z_remove(p_ad70081z_iio_desc);
	}

	/* Register ad70081z DAC device */
	init_status = iio_register(p_ad70081z_iio_desc,
				   p_iio_ad70081z_dac_dev,
				   (char *)ad70081z_dev_name[1],
				   p_ad70081z_dev_inst,
				   NULL,
				   NULL);
	if (init_status != SUCCESS) {
		return iio_ad70081z_remove(p_ad70081z_iio_desc);
	}

	return init_status;
}


/**
 * @brief 	Run the AD70081z IIO event handler
 * @return	none
 * @details	This function monitors the new IIO client event
 */
void ad70081z_iio_event_handler(void)
{
	while (1) {
		(void)iio_step(p_ad70081z_iio_desc);
	}
}
