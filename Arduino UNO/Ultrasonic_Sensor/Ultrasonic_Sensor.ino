//ultrasonic sensor code

void setup()
{
  pinMode(11, OUTPUT);
  pinMode(10, INPUT);
  Serial.begin(9600);
}

void loop()
{
  float duration, distance;
  digitalWrite(11, LOW);
  digitalWrite(11, HIGH);
  //delayMicroseconds(10);
  digitalWrite(11, LOW);
  duration = pulseIn(10, HIGH);
  distance = (duration * 0.034)/2;
  Serial.print("Distance = ");
  Serial.print(distance);
  Serial.println(" cm");
  delay(2000);
}