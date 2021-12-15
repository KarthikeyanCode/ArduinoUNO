/*
 * LaserEmitter.c
 *
 * Author : KarthikeyanCode
 */ 

#define F_CPU 16000000UL

#include<avr/io.h>
#include<util/delay.h>

void init()
{
	DDRD = (1<<DDD2);
	DDRD |= (1<<DDD4);
}

void process()
{
	uint8_t flag=0;
	while(1)
	{
		if(flag==0)
		{
			PORTD = (1<<PORTD2); //setting laser to high
			PORTD |= (1<<PORTD4); //setting passive buzzer to high
			flag=1;
		}
		else
		{
			PORTD = (0<<PORTD2) | (0<<PORTD4); //setting laser and buzzer to low
			flag=0;
		}
		_delay_ms(10000); //10 seconds delay
	}
}

int main(void)
{
    init();
	process();
	return 0;
}

