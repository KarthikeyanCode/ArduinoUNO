/*
 * main.c
 *
 * Created: 15-12-2021 15:34:37
 * Author : Karth
 */ 

#define F_CPU 16000000UL

#include<avr/io.h>
#include<util/delay.h>

void ADC_init()
{
	//setting the ADMUX register
	ADMUX = (0<<REFS1) | (1<<REFS0); //setting VCC (5v) as voltage reference
	ADMUX |= (0<<ADLAR) | (0<<MUX3) | (0<<MUX2) | (0<<MUX1) | (0<<MUX0); //setting ADLAR to 0 and choosing A0 as input
	
	//setting the ADCSRA register
	ADCSRA = (1<<ADEN);
	ADCSRA |= (1<<ADPS2) | (1<<ADPS1) | (0<<ADPS0);//setting the prescalar divisons
	
	//setting the ADCSRB register
	ADCSRB = (0<<ADTS2) | (0<<ADTS1) | (0<<ADTS0); //free running mode
}

void USART_init()
{
	//setting the baud rate
	UBRR0L = 0x67; //9600 bps
	UBRR0H = (0x67>>8); 
	
	//setting the UCSR0C register
	UCSR0C = (0<<UMSEL01) | (0<<UMSEL00) | (0<<UPM01) | (0<<UPM00) | (1<<USBS0); //asyn usart, parity disabled, 1 stop bit
	UCSR0C |= (1<<UCSZ01) | (1<<UCSZ00);//8bit frame size
	
	//setting the UCSR0B register
	UCSR0B = (1<<RXEN0) | (1<<TXEN0);
	UCSR0B |= (0<<UCSZ02);
	
}

void USART_transmit(uint16_t data)
{
	uint8_t ones=0;
	uint8_t tens=0;
	uint8_t hundreds=0;
	uint8_t thousands=0;
	
	ones = data%10;
	data /= 10;
	tens = data%10;
	data /= 10;
	hundreds = data%10;
	data /= 10;
	thousands = data%10;
	
	//transmitting the corresponding ascii values so they will be interpreted as numbers 
	while(!(UCSR0A & (1<<UDRE0))) {}
	UDR0 = thousands+0x30;
	while(!(UCSR0A & (1<<UDRE0))) {}
	UDR0 = hundreds+0x30;
	while(!(UCSR0A & (1<<UDRE0))) {}
	UDR0 = tens+0x30;
	while(!(UCSR0A & (1<<UDRE0))) {}
	UDR0 = ones+0x30;
	while(!(UCSR0A & (1<<UDRE0))) {}
	UDR0 = '\n';
}

int main(void)
{
	uint16_t data = 0x0000;
    ADC_init();
	USART_init();
	DDRB = (1<<DDB5);
	DDRD = (1<<DDD4);
    while (1) 
    {
		if(!(ADCSRA & (1<<ADSC)))
		{
			ADCSRA |= (1<<ADSC); //start the conversion
			while(ADCSRA & (1<<ADSC)) {} //wait for processing to complete 
			data = ADC;//reading the adc value 
			USART_transmit(data);
			if(data<70) //turning on the buzzer and on board LED if flame is detected 
			{
				PORTB = (1<<PORTB5);
				PORTD = (1<<PORTD4);
			}
			else //turning off the buzzer and LED when the flame is put off
			{
				PORTB = (0<<PORTB5);
				PORTD = (0<<PORTD4);
			}
		}
		_delay_ms(1000);
    }
	return 0;
}



