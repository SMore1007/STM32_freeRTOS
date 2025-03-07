#include  "stm32f4xx_hal.h"
#include  "adc.h"

#define ADC_CH1			(1U<<0)
#define ADC_SEQ_LEN_1	 0x00

void adc_init()
	{
	RCC->AHB1ENR|=RCC_AHB1ENR_GPIOAEN;
	RCC->APB2ENR|=RCC_APB2ENR_ADC1EN;
	GPIOA->MODER|=GPIO_MODER_MODE1;

	ADC1->CR2=0;

	/*Conversion sequence start*/
	ADC1->SQR3 = ADC_CH1;

	/*Conversion sequence length*/
	ADC1->SQR1 = ADC_SEQ_LEN_1;

	/*Enable ADC module*/
	ADC1->CR2 |= ADC_CR2_ADON;

	}

uint32_t read_analog_sensor(void)
	{
	ADC1->CR2|=ADC_CR2_SWSTART;
	/*Wait for conversion to be complete*/
	while(!(ADC1->SR & ADC_SR_EOC)){}

	/*Read converted result*/
	return (ADC1->DR);

	}
