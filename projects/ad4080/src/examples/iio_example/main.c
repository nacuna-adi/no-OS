#include <stdio.h>
#include <peripherals.h>

int main(void)
{
	struct no_os_uart_desc *uart_desc;
	int ret;
	if ((ret = no_os_uart_init(&uart_desc, &uart_ip)) != 0) {
		return ret;
	}
	no_os_uart_stdio(uart_desc);
	printf("ADALM-MMSC Project\r\n");
	no_os_uart_remove(uart_desc);
	return 0;
}

