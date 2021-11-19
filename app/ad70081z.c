/*******************************************************************************
 *   @file   ad70081z.c
 *   @brief  Implementation of ad70081z Driver.
 *   @author Darius Berghe (darius.berghe@analog.com)
********************************************************************************
 * Copyright 2021(c) Analog Devices, Inc.
 *
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are met:
 *  - Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 *  - Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in
 *    the documentation and/or other materials provided with the
 *    distribution.
 *  - Neither the name of Analog Devices, Inc. nor the names of its
 *    contributors may be used to endorse or promote products derived
 *    from this software without specific prior written permission.
 *  - The use of this software may or may not infringe the patent rights
 *    of one or more patent holders.  This license does not release you
 *    from the requirement that you obtain separate licenses from these
 *    patent holders to use this software.
 *  - Use of the software either in source or binary form, must be run
 *    on or directly connected to an Analog Devices Inc. component.
 *
 * THIS SOFTWARE IS PROVIDED BY ANALOG DEVICES "AS IS" AND ANY EXPRESS OR
 * IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, NON-INFRINGEMENT,
 * MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED.
 * IN NO EVENT SHALL ANALOG DEVICES BE LIABLE FOR ANY DIRECT, INDIRECT,
 * INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
 * LIMITED TO, INTELLECTUAL PROPERTY RIGHTS, PROCUREMENT OF SUBSTITUTE GOODS OR
 * SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER
 * CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY,
 * OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
 * OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
*******************************************************************************/

/******************************************************************************/
/***************************** Include Files **********************************/
/******************************************************************************/
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <assert.h>

#include "error.h"
#include "util.h"
#include "delay.h"
#include "ad70081z.h"
#include "crc.h"

DECLARE_CRC8_TABLE(ad70081z_crc8);

static inline bool is_addr_valid(struct ad70081z_dev *dev, uint32_t reg_addr)
{
	uint8_t reg_size = AD70081Z_TRANSF_LEN(reg_addr);
	uint32_t addr = AD70081Z_ADDR(reg_addr);
	uint32_t addrmax = dev->dev_spi_settings.short_instruction ? (2 << 8) - 1 :
			   (2 << 16) - 1;

	if (addr > addrmax || reg_size > 2)
		return false;
	else
		return true;
}

static void memswap64(void * buf, uint32_t bytes, size_t step)
{
	uint8_t * p = buf;
	uint32_t i, j;
	uint8_t temp[8];
	if (step < 2 || step > 8 || bytes < step || bytes % step != 0)
		return;
	for(i = 0; i < bytes; i += step) {
		memcpy(temp, p, step);
		for(j = step; j > 0; j--) {
			*p++ = temp[j-1];
		}
	}
}

static inline bool is_big_endian()
{
	uint16_t a = 0x0100;
	return (bool) *(uint8_t *) &a;
}

/**
 * @brief Read device register over SPI.
 *
 * Register may be a multi-byte register.
 *
 * The result of the read transaction is stored into reg_data
 * in the endianess format of the host controller regardless of
 * the ADDR_DIRECTION setting of the device.
 *
 * This function does not perform dynamic memory allocation.
 *
 * @param dev - The device structure.
 * @param reg_addr - The register address.
 * @param reg_data - The register data.
 * @return 0 in case of success, negative error code otherwise.
 */
int ad70081z_spi_reg_read(struct ad70081z_dev *dev,
			  uint32_t reg_addr,
			  uint32_t *reg_data)
{
	uint8_t buf[5];
	uint8_t icrc = 0;
	uint8_t ocrc = 0;
	uint16_t sz;
	uint16_t i = 0;
	uint16_t di;
	uint8_t reg_size = AD70081Z_TRANSF_LEN(reg_addr);
	uint32_t addr = AD70081Z_ADDR(reg_addr);
	int ret;

	if (!dev || !reg_data || !is_addr_valid(dev, reg_addr) || dev->custom_mode)
		return -EINVAL;

	// use register MSB or LSB as address depending on direction
	if (!dev->dev_spi_settings.addr_ascension)
		addr += (reg_size - 1);

	memset(buf, 0, sizeof(buf));
	if (dev->dev_spi_settings.short_instruction) {
		buf[i++] = (uint8_t)(AD70081Z_REG_READ_7(addr));
	} else {
		buf[i++] = (uint8_t)(AD70081Z_REG_READ_15(addr) >> 8);
		buf[i++] = (uint8_t)(addr);
	}

	di = i; // save the data index

	if (dev->dev_spi_settings.crc_enabled) {
		ocrc = crc8(ad70081z_crc8, buf, i,
			    AD70081Z_CRC8_INITIAL_VALUE); // compute instruction crc
		icrc = ocrc;
	}

	i += reg_size; // padding bytes on MOSI (zeroes, due to memset above)
	sz = i;

	if (dev->dev_spi_settings.crc_enabled) {
		ocrc = crc8(ad70081z_crc8, &buf[di], reg_size, ocrc);
		buf[i++] = ocrc;
		sz = i;
	}

	ret = spi_write_and_read(dev->spi_desc, buf, sz);
	if (ret)
		return ret;

	if (dev->dev_spi_settings.crc_enabled) {
		icrc = crc8(ad70081z_crc8, &buf[di], reg_size, icrc);
		if (icrc != buf[sz-1])
			return -EBADMSG;
	}

	*reg_data = 0;
	if (dev->endianess)
		memcpy((uint8_t *)(reg_data + 1) - reg_size, &buf[di], reg_size);
	else
		memcpy(reg_data, &buf[di], reg_size);

	// perform endian swapping of data depending on direction
	if (!(dev->endianess ^ dev->dev_spi_settings.addr_ascension))
		memswap64(reg_data, reg_size, reg_size);

	return ret;
}

