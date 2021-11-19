/*******************************************************************************
 *   @file   ad70081z.h
 *   @brief  Header file for ad70081z Driver.
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
#ifndef AD70081Z_H_
#define AD70081Z_H_

#include <stdint.h>
#include <stdbool.h>
#include <spi.h>
#include <gpio.h>

#define AD70081Z_R1B				(1ul << 16)
#define AD70081Z_R2B				(2ul << 16)
#define AD70081Z_TRANSF_LEN(x)			((x) >> 16)
#define AD70081Z_ADDR(x)			((x) & 0xFFFF)
#define AD70081Z_REG_READ_7(x)			(((x) & 0x7F) | 0x80)
#define AD70081Z_REG_WRITE_7(x)			((x) & 0x7F)
#define AD70081Z_REG_READ_15(x)			(((x) & 0x7FFF) | 0x8000)
#define AD70081Z_REG_WRITE_15(x)		((x) & 0x7FFF)

/* SPI configuration registers */
#define AD70081Z_INTERFACE_CONFIG_A		(AD70081Z_R1B | 0x00)
#define AD70081Z_INTERFACE_CONFIG_B	 	(AD70081Z_R1B | 0x01)
#define AD70081Z_DEVICE_CONFIG 			(AD70081Z_R1B | 0x02)
#define AD70081Z_CHIP_TYPE			(AD70081Z_R1B | 0x03)
#define AD70081Z_PRODUCT_ID_L			(AD70081Z_R1B | 0x04)
#define AD70081Z_PRODUCT_ID_H			(AD70081Z_R1B | 0x05)
#define AD70081Z_CHIP_GRADE			(AD70081Z_R1B | 0x06)
#define AD70081Z_SCRATCH_PAD			(AD70081Z_R1B | 0x0A)
#define AD70081Z_SPI_REVISION			(AD70081Z_R1B | 0x0B)
#define AD70081Z_VENDOR_L			(AD70081Z_R1B | 0x0C)
#define AD70081Z_VENDOR_H			(AD70081Z_R1B | 0x0D)
#define AD70081Z_STREAM_MODE			(AD70081Z_R1B | 0x0E)
#define AD70081Z_INTERFACE_CONFIG_C		(AD70081Z_R1B | 0x10)
#define AD70081Z_INTERFACE_STATUS_A		(AD70081Z_R1B | 0x11)

