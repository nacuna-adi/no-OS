/***************************************************************************//**
 *   @file   ad4080/src/platform/maxim/parameters.h
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
#ifndef __PARAMETERS_H__
#define __PARAMETERS_H__

#include <stdbool.h>

#include <no_os_uart.h>
#include <no_os_spi.h>
#include <no_os_gpio.h>

#include <maxim_irq.h>
#include <maxim_uart.h>
#include <maxim_usb_uart.h>
#include <maxim_spi.h>
#include <maxim_gpio.h>

#define SERIAL_LOG_DEVICE_ID 	1
#define SERIAL_LOG_ASYNC_RX 	false
#define SERIAL_LOG_BAUD_RATE 	115200
#define SERIAL_LOG_CS 		NO_OS_UART_CS_8
#define SERIAL_LOG_PARITY 	NO_OS_UART_PAR_NO
#define SERIAL_LOG_STOP_BIT 	NO_OS_UART_STOP_1_BIT
#define SERIAL_LOG_EXTRA 	&serial_log_extra
#define SERIAL_LOG_OPS 		&max_uart_ops

extern struct max_uart_init_param serial_log_extra;

#define INTC_DEVICE_ID 	0

#define UART_DEVICE_ID 	0
#define UART_ASYNC_RX 	true
#define UART_BAUD_RATE 	115200
#define UART_IRQ_ID 	USB_IRQn
#define UART_CS 	NO_OS_UART_CS_8
#define UART_PARITY 	NO_OS_UART_PAR_NO
#define UART_STOP_BIT 	NO_OS_UART_STOP_1_BIT
#define UART_EXTRA 	&max_usb_uart_extra
#define UART_OPS 	&max_usb_uart_ops

extern struct max_usb_uart_init_param max_usb_uart_extra;


#define SPI_DEVICE_ID 	1
#define SPI_SPEED_HZ 	1000000 /* up to 50 Mhz according to ad4080 data sheet */

#define SPI_CHIP_SELECT 0
#define SPI_MODE 	NO_OS_SPI_MODE_3
#define SPI_BIT_ORDER 	NO_OS_SPI_BIT_ORDER_MSB_FIRST
#define SPI_LANES 	NO_OS_SPI_SINGLE_LANE
#define SPI_EXTRA  	&max_spi_extra
#define SPI_OPS 	&max_spi_ops

extern struct max_spi_init_param max_spi_extra;

#define RESET_LINE_PORT 0	
#define RESET_LINE_NUM 	9
#define RESET_LINE_PULL NO_OS_PULL_DOWN
#define RESET_LINE_OPS 	&max_gpio_ops
#define RESET_LINE_EXTRA 	&max_reset_line_extra

extern struct max_gpio_init_param max_reset_line_extra; 


#define GPIO1_PORT 	0
#define GPIO1_NUM 	3
#define GPIO1_PULL 	NO_OS_PULL_NONE
#define GPIO1_OPS 	&max_gpio_ops
#define GPIO1_EXTRA 	&gpiox_extra

#define GPIO2_PORT 	0
#define GPIO2_NUM 	5
#define GPIO2_PULL 	NO_OS_PULL_NONE
#define GPIO2_OPS 	&max_gpio_ops
#define GPIO2_EXTRA 	&gpiox_extra

#define GPIO3_PORT 	0
#define GPIO3_NUM 	4
#define GPIO3_PULL 	NO_OS_PULL_NONE
#define GPIO3_OPS 	&max_gpio_ops
#define GPIO3_EXTRA 	&gpiox_extra

extern struct max_gpio_init_param gpiox_extra;


#define OSC_40M_PORT 	0
#define OSC_40M_NUM 	2
#define OSC_40M_PULL 	NO_OS_PULL_NONE
#define OSC_40M_OPS 	&max_gpio_ops
#define OSC_40M_EXTRA 	&gpiox_extra

#define OSC_20M_PORT 	0
#define OSC_20M_NUM 	1
#define OSC_20M_PULL 	NO_OS_PULL_NONE
#define OSC_20M_OPS 	&max_gpio_ops
#define OSC_20M_EXTRA 	&gpiox_extra

#define OSC_10M_PORT 	0
#define OSC_10M_NUM 	0
#define OSC_10M_PULL 	NO_OS_PULL_NONE
#define OSC_10M_OPS 	&max_gpio_ops
#define OSC_10M_EXTRA 	&gpiox_extra


#endif /* __PARAMETERS_H__ */

