#include<avr/io.h>
#include<util/delay.h>

#define F_CPU 16000000UL

void USART_init()
{
  //setting the baudrate
  UBRR0L = 0x67;
  UBRR0H = 0x67>>8;

  //setting the UCSR0C register - frame format 
  UCSR0C = (0<<UMSEL01) | (0<<UMSEL00); //async uart
  UCSR0C |= (0<<UPM01) | (0<<UPM00); //parity disabled
  UCSR0C |= (0<<USBS0); //setting one stop bit
  UCSR0C |= (1<<UCSZ01) | (1<<UCSZ00); //8bit frame size

  //setting the UCSR0B register - enable transmitter and receiver
  UCSR0B = (1<<RXEN0) | (1<<TXEN0);
}

uint8_t Rec()
{
  uint8_t data;
  while((UCSR0A & (1<<RXC0)) == 0)
  {
    //idle untill rec flag is set in UCSR0A and rec buffer is full
  }
  data = UDR0;
  return data;
}

void transmit(uint8_t data)
{
  while((UCSR0A & (1<<TXC0) == 0))
  {
    //idle untill transmission buffer is empty
  }
  UDR0 = data;
}

int main(void)
{
  USART_init();
  uint8_t data;
  while(1)
  {
    data = Rec();
    transmit(data);
    //_delay_ms(1000);
  }
  return 0;
}