/* DAC/ADC registers */
#define AD70081Z_REF_CONFIG			(AD70081Z_R1B | 0x15)
#define AD70081Z_IDAC_OUT_SHDN			(AD70081Z_R1B | 0x17)
#define AD70081Z_E25_SOA_ID_0_GND_SWITCH	(AD70081Z_R1B | 0x19)
#define AD70081Z_E25_SOA_ID_1_GND_SWITCH	(AD70081Z_R1B | 0x1B)
#define AD70081Z_CMP_EN				(AD70081Z_R1B | 0x1D)
#define AD70081Z_CMP_MASK0			(AD70081Z_R1B | 0x1F)
#define AD70081Z_CMP_MASK1			(AD70081Z_R1B | 0x20)
#define AD70081Z_CMP_MASK2			(AD70081Z_R1B | 0x21)
#define AD70081Z_CMP_MASK3			(AD70081Z_R1B | 0x22)
#define AD70081Z_HW_LDAC_MASK0			(AD70081Z_R1B | 0x23)
#define AD70081Z_HW_LDAC_MASK1			(AD70081Z_R1B | 0x24)
#define AD70081Z_HW_LDAC_MASK2			(AD70081Z_R1B | 0x25)
#define AD70081Z_HW_LDAC_MASK3			(AD70081Z_R1B | 0x26)
#define AD70081Z_TOGGLE_MODE0			(AD70081Z_R1B | 0x27)
#define AD70081Z_TOGGLE_MODE1			(AD70081Z_R1B | 0x28)
#define AD70081Z_TOGGLE_MODE2			(AD70081Z_R1B | 0x29)
#define AD70081Z_TOGGLE_MODE3			(AD70081Z_R1B | 0x2a)
#define AD70081Z_TOGGLE_CONTROL0		(AD70081Z_R1B | 0x2b)
#define AD70081Z_TOGGLE_CONTROL1		(AD70081Z_R1B | 0x2c)
#define AD70081Z_TOGGLE_CONTROL2		(AD70081Z_R1B | 0x2d)
#define AD70081Z_TOGGLE_CONTROL3		(AD70081Z_R1B | 0x2e)
#define AD70081Z_TOGGLE_ENABLE0			(AD70081Z_R1B | 0x2f)
#define AD70081Z_TOGGLE_ENABLE1			(AD70081Z_R1B | 0x30)
#define AD70081Z_TOGGLE_ENABLE2			(AD70081Z_R1B | 0x31)
#define AD70081Z_TOGGLE_ENABLE3			(AD70081Z_R1B | 0x32)
#define AD70081Z_DAC(ch)			(AD70081Z_R2B | (0x33 + 2 * (ch)))
#define AD70081Z_DAC_PAGE_DATA			(AD70081Z_R2B | 0x6f)
#define AD70081Z_INPUT_A_PAGE_DATA		(AD70081Z_R2B | 0x71)
#define AD70081Z_INPUT_B_PAGE_DATA		(AD70081Z_R2B | 0x73)
#define AD70081Z_DAC_SELECT0			(AD70081Z_R1B | 0x75)
#define AD70081Z_DAC_SELECT1			(AD70081Z_R1B | 0x76)
#define AD70081Z_DAC_SELECT2			(AD70081Z_R1B | 0x77)
#define AD70081Z_DAC_SELECT3			(AD70081Z_R1B | 0x78)
#define AD70081Z_SW_LDAC			(AD70081Z_R1B | 0x7a)
#define AD70081Z_SW_LDAC0_MASK			(AD70081Z_R1B | 0x7c)
#define AD70081Z_SW_LDAC1_MASK			(AD70081Z_R1B | 0x7d)
#define AD70081Z_SW_LDAC2_MASK			(AD70081Z_R1B | 0x7e)
#define AD70081Z_SW_LDAC3_MASK			(AD70081Z_R1B | 0x7f)
#define AD70081Z_INPUT_A(ch)			(AD70081Z_R2B | (0x80 + 2 * (ch)))
#define AD70081Z_INPUT_B(ch)			(AD70081Z_R2B | (0xbc + 2 * (ch)))
#define AD70081Z_I_ADC0_RSENSE			(AD70081Z_R2B | 0xf8)
#define AD70081Z_I_ADC1_RSENSE			(AD70081Z_R2B | 0xf9)
#define AD70081Z_I_ADC2_RSENSE			(AD70081Z_R2B | 0xfa)
#define AD70081Z_I_ADC3_RSENSE			(AD70081Z_R2B | 0xfc)
#define AD70081Z_I_ADC4_RSENSE			(AD70081Z_R2B | 0xfe)
#define AD70081Z_I_ADC5_RSENSE			(AD70081Z_R2B | 0x100)
#define AD70081Z_I_ADC6_RSENSE			(AD70081Z_R2B | 0x102)
#define AD70081Z_I_ADC7_RSENSE			(AD70081Z_R2B | 0x103)
#define AD70081Z_I_ADC_IN_HI_Z			(AD70081Z_R2B | 0x105)
#define AD70081Z_I_ADC_TOND_INPUT_CURRENT_RANGE	(AD70081Z_R2B | 0x107)
#define AD70081Z_ADC_RESULT			(AD70081Z_R2B | 0x109)
#define AD70081Z_CONVST				(AD70081Z_R1B | 0x10c)
#define AD70081Z_ADC_CONFIG			(AD70081Z_R1B | 0x111)

/* AD70081Z_INTERFACE_CONFIG_A */
#define AD70081Z_INTERFACE_CONFIG_A_SW_RESET_MSK		BIT(7) | BIT(0)
#define AD70081Z_INTERFACE_CONFIG_A_SW_RESET(x)			(((x) & 0x1) | 0x80)
#define AD70081Z_INTERFACE_CONFIG_A_ADDR_DIRECTION_MSK		BIT(5)
#define AD70081Z_INTERFACE_CONFIG_A_ADDR_DIRECTION(x)		(((x) & 0x1) << 5)
#define AD70081Z_INTERFACE_CONFIG_A_SDO_EN_MSK			BIT(4) | BIT(3)

