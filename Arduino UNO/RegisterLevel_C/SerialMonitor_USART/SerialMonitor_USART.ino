#define F_CPU 16000000UL // CPU frequency - 16Mhz

#include<avr/io.h>
#include<util/delay.h>

uint8_t *data = "Check\n";

//initialize the USART communication
//we will be setting baud rate, frame format and enabling transmitter and receiver
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

void USART_Transmit(uint8_t *ByteData)
{
	while(*ByteData)
	{
		while((UCSR0A & (1<<UDRE0)) == 0)
		{
			//idle until UDR0 register TX buffer is free
		}
		//writing to UDR0 will directly put the data in TX buffer and reading will read data from RX buffer
		UDR0 = *ByteData;
		ByteData++;	
	}
}

int main(void)
{
	USART_init();
	while(1)
	{
		USART_Transmit(data);
		_delay_ms(200);
	}
	return 0;
}