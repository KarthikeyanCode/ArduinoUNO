#include<avr/io.h>
#include<util/delay.h>

#define F_CPU 16000000UL

void USART_init()
{
  //setting the baud rate to 9600bps
  UBRR0L = 0x67;
  UBRR0H = 0x67>>8;

  //setting the frame format
  UCSR0C = (0<<UMSEL01) | (0<<UMSEL00); //async UART
  UCSR0C |= (0<<UPM01) | (0<<UPM00); //parity check disable
  UCSR0C |= (0<<USBS0); //1 stop bit
  UCSR0C |= (1<<UCSZ01) | (1<<UCSZ00); //8bit frame size of transmission of character
  
  //Enable receiver
  UCSR0B = (1<<RXEN0) | (1<<TXEN0);
}

uint8_t Rec_data()
{
  uint8_t data;
  while((UCSR0A & (1<<RXC0)) == 0)
  {
    //idle untill the RXC0 flag is set i.e receive buffer is full and unread
  }
  data = UDR0;
  return data;
}

int main(void)
{
  USART_init();
  uint8_t data;
  DDRB = (1<<DDB5); //make pinb5 as digital output
  while(1)
  {
    data = Rec_data();
    if(data == 'k' || data == 'K')
    {
      //set on board LED to high
      PORTB = (1<<PORTB5);
    }
    else
    {
      //set on board LED to low
      PORTB = (0<<PORTB5);
    }
    _delay_ms(1000); //delay for 1 sec
  }
  return 0;
}
