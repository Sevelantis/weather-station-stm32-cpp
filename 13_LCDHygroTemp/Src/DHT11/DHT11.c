#include "main.h"
#include"DHT11.h"
#include"../DWT_STM32/dwt_stm32_delay.h"

#define DHT11_PORT			GPIOA
#define DHT11_PIN			GPIO_PIN_1

void set_pin_output(GPIO_TypeDef *GPIOx, uint16_t GPIO_Pin)
{
	GPIO_InitTypeDef gpio = {0};
	gpio.Pin = GPIO_Pin;
	gpio.Mode = GPIO_MODE_OUTPUT_PP;
	gpio.Speed = GPIO_SPEED_FREQ_LOW;
	HAL_GPIO_Init(GPIOx, &gpio);
}

void set_pin_input(GPIO_TypeDef *GPIOx, uint16_t GPIO_Pin)
{
	GPIO_InitTypeDef gpio = {0};
	gpio.Pin = GPIO_Pin;
	gpio.Mode = GPIO_MODE_INPUT;
	gpio.Pull = GPIO_NOPULL;
	HAL_GPIO_Init(GPIOx, &gpio);
}



void DHT11_setup()
{
	set_pin_output(DHT11_PORT, DHT11_PIN);
	HAL_GPIO_WritePin(DHT11_PORT, DHT11_PIN, 0);
	DWT_Delay_us(18000);
	HAL_GPIO_WritePin(DHT11_PORT, DHT11_PIN, 1);
	DWT_Delay_us(20);
	set_pin_input(DHT11_PORT, DHT11_PIN);
}

uint8_t DHT11_check_response()
{
	uint8_t Response = 0;
	DWT_Delay_us (40);
	if (!(HAL_GPIO_ReadPin (DHT11_PORT, DHT11_PIN)))
	{
		DWT_Delay_us (80);
		if ((HAL_GPIO_ReadPin (DHT11_PORT, DHT11_PIN))) Response = 1;
		else Response = -1;
	}
	while ((HAL_GPIO_ReadPin (DHT11_PORT, DHT11_PIN)))   // wait for the pin to go low
	{

	}
	return Response;
}

//uint8_t DHT11_Read (void)
//{
//	uint8_t i=0,j;
//	for (j=0;j<8;j++)
//	{
//		while (!(HAL_GPIO_ReadPin (DHT11_PORT, DHT11_PIN)));   // wait for the pin to go high
//		DWT_Delay_us (50);   // wait for 40 us
//		if (!(HAL_GPIO_ReadPin (DHT11_PORT, DHT11_PIN)))   // if the pin is low
//		{
//			i&= ~(1<<(7-j));   // write 0
//			//0000.0001 << 7 => 1000.0000 ~~~= 0111.1111
//			//i = abcd.efgh
//			//w = 0111.1111
//			//in= 0bcd.efgh
//			//
//			//i = 0000.0000
//			//w = 1011.1111
//			//in= 0000.0000
//
//			//i = 0000.0000
//			//w = 1101.1111
//			//in= 0000.0000
//
//			//...
//		}
//		else
//		{
//			i|= (1<<(7-j));  // if the pin is high, write 1
//		}
//		while ((HAL_GPIO_ReadPin (DHT11_PORT, DHT11_PIN)))  // wait for the pin to go low
//		{
//		}
//	}
//	return i;
//}

uint8_t DHT11_Read (void)
{
	uint8_t i=0,j;
	for (j=0;j<8;j++)
	{
		while (!(HAL_GPIO_ReadPin (DHT11_PORT, DHT11_PIN)));   // wait for the pin to go high
		DWT_Delay_us (40);   // wait for 26-28 us
		if (!(HAL_GPIO_ReadPin (DHT11_PORT, DHT11_PIN)))   // if the pin is low
			i&= ~(1<<(7-j));   // write 0
		else
			i|= (1<<(7-j));  // if the pin is high, write 1

		while ((HAL_GPIO_ReadPin (DHT11_PORT, DHT11_PIN)))  // wait for the pin to go low
		{
		}
	}
	return i;
}
