#include <string.h>
#include "lcd.h"
#include "../font/font.h"
#define PCD8544_FUNCTION_SET		0x20
#define PCD8544_DISP_CONTROL		0x08
#define PCD8544_DISP_NORMAL			0x0c
#define PCD8544_SET_Y				0x40
#define PCD8544_SET_X				0x80
#define PCD8544_H_TC				0x04
#define PCD8544_H_BIAS				0x10
#define PCD8544_H_VOP				0x80

#define LCD_BUFFER_SIZE			(LCD_WIDTH * LCD_HEIGHT / 8)	//in bytes

extern SPI_HandleTypeDef hspi2;

static uint8_t lcd_buffer[LCD_BUFFER_SIZE];

void lcd_cmd(uint8_t cmd)
{
	HAL_GPIO_WritePin(GPIOA, LCD_CE|LCD_DC, GPIO_PIN_RESET);
	HAL_SPI_Transmit(&hspi2, &cmd, 1, HAL_MAX_DELAY);
	HAL_GPIO_WritePin(GPIOA, LCD_CE|LCD_DC, GPIO_PIN_SET);
}

void lcd_setup(void)
{
	HAL_GPIO_WritePin(GPIOA, LCD_RST, GPIO_PIN_RESET);
	HAL_GPIO_WritePin(GPIOA, LCD_RST, GPIO_PIN_SET);

    HAL_GPIO_WritePin(GPIOA, LCD_BL, GPIO_PIN_SET);
    HAL_GPIO_WritePin(GPIOA, LCD_DC, GPIO_PIN_RESET);

	lcd_cmd(PCD8544_FUNCTION_SET | 1);
	lcd_cmd(PCD8544_H_BIAS | 4);
	lcd_cmd(PCD8544_H_VOP | 0x2f);
	lcd_cmd(PCD8544_FUNCTION_SET);
	lcd_cmd(PCD8544_DISP_NORMAL);
}

void lcd_clear(void)
{
	memset(lcd_buffer, 0, LCD_BUFFER_SIZE);
}

void lcd_draw_bitmap(const uint8_t* data)
{
	memcpy(lcd_buffer, data, LCD_BUFFER_SIZE);
}

void lcd_draw_text(int row, int col, const char* text)
{
	uint8_t* pbuf = &lcd_buffer[row * LCD_WIDTH + col];
	while ((*text) && (pbuf < &lcd_buffer[LCD_BUFFER_SIZE - 6]))
	{
		int ch = *text++;
		const uint8_t* font = &font5x8[ch - ' '][0];
		for (int i = 0; i < 5; i++)
		{
			*pbuf++ = *font++;
		}
		*pbuf++ = 0;
	}
}

void lcd_draw_big_text(int row, int col, const char* text)
{
	uint8_t* pbuf1 = &lcd_buffer[row * LCD_WIDTH + col];
	uint8_t* pbuf2 = &lcd_buffer[(row+1) * LCD_WIDTH + col];
	while ((*text) && (pbuf1 < &lcd_buffer[LCD_BUFFER_SIZE - 6]) && (pbuf1 < &lcd_buffer[LCD_BUFFER_SIZE - 6]))
	{
		int ch = *text++;
		const uint8_t* font = &font8x14[ch][0];
		for (int i = 0; i < 15; i++)
		{
			if(i%2==0)
				*pbuf1++ = *font++;
			else
				*pbuf2++ = *font++;
		}
		*pbuf1++;
		*pbuf2++;
		*pbuf2++;
	}
}


inline void lcd_draw_pixel(int x, int y)
{
	lcd_buffer[ x + (y >> 3) * LCD_WIDTH] |= 1 << (y & 7);
}

void lcd_draw_line(int x1, int y1, int x2, int y2)
{
	int dx, dy, sx, sy;
	if (x2 >= x1) {
		dx = x2 - x1;
		sx = 1;
	} else {
		dx = x1 - x2;
		sx = -1;
	}
	if (y2 >= y1) {
		dy = y1 - y2;
		sy = 1;
	} else {
		dy = y2 - y1;
		sy = -1;
	}

	int dx2 = dx << 1;
	int dy2 = dy << 1;
    int err = dx2 + dy2;
    while (1) {
        lcd_draw_pixel(x1, y1);
        if (err >= dy) {
            if (x1 == x2) break;
            err += dy2;
            x1 += sx;
        }
        if (err <= dx) {
            if (y1 == y2) break;
            err += dx2;
            y1 += sy;
        }
    }
}

void lcd_copy(void)
{
	HAL_GPIO_WritePin(GPIOA, LCD_DC, GPIO_PIN_SET);
	HAL_GPIO_WritePin(GPIOA, LCD_CE, GPIO_PIN_RESET);
	HAL_SPI_Transmit(&hspi2, lcd_buffer, LCD_BUFFER_SIZE, HAL_MAX_DELAY);
	HAL_GPIO_WritePin(GPIOA, LCD_CE, GPIO_PIN_SET);
}
