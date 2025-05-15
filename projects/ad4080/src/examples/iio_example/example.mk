SRCS += $(PROJECT)/src/examples/iio_example/main.c

# turn on the following drivers when targetting IIO_EXAMPLE
NOOS_UART=y
NOOS_ERROR=y
NOOS_UART_STDIO=y
NOOS_LF256_FIFO=y
NOOS_MUTEX=y
NOOS_UTIL=y
NOOS_IRQ=y
NOOS_LIST=y
NOOS_ALLOC=y
NOOS_DMA=y

# turn on the following platform drivers also
PLATFORM_UART_STDIO=y
PLATFORM_MAXIM_UART=y
PLATFORM_MAXIM_IRQ=y
PLATFORM_MAXIM_DMA=y

