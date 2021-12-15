//glow the led for 1sec when push button is on

int red_led = 10;
int push_button = 2;

void setup(){
  pinMode(red_led, OUTPUT);
  pinMode(push_button, INPUT);//to read the state of push button
}

void loop(){
 if(digitalRead(push_button))
 {
   digitalWrite(red_led, HIGH);
   delay(1000);//1 sec delay
   digitalWrite(red_led, LOW);
 }
 else
 {
 	digitalWrite(red_led, LOW); 
 }
}
  