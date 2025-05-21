#include <stdio.h>
#include <common_data.h>

int run_iio_example(void)
{
	struct no_os_uart_desc *uart_desc;
	int ret;
	if ((ret = no_os_uart_init(&uart_desc, &uart_ip)) != 0) {
		return ret;
	}
	no_os_uart_stdio(uart_desc);
	static int print_this = 0;
	for (;;) {
		if (!print_this)
			continue;
		printf("ADALM-MMSC Project 123 \r\n");
	}
	no_os_uart_remove(uart_desc);
	return 0;
}

