//UART c file - Contains function definitions

#include "uart.h"

//initialize the USART communication
//we will be setting baud rate, frame format and enabling transmitter and receiver
void UART_Init()
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

void UART_Tx(uint8_t Data)
{
	while((UCSR0A & (1<<UDRE0)) == 0)
	{
		//idle until UDR0 register TX buffer is free
	}
	//writing to UDR0 will directly put the data in TX buffer and reading will read data from RX buffer
	UDR0 = Data;
}

void UART_Tx_String(uint8_t *ByteData)
{
	while(*ByteData)
	{
		UART_Tx(*ByteData); //pass the byte to the UART_TX function
		ByteData++; //increment the pointer
	}
}

uint8_t UART_Rx()
{
	while(!(UCSR0A & (1<<RXC0))){} //Idle untill the receive bit is set
	return UDR0; //Then read from the UDR0 register 
}

void UART_Rx_String(uint8_t* ByteData)
{
	int iter=0;
	while(ByteData[iter] != '\0')
	{
		ByteData[iter] = UART_Rx();
		iter++;
	}
}