/**
 * @brief Write device register over SPI.
 *
 * A register write begins with the given address and auto-increments
 * or decrements for each additional byte in the transfer, depending
 * on the ADDR_DIRECTION setting of the device.
 *
 * The user does not need to care about how to store multi-byte
 * registers in reg_data, because the function automatically
 * sends it in correct order over SPI, regardless of the
 * ADDR_DIRECTION setting of the device. Therefore, if the data
 * is 2 byte wide, the user may simply pass the reg_data as-is,
 * and the function will send LSB or MSB first depending on the
 * combination of host controller endianess and ADDR_DIRECTION
 * setting.
 *
 * This function does not perform dynamic memory allocation.
 *
 * @param dev - The device structure.
 * @param reg_addr - The register address.
 * @param reg_data - The register data.
 * @return 0 in case of success, negative error code otherwise.
 */
int ad70081z_spi_reg_write(struct ad70081z_dev *dev,
			   uint32_t reg_addr,
			   uint32_t reg_data)
{
	uint8_t buf[5];
	uint8_t ocrc = 0;
	uint16_t sz;
	uint16_t i = 0;
	uint8_t reg_size = AD70081Z_TRANSF_LEN(reg_addr);
	uint32_t addr = AD70081Z_ADDR(reg_addr);
	int ret;
	uint32_t data = reg_data;

	if (!dev || !is_addr_valid(dev, reg_addr) || dev->custom_mode)
		return -EINVAL;

	// use register MSB or LSB as address depending on direction
	if (!dev->dev_spi_settings.addr_ascension)
		addr += (reg_size - 1);

	if (dev->dev_spi_settings.short_instruction) {
		buf[i++] = (uint8_t)(AD70081Z_REG_WRITE_7(addr));
	} else {
		buf[i++] = (uint8_t)(AD70081Z_REG_WRITE_15(addr) >> 8);
		buf[i++] = (uint8_t)(addr);
	}

	// perform endian swapping of data depending on direction
	if (!(dev->endianess ^ dev->dev_spi_settings.addr_ascension))
		memswap64(&data, reg_size, reg_size);
	if (dev->endianess)
		memcpy(&buf[i], (uint8_t *)(&data + 1) - reg_size, reg_size);
	else
		memcpy(&buf[i], &data, reg_size);
	i += reg_size;

	sz = i;

	if (dev->dev_spi_settings.crc_enabled) {
		ocrc = crc8(ad70081z_crc8, buf, i, AD70081Z_CRC8_INITIAL_VALUE);
		buf[i++] = ocrc;
		sz = i;
	}

	ret = spi_write_and_read(dev->spi_desc, buf, sz);

	if (dev->dev_spi_settings.crc_enabled) {
		if (ocrc != buf[sz - 1])
			return -EBADMSG;
	}

	return ret;
}

/**
 * @brief SPI write to device using a mask.
 * @param dev - The device structure.
 * @param reg_addr - The register address.
 * @param mask - The mask (only affect set bits).
 * @param data - The data to write with mask applied.
 * @return 0 in case of success, negative error code otherwise.
 */
int ad70081z_spi_reg_write_mask(struct ad70081z_dev *dev,
				uint32_t reg_addr,
				uint32_t mask,
				uint32_t data)
{
	uint32_t regval;
	int ret;

	ret = ad70081z_spi_reg_read(dev, reg_addr, &regval);
	if(ret)
		return ret;

	regval &= ~mask;
	regval |= data;

	ret = ad70081z_spi_reg_write(dev, reg_addr, regval);

	return ret;
}

/**
 * @brief Set device SPI settings.
 * @param dev - The device structure.
 * @param spi_settings - The structure that contains the device spi
 *			   parameters.
 * @return SUCCESS in case of success, negative error code otherwise.
 */
int ad70081z_set_device_spi(struct ad70081z_dev *dev,
			    const struct ad70081z_device_spi_settings *spi_settings)
{
	int ret;

	if (!dev || !spi_settings)
		return -EINVAL;

	// enable crc already to be sure next config instructions are correct.
	ret = ad70081z_spi_reg_write_mask(dev,
					  AD70081Z_INTERFACE_CONFIG_C,
					  AD70081Z_INTERFACE_CONFIG_C_CRC_MSK,
					  AD70081Z_INTERFACE_CONFIG_C_CRC((uint8_t)spi_settings->crc_enabled));
	if (ret)
		return ret;
	else
		dev->dev_spi_settings.crc_enabled =
			spi_settings->crc_enabled;

	ret = ad70081z_spi_reg_write_mask(dev,
					  AD70081Z_INTERFACE_CONFIG_A,
					  AD70081Z_INTERFACE_CONFIG_A_ADDR_DIRECTION_MSK,
					  AD70081Z_INTERFACE_CONFIG_A_ADDR_DIRECTION(spi_settings->addr_ascension));
	if (ret)
		return ret;

	dev->dev_spi_settings.addr_ascension =
		spi_settings->addr_ascension;

	ret = ad70081z_spi_reg_write_mask(dev,
					  AD70081Z_INTERFACE_CONFIG_B,
					  AD70081Z_INTERFACE_CONFIG_B_ACCESS_MODE_MSK |
					  AD70081Z_INTERFACE_CONFIG_B_ADDR_MODE_MSK,
					  AD70081Z_INTERFACE_CONFIG_B_ADDR_MODE(spi_settings->short_instruction));
	if (ret)
		return ret;

	dev->dev_spi_settings.short_instruction =
		spi_settings->short_instruction;

	return SUCCESS;
}

