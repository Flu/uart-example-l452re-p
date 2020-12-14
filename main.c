#include "main.h"

volatile uint32_t UserButtonStatus = 0;

static void SystemClockConfig(void);
static void EXTI15_10_IRQHandler_Config(void);
static void Error_Handler(void);

int main(void) {
  HAL_Init();
  SystemClockConfig();

  BSP_LED_Init(LED4);

  EXTI15_10_IRQHandler_Config();
  
  InitIO();

  while (UserButtonStatus == 0) {
	BSP_LED_Toggle(LED4);
	HAL_Delay(500);
  }

  printk("You pressed a button. Hooray?");
  /** End of program **/
  while (1) {
	BSP_LED_Toggle(LED4);
	HAL_Delay(100);
  }
}

static void SystemClockConfig(void)
{
  RCC_ClkInitTypeDef RCC_ClkInitStruct = {0};
  RCC_OscInitTypeDef RCC_OscInitStruct = {0};

  /* MSI is enabled after System reset, activate PLL with MSI as source */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_MSI;
  RCC_OscInitStruct.MSIState = RCC_MSI_ON;
  RCC_OscInitStruct.MSIClockRange = RCC_MSIRANGE_6;
  RCC_OscInitStruct.MSICalibrationValue = RCC_MSICALIBRATION_DEFAULT;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
  RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_MSI;
  RCC_OscInitStruct.PLL.PLLM = 1;
  RCC_OscInitStruct.PLL.PLLN = 40;
  RCC_OscInitStruct.PLL.PLLR = 2;
  RCC_OscInitStruct.PLL.PLLP = 7;
  RCC_OscInitStruct.PLL.PLLQ = 4;
  if(HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
  {
    /* Initialization Error */
    Error_Handler();
  }
  
  /* Select PLL as system clock source and configure the HCLK, PCLK1 and PCLK2 
     clocks dividers */
  RCC_ClkInitStruct.ClockType = (RCC_CLOCKTYPE_SYSCLK | RCC_CLOCKTYPE_HCLK | RCC_CLOCKTYPE_PCLK1 | RCC_CLOCKTYPE_PCLK2);
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
  /** Originally, RCC_SYSCLK_DIV1, but wanted to be more efficient **/
  RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV4;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV1;  
  RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV1;  
  if(HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_4) != HAL_OK)
  {
    /* Initialization Error */
    Error_Handler();
  }
}

static void EXTI15_10_IRQHandler_Config(void) {
  GPIO_InitTypeDef GPIO_InitStructure;

  __HAL_RCC_GPIOC_CLK_ENABLE();

  GPIO_InitStructure.Mode = GPIO_MODE_IT_RISING;
  GPIO_InitStructure.Pull = GPIO_NOPULL;
  GPIO_InitStructure.Pin = GPIO_PIN_13;
  HAL_GPIO_Init(GPIOC, &GPIO_InitStructure);

  HAL_NVIC_SetPriority(EXTI15_10_IRQn, 2, 0);
  HAL_NVIC_EnableIRQ(EXTI15_10_IRQn);
}

void HAL_GPIO_EXTI_Callback(uint16_t GPIO_Pin) {
  if (GPIO_Pin == GPIO_PIN_13) {
	BSP_LED_Toggle(LED4);
	UserButtonStatus = 1;
  }
}

/** TODO: get data back and put it in the ringbuf struct **/
void HAL_UART_RxCpltCallback(UART_HandleTypeDef *UartHandle) {
}

void HAL_UART_ErrorCallback(UART_HandleTypeDef *UartHandle) {
  Error_Handler();
}

#ifdef USE_FULL_ASSERT
void assert_failed(uint8_t *file, uint32_t line) {
  while (1) {}
}

#endif

static void Error_Handler(void) {
  while (1) {
	HAL_Delay(100);
	BSP_LED_Toggle(LED4);
	HAL_Delay(500);
	BSP_LED_Toggle(LED4);
  }
}
