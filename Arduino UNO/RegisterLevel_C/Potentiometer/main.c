//Preprocessor Directives
#define F_CPU 16000000UL

//Libraries
#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>

//Global Variables
volatile uint8_t data;
volatile uint8_t flag = 0;

//Functions
void ADC_init()
{
	//global enable interrupts
	sei();
	
	//setting the ADMUX register
	ADMUX = (0<<REFS1) | (1<<REFS0) | (0<<MUX3) | (0<<MUX2) | (0<<MUX1) | (0<<MUX0); //A0 is input and AVCC to power the ADC
	
	//setting the ADCSRA register
	ADCSRA = (1<<ADEN) | (1<<ADIE) | (1<<ADATE);  //ADC enable, ADC interrupt enable and ADC auto triggerring disable
	ADCSRA |= (1<<ADPS2) | (1<<ADPS1) | (1<<ADPS0); //division factor 128 (prescalar)
	
	//setting the ADCSRB register
	ADCSRB = (0<<ADTS2) | (0<<ADTS1) | (0<<ADTS0); //free running mode
	
	//Setting the DIDR0 register
	DIDR0 = (1<<ADC0D); //Disabling digital input buffer in the ADC0 pin
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

void USART_transmit(uint8_t data)
{
	uint8_t ones, tens, hundreds, thousands;
	
	ones = data%10;
	data /= 10;
	tens = data%10;
	data /= 10;
	hundreds = data%10;
	data /= 10;
	thousands = data%10;
	
	//Since serial monitor interprets ascii .. we need to give the digits as ascii value
	while(!(UCSR0A & (1<<UDRE0))) {}
	UDR0 = thousands+0x30; //adding 48 to get the ascii value
	while(!(UCSR0A & (1<<UDRE0))) {}
	UDR0 = hundreds+0x30; //subtract 300 i.e 3 from hundreds digit (0x30 - 0x03 = 0x2D)
	while(!(UCSR0A & (1<<UDRE0))) {}
	UDR0 = tens+0x30;
	while(!(UCSR0A & (1<<UDRE0))) {}
	UDR0 = ones+0x30;
	while(!(UCSR0A & (1<<UDRE0))) {}
	UDR0 = '\n';
}

void TimerInit()
{
	//Timer Registers to Create Delay - Using the Timer1 Registers 
	
	//Setting the TCCR1A register 
	TCCR1A = (0<<WGM11) | (0<<WGM10);
	
	//Setting the TCCR1B register 
	TCCR1B = (0<<WGM13) | (0<<WGM12) | (1<<CS12) | (0<<CS11) | (1<<CS10); //Waveform generation and clock select
	
	//Initializing the timer register TCNT1
	TCNT1 = 0x0000; //16 Bit
	
	//Setting the TIMSK1 register
	TIMSK1 = (1<<TOIE1); //OVF interrupt enable 
		
}

//main
int main(void)
{
	
	USART_init();
	ADC_init();
	TimerInit();
		
    while (1) 
    {
		ADCSRA |= (1<<ADSC); //setting the ADSC bit
		while(ADCSRA & (1<<ADSC)) {}
						
		//4 Seconds Delay
		TCNT1 = 0x0000;
		flag = 1;
		while(flag){}
		
					
		USART_transmit(data);
    }
}

//ISRs
//ADC Interrupt Vect 
ISR(ADC_vect) 
{
	data = ADC;
	data &= 0x03FF; //taking only lower 10 bits
}

//Timer0 Overflow Vect
ISR(TIMER1_OVF_vect)
{
	if(flag == 1)
	{
		flag = 0;
	} 
}

