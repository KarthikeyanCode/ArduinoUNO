#define F_CPU 16000000UL

#include<avr/io.h>
#include<util/delay.h>
#include<avr/interrupt.h>

volatile uint8_t flag;
volatile uint8_t data, data1, newline;

void I2C_Slave_init()
{
	//global enable interrupts
	sei();
	
	////clearing the interrupt bit TWINT
	TWCR = (0<<TWINT);
	
	//enabling the interrupts for TWINT bit
	TWCR |= (1<<TWIE);
	
	//enabling TWI enable
	TWCR |= (1<<TWEN);
	
	//setting the prescalar value for SCL freq
	TWSR = (1<<TWPS1) | (1<<TWPS0);
	
	//setting the TWBR - bit rate register to 0 
	TWBR &= 0x00;//sets SCL to 1Mhz
	
	//slave address is 1
	TWAR = (1<<TWA0);
	
	//enabling listening to general call to identify address in serial data
	TWAR |= (1<<TWGCE);
}

void USART_init()
{
	//setting the baud rate - 103 in decimal 0x67 in hex for 9600bps
	UBRR0L = 0x67; 
	UBRR0H = (0x67>>8);
	
	//setting the UCSR0C register - frame format
	UCSR0C = (0<<UMSEL01) | (0<<UMSEL00); //async usart
	UCSR0C |= (0<<UPM01) | (0<<UPM00); //parity mode disabled
	UCSR0C |= (0<<USBS0); //one stop bit
	UCSR0C |= (1<<UCSZ01) | (1<<UCSZ00); //8bit frame size 
	
	//setting the UCSR0B register 
	UCSR0B = (1<<RXEN0) | (1<<TXEN0);
	UCSR0B |= (0<<UCSZ02); //frame size 
}

void USART_transmit()
{
	while((UCSR0A & (1<<TXC0)) == 0)
	{
		//IDLE until UDR0 is ready
	}
	UDR0 = data;
}
/*
void alive()
{
	while((UCSR0A & (1<<TXC0)) == 0)
	{
		//IDLE until UDR0 is ready
	}
	UDR0 = data1;
	while((UCSR0A & (1<<TXC0)) == 0)
	{
		//IDLE until UDR0 is ready
	}
	UDR0 = newline;
}
*/
int main(void)
{
	I2C_Slave_init();
	USART_init();
	data1 = 'A';
	newline = '\n';
	flag = 0;
    while (1) 
    {
		if(flag == 1)
		{
			USART_transmit();
			flag=0;
		}
		//alive();
		//_delay_ms(1000);
    }
	return 0;
}
 
//TWI vect interrupt 
ISR(TWI_vect)
{
	flag = 1;
	
	//reading the data
	data = TWDR;
	
	//clearing the TWINT bit after the interrupt service routine 
	TWCR |= (1<<TWINT);
}