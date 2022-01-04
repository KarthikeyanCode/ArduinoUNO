/*
 * I2C_LCD.c
 *
 * Created: 18-12-2021 21:31:19
 * Author : KarthikeyanCode
 */ 

#define F_CPU 16000000UL

#include<avr/io.h>
#include<util/delay.h>
#include<avr/interrupt.h>

uint8_t address = 0x27;
uint8_t response;

void USART_init()
{
	//setting the baud rate
	//UBRR0[11:0] register
	//UBRR0 = (16Mhz/16*BAUD)-1
	UBRR0L = 0x67; //0x67 = 103 is the value for UBRR0 register to get baud rate of 9600bps
	UBRR0H = 0x67>>8;

	//setting frame format
	UCSR0C = (1<<UCSZ01) | (1<<UCSZ00); //frame size is 8bits
	UCSR0C |= (0<<UMSEL01) | (0<<UMSEL00); //Asynchronous USART
	UCSR0C |= (0<<UPM01) | (0<<UPM00); //parity disabled
	UCSR0C |= (0<<USBS0); //1 stop bit

	//enabling receiver and transmitter
	UCSR0B = (1<<RXEN0) | (1<<TXEN0); //setting 1 to the RX and TX enable registers
}

void USART_Transmit(uint8_t Byte_data)
{
	while((UCSR0A & (1<<UDRE0)) == 0)
	{
		//idle untill UDR0 register TX buffer is free
	}
	//writing to UDR0 will directly put the data in TX buffer and reading will read data from RX buffer
	UDR0 = Byte_data;
}

void TWI_init()
{
	//setting the TWBR register
	TWBR = 0x02; 
	
	//setting the TWCR register
	//TWCR = (1<<TWEN) | (1<<TWEA);
	
	//setting the TWSR register
	TWSR = (1<<TWPS1) | (1<<TWPS0);
}

void TWI_start()
{
	//clearing TWINT bit, setting the TWEN (enable) bit and sending the start condition
	//setting the acknowledge bit
	TWCR = (1<<TWINT) | (1<<TWSTA) | (1<<TWEN); 
	while(!(TWCR & (1<<TWINT))) {} //monitoring the interrupt bit 
	while((TWSR & 0xF8) != 0x08) {} //status value for start condition has been transmitted
}

void TWI_AddressRead()
{
	//transmitting the slave address and read mode
	TWDR = (0x27<<1) | (0<<0);
	TWCR = (1<<TWINT) | (1<<TWEN);//starting the TWI operation
	while(!(TWCR & (1<<TWINT))) {} //checking the setting of TWINT 
	while((TWSR & 0xF8) != 0x18) {} //checking for acknowledgment
}

void TWI_send()
{
	//loading the value in TWDR
	TWDR = 0x61;
	TWCR = (1<<TWINT) | (1<<TWEN);//starting the TWI operation
	while(!(TWCR & (1<<TWINT))) {} //checking the setting of TWINT
	while((TWSR & 0xF8) != 0x28) {} //checking for acknowledgment
}

void TWI_stop()
{
	
	TWCR = (1<<TWINT) | (1<<TWSTO) | (1<<TWEN); //sending the stop bit
	while(!(TWCR & (1<<TWSTO))) {}
}

int main(void)
{
	//setting the pull-up resistor for I2C
	DDRC = (0<<DDC5);
	PORTC = (1<<PORTC5);
	
	USART_init();
	
	TWI_init();
	
	//check the completion
	USART_Transmit('C');
	USART_Transmit('h');
	USART_Transmit('e');
	USART_Transmit('c');
	USART_Transmit('k');
	USART_Transmit(48);
	USART_Transmit('\n');
	_delay_ms(1000); //delay of 1 second
	
	TWI_start();
	
	USART_Transmit('C');
	USART_Transmit('h');
	USART_Transmit('e');
	USART_Transmit('c');
	USART_Transmit('k');
	USART_Transmit(49);
	USART_Transmit('\n');
	_delay_ms(1000); //delay of 1 second
	
	TWI_AddressRead();
	
	USART_Transmit('C');
	USART_Transmit('h');
	USART_Transmit('e');
	USART_Transmit('c');
	USART_Transmit('k');
	USART_Transmit(50);
	USART_Transmit('\n');
	_delay_ms(1000); //delay of 1 second
	
	while(1)
	{
		TWI_send();
	
		USART_Transmit('C');
		USART_Transmit('h');
		USART_Transmit('e');
		USART_Transmit('c');
		USART_Transmit('k');
		USART_Transmit(51);
		USART_Transmit('\n');
		_delay_ms(1000); //delay of 1 second
	}
	
	TWI_stop();
	
	USART_Transmit('C');
	USART_Transmit('h');
	USART_Transmit('e');
	USART_Transmit('c');
	USART_Transmit('k');
	USART_Transmit(52);
	USART_Transmit('\n');
	_delay_ms(1000); //delay of 1 second
	
	while(1)
	{
		//IDLE
	}
}