/**
 * @brief Set the main modes of operation and power.
 * @param dev - The device structure.
 * @param custom_mode - register access or ADC continuous conversion mode.
 * @return SUCCESS in case of success, negative error code otherwise.
 */
int ad70081z_set_device_config(struct ad70081z_dev *dev,
			       enum ad70081z_custom_mode custom_mode)
{
	int ret;

	ret = ad70081z_spi_reg_write(dev,
				     AD70081Z_DEVICE_CONFIG,
				     AD70081Z_DEVICE_CONFIG_CUSTOM_MODES(custom_mode));
	if (ret)
		return ret;

	dev->custom_mode = custom_mode;

	return ret;
}

/**
 * @brief Get interface status value.
 * @param dev - The device structure.
 * @param status - The INTERFACE STATUS A register value.
 * @return SUCCESS in case of success, negative error code otherwise.
 */
int ad70081z_get_interface_status(struct ad70081z_dev *dev,
				  uint8_t *status)
{
	uint32_t s;
	int ret;

	ret = ad70081z_spi_reg_read(dev,
				    AD70081Z_INTERFACE_STATUS_A,
				    &s);
	if (ret)
		return ret;

	*status = (uint8_t)(s);

	return ret;
}

/**
 * @brief Performs a software reset.
 * @param dev - The device structure.
 * @return SUCCESS in case of success, negative error code otherwise.
 */
int ad70081z_hardware_reset(struct ad70081z_dev *dev)
{
	int ret;

	if (!dev)
		return -EINVAL;

	/* Perform a hardware reset */
	ret = gpio_set_value(dev->gpio_reset_n, GPIO_LOW);
	if (ret)
		return ret;

	/* Wait t_RESETBL_PW, Table 12, TODO: adjust value when datasheet is complete. */
	udelay(10);

	ret = gpio_set_value(dev->gpio_reset_n, GPIO_HIGH);
	if (ret)
		return ret;

	/* Wait t_RESETBH_BUSYL, Figure 4, TODO: adjust value when datasheet is complete. */
	mdelay(20);

	return SUCCESS;
}

/**
 * @brief Performs a software reset.
 * @param dev - The device structure.
 * @return SUCCESS in case of success, negative error code otherwise.
 */
int ad70081z_software_reset(struct ad70081z_dev *dev)
{
	int ret;

	if (!dev)
		return -EINVAL;

	ret = ad70081z_spi_reg_write(dev,
				     AD70081Z_INTERFACE_CONFIG_A,
				     AD70081Z_INTERFACE_CONFIG_A_SW_RESET_MSK |
				     AD70081Z_INTERFACE_CONFIG_A_ADDR_DIRECTION(
					     dev->dev_spi_settings.addr_ascension));
	if (ret)
		return ret;

	/* Wait t_RESETBH_BUSYL, Figure 4, TODO: adjust value when datasheet is complete. */
	mdelay(20);

	return SUCCESS;
}

static int _ad70081z_pulse(struct gpio_desc *gpio, uint32_t delay,
			   bool inverted)
{
	int ret;

	ret = gpio_set_value(gpio, inverted ? GPIO_LOW : GPIO_HIGH);
	if (ret)
		return ret;
	udelay(delay);
	return gpio_set_value(gpio, inverted ? GPIO_HIGH : GPIO_LOW);
}

/**
 * @brief Generate LDAC pulse.
 * @param dev - The device structure.
 * @return SUCCESS in case of success, negative error code otherwise.
 */
int ad70081z_ldac(struct ad70081z_dev *dev)
{
	if (!dev)
		return -EINVAL;

	return _ad70081z_pulse(dev->gpio_ldac_n, 1, true);
}

/**
 * @brief Hardware trigger gpio toggle.
 * @param dev - The device structure.
 * @return SUCCESS in case of success, negative error code otherwise.
 */
int ad70081z_toggle(struct ad70081z_dev *dev)
{
	int ret;

	if (!dev)
		return -EINVAL;

	ret = gpio_set_value(dev->gpio_tgp, !dev->gpio_tgp_state);
	if (ret)
		return ret;

	dev->gpio_tgp_state = !dev->gpio_tgp_state;
	return ret;
}

/**
 * @brief Initialize the device.
 * @param device - The device structure.
 * @param init_param - The structure that contains the device initial
 *			   parameters.
 * @return SUCCESS in case of success, negative error code otherwise.
 */
