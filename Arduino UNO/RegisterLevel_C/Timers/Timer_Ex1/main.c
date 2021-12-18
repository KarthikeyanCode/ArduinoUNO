/*
 * Timer_1.c
 *
 * Created: 18-12-2021 11:45:07
 * Author : KarthikeyanCode
 */ 

#define F_CPU 16000000UL

#include<avr/io.h>
#include<util/delay.h>

void Timer_init()
{
	//setting the TCCR1A register
	TCCR1A = (1<<COM1A1) | (0<<COM1A0); //OC1A pin output high (1) on match (digital pin 9 (pwm))
	TCCR1A |= (0<<WGM11) | (0<<WGM10); //CTC mode (non-pwm)
	
	//setting the TCCR1B register
	TCCR1B = (0<<WGM13) | (1<<WGM12); //CTC mode (non-pwm)
	TCCR1B |= (1<<CS12) | (0<<CS11) | (0<<CS10); //CLK(i/o)/256 (prescalar)
	
	//setting the TCCR1C register
	TCCR1C = (0<<FOC1A) | (0<<FOC1B); //disabling force out compare match on pins A and B as
	
	//clearing the timer/counter1 registers
	TCNT1L = 0x00;
	TCNT1H = 0x00;
	
	//setting the OCR1A and OCR1B registers
	OCR1AL = 0xFF;
	OCR1AH = 0xFF;
}

int main(void)
{
	DDRB = (1<<DDB1); //setting digital pin 9 (pwm) as GPIO output
    Timer_init();
    while (1) 
    {
		PORTB |= (1<<PORTB1);
		_delay_ms(1000);
    }
}	

