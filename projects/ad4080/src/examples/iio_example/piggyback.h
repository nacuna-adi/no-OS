/***************************************************************************//**
 *   @file   ad4080/src/examples/iio_example/piggyback.h
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
#ifndef __PIGGYBACK_H__
#define __PIGGYBACK_H__
#include <stddef.h>

#include <no_os_gpio.h>
#include <no_os_uart.h>
#include <no_os_spi.h>

#include <iio_ad4080.h>
#include <iio_app.h>

struct controller_board_class {
	/* data SPI communication for AD4080 is expected to have an explicit
	 * SS sequence. to support feathers that do not have a second 
	 * SPI with SS signal exposed.*/
	struct no_os_spi_init_param *data_spi_class;
	struct no_os_gpio_init_param *data_spi_ss_class;

	struct no_os_gpio_init_param *osc_40_class;
	struct no_os_gpio_init_param *osc_20_class;
	struct no_os_gpio_init_param *osc_10_class;

	struct no_os_uart_init_param *serial_iio_class;
	struct no_os_gpio_init_param *gp3_class;
	struct no_os_gpio_init_param *gp2_class;
	struct no_os_gpio_init_param *gp1_class;
	struct no_os_spi_init_param *cfg_spi_class;
	struct no_os_uart_init_param *serial_log_class;
};

struct controller_board_desc {
	struct no_os_spi_desc *data_spi;
	struct no_os_gpio_desc *data_spi_ss;

	struct no_os_gpio_desc *osc_40;
	struct no_os_gpio_desc *osc_20;
	struct no_os_gpio_desc *osc_10;

	//struct no_os_uart_desc *serial_iio; // stored in iio_app_desc
	struct no_os_gpio_desc *gp3;
	struct no_os_gpio_desc *gp2;
	struct no_os_gpio_desc *gp1;
	struct no_os_spi_desc *cfg_spi;
	struct no_os_uart_desc *serial_log;
};

/* this is our ad4080_piggyback base class */
struct ad4080_piggyback {
	char *name;

#define PIGGYBACK_PROBED 			(1 << 0)
#define PIGGYBACK_SERIAL_LOG_INITIALIZED 	(1 << 1)
#define PIGGYBACK_GP1_INITIALIZED 		(1 << 2)
#define PIGGYBACK_GP2_INITIALIZED 		(1 << 3)
#define PIGGYBACK_GP3_INITIALIZED 		(1 << 4)
#define PIGGYBACK_OSC40_INITIALIZED 		(1 << 5)
#define PIGGYBACK_OSC20_INITIALIZED 		(1 << 6)
#define PIGGYBACK_OSC10_INITIALIZED 		(1 << 7)
#define PIGGYBACK_DATA_SPI_INITIALIZED 		(1 << 8)
#define PIGGYBACK_DATA_SPI_SS_INITIALIZED 	(1 << 9)
#define PIGGYBACK_IIO_INITIALIZED 		(1 << 10)
#define PIGGYBACK_IIO_APP_INITIALIZED 		(1 << 11)
	uint32_t flags;

	/* ad4080 communications require the following hardware definitions
	 * make sure they are given by the system */
	struct controller_board_class *board_class;
	struct controller_board_desc board_desc;

	struct ad4080_iio_device *iio_dev;
	struct ad4080_init_param *ad4080_init_param;

	struct iio_data_buffer adc_data_buffer;

	struct iio_app_desc *iio_app;
	
	int (*probe)(struct ad4080_piggyback *piggyback);
	int (*remove)(struct ad4080_piggyback *piggyback);

	int (*init)(struct ad4080_piggyback *piggyback);
	void (*exit)(struct ad4080_piggyback *piggyback);
};

#define piggyback_container(ptr, type, member) ({ \
	(type *)((char *)(ptr) - offsetof(type, member)); \
})

int init_piggyback(struct ad4080_piggyback *piggyback);
void exit_piggyback(struct ad4080_piggyback *piggyback);

struct ad4080_piggyback *probe_piggyback(struct controller_board_class *board_class);
void remove_piggyback(struct ad4080_piggyback *piggyback);
int start_piggyback(struct ad4080_piggyback *piggyback);
void stop_piggyback(struct ad4080_piggyback *piggyback);


#endif /* __PIGGYBACK_H__ */
