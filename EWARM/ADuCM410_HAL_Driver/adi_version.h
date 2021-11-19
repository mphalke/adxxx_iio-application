/*!
 *****************************************************************************
 * @file:    adi_version.h
 * @brief:   Version macros for ADI ADuCM410
 *-----------------------------------------------------------------------------
 *
Copyright (c) 2010-2018 Analog Devices, Inc. All Rights Reserved.

This software is proprietary to Analog Devices, Inc. and its licensors.
By using this software you agree to the terms of the associated
Analog Devices Software License Agreement.
 ******************************************************************************/

#ifndef __ADI_VERSION_H__
#define __ADI_VERSION_H__

/* use a 32-bit versioning scheme that supports numerical compares */
#define ADI_VERSION_MAJOR               0u     /* must be <= 255 */
#define ADI_VERSION_MINOR               2u     /* must be <= 255 */
#define ADI_VERSION_PATCH               0u     /* must be <= 255 */

#define ADI_CONSTRUCT_VERSION(a,b,c)    (((a) << 16u) | ((b) << 8u) | ((c))

/* known versions */
#define ADI_VERSION_0_1_0               ADI_CONSTRUCT_VERSION(0u, 1u, 0u)
#define ADI_VERSION_0_2_0               ADI_CONSTRUCT_VERSION(0u, 2u, 0u)

/* test current version against known predefines */
#define ADI_VERSION_CURRENT             ADI_CONSTRUCT_VERSION(ADI_VERSION_MAJOR, ADI_VERSION_MINOR, ADI_VERSION_PATCH)

#endif /* __ADI_VERSION_H__ */
