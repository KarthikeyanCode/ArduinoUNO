//interfacing DHT11 

#include "DHT.h"

#define DHTPIN 2     // Digital pin connected to the DHT sensor
#define DHTTYPE DHT22   // DHT 22  

DHT dht(2, 11);

void setup() {
  Serial.begin(9600);
  Serial.println("DHT11 test!");
  dht.begin();
}

void loop() {
  // Wait a few seconds between measurements.
  delay(2000);


  float h = dht.readHumidity();

  float t = dht.readTemperature();//read temp in deg cel

  float f = dht.readTemperature(true);//read temp in faranheit

  Serial.println(h);
  Serial.print(t);
  Serial.println(" deg cel");
  Serial.print(f);
  Serial.println(" F");
}
