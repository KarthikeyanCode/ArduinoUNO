/*
 * TapModule.c
 *
 * Author : KarthikeyanCode
 */ 

#define F_CPU 16000000UL

#include<avr/io.h>
#include<util/delay.h>

int main(void)
{
	DDRB = (1<<DDB5); //on board LED 
	DDRD = (0<<DDD2) | (1<<DDD4);//setting tilt sensor as input and buzzer as out
    while (1) 
    {
		if(PIND & (1<<PIND2))//if input is high
		{
			PORTD = (0<<PORTD4);//turn off buzzer
			PORTB = (0<<PORTB5);//turn off on-board LED
		}
		else //intput low - circuit is closed
		{
			//buzzer and onboard LED high
			PORTD = (1<<PORTD4);
			PORTB = (1<<PORTB5);
		}
		_delay_ms(100);
    }
	return 0;
}

