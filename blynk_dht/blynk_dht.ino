/*Program: GemüseGarten WeatherStation
   created by Paloma Passos
    ESP8266 Deep sleep mode example

*/

//Include Libraries
#include <DHT.h>
#include <ESP8266WiFi.h>
#include "secrets.h"
#include <BlynkSimpleEsp8266.h>
BlynkTimer timer;

DHT dht(D1, DHT22); // what digital pin the DHT22 is conected to

// Auth Token in the Blynk App.
char auth[] = SECRET_AUTH;

const char* ssid = SECRET_SSID; // your network SSID (name)
const char* password = SECRET_PASS; // your network password

const int sleepTime = 10;

//Function to read uv sensor
void readData() {
 
  int h = dht.readHumidity();
  float t = dht.readTemperature();
  int hi = dht.computeHeatIndex(t, h, false);

  if (isnan(t) || isnan(h) || isnan(hi)) {
    Serial.println("Unable to read sensor data!");
    return;
  }
  //Write values in Blynk App
  Blynk.virtualWrite(V1, t);
  Blynk.virtualWrite(V2, h);
  Blynk.virtualWrite(V3, hi);
  
}

void goToSleep(){

   ESP.deepSleep(5 * 3 * 1000000); //sleep for 15 seconds


}

void setup()
{
  
  Serial.begin(115200);
 
  // Initiate DHT22 sensor
  dht.begin();

  Blynk.begin(auth, ssid, password); //Auth into blynk server

  timer.setInterval(20000L, readData);
   

 }


void loop()
{
  Blynk.run();
  timer.run();
 
}
