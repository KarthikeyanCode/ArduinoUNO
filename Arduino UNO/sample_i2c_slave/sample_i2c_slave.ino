//sample arduino I2C slave code

#include<Wire.h>

byte x;
void setup() {
  Wire.begin(1);
  Wire.onRequest(onreq);
}

void loop() {
  
}

void onreq()
{
  x = 4;
  Wire.write(x);
}
