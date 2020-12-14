# Path to stlink folder for uploading code to board
STM_COMMON=/home/roflu/stm32cube
# Put your source files here (*.c)
SRCS=main.c ringbuf.c io.c stm32l4xx_hal_msp.c stm32l4xx_it.c system_stm32l4xx.c stm32l4xx_nucleo.c stm32l4xx_hal_rcc.c      stm32l4xx_hal_rcc_ex.c  stm32l4xx_hal.c          stm32l4xx_hal_rtc.c stm32l4xx_hal_comp.c           stm32l4xx_hal_rtc_ex.c stm32l4xx_hal_cortex.c              stm32l4xx_hal_spi.c         stm32l4xx_hal_spi_ex.c       stm32l4xx_hal_sram.c stm32l4xx_hal_dma2d.c           stm32l4xx_hal_dma.c            stm32l4xx_hal_tim.c           stm32l4xx_hal_tim_ex.c stm32l4xx_hal_exti.c     stm32l4xx_hal_uart.c stm32l4xx_hal_flash.c          stm32l4xx_hal_uart_ex.c stm32l4xx_hal_flash_ex.c       stm32l4xx_hal_usart.c   stm32l4xx_hal_wwdg.c stm32l4xx_hal_gpio.c      stm32l4xx_hal_adc.c stm32l4xx_hal_adc_ex.c     stm32l4xx_ll_adc.c      stm32l4xx_ll_dma2d.c           stm32l4xx_ll_dma.c       stm32l4xx_ll_exti.c        stm32l4xx_ll_gpio.c         stm32l4xx_ll_i2c.c stm32l4xx_hal_ltdc_ex.c         stm32l4xx_ll_lpuart.c stm32l4xx_hal_mmc_ex.c                 stm32l4xx_ll_pwr.c   stm32l4xx_hal_ospi.c stm32l4xx_hal_pcd.c  stm32l4xx_hal_pcd_ex.c           stm32l4xx_ll_usart.c stm32l4xx_hal_pwr.c            stm32l4xx_ll_usb.c stm32l4xx_hal_pwr_ex.c

# Binaries will be generated with this name (.elf, .bin, .hex)
PROJ_NAME=template

# Compiler settings. Only edit CFLAGS to include other header files.
CC=arm-none-eabi-gcc
OBJCOPY=arm-none-eabi-objcopy

# Compiler flags
CFLAGS  = -g -O2 -Wall --specs=nosys.specs -Tstm32_flash.ld
CFLAGS += -DUSE_STDPERIPH_DRIVER
CFLAGS += -mlittle-endian -mthumb -mcpu=cortex-m4 -mthumb-interwork
CFLAGS += -mfloat-abi=hard -mfpu=fpv4-sp-d16
CFLAGS += -I.
CFLAGS += -DUSE_ADP5301ACBZ -DUSE_STM32L4XX_NUCLEO_64_SMPS

# Include files from STM libraries
CFLAGS += -I$(STM_COMMON)/Drivers/CMSIS/Device/ST/STM32L4xx/Include
CFLAGS += -I$(STM_COMMON)/Drivers/STM32L4xx_HAL_Driver/Inc
CFLAGS += -I$(STM_COMMON)/Drivers/BSP/STM32L4xx_Nucleo
CFLAGS += -I$(STM_COMMON)/Drivers/BSP/Components/Common
CFLAGS += -I$(STM_COMMON)/Drivers/CMSIS/Include

# add startup file to build
SRCS += startup_stm32l452xx.s
OBJS = $(SRCS:.c=.o)

vpath %.c $(STM_COMMON)/Drivers/STM32L4xx_HAL_Driver/Src $(STM_COMMON)/Drivers/BSP/STM32L4xx_Nucleo \

.PHONY: proj

# Commands
all: proj

proj: $(PROJ_NAME).elf

$(PROJ_NAME).elf: $(SRCS)
	$(CC) $(CFLAGS) $^ -o $@
	$(OBJCOPY) -O ihex $(PROJ_NAME).elf $(PROJ_NAME).hex
	$(OBJCOPY) -O binary $(PROJ_NAME).elf $(PROJ_NAME).bin

clean:
	rm -f *.o $(PROJ_NAME).elf $(PROJ_NAME).hex $(PROJ_NAME).bin

# Flash the STM32F4
burn: proj
	openocd -f interface/stlink-v2-1.cfg -c "transport select hla_swd" -f board/st_nucleo_l4.cfg

debug:
	arm-none-eabi-gdb -ex 'target extended-remote localhost:3333' -ex load template.elf
