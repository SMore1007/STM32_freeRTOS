#include "main.h"
#include "cmsis_os.h"
#include "stdio.h"
#include "uart.h"
#include "adc.h"
#include "exti.h"
UART_HandleTypeDef huart2;

void SystemClock_Config(void);
static void MX_GPIO_Init(void);


#define mainOnE_SHOT_TIMER 			 (pdMS_TO_TICKS(4000UL))
#define mainAUTO_RELOAD_TIMER_PERIOD (pdMS_TO_TICKS(500UL))

TimerHandle_t xAutoReloadTimer, xOneShotTimer;
BaseType_t xTimer1Started,xTimer2Started;

void prvOneShotTImerCallback(TimerHandle_t xtimer);
void prvAutoReloadTimerCallback(TimerHandle_t xtimer);


int main(void)
{

  HAL_Init();
  SystemClock_Config();
  MX_GPIO_Init();
  USART2_UART_TX_Init();
  printf("system initializing........\r\n");

  xOneShotTimer=xTimerCreate("OneShot",mainOnE_SHOT_TIMER,pdFALSE,0,prvOneShotTImerCallback);
  xAutoReloadTimer=xTimerCreate("AutoReload",mainAUTO_RELOAD_TIMER_PERIOD,pdTRUE,0,prvAutoReloadTimerCallback);
  xTimer1Started=xTimerStart(xOneShotTimer,0);
  xTimer2Started=xTimerStart(xAutoReloadTimer,0);

  vTaskStartScheduler();

  while (1)
  {

  }

}


void prvOneShotTImerCallback(TimerHandle_t xtimer)
	{
		static TickType_t xTimeNow;
		xTimeNow=xTaskGetTickCount();
		printf(" One Shot ticks so far %ld\r\n",xTimeNow);
	}
void prvAutoReloadTimerCallback(TimerHandle_t xtimer)
	{
	static TickType_t xTimeNow;
	xTimeNow=xTaskGetTickCount();
	printf("Auto reload ticks so far %ld\r\n",xTimeNow);
	}




void SystemClock_Config(void)
{
  RCC_OscInitTypeDef RCC_OscInitStruct = {0};
  RCC_ClkInitTypeDef RCC_ClkInitStruct = {0};

  /** Configure the main internal regulator output voltage
  */
  __HAL_RCC_PWR_CLK_ENABLE();
  __HAL_PWR_VOLTAGESCALING_CONFIG(PWR_REGULATOR_VOLTAGE_SCALE1);
  /** Initializes the RCC Oscillators according to the specified parameters
  * in the RCC_OscInitTypeDef structure.
  */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSI;
  RCC_OscInitStruct.HSIState = RCC_HSI_ON;
  RCC_OscInitStruct.HSICalibrationValue = RCC_HSICALIBRATION_DEFAULT;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_NONE;
  if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
  {
    Error_Handler();
  }
  /** Initializes the CPU, AHB and APB buses clocks
  */
  RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK|RCC_CLOCKTYPE_SYSCLK
                              |RCC_CLOCKTYPE_PCLK1|RCC_CLOCKTYPE_PCLK2;
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_HSI;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV1;
  RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV1;

  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_0) != HAL_OK)
  {
    Error_Handler();
  }
}

/**
  * @brief GPIO Initialization Function
  * @param None
  * @retval None
  */
static void MX_GPIO_Init(void)
{

  /* GPIO Ports Clock Enable */
  __HAL_RCC_GPIOA_CLK_ENABLE();

}

/* USER CODE BEGIN 4 */

/* USER CODE END 4 */


/**
  * @brief  Period elapsed callback in non blocking mode
  * @note   This function is called  when TIM11 interrupt took place, inside
  * HAL_TIM_IRQHandler(). It makes a direct call to HAL_IncTick() to increment
  * a global variable "uwTick" used as application time base.
  * @param  htim : TIM handle
  * @retval None
  */
void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim)
{
  /* USER CODE BEGIN Callback 0 */

  /* USER CODE END Callback 0 */
  if (htim->Instance == TIM11) {
    HAL_IncTick();
  }
  /* USER CODE BEGIN Callback 1 */

  /* USER CODE END Callback 1 */
}

/**
  * @brief  This function is executed in case of error occurrence.
  * @retval None
  */
void Error_Handler(void)
{
  /* USER CODE BEGIN Error_Handler_Debug */
  /* User can add his own implementation to report the HAL error return state */
  __disable_irq();
  while (1)
  {
  }
  /* USER CODE END Error_Handler_Debug */
}

#ifdef  USE_FULL_ASSERT
/**
  * @brief  Reports the name of the source file and the source line number
  *         where the assert_param error has occurred.
  * @param  file: pointer to the source file name
  * @param  line: assert_param error line source number
  * @retval None
  */
void assert_failed(uint8_t *file, uint32_t line)
{
  /* USER CODE BEGIN 6 */
  /* User can add his own implementation to report the file name and line number,
     ex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */
  /* USER CODE END 6 */
}
#endif /* USE_FULL_ASSERT */

