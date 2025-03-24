#include "main.h"
#include "cmsis_os.h"
#include "usart.h"
#include "gpio.h"
#include<stdio.h>
#include<stdint.h>
#include<stdbool.h>

void SystemClock_Config(void);
void MX_FREERTOS_Init(void);

int __IO_putchar(int ch);

// Task Prototypes
void vBlueLedControllerTask(void *pvParameters);
void vRedLedControllerTask(void *pvParameters);
void vGreenLedControllerTask(void *pvParameters);

typedef uint32_t TaskProfiler;

TaskProfiler BlueTaskProfiler,RedTaskProfiler,GreenTaskProfiler;

TaskHandle_t blue_handle, red_handle, green_handle;

uint32_t greenPriority;
uint32_t executionMonitor;
uint32_t resumeMonitor;

bool is_killed = false;
int main(void)
{
  HAL_Init();
  SystemClock_Config();
  MX_GPIO_Init();
  MX_USART2_UART_Init();


  // Create a task
  xTaskCreate(vBlueLedControllerTask,  // Task Function like our main()
		      "Blue LED Control",      // Task Name for our understanding
			  100,                     // Task depth size
			  NULL,                    // Task Parameters if any
			  1,                       // Task Priority
			  &blue_handle);                   // Task handle (NULL if not required to store task handle)

  // Create a task for controlling the Red LED
  xTaskCreate(
      vRedLedControllerTask, // Function that implements the task (Task Handler)
      "Red LED Control",     // Name of the task (for debugging and monitoring)
      100,                   // Stack size allocated for the task (in words, not bytes)
      NULL,                  // Parameter passed to the task (NULL if no parameter is needed)
      1,                     // Task priority (Higher value = Higher priority)
      &red_handle);          // Task handle (NULL if not required to store task handle)


  // Create a task
  xTaskCreate(vGreenLedControllerTask,
		      "Green LED Control",
			  100,
			  NULL,
			  1,
			  &green_handle);

  // Manage the task using task scheduler
  vTaskStartScheduler();



  // Main while loop
  while (1)
  {
   //  printf("Hello From STM32Cube IDE\r\n");
  }


} // main end

void vBlueLedControllerTask(void *pvParameters)
{
	while(1)
	{
		BlueTaskProfiler++;
	}
}

void vRedLedControllerTask(void *pvParameters)
{
	int i = 0;
	while(1)
	{
		RedTaskProfiler++;
		for(i = 0; i < 100000; i++) {}
		executionMonitor++;

		if(executionMonitor >= 50)
		{
			is_killed = true;
			executionMonitor = 0;

			vTaskDelete(red_handle); // Delete the Red task
		}
	}
}

void vGreenLedControllerTask(void *pvParameters)
{
	int i;
	while(1)
	{
		GreenTaskProfiler++;
		for(i = 0; i < 10000; i++){}
		if(is_killed)
		{
			resumeMonitor++;
			if(resumeMonitor >= 30)
			{
				vTaskResume(red_handle);
				resumeMonitor = 0;
				is_killed = false;
			}
		}
	}
}


















































int __io_putchar(int ch)
{
	HAL_UART_Transmit(&huart2, (uint8_t *) &ch, 1, 0xFFFF);
	return ch;
}


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


void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim)
{

  if (htim->Instance == TIM1) {
    HAL_IncTick();
  }
}


void Error_Handler(void)
{
  __disable_irq();
  while (1)
  {
  }
  /* USER CODE END Error_Handler_Debug */
}

#ifdef  USE_FULL_ASSERT

void assert_failed(uint8_t *file, uint32_t line)
{

}
#endif /* USE_FULL_ASSERT */
