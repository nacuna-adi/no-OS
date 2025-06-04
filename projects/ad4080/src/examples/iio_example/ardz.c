/***************************************************************************//**
 *   @file   ad4080/src/examples/iio_example/ardz.c
 *   @brief  Parameters Definitions.
 *   @author Niel Acuna (niel.acuna@analog.com)
 *           Marc Paolo Sosa (marcpaolo.sosa@analog.com)
********************************************************************************
 * Copyright 2021(c) Analog Devices, Inc.
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
#include <no_os_delay.h>
#include <common_data.h>
#include <ardz.h>

static int ardz_probe(struct ad4080_piggyback *piggyback)
{
	struct ardz_piggyback *ardz;

	ardz = piggyback_container(piggyback, struct ardz_piggyback, gen_piggyback);

	/* reset the ardz board. this is for debugging purposes for the 
	 * time being */
	no_os_gpio_get(&ardz->reset_line, ardz->reset_line_class);
	no_os_gpio_direction_output(ardz->reset_line, NO_OS_GPIO_LOW);
	no_os_gpio_set_value(ardz->reset_line, NO_OS_GPIO_LOW);
	no_os_mdelay(500);
	no_os_gpio_set_value(ardz->reset_line, NO_OS_GPIO_HIGH);
	no_os_mdelay(500);

	/* interface with the ACE discovery sequence here 
	 * (if such a library exists). for now, its always assumed
	 * that we are connected to an ardz board so return success. */

	return 0;
}

static int ardz_init(struct ad4080_piggyback *piggyback)
{
	return init_piggyback(piggyback);
}

static void ardz_exit(struct ad4080_piggyback *piggyback)
{
	exit_piggyback(piggyback);
	return;
}

static int ardz_remove(struct ad4080_piggyback *piggyback)
{
	struct ardz_piggyback *ardz;
	ardz = piggyback_container(piggyback, struct ardz_piggyback, gen_piggyback);
	
	/* power down the line prior to removing it */
	no_os_gpio_set_value(ardz->reset_line, NO_OS_GPIO_LOW);
	no_os_gpio_remove(ardz->reset_line);
	return 0;
}

struct ardz_piggyback ardz_piggyback = {
	.gen_piggyback = {
		.name = "EVAL-AD4080ARDZ",
		.probe = ardz_probe,
		.remove = ardz_remove,
		.init = ardz_init,
		.exit = ardz_exit,
	},

	.reset_line_class = &reset_line_class,
};