int ad70081z_init(struct ad70081z_dev **device,
		  const struct ad70081z_init_param *init_param)
{
	struct ad70081z_dev *dev;
	uint32_t product_id_l, product_id_h;
	int ret;
	uint8_t status;
	enum ad70081z_afe_mux_channel iadc_chn;

	if (!device || !init_param)
		return -EINVAL;

	// mahesh
	printf("\r\nInitializing AD70081z...");
	
	dev = (struct ad70081z_dev *)calloc(1, sizeof(*dev));
	if (!dev)
		return -ENOMEM;

	/* detect endianess */
	dev->endianess = is_big_endian();

	crc8_populate_msb(ad70081z_crc8, 0x7);

	ret = gpio_get_optional(&dev->gpio_ldac_n, init_param->gpio_ldac_n);
	if (ret)
		goto error;

	if (dev->gpio_ldac_n) {
		ret = gpio_direction_output(dev->gpio_ldac_n, GPIO_HIGH);
		if (ret)
			goto error;
	}

	// mahesh
	printf("\r\nLDAC GPIO Init Success...");
	
	ret = gpio_get_optional(&dev->gpio_tgp, init_param->gpio_tgp);
	if (ret)
		goto error;

	if(dev->gpio_tgp) {
		ret = gpio_direction_output(dev->gpio_tgp, GPIO_LOW);
		if (ret)
			goto error;
	}

	// mahesh
	printf("\r\nTGP GPIO Init Success...");
	
	ret = gpio_get_optional(&dev->gpio_convst, init_param->gpio_convst);
	if (ret)
		goto error;

	if(dev->gpio_convst) {
		ret = gpio_direction_output(dev->gpio_convst, GPIO_HIGH);
		if (ret)
			goto error;
	}

	// mahesh
	printf("\r\nCONVST GPIO Init Success...");
	
	ret = spi_init(&dev->spi_desc, &init_param->spi_init);
	if (ret)
		goto error;

	// mahesh
	printf("\r\nSPI Init Success...");
	
	ret = gpio_get_optional(&dev->gpio_reset_n, init_param->gpio_reset_n);
	if (ret)
		goto error;

	if (dev->gpio_reset_n) {
		ret = gpio_direction_output(dev->gpio_reset_n, GPIO_HIGH);
		if (ret)
			goto error;

		ret = ad70081z_hardware_reset(dev);
		if (ret)
			goto error;
	} else {
		ret = ad70081z_software_reset(dev);
		if (ret)
			goto error;
	}

	// mahesh
	printf("\r\nAD70081z H/W Reset Success...");
	
	ret = ad70081z_get_interface_status(dev, &status);
	if (ret)
		goto error;

	if (status) {
		/* This can happen for the following reasons:
		 * - unconnected or misconfigured reset line when using hardware reset
		 * - spi settings mismatch (crc, 7/15 bit addressing) when using software reset
		 */
		ret = -EFAULT;
		goto error;
	}

	// mahesh
	printf("\r\nInterface Status Register Read Success...");
	
	/* Query product id */
	ret = ad70081z_spi_reg_read(dev, AD70081Z_PRODUCT_ID_L, &product_id_l);
	if (ret)
		goto error;
	ret = ad70081z_spi_reg_read(dev, AD70081Z_PRODUCT_ID_H, &product_id_h);
	if (ret)
		goto error;

	// mahesh
	printf("\r\nAD70081Z_PRODUCT_ID_L: %d...", product_id_l);
	printf("\r\nAD70081Z_PRODUCT_ID_H: %d...", product_id_h);
	
	if (product_id_l != AD70081Z_PRODUCT_ID_L_VALUE ||
	    product_id_h != AD70081Z_PRODUCT_ID_H_VALUE) {
		printf("unexpected product id (0x%.2X%.2X)\n",
		       (uint16_t)product_id_h, (uint16_t)product_id_l);
		ret = -EFAULT;
		goto error;
	}

	// mahesh
	printf("\r\nProduct ID Read Success...");
	
	ret = ad70081z_set_device_spi(dev,
				      &init_param->dev_spi_settings);
	if (ret)
		goto error;

	ad70081z_adc_set_osr(dev, init_param->osr);

	/* Enable internal reference source */
	if (init_param->enable_internal_reference)
		ad70081z_set_reference(dev, true);

	/* Configure the IADC Rsense values */
	for (iadc_chn = AD70081Z_E10_WPD_IS0; iadc_chn <= AD70081Z_E21_RTAP_IS;
	     iadc_chn++) {
		ret = ad70081z_iadc_rsense_config(dev, iadc_chn,
						  init_param->iadc_rsense[iadc_chn - AD70081Z_E10_WPD_IS0]);
		if (ret)
			goto error;
	}

	/* Configure the IADC input current range values */
	for (iadc_chn = AD70081Z_E19_TOND_IS0; iadc_chn <= AD70081Z_E19_TOND_IS3;
	     iadc_chn++) {
		ret = ad70081z_iadc_config(dev, iadc_chn,
					   init_param->idac_tond_is_current_range[iadc_chn - AD70081Z_E19_TOND_IS0]);
		if (ret)
			goto error;
	}

	*device = dev;

	// mahesh
	printf("\r\nAD70081z Init Complete...");
	
	return SUCCESS;
error:
	ad70081z_remove(dev);

	return ret;
}

/**
 * @brief Free allocated resources by the device.
 * @param device - The device structure.
 * @return SUCCESS in case of success, negative error code otherwise.
 */
