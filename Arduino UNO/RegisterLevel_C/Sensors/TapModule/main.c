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
	DDRD = (0<<DDD2) | (1<<DDD4);//setting sensor as input and buzzer as out
    while (1) 
    {
		if(PIND & (1<<PIND2))
		{
			PORTD = (0<<PORTD4);
		}
		else
		{
			PORTD = (1<<PORTD4);
		}
		_delay_ms(100);
    }
	return 0;
}

