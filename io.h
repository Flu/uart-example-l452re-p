#ifndef __IO_H
#define __IO_H

#include "stm32l4xx_hal_conf.h"
#include "stm32l4xx_hal.h"
#include "stm32l4xx_nucleo.h"

#include <stdlib.h>
#include <stdio.h>
#include <stdarg.h>
#include "main.h"
#include "ringbuf.h"

UART_HandleTypeDef UartHandle;

void InitIO(void);
void printk(const char*, ...);
void scank(const uint8_t*, ...);

#endif
