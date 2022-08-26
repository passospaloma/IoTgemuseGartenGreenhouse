/*Program: GemüseGarten WeatherStation
   created by Paloma Passos
*/

//Include Libraries
#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>
#include "secrets.h"
BlynkTimer timer;

// Auth Token in the Blynk App.
char auth[] = SECRET_AUTH;

const char* ssid = SECRET_SSID; // your network SSID (name)
const char* password = SECRET_PASS; // your network password

void readData() {

  int R1 = D3;   // Output Relay 1 GPI0 05 (D3)

  if (isnan(R1)) {
    Serial.println("Unable to read sensor data!");
    return;
  }
  pinMode(R1, OUTPUT);
  digitalWrite(R1, LOW);
}


void setup()
{
  Serial.begin(115200); // Debug console

  Blynk.begin(auth, ssid, password);
  readData();
}

void loop()
{
  Blynk.run(); //Start Blynk
  timer.run();
}
