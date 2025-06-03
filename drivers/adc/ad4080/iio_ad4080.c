/***************************************************************************//**
 *   @file   ad4080.c
 *   @brief  Implementation of AD4080 IIO Driver.
 *   @author Niel Anthony Acuna (niel.acuna@analog.com)
********************************************************************************
 * Copyright 2023(c) Analog Devices, Inc.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are met:
 *
 * 1. Redistributions of source code must retain the above copyright notice,
 *    this list of conditions and the following disclaimer.
 *
 * 2. Redistributions in binary form must reproduce the above copyright notice,
 *    this list of conditions and the following disclaimer in the documentation
 *    and/or other materials provided with the distribution.
 *
 * 3. Neither the name of Analog Devices, Inc. nor the names of its
 *    contributors may be used to endorse or promote products derived from this
 *    software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY ANALOG DEVICES, INC. “AS IS” AND ANY EXPRESS OR
 * IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF
 * MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO
 * EVENT SHALL ANALOG DEVICES, INC. BE LIABLE FOR ANY DIRECT, INDIRECT,
 * INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
 * LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA,
 * OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF
 * LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING
 * NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE,
 * EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
*******************************************************************************/
#include <errno.h>
#include "iio_ad4080.h"

#include "no_os_alloc.h"


static int iio_ad4080_attr_get(void *device, char *buf, uint32_t len,
			       const struct iio_ch_info *channel, intptr_t priv);

static int iio_ad4080_attr_set(void *device, char *buf, uint32_t len,
			       const struct iio_ch_info *channel, intptr_t priv);
static int32_t iio_ad4080_debug_reg_read(void *dev, uint32_t reg, 
					 uint32_t *read_val);
static int32_t iio_ad4080_debug_reg_write(void *dev, uint32_t reg, 
					  uint32_t write_val);

enum ad4080_attribute_id {
	RAW_ATTR_ID,
	SCALE_ATTR_ID,
	OFFSET_ATTR_ID,
};

static struct iio_attribute ad4080_iio_ch_attributes[] = {
	{
		.name = "raw",
		.priv = RAW_ATTR_ID,
		.show = iio_ad4080_attr_get,
		.store = iio_ad4080_attr_set,
		
	},
	{
		.name = "scale",
		.priv = SCALE_ATTR_ID,
		.show = iio_ad4080_attr_get,
		.store = iio_ad4080_attr_set,
	},
	{
		.name = "offset",
		.priv = OFFSET_ATTR_ID,
		.show = iio_ad4080_attr_get,
		.store = iio_ad4080_attr_set,
	},
	{0}, /* end sentinel */
};

static struct scan_type ad4080_iio_scan_type = {
	.sign = 's',
	.realbits = 20,
	.storagebits = 32,
	.shift = 0,
	.is_big_endian = false, 
};

static struct iio_channel iio_ad4080_channel = {
	.name = "voltage0",
	.ch_type = IIO_VOLTAGE,
	.channel = 0,
	.scan_index = 0,
	.indexed = true,
	.scan_type = &ad4080_iio_scan_type,
	.ch_out = false,
	.attributes = ad4080_iio_ch_attributes,
};

static struct iio_device ad4080_iiodev_template = {
	.num_ch = 1,
	.channels = &iio_ad4080_channel,
	.attributes = NULL,
	.submit = NULL,//iio_ad4080_submit_samples,
	.pre_enable = NULL,//iio_ad4080_prepare_transfer,
	.post_disable = NULL,//iio_ad4080_end_transfer,
	.read_dev = NULL,
	.write_dev = NULL,
	.debug_reg_read = iio_ad4080_debug_reg_read,
	.debug_reg_write = iio_ad4080_debug_reg_write,
};

static int32_t iio_ad4080_debug_reg_read(void *dev,
		uint32_t reg,
		uint32_t *read_val)
{
	if (!dev || !read_val) { //|| (reg > AD4080_LAST_REG_ADDR)) {
		return -EINVAL;
	}
	return ad4080_read(dev, reg, (uint8_t *)read_val);
}

static int32_t iio_ad4080_debug_reg_write(void *dev,
		uint32_t reg,
		uint32_t write_val)
{
	if (!dev) { //}|| (reg > AD4080_LAST_REG_ADDR)) {
		return -EINVAL;
	}
	return ad4080_write(dev, reg, write_val);
}

static unsigned long tmp_raw_value = 1024;
static unsigned long tmp_scale_value = 2048;
static unsigned long tmp_offset_value = 4096;

static int iio_ad4080_attr_get(void *device,
			       char *buf,
			       uint32_t len,
			       const struct iio_ch_info *channel,
			       intptr_t priv)
{


	switch (priv) {
	case RAW_ATTR_ID:
		return sprintf(buf, "%ld", tmp_raw_value);
	case SCALE_ATTR_ID:
		return sprintf(buf, "%ld", tmp_scale_value);
	case OFFSET_ATTR_ID:
		return sprintf(buf, "%ld", tmp_offset_value);
	default:
		break;
	}
	return len;
}

static int iio_ad4080_attr_set(void *device,
			       char *buf,
			       uint32_t len,
			       const struct iio_ch_info *channel,
			       intptr_t priv)
{
	switch (priv) {
	case RAW_ATTR_ID:
	case SCALE_ATTR_ID:
	case OFFSET_ATTR_ID:
	default:
		break;
	}
	return len;
}

int ad4080_iio_init(struct ad4080_iio_device **iio_dev,
		    struct ad4080_init_param *init_param)
{
	struct ad4080_iio_device *ad4080_iiodev;
	int ret;

	/* allocate our instance */
	ad4080_iiodev = no_os_calloc(1, sizeof *ad4080_iiodev);
	if (!ad4080_iiodev)
		return -ENOMEM;

	/* fill in the device instance */
	ret = ad4080_init(&ad4080_iiodev->ad4080, *init_param);
	if (ret)
		goto error_setup;

	/* fill in the IIO device descriptor */
	ad4080_iiodev->iio_dev = &ad4080_iiodev_template;

	*iio_dev = ad4080_iiodev;
	return 0;

error_setup:
	no_os_free(ad4080_iiodev);
	return ret;
}

int ad4080_iio_remove(struct ad4080_iio_device *iiodev)
{
	int ret;
	if ((ret = ad4080_remove(iiodev->ad4080)) == 0) {
		no_os_free(iiodev);
	}
	return ret;
}

