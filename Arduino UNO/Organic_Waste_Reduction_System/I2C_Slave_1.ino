// C++ code
//crate 1
#include<LiquidCrystal.h>
#include<Wire.h>
float gas = 0;
float tmp = 0;
float mv = 0;
int led_pin = 8;
int tmp_read = 0;
char gas_string[7];
char tmp_string[7];
LiquidCrystal lcd(12, 11, 5, 4, 3, 2);

void setup()
{
  pinMode(A0, INPUT);
  pinMode(A1, INPUT);
  pinMode(9, OUTPUT);
  pinMode(10, OUTPUT);
  pinMode(led_pin, OUTPUT);
  Wire.begin(1);
  Wire.onRequest(reqEvent);
  Wire.onReceive(recEvent);
  lcd.begin(16, 2);
  Serial.begin(9600);
}

void loop()
{
  gas = analogRead(A0);
  tmp_read = analogRead(A1);
  mv = (tmp_read/1024.0)*5000;
  tmp = (mv - 500)/10;
  lcd.setCursor(14,1);
  lcd.print("R1");
  lcd.setCursor(0,0); // (column, row)
  lcd.print("Gas: ");
  lcd.print(gas);
  lcd.setCursor(0,1); //(column, row)
  lcd.print("Tmp: ");
  lcd.print(tmp);
  //Serial.println(rank);
  //pin 9 is MSB and 10 is LSBWire.begin(1);
  delay(53);
}

void reqEvent()
{
  dtostrf(gas,7,2,gas_string);
  dtostrf(tmp,7,2,tmp_string);
  //Serial.print("some random string");
  Wire.write(gas_string, sizeof(gas_string));
  Wire.write(tmp_string, sizeof(tmp_string));
  
}

void recEvent(int no_bytes)
{
  int rank;
 while(Wire.available())
 {
   rank = Wire.read();
 }
  if(rank == 1)
  {
    digitalWrite(9, LOW);
    digitalWrite(10, HIGH);
  }
  else if(rank == 2)
  {
    digitalWrite(9, HIGH);
    digitalWrite(10, LOW);
  }
  else if(rank == 3)
  {
    digitalWrite(9, HIGH);
    digitalWrite(10, HIGH);
  }
  
}