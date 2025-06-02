CFLAGS += -D IIO_EXAMPLE

SRCS += $(PROJECT)/src/examples/main.c

SRCS += $(PROJECT)/src/examples/iio_example/iio_example.c \
	$(PROJECT)/src/examples/iio_example/piggyback.c \
	$(PROJECT)/src/examples/iio_example/ardz.c

INCS += $(PROJECT)/src/examples/iio_example/iio_example.h \
	$(PROJECT)/src/examples/iio_example/piggyback.h \
	$(PROJECT)/src/examples/iio_example/ardz.h


SRCS += $(DRIVERS)/adc/ad4080/iio_ad4080.c \
	$(DRIVERS)/adc/ad4080/ad4080.c

INCS += $(DRIVERS)/adc/ad4080/iio_ad4080.h \
	$(DRIVERS)/adc/ad4080/ad4080.h

SRC_DIRS += $(NO_OS)/iio/iio_app