void ad70081z_remove(struct ad70081z_dev *dev)
{
	if (!dev)
		return;

	if (dev->spi_desc)
		spi_remove(dev->spi_desc);
	if (dev->gpio_convst)
		gpio_remove(dev->gpio_convst);
	if (dev->gpio_ldac_n)
		gpio_remove(dev->gpio_ldac_n);
	if (dev->gpio_reset_n)
		gpio_remove(dev->gpio_reset_n);
	if (dev->gpio_tgp)
		gpio_remove(dev->gpio_tgp);
	free(dev);
}

/**
 * @brief Set the reference.
 * @param dev - The device structure.
 * @param internal - Specifies whether the reference is internal (true) or external (false).
 * @return SUCCESS in case of success, negative error code otherwise.
 */
int ad70081z_set_reference(struct ad70081z_dev *dev, bool internal)
{
	uint32_t reg = internal ? AD70081Z_REF_CONFIG_REFERENCE_SELECTION_MSK : 0;

	if (!dev)
		return -EINVAL;

	return ad70081z_spi_reg_write(dev, AD70081Z_REF_CONFIG, reg);
}

static bool _ad70081z_find_reg(uint32_t reg0, enum ad70081z_channel ch,
			       enum ad70081z_channel chmin, uint8_t *mask, uint32_t *reg)
{
	int range = ch - chmin;

	if (range < 0)
		return false;

	*mask = BIT(range % 8);
	*reg = reg0 + range / 8;

	return true;
}

static inline int _ad70081z_set_multi_regs(struct ad70081z_dev *dev,
		uint32_t reg0,
		enum ad70081z_channel ch, bool boolean)
{
	uint32_t reg, regval;
	uint8_t regmask;

	if (!dev || ch >= AD70081Z_VDAC_CH_LIMIT)
		return -EINVAL;

	if(!_ad70081z_find_reg(reg0, ch, (enum ad70081z_channel)0, &regmask, &reg))
		return -EINVAL;

	regval = field_prep(regmask, boolean);
	return ad70081z_spi_reg_write_mask(dev, reg, regmask, regval);
}

/**
 * @brief Configure a specific current DAC channel.
 * @param dev - The device structure.
 * @param ch - The current DAC channel.
 * @param enable - specify whether to enable or disable the channel.
 * @param config - Ground switch control config (optional).
 * @return SUCCESS in case of success, negative error code otherwise.
 */
int ad70081z_idac_config(struct ad70081z_dev *dev, enum ad70081z_channel ch,
			 bool enable, struct ad70081z_idac_gsc_config *config)
{
	int ret;
	uint32_t regval, reg;

	if (!dev)
		return -EINVAL;

	switch(ch) {
	case AD70081Z_E24_GAIN:
		/* nothing to do */
		break;
	case AD70081Z_E25_SOA(0):
		if (!config)
			return -EINVAL;
		reg = AD70081Z_E25_SOA_ID_0_GND_SWITCH;
		break;
	case AD70081Z_E25_SOA(1):
		if (!config)
			return -EINVAL;
		reg = AD70081Z_E25_SOA_ID_1_GND_SWITCH;
		break;
	default:
		return -EINVAL;
	}

	ret = _ad70081z_set_multi_regs(dev, AD70081Z_IDAC_OUT_SHDN, ch, enable);
	if (ret)
		return ret;

	regval = field_prep(AD70081Z_E25_SOA_ID_GND_SWITCH_EN_MSK, config->en);
	regval |= field_prep(AD70081Z_E25_SOA_ID_GND_SWITCH_HW_TGL_MSK, config->hw_tgl);
	regval |= field_prep(AD70081Z_E25_SOA_ID_GND_SWITCH_SW_TGL_MSK, config->sw_tgl);
	regval |= field_prep(AD70081Z_E25_SOA_ID_GND_SWITCH_CMP_TGL_MSK,
			     config->cmp_tgl);
	return ad70081z_spi_reg_write(dev, reg, regval);
}

/**
 * @brief Set dac value directly (no masking, no toggle, no ldac).
 * @param dev - The device structure.
 * @param dac_value - value that will be set in the DAC Data register.
 * @param channel - the selected channel.
 * @return SUCCESS in case of success, negative error code otherwise.
 */
int ad70081z_set_dac_value(struct ad70081z_dev *dev, uint16_t dac_value,
			   enum ad70081z_channel channel)
{
	if (!dev)
		return FAILURE;

	return ad70081z_spi_reg_write(dev, AD70081Z_DAC(channel), dac_value);
}

/**
 * @brief Set dac input registers directly, without using page mask.
 * @param dev - The device structure.
 * @param dac_input - value that will be set in the register.
 * @param input - INPUT_A or INPUT_B selection.
 * @param channel - the selected channel.
 * @return SUCCESS in case of success, negative error code otherwise.
 */
int ad70081z_set_dac_input(struct ad70081z_dev *dev, uint16_t dac_input,
			   enum ad70081z_input input, enum ad70081z_channel channel)
{
	uint32_t reg = (input == AD70081Z_INPUT_A ? AD70081Z_INPUT_A(channel) :
			AD70081Z_INPUT_B(channel));

	if (!dev)
		return FAILURE;

	return ad70081z_spi_reg_write(dev, reg, dac_input);
}

/**
 * @brief Set IDAC shutdown mask
 * @param dev - The device structure.
 * @param channel - The selected IDAC channel.
 * @param enable - Enable/Disable IDAC shutdown
 * @return SUCCESS in case of success, negative error code otherwise.
 */
