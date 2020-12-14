#include "io.h"

RingBuf outBuffer;
RingBuf inBuffer;

static void Error_Handler(void);
static void InitUartHandle(void);

void InitIO(void) {
  ringbuf_init(&outBuffer);
  ringbuf_init(&inBuffer);
  InitUartHandle();
}

void printk(const char* format, ...) {
  if (format == NULL || format[0] == '\0') {
	return;
  }

  char va_buffer[RING_BUFFER_SIZE];
  va_list(args);
  va_start(args, format);
  vsnprintf(va_buffer, RING_BUFFER_SIZE, format, args);
  va_end(args);

  HAL_NVIC_DisableIRQ(USARTx_IRQn);
  uint8_t i = 0;
  while (ringbuf_add(&outBuffer, va_buffer[i]) != -1 && va_buffer[i+1] != '\0') {
	i++;
  }
  HAL_NVIC_EnableIRQ(USARTx_IRQn);
  
  uint8_t dummy_char = '\0';
  while (UartHandle.gState != HAL_UART_STATE_READY);
  HAL_UART_Transmit_IT(&UartHandle, &dummy_char, 1);
}

void HAL_UART_TxCpltCallback(UART_HandleTypeDef *UartHandle) {
  if (ringbuf_empty(&outBuffer) == 0) {
	uint8_t next_char;
	ringbuf_peek(&outBuffer, &next_char);
	
	if (HAL_UART_Transmit_IT(UartHandle, &next_char, 1) == HAL_ERROR) {
	  Error_Handler();
	}
  }
}

void scank(const uint8_t* format, ...) {
  
}

static void InitUartHandle(void) {
  UartHandle.Instance = USARTx;
  UartHandle.Init.BaudRate = 115200;
  UartHandle.Init.WordLength = UART_WORDLENGTH_8B;
  UartHandle.Init.StopBits = UART_STOPBITS_1;
  UartHandle.Init.Parity = UART_PARITY_NONE;
  UartHandle.Init.HwFlowCtl = UART_HWCONTROL_NONE;
  UartHandle.Init.Mode = UART_MODE_TX_RX;

  if (HAL_UART_DeInit(&UartHandle) != HAL_OK) {
	Error_Handler();
  }
  if (HAL_UART_Init(&UartHandle) != HAL_OK) {
	Error_Handler();
  }
}

static void Error_Handler(void) {
  while (1) {
	HAL_Delay(100);
	BSP_LED_Toggle(LED4);
	HAL_Delay(500);
	BSP_LED_Toggle(LED4);
  }
}
