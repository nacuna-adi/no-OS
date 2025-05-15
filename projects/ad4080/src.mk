AD4080_SRC_DIR:=$(PROJECT)/src

include $(AD4080_SRC_DIR)/examples/$(TARGET_EXAMPLE)/example.mk
include $(AD4080_SRC_DIR)/platform/$(PLATFORM)/platform.mk

# pull in our platform agnostic peripheral descriptors
INCS += $(AD4080_SRC_DIR)/common/peripherals.h

# pull in no-OS facilities we will need... depending on the example
AD4080_SRCS-$(NOOS_UART) += $(DRIVERS)/api/no_os_uart.c
AD4080_INCS-$(NOOS_UART) += $(INCLUDE)/no_os_uart.h

AD4080_SRCS-$(NOOS_LF256_FIFO) += $(NO-OS)/util/no_os_lf256fifo.c
AD4080_INCS-$(NOOS_LF256_FIFO) += $(INCLUDE)/no_os_lf256fifo.h

AD4080_INCS-$(NOOS_ERROR) += $(INCLUDE)/no_os_error.h

AD4080_SRCS-$(NOOS_MUTEX) += $(NO-OS)/util/no_os_mutex.c
AD4080_INCS-$(NOOS_MUTEX) += $(INCLUDE)/no_os_mutex.h

AD4080_SRCS-$(NOOS_UTIL) += $(NO-OS)/util/no_os_util.c
AD4080_INCS-$(NOOS_UTIL) += $(INCLUDE)/no_os_util.h

AD4080_SRCS-$(NOOS_IRQ) += $(NO-OS)/drivers/api/no_os_irq.c
AD4080_INCS-$(NOOS_IRQ) += $(INCLUDE)/no_os_irq.h

AD4080_SRCS-$(NOOS_LIST) += $(NO-OS)/util/no_os_list.c
AD4080_INCS-$(NOOS_LIST) += $(INCLUDE)/no_os_list.h

AD4080_SRCS-$(NOOS_ALLOC) += $(NO-OS)/util/no_os_alloc.c
AD4080_INCS-$(NOOS_ALLOC) += $(INCLUDE)/no_os_alloc.h

AD4080_SRCS-$(NOOS_DMA) += $(NO-OS)/drivers/api/no_os_dma.c
AD4080_INCS-$(NOOS_DMA) += $(INCLUDE)/no_os_dma.h

SRCS += $(AD4080_SRCS-y)
INCS += $(AD4080_INCS-y)
