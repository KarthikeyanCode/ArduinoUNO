/*
 * Timer_ISR.c
 *
 * Created: 18-12-2021 12:37:35
 * Author : Karth
 */ 

#define F_CPU 16000000UL

#include<avr/io.h>
#include<util/delay.h>
#include<avr/interrupt.h>

volatile uint8_t count = 0;
volatile uint8_t flag = 0;

void Timer_init()
{
	//gloabal enable interrupts
	sei();
	
	//setting the TCCR1A register 
	TCCR1A = (0<<COM1A1) | (0<<COM1A0) | (0<<COM1B1) | (0<<COM1B0); //disconnecting OC1A and OC1B operation on GPIO pins
	TCCR1A |= (0<<WGM11) | (0<<WGM10);//CTC OCR1A mode
	
	//setting the TCCR1B register
	TCCR1B = (0<<WGM13) | (0<<WGM12); //setting the CTC OCR1A mode 
	TCCR1B |= (1<<CS12) | (0<<CS11) | (0<<CS10); //setting the clock (CLK(i/o)/256) - prescalar
	
	//setting the TCCR1C register
	TCCR1C = (0<<FOC1A) | (0<<FOC1B); //disabling force compare
	
	//setting the TCNT1 register
	TCNT1 = 0x0000;
	
	//setting the OCR1A register
	//OCR1A = 0xFFFF;
	
	//setting the TIMSK1 register
	TIMSK1 = (1<<TOIE1); //OCR1A match interrupt enable 
}

void PORTB_init()
{
	DDRB = (1<<DDB1); //PB1 as output
	PORTB = (0<<PORTB1); //logic 0 as o/p on PB5
}

int main(void)
{
    Timer_init();
	PORTB_init();
    while (1) 
    {
		if(flag==1)
		{
			flag=0;
			_delay_ms(1000);
			PORTB = (0<<PORTB1);
		}
    }
}

ISR(TIMER1_OVF_vect)
{
	if(count==5)
	{
		PORTB = (1<<PORTB1);
		flag=1;
		count=0;
	}	
	count++;
}

