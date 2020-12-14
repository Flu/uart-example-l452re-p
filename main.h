#ifndef __MAIN_H
#define __MAIN_H

/** HAL Library Includes **/
#include "stm32l4xx_hal_conf.h"
#include "stm32l4xx_hal.h"
#include "stm32l4xx_nucleo.h"

/** Utilities and other libraries **/
#include "ringbuf.h"
#include "io.h"

/** Defines for the UART module - if you change the UART, you only have to change here **/
#define USARTx LPUART1
#define USARTx_CLK_ENABLE() __HAL_RCC_LPUART1_CLK_ENABLE()
#define USARTx_RX_GPIO_CLK_ENABLE() __HAL_RCC_GPIOA_CLK_ENABLE()
#define USARTx_TX_GPIO_CLK_ENABLE() __HAL_RCC_GPIOA_CLK_ENABLE()

#define USARTx_FORCE_RESET() __HAL_RCC_LPUART1_FORCE_RESET()
#define USARTx_RELEASE_RESET() __HAL_RCC_LPUART1_RELEASE_RESET()

/** Defines for pin locations and ports for RX/TX of used UART **/
#define USARTx_TX_PIN GPIO_PIN_2
#define USARTx_TX_GPIO_PORT GPIOA
#define USARTx_TX_AF GPIO_AF8_LPUART1
#define USARTx_RX_PIN GPIO_PIN_3
#define USARTx_RX_GPIO_PORT GPIOA
#define USARTx_RX_AF GPIO_AF8_LPUART1

#define USARTx_IRQn LPUART1_IRQn
#define USARTx_IRQHandler LPUART1_IRQHandler
  
#define RTC_ASYNCH_PREDIV 0x7F
#define RTC_SYNCH_PREDIV 0xF9
  
#endif // _MAIN_H
