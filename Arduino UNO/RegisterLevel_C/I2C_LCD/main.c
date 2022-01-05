/*
 * I2C_LCD.c
 *
 * Created: 05-01-2022 18:01:52
 * Author : KarthikeyanCode
 */ 

#define F_CPU 16000000UL

#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>
#include "lcd.h"

extern void lcd_backlight(char on);

int main(void)
{
	//initializing the LCD 
	lcd_init(LCD_ON_DISPLAY);
	lcd_backlight(0);
	_delay_ms(200);
	lcd_backlight(1);
	_delay_ms(200);
	lcd_clrscr();
	
    while (1) 
    {
		lcd_clrscr();
		lcd_home();
		lcd_gotoxy(0, 0);
		lcd_puts("Hello!! :D");
		_delay_ms(1000);		
    }
	
	return 0;
}