int ad70081z_set_idac_shutdown(struct ad70081z_dev *dev,
			       enum ad70081z_channel chn,
			       bool enable)
{
	uint32_t reg = (enable == true ? (1 << chn) : 0);

	if (!dev)
		return FAILURE;

	return ad70081z_spi_reg_write_mask(dev, AD70081Z_IDAC_OUT_SHDN,
					   AD70081Z_IDAC_OUT_SHDN_MSK(chn), reg);
}

/**
 * @brief Configure the compare function.
 * @param dev - The device structure.
 * @param enable - Specifies whether to enable (true) or disable (false) the compare function.
 * @return SUCCESS in case of success, negative error code otherwise.
 */
int ad70081z_set_compare(struct ad70081z_dev *dev, bool enable)
{
	uint32_t reg = enable ? AD70081Z_CMP_EN_CMP_EN_MSK : 0;

	if (!dev)
		return -EINVAL;

	return ad70081z_spi_reg_write(dev, AD70081Z_CMP_EN, reg);
}

/**
 * @brief Configure the compare mask.
 * @param dev - The device structure.
 * @param ch - The VDAC/IDAC channel.
 * @param mask - Specifies whether to enable (true) or disable (false) the compare mask.
 * @return SUCCESS in case of success, negative error code otherwise.
 */
int ad70081z_set_compare_mask(struct ad70081z_dev *dev,
			      enum ad70081z_channel ch,
			      bool mask)
{
	return _ad70081z_set_multi_regs(dev, AD70081Z_CMP_MASK0, ch, mask);
}

/**
 * @brief Configure the hardware load DAC mask.
 * @param dev - The device structure.
 * @param ch - The VDAC/IDAC channel.
 * @param mask - Specifies whether to enable (true) or disable (false) the hardware load DAC mask.
 * @return SUCCESS in case of success, negative error code otherwise.
 */
int ad70081z_set_hw_ldac_mask(struct ad70081z_dev *dev,
			      enum ad70081z_channel ch,
			      bool mask)
{
	return _ad70081z_set_multi_regs(dev, AD70081Z_HW_LDAC_MASK0, ch, mask);
}

/**
 * @brief Configure the toggle mode.
 * @param dev - The device structure.
 * @param ch - The VDAC/IDAC channel.
 * @param software - Specifies whether toggling should be triggered by software (true) or TGP pin (false).
 * @return SUCCESS in case of success, negative error code otherwise.
 */
int ad70081z_set_toggle_mode(struct ad70081z_dev *dev, enum ad70081z_channel ch,
			     bool software)
{
	return _ad70081z_set_multi_regs(dev, AD70081Z_TOGGLE_MODE0, ch, software);
}

/**
 * @brief Software toggle control.
 * @param dev - The device structure.
 * @param ch - The VDAC/IDAC channel.
 * @param state - Software toggle control for the given channel.
 * @return SUCCESS in case of success, negative error code otherwise.
 */
int ad70081z_set_toggle_control(struct ad70081z_dev *dev,
				enum ad70081z_channel ch,
				bool state)
{
	return _ad70081z_set_multi_regs(dev, AD70081Z_TOGGLE_CONTROL0, ch, state);
}

/**
 * @brief Configure the toggle enable switch.
 * @param dev - The device structure.
 * @param ch - The VDAC/IDAC channel.
 * @param enable - Specifies whether toggling functionality should be enabled (true) or disabled (false).
 * @return SUCCESS in case of success, negative error code otherwise.
 */
int ad70081z_set_toggle_enable(struct ad70081z_dev *dev,
			       enum ad70081z_channel ch,
			       bool enable)
{
	return _ad70081z_set_multi_regs(dev, AD70081Z_TOGGLE_ENABLE0, ch, enable);
}

/**
 * @brief Configure the page mask write enable.
 * @param dev - The device structure.
 * @param ch - The VDAC/IDAC channel.
 * @param copy - Specifies whether to copy (true) or not (false) data to the specified channel.
 * @return SUCCESS in case of success, negative error code otherwise.
 */
int ad70081z_set_dac_select(struct ad70081z_dev *dev, enum ad70081z_channel ch,
			    bool copy)
{
	return _ad70081z_set_multi_regs(dev, AD70081Z_DAC_SELECT0, ch, copy);
}

/**
 * @brief Configure the global software LDAC functionality.
 * @param dev - The device structure.
 * @param enable - Specifies whether to enable (true) or disable (false) the LDAC function.
 * @return SUCCESS in case of success, negative error code otherwise.
 */
int ad70081z_set_sw_ldac(struct ad70081z_dev *dev, bool enable)
{
	uint32_t reg = enable ? AD70081Z_SW_LDAC_SW_LDAC_EN_MSK : 0;

	if (!dev)
		return -EINVAL;

	return ad70081z_spi_reg_write(dev, AD70081Z_SW_LDAC, reg);
}

/**
 * @brief Configure the software LDAC mask channel-wise.
 * @param dev - The device structure.
 * @param ch - The VDAC/IDAC channel.
 * @param enable - Specifies whether to enable (true) or disable (false) the software LDAC function for the given channel.
 * @return SUCCESS in case of success, negative error code otherwise.
 */
