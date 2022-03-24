/*
 * GccApplication2.cpp
 *
 * Created: 24-03-2022 21:41:33
 * Author : Karthikeyan
 */ 

//EEPROM

#define F_CPU 16000000UL

#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>

uint8_t ReadData;

void EEPROM_Init()
{
	//EEPROM Address Register
	EEARH = (0 << EEAR8);
	EEARL = 0x00;
	
}

void UART_Init()
{
	//setting the baud rate to 9600bps
	UBRR0L = 0x67;
	UBRR0H = 0x67>>8;

	//configuring the UCSR0C register for frame format
	UCSR0C = (0<<UMSEL01) | (0<<UMSEL00); //async uart
	UCSR0C |= (0<<UPM01) | (0<<UPM00); //parity mode disabled
	UCSR0C |= (1<<USBS0); // 1 stop bit
	UCSR0C |= (1<<UCSZ01) | (1<<UCSZ00); // 8bit frame size

	//enabling transmitter 
	UCSR0B = (0<<RXEN0) | (1<<TXEN0);
	
	//UCSR0B |= (1<<UDRIE0); //enabling the UDRE register interrupts
}

void EEPROM_Write(uint8_t data)
{
	//EEPROM Control Register EECR - Write Operations
	EECR &= ~(1<<EEPE);
	while(EECR & (1<<EEPE)){}
	
	//EECR - Programming mode bits
	EECR = (0<<EEPM1) | (0<<EEPM0); //Erase and Write
	
	while(SPMCSR & (1<<SELFPRGEN)){}
	EEDR = data;
	EECR &= ~(1<<EEPE);
	while(EECR & (1<<EEPE)){}
	EECR |= (1<<EEMPE);
	EECR |= (1<<EEPE);
}

void EEPROM_Read()
{	
	//EEPROM Control Register EECR - Read Operations
	EECR &= ~(1<<EEPE);
	while(EECR & (1<<EEPE)){}
	EEDR = 0x00;
	EECR = (1<<EERE);
}

int main(void)
{
	uint8_t data;
	data = 0x41;
    sei(); //Set Enable Interrupts 
	EEPROM_Init(); // Initialize EEPROM 
	UART_Init();
	EEPROM_Write(data);
	EEPROM_Read();
	ReadData = EEDR;
    while (1) 
    {
		while(!(UCSR0A & (1<<UDRE0))){} //if UDRE bit is set to 1, we can write the buffer
		UDR0 = ReadData;
		while(!(UCSR0A & (1<<UDRE0))){}
		UDR0 = '\n';
		_delay_ms(2000); //short delay
    }
}

/*ISR(USART_UDRE_vect)
{
	UDR0 = ReadData;
}*/
