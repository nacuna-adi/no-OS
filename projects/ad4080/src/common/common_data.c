#include <common_data.h>

struct no_os_uart_init_param uart_ip = {
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

