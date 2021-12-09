#include<avr/io.h>
#include<util/delay.h>
#include<avr/interrupt.h>

#define F_CPU 16000000UL

volatile uint8_t transmit_buffer;

void USART_init()
{
  //setting the baud rate to 9600bps
  UBRR0L = 0x67;
  UBRR0H = 0x67>>8;

  //configuring the UCSR0C register for frame format
  UCSR0C = (0<<UMSEL01) | (0<<UMSEL00); //async uart
  UCSR0C |= (0<<UPM01) | (0<<UPM00); //partiy mode disabled
  UCSR0C |= (1<<USBS0); // 1 stop bit
  UCSR0C |= (1<<UCSZ01) | (1<<UCSZ00); // 8bit frame size

  //enabling transmitter and receiver
  UCSR0B = (1<<RXEN0) | (1<<TXEN0);

  //gloabal enable interrupts
  sei();

  UCSR0B |= (1<<UDRIE0); //enabling the UDRE register interrupts 
   
}

int  main(void)
{
  DDRB = (1<<DDB5);
  USART_init();
  transmit_buffer = 'k';
  while(1)
  {
    PORTB = (1<<PORTB5);
    _delay_ms(1000);
    PORTB = (0<<PORTB5);
    _delay_ms(1000);
  }
  return 0;
}

ISR(USART_UDRE_vect)
{
  UDR0 = transmit_buffer;
}