/* AD70081Z_INTERFACE_CONFIG_B */
#define AD70081Z_INTERFACE_CONFIG_B_ACCESS_MODE_MSK		BIT(7)
#define AD70081Z_INTERFACE_CONFIG_B_ACCESS_MODE(x)		(((x) & 0x1) << 7)
#define AD70081Z_INTERFACE_CONFIG_B_ADDR_MODE_MSK		BIT(3)
#define AD70081Z_INTERFACE_CONFIG_B_ADDR_MODE(x)		(((x) & 0x1) << 3)

/* AD70081Z_INTERFACE_CONFIG_C */
#define AD70081Z_INTERFACE_CONFIG_C_CRC_MSK			BIT(7) | BIT(6) | BIT(1) | BIT(0)
#define AD70081Z_INTERFACE_CONFIG_C_CRC(x)			(((~x) & 0x3) | (((x) << 6) & 0xC0))
#define AD70081Z_INTERFACE_CONFIG_C_STRICT_REG_ACCESS_MSK	BIT(5)
#define AD70081Z_INTERFACE_CONFIG_C_STRICT_REG_ACCESS(x)	(((x) & 0x1) << 5)
#define AD70081Z_CRC8_POLYNOMIAL				0x7
#define AD70081Z_CRC8_INITIAL_VALUE				0xA5

/* AD70081Z_INTERFACE_STATUS_A */
#define AD70081Z_INTERFACE_STATUS_A_NOT_READY_ERR_MSK		BIT(7)
#define AD70081Z_INTERFACE_STATUS_A_CLOCK_COUNT_ERR_MSK		BIT(4)
#define AD70081Z_INTERFACE_STATUS_A_CRC_ERR_MSK			BIT(3)
#define AD70081Z_INTERFACE_STATUS_A_INVALID_ACCESS_ERR_MSK	BIT(2)
#define AD70081Z_INTERFACE_STATUS_A_PARTIAL_ACCESS_ERR_MSK	BIT(1)
#define AD70081Z_INTERFACE_STATUS_A_ADDR_INVALID_ERR_MSK	BIT(0)

/* AD70081Z_DEVICE_CONFIG */
#define AD70081Z_DEVICE_CONFIG_CUSTOM_MODES_MSK			GENMASK(3, 2)
#define AD70081Z_DEVICE_CONFIG_CUSTOM_MODES(x)			(((x) & 0x3) << 2)
#define AD70081Z_DEVICE_CONFIG_OPERATING_MODES_MSK		GENMASK(1, 0)
#define AD70081Z_DEVICE_CONFIG_OPERATING_MODES(x)		(((x) & 0x3) << 0)

/* AD70081Z_PRODUCT_ID */
#define AD70081Z_PRODUCT_ID_L_VALUE				0x1e
#define AD70081Z_PRODUCT_ID_H_VALUE				0x40

/* AD70081Z_REF_CONFIG */
#define AD70081Z_REF_CONFIG_REFERENCE_SELECTION_MSK		BIT(0)

/* AD70081Z_IDAC_OUT_SHDN */
#define AD70081Z_IDAC_OUT_SHDN_MSK(ch)			(1 << ch)

/* AD70081Z_E25_SOA_ID_0_GND_SWITCH & AD70081Z_E25_SOA_ID_1_GND_SWITCH */
#define AD70081Z_E25_SOA_ID_GND_SWITCH_CMP_TGL_MSK		BIT(3)
#define AD70081Z_E25_SOA_ID_GND_SWITCH_SW_TGL_MSK		BIT(2)
#define AD70081Z_E25_SOA_ID_GND_SWITCH_HW_TGL_MSK		BIT(1)
#define AD70081Z_E25_SOA_ID_GND_SWITCH_EN_MSK			BIT(0)

/* AD70081Z_CMP_EN */
#define AD70081Z_CMP_EN_CMP_EN_MSK				BIT(0)

/* AD70081Z_SW_LDAC */
#define AD70081Z_SW_LDAC_SW_LDAC_EN_MSK				BIT(0)

