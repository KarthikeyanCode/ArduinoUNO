#include<avr/io.h>
#include<util/delay.h>
#include<avr/interrupt.h>

volatile uint8_t data;

void USART_init()
{
  //setting baudrate
  UBRR0L = 0x67; //baudrate 9600bps
  UBRR0H = 0x67>>8;

  //setting frame format
  UCSR0C = 0x06;

  //enabling transmitter and receiver and enabling interrupts for RXC0 and TXC0 flags
  UCSR0B = 0xD8;

  sei();
}

int main(void)
{
  DDRB = (1<<DDB5);
  USART_init();
  while(1)
  {
    PORTB ^= (1<<PORTB5);
    _delay_ms(1000);
    PORTB ^= (1<<PORTB5);
    _delay_ms(1000);
  }
  return 0;
}

ISR(USART_RX_vect)
{
  data = UDR0;
  UDR0 = data;
}
