# FreeRTOS LED Blinking on STM32

This project demonstrates a basic **FreeRTOS multitasking application** on an STM32 microcontroller using STM32 HAL drivers. 
Two LEDs connected to GPIO pins **PA5** and **PA6** are toggled independently via two separate FreeRTOS tasks.

---

## 🧠 Project Overview

- **Platform**: STM32 (tested on STM32F4 series)
- **Framework**: FreeRTOS + STM32 HAL
- **IDE**: STM32CubeIDE / Espressif IDE (if applicable)
- **Language**: C

---

## 🚀 Features

- Creates two FreeRTOS tasks:
  - `blueLedControllerTask` for PA5
  - `redLedControllerTask` for PA6
- Demonstrates task concurrency using FreeRTOS scheduler
- Uses busy-wait delay (to be improved in future iterations)
- Toggles GPIO pins independently without blocking each other

---

## 📁 Project Structure
```
Core/
├── Src/
│ ├── main.c # Contains task creation and logic
│ └── ...
├── Inc/
│ ├── main.h
│ └── ...
Middlewares/
├── FreeRTOS/ # FreeRTOS kernel files
STM32CubeMX/
├── *.ioc # CubeMX project file (if used)
```

---

## 🔧 How It Works

- Two tasks are created using `xTaskCreate()` in `main.c`.
- Each task toggles a specific GPIO pin in an infinite loop.
- The tasks simulate delay using a busy-loop (for simplicity).
- FreeRTOS handles task switching via its preemptive scheduler.

---

## 💡 Code Snippet

```c
// Task creation
xTaskCreate(blueLedControllerTask, "Blue LED Controller Task", 100, NULL, 1, NULL);
xTaskCreate(redLedControllerTask, "Red Led Controller", 100, NULL, 1, NULL);

// Task Schedular
vTaskStartScheduler();

/* independant thread/Task/function Definitions */

// Task 1
void blueLedControllerTask(void *pvParameters)
{

	while(1)
	{
		redProfilerCounter++;
		HAL_GPIO_TogglePin(GPIOA, GPIO_PIN_5);
		for(int i = 0; i < 1000000; i++){}
	}
}

// Task 2
void redLedControllerTask(void *pvParameters)
{
	while(1)
	{
		blueProfilerCounter++;
		HAL_GPIO_TogglePin(GPIOA, GPIO_PIN_6);
		for(int i = 0; i < 1000000; i++){}
	}
}

```

## 📷 Demo
```
    https://youtu.be/vNYEzkMgZIQ
```
---

## 📚 What I Learned

- Basics of FreeRTOS task management

- Importance of non-blocking design in real-time systems

- Initial hands-on with STM32 HAL and FreeRTOS integration


---

## Future Improvements

- Replace busy-wait loops with vTaskDelay()

- Use semaphores or mutexes for shared resources

- Add inter-task communication (queues, event groups)

- Integrate ISRs with FreeRTOS APIs

- Expand to real-world applications like sensor control or IoT tasks

---


## Requirements

- STM32 board (e.g., STM32F401RE or compatible)

- STM32CubeIDE or another STM32 development environment

- Basic knowledge of C and embedded programming
