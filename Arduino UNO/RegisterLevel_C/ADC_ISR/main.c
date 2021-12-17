/*
 * ADC_ISR.c
 *
 * Created: 16-12-2021 13:42:21
 * Author : KarthikeyanCode
 */ 

#define F_CPU 16000000UL

#include<avr/io.h>
#include<util/delay.h>
#include<avr/interrupt.h>


volatile uint16_t data=0;

void ADC_init()
{
	//global enable interrupts
	sei();
	
	//setting the ADMUX register 
	ADMUX = (0<<REFS1) | (1<<REFS0) | (0<<MUX3) | (0<<MUX2) | (0<<MUX1) | (0<<MUX0); //A0 is input and AVCC to power the ADC
	
	//setting the ADCSRA register
	ADCSRA = (1<<ADEN) | (1<<ADIE) | (0<<ADATE);  //ADC enable, ADC interrupt enable and ADC auto triggerring disable
	ADCSRA |= (1<<ADPS2) | (1<<ADPS1) | (1<<ADPS0); //division factor 128 (prescalar)
	
	//setting the ADCSRB register
	ADCSRB = (0<<ADTS2) | (0<<ADTS1) | (0<<ADTS0); //free running mode 
}

void USART_init()
{
	//setting the baud rate
	UBRR0L = 0x67; //9600 bps
	UBRR0H = (0x67>>8);
	
	//setting the UCSR0B register
	UCSR0B = (1<<RXEN0) | (1<<TXEN0) | (0<<UCSZ02); //rxen, txen and MSB of frame size
	
	//setting the UCSR0C register
	UCSR0C = (0<<UMSEL01) | (0<<UMSEL00) | (0<<UPM01) | (0<<UPM00) | (0<<USBS0); //async usart, parity mode disabled, 1 stop bit
	UCSR0C |= (1<<UCSZ01) | (1<<UCSZ00); //frame size 
}

void USART_transmit()
{
	uint8_t ones, tens, hundreds, thousands;
	
	ones = data%10;
	data /= 10;
	tens = data%10;
	data /= 10;
	hundreds = data%10;
	data /= 10;
	thousands = data%10;
	
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
	ADC_init();
	USART_init(); 
    while (1) 
    {
		ADCSRA |= (1<<ADSC); //setting the ADSC bit 
		while(ADCSRA & (1<<ADSC)) {}
		_delay_ms(500);
    }
}

ISR(ADC_vect)
{
	data = ADC;
	USART_transmit();
}