/*Program: GemüseGarten WeatherStation
   created by Paloma Passos
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

int R1  = D2;            // Output Relay 1 GPI0 05 (D2)
int R2  = D4;            // Output Relay 2 GPI0 04 (D4)


void readData() {

  int AirValue = 845; //Setting air value
  int WaterValue = 403; //Setting water value
  int intervals = (AirValue - WaterValue) / 3;
  int soil = 0;
  String sm = "0";

  soil1 = analogRead(A0); //connect soil sensor to Analog 0

  if (soil > WaterValue && soil < (WaterValue + intervals))
  {
    sm = "WET";
  }
  else if (soil > (WaterValue + intervals) && soil < (AirValue - intervals))
  {
    sm = "MOIST";
  }
  else if (soil < AirValue && soil > (AirValue - intervals))
  {
    sm = "DRY";
  }

  int h = dht.readHumidity();
  float t = dht.readTemperature();
  int hi = dht.computeHeatIndex(t, h, false);

  if (isnan(t) || isnan(h) || isnan(hi)) {
    Serial.println("Unable to read sensor data!");
    return;
  }

  if (isnan(R1) || isnan(R2) ) {
    Serial.println("Unable to read sensor data!");
    return;
  }

  Blynk.virtualWrite(V0, t);
  Blynk.virtualWrite(V1, h);
  Blynk.virtualWrite(V2, hi);
  Blynk.virtualWrite(V3, sm);
}


void setup()
{
  Serial.begin(115200);

  // Inicializa o DHT22
  dht.begin();

  Blynk.begin(auth, ssid, password);

  timer.setInterval(1000L, readData);
  pinMode(R1, OUTPUT);
  pinMode(R2, OUTPUT);
  digitalWrite(R1, HIGH);
  digitalWrite(R2, HIGH);
}


void loop()
{
  Blynk.run();
  timer.run();
}
