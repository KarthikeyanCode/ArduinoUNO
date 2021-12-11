/*
 * Arduino_I2C.c
 *
 * Author : KarthikeyanCode
 */ 

#define F_CPU 16000000UL 

#include<avr/io.h>
#include<util/delay.h>
#include<avr/interrupt.h>

volatile uint8_t data;

//initializing the TWI process (I2C)
void TWI_init()
{	
	//Enabling interrupts globally 
	sei();
	
	//TWCR - two wire control register 
	//enabling the TWI bit for TWI interface
	TWCR = (1<<TWEN);
	
	//writing the acknowledge bit to 1
	TWCR |= (1<<TWEA);
	
	//setting TWIE interrupt enable bit
	TWCR |= (1<<TWIE);
	
	//setting the SCL frequency 
	TWBR = 0x00;
	TWSR = (0<<TWPS1) | (0<<TWPS0);
	
}

int main(void)
{
	DDRB = (1<<DDB5);
	data = 'C';
    TWI_init();
    while (1) 
    {
		PORTB ^= (1<<PORTB5);
		_delay_ms(1000);
		PORTB ^= (1<<PORTB5);
		_delay_ms(1000);
    }
}

ISR(TWI_vect)
{
	//sets the start bit
	TWCR ^= (1<<TWSTA);
	_delay_ms(1);
	TWCR ^= (1<<TWSTA); //clearing the TWSTA bit after start condition has been transmitted
	
	//writing data to the TWDR register 
	TWDR = data;
	
	//setting the stop bit, so that we can start the transmission again in another ISR
	TWCR |= (1<<TWSTO);
	_delay_ms(1);
	
	//clearing the TWINT flag after servicing the interrupt
	TWCR ^= (1<<TWINT);
}