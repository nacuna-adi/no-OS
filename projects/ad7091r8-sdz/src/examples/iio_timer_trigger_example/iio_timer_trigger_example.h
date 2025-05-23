/***************************************************************************//**
 *   @file   iio_timer_trigger_example.h
 *   @brief  IIO timer trigger example header for ad7091r8-sdz project
 *   @author Marcelo Schmitt (marcelo.schmitt@analog.com)
********************************************************************************
 * Copyright 2024(c) Analog Devices, Inc.
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
#ifndef __AD7091R8_IIO_TIMER_TRIGGER_EXAMPLE_H__
#define __AD7091R8_IIO_TIMER_TRIGGER_EXAMPLE_H__

#ifdef AD7091R2_DEV
#define ADC_CHANNELS 2
#elif defined AD7091R4_DEV
#define ADC_CHANNELS 4
#else
#define ADC_CHANNELS 8
#endif

#ifndef IIO_DATA_BUFFER_SIZE
#define IIO_DATA_BUFFER_SIZE (400 * ADC_CHANNELS * sizeof(int32_t))
#endif

//extern uint16_t *ad7091r8_data_buffer;

int iio_timer_trigger_example_main();

#endif /* __AD7091R8_IIO_TIMER_TRIGGER_EXAMPLE_H__ */
