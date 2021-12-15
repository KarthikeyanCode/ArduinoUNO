// Reading the values of temprature sensor
int temp_input = A0;
void setup()
{
  Serial.begin(9600);
}

void loop()
{
  int temp_analog = analogRead(temp_input);
  float milli_volts = (temp_analog/1024.0)*5000;
  float deg_cel = (milli_volts - 500)/10;//10mv/deg_cel - sensor 
  Serial.print("Temprature = ");
  Serial.println(deg_cel);
  delay(2000);
  Serial.println("");
}