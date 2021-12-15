// forever while loop with serial monitor

int red_led = 10;
int count = 1;

void setup()
{
  pinMode(red_led, OUTPUT);
  Serial.begin(9600);
}

void loop()
{
  digitalWrite(red_led, HIGH);
  delay(1000); // Wait for 1000 millisecond(s)
  digitalWrite(red_led, LOW);
  delay(1000); // Wait for 1000 millisecond(s)
  count++;
  Serial.print("Count: ");
  Serial.println(count);
  if(count == 4)
  {
    digitalWrite(red_led,LOW);
    while(true)
    {}
  }
}