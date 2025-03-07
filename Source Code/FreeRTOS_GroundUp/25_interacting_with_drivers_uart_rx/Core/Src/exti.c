#include  "stm32f4xx_hal.h"
#include "exti.h"


#define GPIOCEN		    (1U<<2)
#define SYSCFGEN		(1U<<14)

void p13_interrupt(void)
{
	/*Disable global interrupts*/
	__disable_irq();

	/*Enable clock access for GPIOC*/
	RCC->AHB1ENR |=GPIOCEN;

	/*Set PC13 as input*/
	GPIOC->MODER &=~(1U<<26);
	GPIOC->MODER &=~(1U<<27);


	/*Enable clock access to SYSCFG*/
	RCC->APB2ENR |=SYSCFGEN;

	/*Select PORTC for EXTI13*/
	SYSCFG->EXTICR[3] |=(1U<<5);

	/*Unmask EXTI13*/
	EXTI->IMR |=(1U<<13);

	/*Select falling edge trigger*/
	EXTI->FTSR |=(1U<<13);
	/*set the priority to 6*/
	NVIC_SetPriority(EXTI15_10_IRQn,6);
	/*Enable EXTI13 line in NVIC*/
	NVIC_EnableIRQ(EXTI15_10_IRQn);

	/*Enable global interrupts*/
	__enable_irq();

}

void gpio_init()
	{
	/*Enable clock access for GPIOC*/
	RCC->AHB1ENR |=GPIOCEN;
	/*Set PC13 as input*/
	GPIOC->MODER &=~(1U<<26);
	GPIOC->MODER &=~(1U<<27);


	}

uint8_t read_digital_sensor()
	{

	if (GPIOC->IDR & GPIO_IDR_ID13)
		{
		return 1;
		}
	else return 0;
	}
