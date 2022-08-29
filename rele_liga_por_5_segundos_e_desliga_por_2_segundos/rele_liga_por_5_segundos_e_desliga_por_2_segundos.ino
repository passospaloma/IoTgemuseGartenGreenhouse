/*Program: GemüseGarten WeatherStation
   created by Paloma Passos
*/

//Include Libraries
#include <Wire.h>
#include <SPI.h>
#include <ESP8266WiFi.h>

#include <SimpleTimer.h>

int rele1 = D1;

void setup() {
 pinMode(rele1, OUTPUT);
 
             }
 
void loop(){

  digitalWrite(rele1, HIGH);
 delay (5000); //Fica ligado por 5 segundos o relé e o led 
 
 digitalWrite(rele1, LOW);
 delay (2000); //Fica desligado por 2 segundos o relé e o led 
  digitalWrite(rele1, HIGH);
 delay (5000); //Fica ligado por 5 segundos  o relé e o led 
 
 digitalWrite(rele1, LOW);
 delay (2000); //Fica desligado por 2 segundos o relé e o led

   digitalWrite(rele1, HIGH);
 delay (500); //Fica ligado por 5 segundos o relé e o led 
 
 digitalWrite(rele1, LOW);
 delay (2000); //Fica desligado por 2 segundos o relé e o led 


  
}
