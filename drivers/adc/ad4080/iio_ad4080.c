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
	ad4080_iiodev->iio_dev = NULL;

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

