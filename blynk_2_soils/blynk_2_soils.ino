/*Program: GemüseGarten WeatherStation
  created by Paloma Passos
*/

//Include Libraries
#include <DHT.h>
#include <ESP8266WiFi.h>
#include "secrets.h"
#include <BlynkSimpleEsp8266.h>
BlynkTimer timer;


// Auth Token in the Blynk App.
char auth[] = SECRET_AUTH;

const char* ssid = SECRET_SSID; // your network SSID (name)
const char* password = SECRET_PASS; // your network password


//Function to read soil moisture sensor
void readData1() {

  int AirValue1 = 845; //Setting air value
  int WaterValue1 = 403; //Setting water value
  int intervals1 = (AirValue1 - WaterValue1) / 3;
  int soil1 = 0;
  String sm1 = "0";

  soil1 = analogRead(A0); //connect soil sensor to Analog 0

  if (soil1 > WaterValue1 && soil1 < (WaterValue1 + intervals1))
  {
    sm1 = "WET";
  }
  else if (soil1 > (WaterValue1 + intervals1) && soil1 < (AirValue1 - intervals1))
  {
    sm1 = "MOIST";
  }
  else if (soil1 < AirValue1 && soil1 > (AirValue1 - intervals1))
  {
    sm1 = "DRY";
  }
  Blynk.virtualWrite(V8, sm1);
}


void readData2() {

  int AirValue2 = 845; //Setting air value
  int WaterValue2 = 403; //Setting water value
  int intervals2 = (AirValue2 - WaterValue2) / 3;
  int soil2 = 0;
  String sm2 = "0";

  soil2 = digitalRead(D7); //connect soil sensor to D7 pin
  if (soil2 > WaterValue2 && soil2 < (WaterValue2 + intervals2))
  {
    sm2 = "WET";
  }
  else if (soil2 > (WaterValue2 + intervals2) && soil2 < (AirValue2 - intervals2))
  {
    sm2 = "MOIST";
  }
  else if (soil2 < AirValue2 && soil2 > (AirValue2 - intervals2))
  {
    sm2 = "DRY";
  }

  Blynk.virtualWrite(V9, sm2);
}


void setup()
{
  Serial.begin(115200);

  readData1();
  readData2();

  Blynk.begin(auth, ssid, password);

  timer.setInterval(5000L, readData1);
  timer.setInterval(5000L, readData2);
}


void loop()
{
  Blynk.run();
  timer.run();
}
