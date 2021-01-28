#ifndef __LCD__
#define __LCD__

#include <stdint.h>
#include "gpio.h"

#define LCD_WIDTH				84
#define LCD_HEIGHT				48

#define LCD_RST					RESET_Pin
#define LCD_CE 					CE_Pin
#define LCD_DC 					DC_Pin
#define LCD_BL 					BL_Pin

extern SPI_HandleTypeDef spi;

void lcd_setup(void);

void lcd_clear(void);
void lcd_draw_bitmap(const uint8_t* data);
void lcd_draw_text(int row, int col, const char* text);
void lcd_draw_big_text(int row, int col, const char* text);
void lcd_draw_pixel(int x, int y);
void lcd_draw_line(int x1, int y1, int x2, int y2);

void lcd_copy(void);

#endif // __LCD__
