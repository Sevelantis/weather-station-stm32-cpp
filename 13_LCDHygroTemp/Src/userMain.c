/*
 * userMain.c
 *
 *  Created on: 04.12.2020
 *      Author: Aron
 */
#include<stdlib.h>
#include "main.h"
#include"lcd/lcd.h"
#include "images.h"
#include "DWT_STM32/dwt_stm32_delay.h"

#define DHT11_PORT			GPIOA
#define DHT11_PIN			GPIO_PIN_1

void welcome();
void userMain();

extern void float_to_string(float f, char[]);
//extern float _round(float f);
extern TIM_HandleTypeDef htim2;


const unsigned char *film[6] = {&KON, &THUGLIFE1, &BACKGROUND_WHITE, &BACKGROUND_BLACK,
								&NARA1, &NARA2};

uint8_t lcd_ready = 0;


void welcome()
{
	lcd_draw_bitmap(NARA1);
	lcd_copy();
	HAL_Delay(1111);

	lcd_draw_bitmap(NARA2);
	lcd_copy();
	HAL_Delay(1111);

	lcd_draw_bitmap(THUGLIFE1);
	lcd_copy();
	HAL_Delay(3333);

	lcd_draw_bitmap(ZOSIA);
	lcd_copy();
	HAL_Delay(3333);

	lcd_draw_bitmap(SEBA1);
	lcd_copy();
	HAL_Delay(3333);

	lcd_draw_bitmap(BART1);
	lcd_copy();
	HAL_Delay(3333);
}

void print_value(int x, int y, uint8_t integral, uint8_t decimal)
{
	char temp_str[5];
	sprintf(temp_str, "%d.", integral);
	sprintf((temp_str+3), "%d", decimal);
	lcd_draw_big_text(x,y,temp_str);
	lcd_copy();
}

unsigned int x = 0;

uint8_t temp_int, temp_dec;
uint8_t hygr_int, hygr_dec;
uint8_t checksum;

void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef* htim)//250ms
{
}

void userMain()
{
	HAL_TIM_Base_Start_IT(&htim2);//
	lcd_setup();
	DWT_Delay_Init();

//	welcome();

	lcd_draw_bitmap(BACKGROUND_WHITE);
	lcd_copy();

	while(1)
	{
		//DHT11
		DHT11_setup();
		DHT11_check_response();
		hygr_int = DHT11_Read();//0-7
		hygr_dec = DHT11_Read();//8-15
    	temp_int = DHT11_Read();//16-23
    	temp_dec = DHT11_Read();//24-31
    	checksum = DHT11_Read();//32-39

        print_value(4, 2, temp_int, temp_dec);
        print_value(4, 43, hygr_int, hygr_dec);

		HAL_GPIO_TogglePin(EXTLED_GPIO_Port, EXTLED_Pin);
    	HAL_Delay(100);
		HAL_GPIO_TogglePin(EXTLED_GPIO_Port, EXTLED_Pin);
    	HAL_Delay(6000);
	}
}
