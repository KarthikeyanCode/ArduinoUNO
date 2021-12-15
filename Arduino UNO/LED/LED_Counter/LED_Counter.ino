// LED counter

int red_pin = 13;
int green_pin = 12;
int blue_pin = 11;
void setup()
{
  pinMode(red_pin, OUTPUT);
  pinMode(green_pin, OUTPUT);
  pinMode(blue_pin, OUTPUT);
  Serial.begin(9600);
}

void loop()
{
  for(int i=0;i<=7;i++)
  {
    if(i == 0)
    {
      delay(1000);
      digitalWrite(red_pin, LOW);
      digitalWrite(green_pin, LOW);
      digitalWrite(blue_pin, LOW);
      Serial.print("Count: ");
      Serial.println(i);
      delay(1000);
    }
    else if(i==1)
    {
      delay(1000);
      digitalWrite(red_pin, LOW);
      digitalWrite(green_pin, LOW);
      digitalWrite(blue_pin, HIGH);
      Serial.print("Count: ");
      Serial.println(i);
      delay(1000);
    }
    else if(i==2)
    {
      delay(1000);
      digitalWrite(red_pin, LOW);
      digitalWrite(green_pin, HIGH);
      digitalWrite(blue_pin, LOW);
      Serial.print("Count: ");
      Serial.println(i);
      delay(1000);
    }
    else if(i==3)
    {
      delay(1000);
      digitalWrite(red_pin, LOW);
      digitalWrite(green_pin, HIGH);
      digitalWrite(blue_pin, HIGH);
      Serial.print("Count: ");
      Serial.println(i);
      delay(1000);
    }
    else if(i==4)
    {
      delay(1000);
      digitalWrite(red_pin, HIGH);
      digitalWrite(green_pin, LOW);
      digitalWrite(blue_pin, LOW);
      Serial.print("Count: ");
      Serial.println(i);
      delay(1000);
    }
    else if(i==5)
    {
      delay(1000);
      digitalWrite(red_pin, HIGH);
      digitalWrite(green_pin, LOW);
      digitalWrite(blue_pin, HIGH);
      Serial.print("Count: ");
      Serial.println(i);
      delay(1000);
    }
    else if(i==6)
    {
      delay(1000);
      digitalWrite(red_pin, HIGH);
      digitalWrite(green_pin, HIGH);
      digitalWrite(blue_pin, LOW);
      Serial.print("Count: ");
      Serial.println(i);
      delay(1000);
    }
    else
    {
      delay(1000);
      digitalWrite(red_pin, HIGH);
      digitalWrite(green_pin, HIGH);
      digitalWrite(blue_pin, HIGH);
      Serial.print("Count: ");
      Serial.println(i);
      delay(1000);
    }
  }
  digitalWrite(red_pin, LOW);
  digitalWrite(green_pin, LOW);
  digitalWrite(blue_pin, LOW);
  while(true){}
}