/*
 * FlameSensor.c
 *
 * Author: KarthikyeanCode
 */ 

#define F_CPU 16000000UL

#include<avr/io.h>
#include<util/delay.h>

void init()
{
	DDRB = (1<<DDB5); //setting pinb5 as output (digital pin 13)
	DDRD = (0<<DDD2); //setting pind2 as input (digital pin 2);
	DDRD |= (1<<DDD4); //buzzer pin as output (digital pin 4);
}

void process()
{
	while(1)
	{
		if(PIND & (1<<PIND2))
		{
			PORTB = (1<<PORTB5);
			PORTD = (1<<PORTD4);
		}
		else
		{
			PORTB = (0<<PORTB5);
			PORTD = (0<<PORTD4);
		}
		_delay_ms(1000);
	}
}

int main(void)
{
	init();
	process();
	return 0;
}

