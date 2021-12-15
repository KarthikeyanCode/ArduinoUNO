//Automated door using ultrasonic sensor
int buzzer_pin = 11;

void setup()
{
  pinMode(buzzer_pin, OUTPUT);
  pinMode(10, OUTPUT);
  pinMode(9, INPUT);
  Serial.begin(9600);
}

void loop()
{
  float duration, distance;
  
  digitalWrite(10, LOW);
  digitalWrite(10, HIGH);
  digitalWrite(10, LOW);
  
  duration = pulseIn(9, HIGH);
  distance = (duration * 0.034)/2;
  
  if(distance <= 80)
  {
    digitalWrite(buzzer_pin, HIGH);
    Serial.println("Door is open");
    Serial.print("Distance = ");
    Serial.print(distance);
    Serial.println(" cm");
  }
  else
  {
    digitalWrite(buzzer_pin, LOW);
    Serial.println("Door is closed");
    Serial.print("Distance = ");
    Serial.print(distance);
    Serial.println(" cm");
  }
  delay(3000);
}