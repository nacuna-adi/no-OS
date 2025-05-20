#include <maxim_uart.h>

static struct max_uart_init_param uart_extra_ip = {
	.flow = UART_FLOW_DIS
};

struct no_os_uart_init_param uart_ip = {
	.device_id = 1,
	.asynchronous_rx = false,
	.baud_rate = 115200,
	.size = NO_OS_UART_CS_8,
	.parity = NO_OS_UART_PAR_NO,
	.stop = NO_OS_UART_STOP_1_BIT,
	.extra = &uart_extra_ip,
	.platform_ops = &max_uart_ops,
};

