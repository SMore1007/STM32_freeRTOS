
/* Includes ------------------------------------------------------------------*/
#include "main.h"
#include "cmsis_os.h"
#include<stdint.h>
#include<stdio.h>
#include<stdbool.h>


UART_HandleTypeDef huart2;

void SystemClock_Config(void);
static void MX_GPIO_Init(void);
static void MX_USART2_UART_Init(void);

int __io_putchar(int ch);

void greenLEDControllerTask(void *pvParameters);
void blueLEDControllerTask(void *pvParameters);
void redLEDControllerTask(void *pvParameters);

typedef uint32_t taskCountType_t;

taskCountType_t RedLedCounter, BlueLedCounter, greenLedCounter;
TaskHandle_t greenTaskHandle, blueTaskHandle, redTaskHandle;

uint8_t redCounter;
uint8_t red_Priority, blue_Priority, green_Priority;
bool suspend_monitor = false;
int main(void)
{
  HAL_Init();
  SystemClock_Config();
  MX_GPIO_Init();
  MX_USART2_UART_Init();


  /* Creating a Task blueLEDControllerTask  */
  xTaskCreate(blueLEDControllerTask,       // Task Function Name
			  "Blue LED Controller ",	// Task Understandable Name
			   100,                     // Task Depth(Task Size)
			   NULL,                    // Task Function parameters any
			   2,                       // TAsk Priority
			   &blueTaskHandle);        // Task Handle (for runtime control)


  /* Creating a Task redLEDControllerTask  */
  xTaskCreate(redLEDControllerTask,     // Task Function Name
			  "Red LED Controller ",	// Task Understandable Name
			   100,                     // Task Depth(Task Size)
			   NULL,                    // Task Function parameters any
			   1,                       // TAsk Priority
			   &redTaskHandle);         // Task Handle (for runtime control)

  /* Creating a Task greenLEDControllerTask  */
  xTaskCreate(greenLEDControllerTask,       // Task Function Name
			  "Blue LED Controller ",	// Task Understandable Name
			   100,                     // Task Depth(Task Size)
			   NULL,                    // Task Function parameters any
			   1,                       // TAsk Priority
			   &greenTaskHandle);                   // Task Handle (for runtime control)

  vTaskStartScheduler();  // used for start scheduling of the task


  // main thread loop
  while (1)
  {

  }
  /* USER CODE END 3 */
}

int __io_putchar(int ch)
{
    uint8_t c = ch;
    HAL_UART_Transmit(&huart2, &c, 1, 0xFFFF);
    return ch;
}

/*
 *  blueLEDControllerTask definition
 *
 **/


void blueLEDControllerTask(void *pvParameters)
{

	while(1)
	{
		BlueLedCounter++;
		for(int i = 0; i < 500000; i++){}

		// Getting priority of the task
		blue_Priority  = uxTaskPriorityGet(blueTaskHandle);
		red_Priority   = uxTaskPriorityGet(redTaskHandle);
		green_Priority = uxTaskPriorityGet(greenTaskHandle);

		if(BlueLedCounter == 100)
		{
			BlueLedCounter = 0;

			// Setting runtime priority
			vTaskPrioritySet(blueTaskHandle, 1);
			vTaskPrioritySet(redTaskHandle, 2);
			vTaskPrioritySet(greenTaskHandle, 1);
		}
	}

}


void redLEDControllerTask(void *pvParameters)
{
	while(1)
	{
		RedLedCounter++;
		for(int i = 0; i < 500000; i++){}

		// Getting priority of the task
		blue_Priority  = uxTaskPriorityGet(blueTaskHandle);
		red_Priority   = uxTaskPriorityGet(redTaskHandle);
		green_Priority = uxTaskPriorityGet(greenTaskHandle);

		if(RedLedCounter == 100)
		{

			// Setting runtime priority
			vTaskPrioritySet(redTaskHandle, 1);
			vTaskPrioritySet(blueTaskHandle, 1);
			vTaskPrioritySet(greenTaskHandle, 2);
		}else if(RedLedCounter == 200){
			RedLedCounter = 0;
			vTaskSuspend(redTaskHandle); // Suspend the particular Task
			suspend_monitor = true;
		}
	}
}


void greenLEDControllerTask(void *pvParameters)
{

	while(1)
	{
		greenLedCounter++;
		for(int i = 0; i < 500000; i++){}

		// Getting priority of the task
		blue_Priority  = uxTaskPriorityGet(blueTaskHandle);
		red_Priority   = uxTaskPriorityGet(redTaskHandle);
		green_Priority = uxTaskPriorityGet(greenTaskHandle);

		if(greenLedCounter == 100)
		{
			greenLedCounter = 0;

			// Setting runtime priority
			vTaskPrioritySet(greenTaskHandle, 1);
			vTaskPrioritySet(blueTaskHandle, 2);
			vTaskPrioritySet(redTaskHandle, 1);
		}


		if(greenLedCounter == 100 && suspend_monitor)
		{
			vTaskResume(redTaskHandle);
			suspend_monitor = false;
		}
	}
}


