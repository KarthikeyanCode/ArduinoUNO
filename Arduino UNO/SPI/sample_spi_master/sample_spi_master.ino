//ESP32 SPI master sample code

#include<SPI.h>

void setup() {
  Serial.begin(115200);
  pinMode(2, OUTPUT);
  SPI.begin();//begining SPI 
  SPI.setClockDivider(SPI_CLOCK_DIV8);//settting the clock for SPI
  digitalWrite(SS, HIGH);//
}

void loop() {
  digitalWrite(SS, LOW);
  byte msg= 1;
  byte msg_received = SPI.transfer(msg);
  digitalWrite(SS, HIGH);
  Serial.println(msg_received);
  digitalWrite(2, HIGH);
  delay(1000);
  digitalWrite(2, LOW);
  delay(2000);
}
