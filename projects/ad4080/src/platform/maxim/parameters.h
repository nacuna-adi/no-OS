#ifndef __PARAMETERS_H__
#define __PARAMETERS_H__

#include <maxim_uart.h>
#include <maxim_usb_uart.h>
#include <stdbool.h>

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

#endif /* __PARAMETERS_H__ */
