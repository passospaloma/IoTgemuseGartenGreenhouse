/*Program: GemüseGarten WeatherStation
   created by Paloma Passos
*/
//Include Libraries
#include <ESP8266WiFi.h>
#include "secrets.h"
#include <BlynkSimpleEsp8266.h>
BlynkTimer timer;

// Auth Token in the Blynk App.
char auth[] = SECRET_AUTH;

const char* ssid = SECRET_SSID; // your network SSID (name)
const char* password = SECRET_PASS; // your network password


void sendUvData()
{
  String UVIndex = "0";
  int sensorValue = 0;
  
  sensorValue = analogRead(A0);  ///connect UV sensor to Analog 0   
  int voltage = (sensorValue * (5.0 / 1023.0))*1000;  //Voltage in miliVolts
  
  if(voltage<50)
  {
    UVIndex = "0";
  }else if (voltage>50 && voltage<=227)
  {
    UVIndex = "0";
  }else if (voltage>227 && voltage<=318)
  {
    UVIndex = "1";
  }
  else if (voltage>318 && voltage<=408)
  {
    UVIndex = "2";
  }else if (voltage>408 && voltage<=503)
  {
    UVIndex = "3";
  }
  else if (voltage>503 && voltage<=606)
  {
    UVIndex = "4";
  }else if (voltage>606 && voltage<=696)
  {
    UVIndex = "5";
  }else if (voltage>696 && voltage<=795)
  {
    UVIndex = "6";
  }else if (voltage>795 && voltage<=881)
  {
    UVIndex = "7";
  }
  else if (voltage>881 && voltage<=976)
  {
    UVIndex = "8";
  }
  else if (voltage>976 && voltage<=1079)
  {
    UVIndex = "9";
  }
  else if (voltage>1079 && voltage<=1170)
  {
    UVIndex = "10";
  }else if (voltage>1170)
  {
    UVIndex = "11";
  }
  
  

  Blynk.virtualWrite(V4, UVIndex);
  Serial.print("UVIndex = ");
  Serial.println(UVIndex); 
   Serial.print("voltage = ");
  Serial.print(voltage);
   Serial.print("sensorvalue = ");
  Serial.print(sensorValue);

}


void setup()   
{
  Serial.begin(115200);
    
   Blynk.begin(auth, ssid, password);
   timer.setInterval(1000L, sendUvData);
 }
 
 
void loop()
{
 
  Blynk.run();
  timer.run();
}
