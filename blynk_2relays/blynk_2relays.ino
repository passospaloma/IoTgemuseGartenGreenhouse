 /*Program: GemüseGarten WeatherStation
   created by Paloma Passos
*/

//Include Libraries
#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>
#include "secrets.h"
BlynkTimer timer;
 
// You should get Auth Token in the Blynk App.
// Go to the Project Settings (nut icon).
char auth[] = SECRET_AUTH;
 

// Auth Token in the Blynk App.
char auth[] = SECRET_AUTH;

const char* ssid = SECRET_SSID; // your network SSID (name)
const char* password = SECRET_PASS; // your network password

void readData(){

  int R1  = D2;            // Output Relay 1 GPI0 05 (D2)
  int R2  = D4;            // Output Relay 2 GPI0 04 (D4)

  
  if (isnan(R1) || isnan(R2) ) {
    Serial.println("Unable to read sensor data!!");
    return;
  }
  pinMode(R1,OUTPUT);
  digitalWrite(R1, LOW);
  pinMode(R2,OUTPUT);
  digitalWrite(R2, LOW);
 
}
 

void setup()
{
  Serial.begin(115200);         // Debug console
  
 Blynk.begin(auth, ssid, password);
  readData();
 }
 
void loop()
{
  Blynk.run();
  timer.run();
}