/* AD70081Z_ADC_CONFIG */
#define AD70081Z_ADC_CONFIG_AFE_MUX_CH_MSK			GENMASK(7,2)
#define AD70081Z_ADC_CONFIG_ADC_OSR_MSK				GENMASK(1,0)

#define AD70081Z_E25_SOA(ch) 					AD70081Z_E25_SOA_##ch
#define AD70081Z_E4_MIR(ch) 					AD70081Z_E4_MIR_##ch
#define AD70081Z_E6_PHTR(ch) 					AD70081Z_E6_PHTR_##ch
#define AD70081Z_E17_SPVOA(ch) 					AD70081Z_E17_SPVOA_##ch
#define AD70081Z_E18_TPVOA(ch) 					AD70081Z_E18_TPVOA_##ch
#define AD70081Z_E16_RPVOA(ch) 					AD70081Z_E16_RPVOA_##ch
#define AD70081Z_E16_RPVOA(ch) 					AD70081Z_E16_RPVOA_##ch
#define AD70081Z_E26_TONF(ch) 					AD70081Z_E26_TONF_##ch

enum ad70081z_channel {
	AD70081Z_E24_GAIN,
	AD70081Z_E25_SOA(0),
	AD70081Z_E25_SOA(1),
	AD70081Z_IDAC_CH_LIMIT,
	AD70081Z_E4_MIR(0) = AD70081Z_IDAC_CH_LIMIT,
	AD70081Z_E4_MIR(1),
	AD70081Z_E6_PHTR(0),
	AD70081Z_E6_PHTR(1),
	AD70081Z_E6_PHTR(2),
	AD70081Z_E6_PHTR(3),
	AD70081Z_E6_PHTR(4),
	AD70081Z_E6_PHTR(5),
	AD70081Z_E6_PHTR(6),
	AD70081Z_E6_PHTR(7),
	AD70081Z_E5_SPH,
	AD70081Z_E17_SPVOA(0),
	AD70081Z_E17_SPVOA(1),
	AD70081Z_E17_SPVOA(2),
	AD70081Z_E17_SPVOA(3),
	AD70081Z_E18_TPVOA(0),
	AD70081Z_E18_TPVOA(1),
	AD70081Z_E16_RPVOA(0),
	AD70081Z_E16_RPVOA(1),
	AD70081Z_E12_WHTR,
	AD70081Z_E8_MZDB,
	AD70081Z_E9_RFPD,
	AD70081Z_E0_TECC,
	AD70081Z_E19_TOND,
	AD70081Z_E26_TONF(0),
	AD70081Z_E26_TONF(1),
	AD70081Z_E22_FSOPD,
	AD70081Z_VDAC_CH_LIMIT
};

enum ad70081z_afe_mux_channel {
	AD70081Z_AFE_MUX_CHANNEL_NOCHANGE,
	AD70081Z_E1_CTHRM_VS,
	AD70081Z_E2_TECC_VS,
	AD70081Z_E3_TECC_VS,
	AD70081Z_E4_MIRS_VS0,
	AD70081Z_E4_MIRS_VS1,
	AD70081Z_E5_SPHS_VS,
	AD70081Z_E7_LHGS_VS,
	AD70081Z_E24_GAINS_VS,
	AD70081Z_E13_WTHRM_VS,
	AD70081Z_E27_ASIG_VS0,
	AD70081Z_E27_ASIG_VS1,
	AD70081Z_E27_ASIG_VS2,
	AD70081Z_E27_ASIG_VS3,
	AD70081Z_E10_WPD_IS0, // is start
	AD70081Z_E10_WPD_IS1,
	AD70081Z_E19_TOND_IS0,
	AD70081Z_E19_TOND_IS1,
	AD70081Z_E19_TOND_IS2,
	AD70081Z_E19_TOND_IS3,
	AD70081Z_E20_TTAP_IS,
	AD70081Z_E21_RTAP_IS, // is end
	AD70081Z_AVDD_3P3V,
	AD70081Z_AVDD_5V,
	AD70081Z_V_ACT_GAIN,
	AD70081Z_V_ACT_SOA0,
	AD70081Z_V_ACT_SOA1,
	AD70081Z_IOVDD = 0x1c,
	AD70081Z_INTERNAL_ADC_VREF,
	AD70081Z_AGND,
	AD70081Z_TEMP0,
	AD70081Z_TEMP0_HCD,
	AD70081Z_TEMP1,
	AD70081Z_TEMP1_HCD,
	AD70081Z_TEMP2,
	AD70081Z_TEMP2_HCD,
	AD70081Z_TEMP3,
	AD70081Z_TEMP3_HCD,
	AD70081Z_E25_SOA_VS0,
	AD70081Z_E25_SOA_VS1,
	AD70081Z_EXIT_CONT = 0x3a,
	AD70081Z_NO_CHANGE = 0xff
};