int ad70081z_set_sw_ldac_mask(struct ad70081z_dev *dev,
			      enum ad70081z_channel ch,
			      bool enable)
{
	return _ad70081z_set_multi_regs(dev, AD70081Z_SW_LDAC0_MASK, ch, enable);
}

/**
 * @brief Generate ADC conversion start pulse.
 * @param dev - The device structure.
 * @return SUCCESS in case of success, negative error code otherwise.
 */
int ad70081z_adc_convst(struct ad70081z_dev *dev)
{
	if (!dev)
		return -EINVAL;

	switch (dev->custom_mode) {
	case AD70081Z_REGISTER_ACCESS_MODE:
		return ad70081z_spi_reg_write(dev, AD70081Z_CONVST, 1);
		break;
	case AD70081Z_ADC_CONTINUOUS_CONVERSION_MODE:
		if (dev->gpio_convst) {
			/* TODO: tCONVST_PW is TBD in datasheet. */
			return _ad70081z_pulse(dev->gpio_convst, 1, true);
		} else {
			/* Do nothing, user likely is tying CSB to CONVST electrically. */
			return SUCCESS;
		}
		break;
	default:
		return -EINVAL;
	}
}

/**
 * @brief Set the cached ADC oversampling ratio.
 * @param dev - The device structure.
 * @return None.
 */
void ad70081z_adc_set_osr(struct ad70081z_dev *dev,
			  enum ad70081z_adc_config_osr osr)
{
	if (dev)
		dev->osr = osr;
}

/**
 * @brief Set the ADC conversion configuration (channel and oversampling).
 * @param dev - The device structure.
 * @param ch - The VADC/IADC channel.
 * @return SUCCESS in case of success, negative error code otherwise.
 * @note The oversamping is taken from the cached value specified with ad70081z_adc_set_osr().
 */
int ad70081z_adc_set_config(struct ad70081z_dev *dev,
			    enum ad70081z_afe_mux_channel ch)
{
	int ret;
	uint32_t regval;

	/* select AFE mux channel, osr */
	regval = field_prep(AD70081Z_ADC_CONFIG_AFE_MUX_CH_MSK, ch);
	regval |= field_prep(AD70081Z_ADC_CONFIG_ADC_OSR_MSK, dev->osr);
	ret = ad70081z_spi_reg_write(dev, AD70081Z_ADC_CONFIG, regval);
	if (ret)
		return ret;

	/* wait tAFE_MUX_STL */
	udelay(1);

	return SUCCESS;
}

/**
 * @brief Read a sample for a specific ADC channel in register mode.
 * @param dev - The device structure.
 * @param ch - The VADC/IADC channel.
 * @param data - Pointer to the memory that will hold the data.
 * @return SUCCESS in case of success, negative error code otherwise.
 * @note The oversamping is taken from the cached value specified with ad70081z_adc_set_osr().
 */
int ad70081z_adc_read(struct ad70081z_dev *dev,
		      enum ad70081z_afe_mux_channel ch, uint16_t *data)
{
	int ret;
	uint32_t regval;

	if (!dev || !data)
		return -EINVAL;

	ret = ad70081z_adc_set_config(dev, ch);
	if (ret)
		return ret;

	ret = ad70081z_adc_convst(dev);
	if (ret)
		return ret;

	/* TODO: allow for conversion to finish (TBD) */
	udelay(8 * (2 << dev->osr));

	ret = ad70081z_spi_reg_read(dev, AD70081Z_ADC_RESULT, &regval);
	if (ret)
		return ret;

	*data = regval;

	return SUCCESS;
}

/**
 * @brief Put the device in continuous conversion mode.
 * @param dev - The device structure.
 * @return SUCCESS in case of success, negative error code otherwise.
 */
int ad70081z_cc_start(struct ad70081z_dev *dev)
{
	if (!dev)
		return -EINVAL;

	if (dev->custom_mode != AD70081Z_REGISTER_ACCESS_MODE)
		return -EINVAL;

	return ad70081z_set_device_config(dev, AD70081Z_ADC_CONTINUOUS_CONVERSION_MODE);
}

/**
 * @brief Get the device out of continuous conversion mode.
 * @param dev - The device structure.
 * @return SUCCESS in case of success, negative error code otherwise.
 */
int ad70081z_cc_exit(struct ad70081z_dev *dev)
{
	int ret;

	if (!dev)
		return -EINVAL;

	if (dev->custom_mode != AD70081Z_ADC_CONTINUOUS_CONVERSION_MODE)
		return -EINVAL;

	enum ad70081z_afe_mux_channel cmd = AD70081Z_EXIT_CONT;
	ret = ad70081z_cc_read(dev, &cmd, NULL);
	if (ret)
		return ret;

	dev->custom_mode = AD70081Z_REGISTER_ACCESS_MODE;
	return ret;
}

/**
 * @brief  Read the continuous conversion result using device SPI.
 * @param  dev[in] - The device structure.
 * @param  nextch[in] - Next afe mux channel (if NULL, read the same channel).
 * @param  data[out] - Conversion result.
 * @return 0 in case of success, negative error code otherwise.
 * @note   During continuous conversion mode, access to device registers using SPI read/write
 * 		   operations are disabled. User must use SPI pins (using standard SPI protocol) to access
 * 		   adc conversion result.
 */
