#include<avr/io.h>
#include<util/delay.h>
#include<avr/interrupt.h>

volatile uint8_t input;

void USART_init()
{
  //setting the baudrate to 9600bps
  UBRR0L = 0x67;
  UBRR0H = 0x67>>8;

  //frame format - UCSR0C register initialization
  UCSR0C = (0<<UMSEL01) | (0<<UMSEL00); //async uart
  UCSR0C |= (0<<UPM01) | (0<<UPM00); //parity check disabled
  UCSR0C |= (0<<USBS0); //1 stop bit
  UCSR0C |= (1<<UCSZ01) | (1<<UCSZ00); //frame size

  //enable the receiver and transmitter
  UCSR0B = (1<<RXEN0) | (1<<TXEN0); 

  sei();

  //enable USART receive interrupt 
  UCSR0B |= (1<<RXCIE0);
}

int main(void)
{
  DDRB = (1<<DDB5); //setting PB5 as digital out
  USART_init();
  while(1)
  {
    //idle
  }
  return 0;
}

ISR(USART_RX_vect)
{
  input = UDR0;
  if(input == 'k')
  {
    //digital high for PB5 pin
    PORTB = (1<<PORTB5);
  }
  else
  {
    //digital low for PB5 pin
    PORTB = (0<<PORTB5);
  }
}
