//thermal door sensor 
int temp_read = A0;
int trig_pin = 12;
int echo_pin = 11;
int door_pin = 10;
void setup()
{
  pinMode(door_pin, OUTPUT);
  pinMode(trig_pin, OUTPUT);
  pinMode(echo_pin, INPUT);
  Serial.begin(9600);
}

void loop()
{
  int duration,distance;
  int temp_analog = analogRead(temp_read);
  float milli_volts = (temp_analog/1024.0)*5000;//analog read values to mv
  float deg_cel = (milli_volts - 500)/10;// mv to deg celsius
  digitalWrite(trig_pin, LOW);
  digitalWrite(trig_pin, HIGH);
  digitalWrite(trig_pin, LOW);
  duration = pulseIn(echo_pin, HIGH);
  distance = (duration * 0.034)/2;
  
  if(distance <= 100)
  {
    if(deg_cel<40 && deg_cel>=32)
    {
      digitalWrite(door_pin, HIGH);
      Serial.print("Distance: ");
      Serial.println(distance);
      Serial.print("Temp: ");
      Serial.println(deg_cel);
   	  Serial.println("Door is open");
    }
    else
    {
      digitalWrite(door_pin, LOW);
      Serial.print("Distance: ");
      Serial.println(distance);
      Serial.print("Temp: ");
      Serial.println(deg_cel);
      Serial.println("Door is closed");
    }
  }
  else
  {
    digitalWrite(door_pin, LOW);
    Serial.print("Distance: ");
    Serial.println(distance);
    Serial.print("Temp: ");
    Serial.println(deg_cel);
    Serial.println("Door is closed");
  }
  delay(2000);
  Serial.println("");
}