/***************************************************************************//**
 *   @file   ad4080/src/examples/iio_example/piggyback.c
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
#include <stdio.h>

#include <no_os_alloc.h>

#include <piggyback.h>
#include <ardz.h>

/* collect all piggyback boards here. currently we only have 1. ARDZ */
struct ad4080_piggyback *piggybacks[] = {
	&ardz_piggyback.gen_piggyback,
	NULL, /* end sentinel */
};

static struct ad4080_init_param default_ad4080_init_param = {
	//.spi_init = NULL,
	.spi3wire = false,
	.addr_asc = AD4080_ADDR_INCR,
	.single_instr = AD4080_SINGLE_INST,
	.short_instr = AD4080_15_BIT_ADDR,
	.strict_reg = AD4080_REG_NORMAL_MODE,
	.intf_chk_en = AD4080_DATA,
	.cnv_spi_lvds_lanes = AD4080_ONE_LANE,
	.conv_data_spi_lvds = AD4080_CONV_DATA_SPI,
	.lvds_cnv_clk_cnt = 0,
	.lvds_self_clk_mode = AD4080_SELF_CLK_MODE,
	.cnv_clk_mode = AD4080_CNV_CMOS_MODE,
	.lvds_vod = AD4080_185mVPP,
	.ana_dig_ldo_pd = AD4080_AD_LDO_EN,
	.intf_ldo_pd = AD4080_INTF_LDO_EN,
	.fifo_mode = AD4080_FIFO_DISABLE,
	.op_mode = AD4080_OP_NORMAL,
	.gpio_op_enable = {
		AD4080_GPIO_OUTPUT,
		AD4080_GPIO_INPUT, 
		AD4080_GPIO_INPUT,
	},
	.gpio_op_func_sel = {
		AD4080_GPIO_ADI_NSPI_SDO_DATA,
		AD4080_GPIO_ADI_NSPI_SDO_DATA,
		AD4080_GPIO_ADI_NSPI_SDO_DATA,
	},
};

/* piggyback implementers should call this to initialize the piggyback
 * system on your piggyback object */
int piggyback_init(struct ad4080_piggyback *piggyback)
{
	no_os_uart_init(&piggyback->board_desc.serial_log, 
			piggyback->board_class->serial_log_class);
	no_os_uart_stdio(piggyback->board_desc.serial_log);

	/* initialize the side band GPIOs (1 output, 2 input , 3 input) */
	no_os_gpio_get(&piggyback->board_desc.gp1,
			piggyback->board_class->gp1_class);
	no_os_gpio_direction_output(piggyback->board_desc.gp1,
			NO_OS_GPIO_LOW);
	
	no_os_gpio_get(&piggyback->board_desc.gp2,
			piggyback->board_class->gp2_class);
	no_os_gpio_direction_input(piggyback->board_desc.gp2);
	
	no_os_gpio_get(&piggyback->board_desc.gp3,
			piggyback->board_class->gp3_class);
	no_os_gpio_direction_input(piggyback->board_desc.gp3);


	piggyback->flags |= PIGGYBACK_PREINITIALIZED;
	
	return 0;
}

/* given a list of supported piggybacks, lets try to probe them 1 by 1
 * until one of them responds - then we have found a supported piggyback that
 * is plugged in to us */
struct ad4080_piggyback *
	probe_piggyback(struct controller_board_class *board_class)
{
	struct ad4080_piggyback **piggybackpp;
	for (piggybackpp = piggybacks; *piggybackpp != NULL; piggybackpp += 1) {
		int ret = -1;
		struct ad4080_piggyback *piggyback = *piggybackpp;
		piggyback->board_class = board_class;
		piggyback->flags = 0;
		if (piggyback->probe)
			ret = piggyback->probe(piggyback);
		if (ret == -1) {
			continue;
		}
		piggyback->flags |= PIGGYBACK_PROBED;
		printf("%s found!\r\n", piggyback->name);
		break;
	}
	return *piggybackpp;
}

int start_piggyback(struct ad4080_piggyback *piggyback)
{
	int ret;

	/* provide an opportunity for the piggyback to run 
	 * some initialization. if any. */
	if (piggyback && piggyback->init) {
		ret = piggyback->init(piggyback);
		if (ret) {
			return ret;
		}
		piggyback->flags |= PIGGYBACK_INITIALIZED;
	}

	/* now prepare iio stuff */
	struct iio_app_init_param app_init_param = {0};

	if (piggyback->ad4080_init_param == NULL)
		piggyback->ad4080_init_param = &default_ad4080_init_param;
	piggyback->ad4080_init_param->spi_init = piggyback->board_class->cfg_spi_class;
	ret = ad4080_iio_init(&piggyback->iio_dev,
			      piggyback->ad4080_init_param);
	if (ret) {
		return ret;
	}
	piggyback->flags |= PIGGYBACK_IIO_INITIALIZED;

	/* initialize the adc data buffer */
	piggyback->adc_data_buffer.size = 65536;
	piggyback->adc_data_buffer.buff = no_os_malloc(piggyback->adc_data_buffer.size);
	if(piggyback->adc_data_buffer.buff == NULL) {
		return -ENOMEM;
	}
	struct iio_app_device iio_app_devices[] = {
		IIO_APP_DEVICE("NACUNA_ad4080_demo", piggyback->iio_dev->ad4080,
				piggyback->iio_dev->iio_dev, 
				&piggyback->adc_data_buffer, 
				NULL, NULL),
	};
	app_init_param.devices = iio_app_devices;	
	app_init_param.nb_devices = 1;
	app_init_param.uart_init_params = *piggyback->board_class->serial_iio_class;
	ret = iio_app_init(&piggyback->iio_app, app_init_param);
	if (ret)
		return ret;

	piggyback->flags |= PIGGYBACK_IIO_APP_INITIALIZED;
	return iio_app_run(piggyback->iio_app);
}

void stop_piggyback(struct ad4080_piggyback *piggyback)
{
	if ((piggyback->flags & PIGGYBACK_IIO_APP_INITIALIZED) == PIGGYBACK_IIO_APP_INITIALIZED) {
		iio_app_remove(piggyback->iio_app);
		no_os_free(piggyback->adc_data_buffer.buff);
		piggyback->flags &= ~(PIGGYBACK_IIO_INITIALIZED);
	}

	if ((piggyback->flags & PIGGYBACK_IIO_INITIALIZED) == PIGGYBACK_IIO_INITIALIZED) {
		ad4080_iio_remove(piggyback->iio_dev);
		piggyback->flags &= ~(PIGGYBACK_IIO_INITIALIZED);
	}

	if ((piggyback->flags & PIGGYBACK_INITIALIZED) == PIGGYBACK_INITIALIZED) {
		if (piggyback->exit)
			piggyback->exit(piggyback);
		piggyback->flags &= ~(PIGGYBACK_INITIALIZED);
	}
	return;
}

void remove_piggyback(struct ad4080_piggyback *piggyback)
{
	if ((piggyback->flags & PIGGYBACK_PROBED) == PIGGYBACK_PROBED) {
		if (piggyback->remove)
			piggyback->remove(piggyback);
		piggyback->flags = piggyback->flags & ~(PIGGYBACK_PROBED);
	}
	
	if ((piggyback->flags & PIGGYBACK_PREINITIALIZED) == PIGGYBACK_PREINITIALIZED) {
		no_os_uart_remove(piggyback->board_desc.serial_log);
		piggyback->flags = piggyback->flags & ~(PIGGYBACK_PREINITIALIZED);
	}
	return;
}