int ad70081z_cc_read(struct ad70081z_dev *dev,
		     enum ad70081z_afe_mux_channel *nextch, uint16_t *data)
{
	uint8_t buf[2];
	int ret;

	if (!dev)
		return -EINVAL;

	if (dev->custom_mode != AD70081Z_ADC_CONTINUOUS_CONVERSION_MODE)
		return -EINVAL;

	// select AFE mux channel, osr
	buf[0] = field_prep(AD70081Z_ADC_CONFIG_AFE_MUX_CH_MSK,
			    nextch ? *nextch : AD70081Z_AFE_MUX_CHANNEL_NOCHANGE);
	buf[0] |= field_prep(AD70081Z_ADC_CONFIG_ADC_OSR_MSK, dev->osr);
	buf[1] = 0;

	ret = spi_write_and_read(dev->spi_desc, buf, sizeof(buf));
	if (ret)
		return ret;

	/* Get the conversion result of previous channel (2-bytes) */
	if (data)
		*data = (((uint16_t)buf[0] << 8) | buf[1]);

	return SUCCESS;
}

/**
 * @brief Enable ADC for the IADC AFE MUX channels.
 * @param dev - The device structure.
 * @param ch - The IADC (only!) channel.
 * @param enable - Whether to enable (true) or disable (false) the specified channel.
 * @return SUCCESS in case of success, negative error code otherwise.
 */
int ad70081z_iadc_enable(struct ad70081z_dev *dev,
			 enum ad70081z_afe_mux_channel ch, bool enable)
{
	uint32_t mask;

	if (!dev || ch < AD70081Z_E10_WPD_IS0 || ch > AD70081Z_E21_RTAP_IS)
		return -EINVAL;

	mask = BIT(ch - AD70081Z_E10_WPD_IS0);
	return ad70081z_spi_reg_write_mask(dev, AD70081Z_I_ADC_IN_HI_Z, mask,
					   enable ? mask : 0);
}

/**
 * @brief Configure AD70081Z_E19_TOND_IS0 -> AD70081Z_E19_TOND_IS3 channels.
 * @param dev - The device structure.
 * @param ch - The IADC channels: AD70081Z_E19_TOND_IS0 -> AD70081Z_E19_TOND_IS3
 * @param range - Current sense operation range.
 * @return SUCCESS in case of success, negative error code otherwise.
 */
int ad70081z_iadc_config(struct ad70081z_dev *dev,
			 enum ad70081z_afe_mux_channel ch, enum ad70081z_iadc_range range)
{
	int ret;
	uint32_t mask;
	uint32_t regval;

	if (!dev || ch < AD70081Z_E19_TOND_IS0 || ch > AD70081Z_E19_TOND_IS3)
		return -EINVAL;

	mask = 0x3 << (2 * (ch - AD70081Z_E19_TOND_IS0));
	regval = field_prep(mask, range);
	ret = ad70081z_spi_reg_write_mask(dev, AD70081Z_I_ADC_TOND_INPUT_CURRENT_RANGE,
					  mask, regval);
	if (ret)
		return ret;

	dev->idac_current_range[ch - AD70081Z_E19_TOND_IS0] = range;
	return ret;
}

/**
 * @brief Configure the rsense value for IDAC channel.
 * @param dev - The device structure.
 * @param ch - The IADC channels: AD70081Z_E19_TOND_IS0 -> AD70081Z_E21_RTAP_IS
 * @param range - Rsense value
 * @return SUCCESS in case of success, negative error code otherwise.
 */
int ad70081z_iadc_rsense_config(struct ad70081z_dev *dev,
				enum ad70081z_afe_mux_channel ch, uint16_t rsense_val)
{
	int ret;
	enum ad70081z_afe_mux_channel chn_offset;

	if (!dev || ch < AD70081Z_E10_WPD_IS0 || ch > AD70081Z_E21_RTAP_IS)
		return -EINVAL;

	if (ch == AD70081Z_E10_WPD_IS0 || ch == AD70081Z_E10_WPD_IS1) {
		chn_offset = ch - AD70081Z_E10_WPD_IS0;
		rsense_val = (uint8_t)rsense_val;
		ret = ad70081z_spi_reg_write(dev, AD70081Z_I_ADC0_RSENSE + chn_offset,
					     rsense_val);
	} else if (ch == AD70081Z_E20_TTAP_IS || ch == AD70081Z_E21_RTAP_IS) {
		chn_offset = ch - AD70081Z_E20_TTAP_IS;
		rsense_val = (uint8_t)rsense_val;
		ret = ad70081z_spi_reg_write(dev, AD70081Z_I_ADC6_RSENSE + chn_offset,
					     rsense_val);
	} else {
		chn_offset = ch - AD70081Z_E19_TOND_IS0;
		/* Write lower byte */
		ret = ad70081z_spi_reg_write(dev, AD70081Z_I_ADC2_RSENSE + (chn_offset * 2),
					     (uint8_t)rsense_val);
		/* Write higher byte */
		ret |= ad70081z_spi_reg_write(dev,
					      AD70081Z_I_ADC2_RSENSE + (chn_offset * 2) + 1,
					      (uint8_t)(rsense_val >> 8));
	}

	if (ret)
		return ret;

	dev->iadc_rsense[ch - AD70081Z_E10_WPD_IS0] = rsense_val;
	return ret;
}
