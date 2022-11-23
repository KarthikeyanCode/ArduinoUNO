//uart header file - contains preprocessor directives and fuinction declarations

#define F_CPU 16000000UL // CPU frequency - 16Mhz

#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>


//Functions
extern void UART_Init(void); //Intialize uart

extern void UART_Tx(uint8_t); //Transmit 8Bits to uart

extern void UART_Tx_String(uint8_t*); //Transmit String to uart

extern uint8_t UART_Rx(void); //Receive 8bits from uart

extern void UART_Rx_String(uint8_t*); //Receive string from uart