/**
  * @brief System Clock Configuration
  * @retval None
  */
void SystemClock_Config(void)
{
  RCC_OscInitTypeDef RCC_OscInitStruct = {0};
  RCC_ClkInitTypeDef RCC_ClkInitStruct = {0};

  /** Configure the main internal regulator output voltage
  */
  __HAL_RCC_PWR_CLK_ENABLE();
  __HAL_PWR_VOLTAGESCALING_CONFIG(PWR_REGULATOR_VOLTAGE_SCALE3);

  /** Initializes the RCC Oscillators according to the specified parameters
  * in the RCC_OscInitTypeDef structure.
  */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSI;
  RCC_OscInitStruct.HSIState = RCC_HSI_ON;
  RCC_OscInitStruct.HSICalibrationValue = RCC_HSICALIBRATION_DEFAULT;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
  RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSI;
  RCC_OscInitStruct.PLL.PLLM = 16;
  RCC_OscInitStruct.PLL.PLLN = 336;
  RCC_OscInitStruct.PLL.PLLP = RCC_PLLP_DIV4;
  RCC_OscInitStruct.PLL.PLLQ = 2;
  RCC_OscInitStruct.PLL.PLLR = 2;
  if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
  {
    Error_Handler();
  }

  /** Initializes the CPU, AHB and APB buses clocks
  */
  RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK|RCC_CLOCKTYPE_SYSCLK
                              |RCC_CLOCKTYPE_PCLK1|RCC_CLOCKTYPE_PCLK2;
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV2;
  RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV1;

  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_2) != HAL_OK)
  {
    Error_Handler();
  }
}

/**
  * @brief USART2 Initialization Function
  * @param None
  * @retval None
  */
static void MX_USART2_UART_Init(void)
{

  /* USER CODE BEGIN USART2_Init 0 */

  /* USER CODE END USART2_Init 0 */

  /* USER CODE BEGIN USART2_Init 1 */

  /* USER CODE END USART2_Init 1 */
  huart2.Instance = USART2;
  huart2.Init.BaudRate = 115200;
  huart2.Init.WordLength = UART_WORDLENGTH_8B;
  huart2.Init.StopBits = UART_STOPBITS_1;
  huart2.Init.Parity = UART_PARITY_NONE;
  huart2.Init.Mode = UART_MODE_TX_RX;
  huart2.Init.HwFlowCtl = UART_HWCONTROL_NONE;
  huart2.Init.OverSampling = UART_OVERSAMPLING_16;
  if (HAL_UART_Init(&huart2) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN USART2_Init 2 */

  /* USER CODE END USART2_Init 2 */

}

/**
  * @brief GPIO Initialization Function
  * @param None
  * @retval None
  */
static void MX_GPIO_Init(void)
{
  GPIO_InitTypeDef GPIO_InitStruct = {0};
/* USER CODE BEGIN MX_GPIO_Init_1 */
/* USER CODE END MX_GPIO_Init_1 */

  /* GPIO Ports Clock Enable */
  __HAL_RCC_GPIOC_CLK_ENABLE();
  __HAL_RCC_GPIOH_CLK_ENABLE();
  __HAL_RCC_GPIOA_CLK_ENABLE();
  __HAL_RCC_GPIOB_CLK_ENABLE();

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(LD2_GPIO_Port, LD2_Pin, GPIO_PIN_RESET);

  /*Configure GPIO pin : B1_Pin */
  GPIO_InitStruct.Pin = B1_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_IT_FALLING;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  HAL_GPIO_Init(B1_GPIO_Port, &GPIO_InitStruct);

  /*Configure GPIO pin : LD2_Pin */
  GPIO_InitStruct.Pin = LD2_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(LD2_GPIO_Port, &GPIO_InitStruct);

/* USER CODE BEGIN MX_GPIO_Init_2 */
/* USER CODE END MX_GPIO_Init_2 */
}

/* USER CODE BEGIN 4 */

/* USER CODE END 4 */



/**
  * @brief  Period elapsed callback in non blocking mode
  * @note   This function is called  when TIM1 interrupt took place, inside
  * HAL_TIM_IRQHandler(). It makes a direct call to HAL_IncTick() to increment
  * a global variable "uwTick" used as application time base.
  * @param  htim : TIM handle
  * @retval None
  */
void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim)
{
  /* USER CODE BEGIN Callback 0 */

  /* USER CODE END Callback 0 */
  if (htim->Instance == TIM1) {
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
