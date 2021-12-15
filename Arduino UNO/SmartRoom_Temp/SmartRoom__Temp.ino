// smart room temprature controller
int led_pin = 10;
int motor_pin = 11;
int temp_input = A0;

void setup()
{
  pinMode(led_pin, OUTPUT);
  pinMode(motor_pin, OUTPUT);
  Serial.begin(9600);
}

void loop()
{
  int temp_analog = analogRead(temp_input);
  float milli_volts = (temp_analog/1024.0)*5000;
  float deg_cel = (milli_volts - 500)/10;
  
  if(deg_cel <= 80)
  {
    Serial.print("temp = ");
    Serial.print(deg_cel);
    Serial.println(" deg.cel");
    digitalWrite(motor_pin, LOW);
    digitalWrite(led_pin, HIGH);
  }
  else
  {
    Serial.print("temp = ");
    Serial.print(deg_cel);
    Serial.println(" deg.cel");
    digitalWrite(led_pin, LOW);
    digitalWrite(motor_pin, HIGH);
  }
  delay(3000);
}