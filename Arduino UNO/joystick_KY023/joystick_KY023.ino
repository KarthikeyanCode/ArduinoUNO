

void setup() {
  pinMode(7, INPUT_PULLUP);//making pin 7 as input and enabling internal pull up resistor 
  Serial.begin(9600);
}

void loop() {
  //reading values
  int xvalue = analogRead(A0);
  int yvalue = analogRead(A1);
  int button = digitalRead(7);

  //logging them to serial monitor
  Serial.print("X: ");
  Serial.println(xvalue);
  Serial.print("Y: ");
  Serial.println(yvalue);
  Serial.print("button: ");
  Serial.println(button);
  Serial.println("");

  //delay
  delay(1000);
}