enum ad70081z_adc_config_osr {
	AD70081Z_ADC_CONFIG_OSR_NO_OVERSAMPLING = 0,
	AD70081Z_ADC_CONFIG_OSR_OVERSAMPLING_X_4,
	AD70081Z_ADC_CONFIG_OSR_OVERSAMPLING_X_16,
	AD70081Z_ADC_CONFIG_OSR_OVERSAMPLING_X_64
};

enum ad70081z_iadc_range {
	AD70081Z_IADC_RANGE_6p25_50uA,
	AD70081Z_IADC_RANGE_1p25_10uA,
	AD70081Z_IADC_RANGE_5_40uA
};

enum ad70081z_input {
	AD70081Z_INPUT_A = 0,
	AD70081Z_INPUT_B,
	AD70081Z_INPUT_COUNT
};

enum ad70081z_custom_mode {
	AD70081Z_REGISTER_ACCESS_MODE = 0,
	AD70081Z_ADC_CONTINUOUS_CONVERSION_MODE
};

struct ad70081z_device_spi_settings {
	bool addr_ascension;
	bool short_instruction;
	bool crc_enabled;
};

struct ad70081z_idac_gsc_config {
	bool cmp_tgl; /** Comp Function Triggering Ground Switch Closing */
	bool sw_tgl; /** SW Toggle Triggering Ground Switch Closing */
	bool hw_tgl; /** HW Toggle Triggering Ground Switch Closing */
	bool en; /** Ground Switch Closing */
};

struct ad70081z_dev {
	/* SPI */
	spi_desc				*spi_desc;

	/* Digital GPIO interface */
	gpio_desc				*gpio_reset_n;
	gpio_desc				*gpio_ldac_n;
	gpio_desc				*gpio_tgp;
	bool					gpio_tgp_state;
	gpio_desc				*gpio_convst;

	/* Device SPI Settings */
	struct ad70081z_device_spi_settings	dev_spi_settings;
	/* Device Modes */
	enum ad70081z_custom_mode		custom_mode;
	/* Driver specific */
	bool					endianess;
	enum ad70081z_adc_config_osr		osr;
	/* IADC current sense values */
	uint16_t iadc_rsense[8];
	/* IADC current range values for TOND_ISx channels */
	enum ad70081z_iadc_range idac_current_range[4];
};

struct ad70081z_init_param {
	/* SPI */
	spi_init_param				spi_init;

	/* Digital GPIO interface */
	gpio_init_param				*gpio_reset_n;
	gpio_init_param				*gpio_ldac_n;
	gpio_init_param				*gpio_tgp;
	gpio_init_param				*gpio_convst;

	/* Device SPI Settings */
	struct ad70081z_device_spi_settings	dev_spi_settings;
	/* Device Modes */
	enum ad70081z_custom_mode		custom_mode;
	/* Oversampling ratio  */
	enum ad70081z_adc_config_osr	osr;
	/* Enable/Disable internal reference source */
	bool enable_internal_reference;
	/* IADC current sense values */
	uint16_t iadc_rsense[8];
	/* IADC current range values for TOND_ISx channels */
	enum ad70081z_iadc_range idac_tond_is_current_range[4];
};

/* Device */
int ad70081z_init(struct ad70081z_dev **device,
		  const struct ad70081z_init_param *init_param);
void ad70081z_remove(struct ad70081z_dev *dev);

/* SPI */
int ad70081z_spi_reg_read(struct ad70081z_dev *dev,
			  uint32_t reg_addr,
			  uint32_t *reg_data);
