#ifndef __PARAMETERS_H__
#define __PARAMETERS_H__

#include <maxim_uart.h>
#include <stdbool.h>

#if (TARGET_NUM == 32665)
#define UART_DEVICE_ID 		1
#else
#error "Maxim Target is not yet supported"
#endif

#define UART_ASYNC_RX 	false
#define UART_BAUD_RATE 	115200
#define UART_CS 	NO_OS_UART_CS_8
#define UART_PARITY 	NO_OS_UART_PAR_NO
#define UART_STOP_BIT 	NO_OS_UART_STOP_1_BIT
#define UART_EXTRA 	&max_uart_extra
#define UART_OPS 	&max_uart_ops

extern struct max_uart_init_param max_uart_extra;

#endif /* __PARAMETERS_H__ */
