/***************************************************************************//**
 *   @file   ad4080/src/common/common_data.c
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
#include <common_data.h>

struct no_os_uart_init_param serial_log_class = {
	.device_id = SERIAL_LOG_DEVICE_ID,
	.asynchronous_rx = SERIAL_LOG_ASYNC_RX,
	.baud_rate = SERIAL_LOG_BAUD_RATE,
	.size = SERIAL_LOG_CS,
	.parity = SERIAL_LOG_PARITY,
	.stop = SERIAL_LOG_STOP_BIT,
	.extra = SERIAL_LOG_EXTRA,
	.platform_ops = SERIAL_LOG_OPS,
};

struct no_os_uart_init_param serial_iio_class = {
	.device_id = UART_DEVICE_ID,
	.asynchronous_rx = UART_ASYNC_RX,
	.irq_id = UART_IRQ_ID,
	.baud_rate = UART_BAUD_RATE,
	.size = UART_CS,
	.parity = UART_PARITY,
	.stop = UART_STOP_BIT,
	.extra = UART_EXTRA,
	.platform_ops = UART_OPS,
};

struct no_os_spi_init_param spi_class = {
	.device_id = SPI_DEVICE_ID,
	.max_speed_hz = SPI_SPEED_HZ,
	.chip_select = SPI_CHIP_SELECT,
	.mode = SPI_MODE,
	.bit_order = SPI_BIT_ORDER,
	.lanes = SPI_LANES,
	.extra = SPI_EXTRA,
	.platform_ops = SPI_OPS, 
};

struct no_os_gpio_init_param reset_line_class = {
	.port = RESET_LINE_PORT,
	.number = RESET_LINE_NUM,
	.pull = RESET_LINE_PULL,
	.platform_ops = RESET_LINE_OPS,
	.extra = RESET_LINE_EXTRA,
};

struct no_os_gpio_init_param gpio1_class = {
	.port = GPIO1_PORT,
	.number = GPIO1_NUM,
	.pull = GPIO1_PULL,
	.platform_ops = GPIO1_OPS,
	.extra = GPIO1_EXTRA,
};

struct no_os_gpio_init_param gpio2_class = {
	.port = GPIO2_PORT,
	.number = GPIO2_NUM,
	.pull = GPIO2_PULL,
	.platform_ops = GPIO2_OPS,
	.extra = GPIO2_EXTRA,
};

struct no_os_gpio_init_param gpio3_class = {
	.port = GPIO3_PORT,
	.number = GPIO3_NUM,
	.pull = GPIO3_PULL,
	.platform_ops = GPIO3_OPS,
	.extra = GPIO3_EXTRA,
};

