//Arduino UNO SPI slave sample code

#include<SPI.h>

volatile bool received;
volatile byte srec, ssend;

void setup() {
  Serial.begin(115200);
  SPCR |= _BV(SPE);//activating the SPI register
  received = false; //true if msg received and false otherwise
  SPI.attachInterrupt();

}

ISR (SPI_STC_vect)
{
  srec = SPDR;
  received = true;
}

void loop() {
  if(received)
  {
    Serial.println(srec);
    ssend = 1;
    SPDR = ssend; //update the SPDR register with the data to send to master
    delay(2000);
  }
}
