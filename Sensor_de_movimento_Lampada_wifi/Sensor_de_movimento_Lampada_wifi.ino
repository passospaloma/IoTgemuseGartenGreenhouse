
 /*Program: GemüseGarten WeatherStation
   created by Paloma Passos
*/

//Include Libraries
#include <ESP8266WiFi.h>

#include <SPI.h>
#include <Wire.h>

#include <SimpleTimer.h>



//definição do pino de saída do sensor PIR 

int PINLight = D1;
int PINSensor = D4;

void setup() {
   Serial.begin(115200);
   
  pinMode(PINSensor, INPUT);
  pinMode(PINLight, OUTPUT);
}

   

void loop()
{
  int sensor = digitalRead(PINSensor);

  if (sensor == LOW ){
    digitalWrite(PINLight, LOW);
  } else {
    digitalWrite(PINLight, HIGH);
  }

  }
  