int ad70081z_spi_reg_write(struct ad70081z_dev *dev,
			   uint32_t reg_addr,
			   uint32_t reg_data);
int ad70081z_spi_reg_write_mask(struct ad70081z_dev *dev,
				uint32_t reg_addr,
				uint32_t mask,
				uint32_t data);
int ad70081z_set_device_spi(struct ad70081z_dev *dev,
			    const struct ad70081z_device_spi_settings *spi_settings);
int ad70081z_set_device_config(struct ad70081z_dev *dev,
			       enum ad70081z_custom_mode custom_mode);
int ad70081z_get_interface_status(struct ad70081z_dev *dev,
				  uint8_t *status);
int ad70081z_get_device_status(struct ad70081z_dev *dev,
			       uint8_t *status);
int ad70081z_hardware_reset(struct ad70081z_dev *dev);
int ad70081z_software_reset(struct ad70081z_dev *dev);

/* DAC */
int ad70081z_set_reference(struct ad70081z_dev *dev, bool internal);
int ad70081z_idac_config(struct ad70081z_dev *dev, enum ad70081z_channel ch,
			 bool enable, struct ad70081z_idac_gsc_config *config);
int ad70081z_set_dac_value(struct ad70081z_dev *dev, uint16_t dac_value,
			   enum ad70081z_channel channel);
int ad70081z_set_dac_input(struct ad70081z_dev *dev, uint16_t dac_input,
			   enum ad70081z_input input, enum ad70081z_channel channel);
int ad70081z_set_idac_shutdown(struct ad70081z_dev *dev,
			       enum ad70081z_channel chn, bool enable);
int ad70081z_set_compare(struct ad70081z_dev *dev, bool enable);
int ad70081z_set_compare_mask(struct ad70081z_dev *dev,
			      enum ad70081z_channel ch,
			      bool mask);
int ad70081z_set_hw_ldac_mask(struct ad70081z_dev *dev,
			      enum ad70081z_channel ch,
			      bool mask);
int ad70081z_set_toggle_mode(struct ad70081z_dev *dev, enum ad70081z_channel ch,
			     bool software);
int ad70081z_set_toggle_control(struct ad70081z_dev *dev,
				enum ad70081z_channel ch,
				bool state);
int ad70081z_set_toggle_enable(struct ad70081z_dev *dev,
			       enum ad70081z_channel ch,
			       bool enable);
int ad70081z_set_dac_select(struct ad70081z_dev *dev, enum ad70081z_channel ch,
			    bool copy);
int ad70081z_set_sw_ldac(struct ad70081z_dev *dev, bool enable);
int ad70081z_set_sw_ldac_mask(struct ad70081z_dev *dev,
			      enum ad70081z_channel ch,
			      bool enable);
int ad70081z_ldac(struct ad70081z_dev *dev);
int ad70081z_toggle(struct ad70081z_dev *dev);

/* ADC */
int ad70081z_adc_convst(struct ad70081z_dev *dev);
void ad70081z_adc_set_osr(struct ad70081z_dev *dev,
			  enum ad70081z_adc_config_osr osr);
int ad70081z_adc_set_config(struct ad70081z_dev *dev,
			    enum ad70081z_afe_mux_channel ch);
int ad70081z_adc_read(struct ad70081z_dev *dev,
		      enum ad70081z_afe_mux_channel ch, uint16_t *data);
int ad70081z_cc_start(struct ad70081z_dev *dev);
int ad70081z_cc_exit(struct ad70081z_dev *dev);
int ad70081z_cc_read(struct ad70081z_dev *dev,
		     enum ad70081z_afe_mux_channel *nextch, uint16_t *data);
int ad70081z_iadc_enable(struct ad70081z_dev *dev,
			 enum ad70081z_afe_mux_channel ch, bool enable);
int ad70081z_iadc_config(struct ad70081z_dev *dev,
			 enum ad70081z_afe_mux_channel ch, enum ad70081z_iadc_range range);
int ad70081z_iadc_rsense_config(struct ad70081z_dev *dev,
				enum ad70081z_afe_mux_channel ch, uint16_t rsense_val);

#endif /* AD70081Z_H_ */
