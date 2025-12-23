EXAMPLE ?= iio_example

NO_OS_USB_UART = y
IIOD = y

# change this to whatever external VRef you are using in your project
CUSTOM_VREF = 3300

CFLAGS += -DEXTERNAL_VREF=$(CUSTOM_VREF)

include ../../tools/scripts/generic_variables.mk

include ../../tools/scripts/examples.mk

include src.mk

include ../../tools/scripts/generic.mk
