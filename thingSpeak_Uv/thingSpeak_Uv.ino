/*Program: GemüseGarten WeatherStation
   created by Paloma Passos
*/

//Include Libraries
#include <SPI.h>
#include<Wire.h>
#include <ESP8266WiFi.h>
#include "secrets.h"
#include "ThingSpeak.h"

char ssid[] = SECRET_SSID;   // your network SSID (name)
char pass[] = SECRET_PASS;   // your network password

//ThingSpeak Channel and ApiKey
unsigned long myChannelNumber = SECRET_CH_ID;
const char * myWriteAPIKey = SECRET_WRITE_APIKEY;

WiFiClient  client;


void setup()
{
  Serial.begin(115200);
  delay(100);

  WiFi.mode(WIFI_STA);
  // Initiate ThingSpeak
  ThingSpeak.begin(client);
}


void loop()
{

  String UVIndex = "0";
  int sensorValue = 0;

  sensorValue = analogRead(A0);  //connect UV sensor to Analog 0
  int voltage = (sensorValue * (5.0 / 1023.0)) * 1000; //Voltage in miliVolts

  if (voltage < 50)
  {
    UVIndex = "0";
  } else if (voltage > 50 && voltage <= 227)
  {
    UVIndex = "0";
  } else if (voltage > 227 && voltage <= 318)
  {
    UVIndex = "1";
  }
  else if (voltage > 318 && voltage <= 408)
  {
    UVIndex = "2";
  } else if (voltage > 408 && voltage <= 503)
  {
    UVIndex = "3";
  }
  else if (voltage > 503 && voltage <= 606)
  {
    UVIndex = "4";
  } else if (voltage > 606 && voltage <= 696)
  {
    UVIndex = "5";
  } else if (voltage > 696 && voltage <= 795)
  {
    UVIndex = "6";
  } else if (voltage > 795 && voltage <= 881)
  {
    UVIndex = "7";
  }
  else if (voltage > 881 && voltage <= 976)
  {
    UVIndex = "8";
  }
  else if (voltage > 976 && voltage <= 1079)
  {
    UVIndex = "9";
  }
  else if (voltage > 1079 && voltage <= 1170)
  {
    UVIndex = "10";
  } else if (voltage > 1170)
  {
    UVIndex = "11";
  }

  int Uv = UVIndex.toInt();

  // Update ThingSpeak field with the new data
  ThingSpeak.setField(4, Uv);

  // Write the fields that you've set all at once.
  ThingSpeak.writeFields(myChannelNumber, myWriteAPIKey);

  // Wait 60 seconds to update the channel again
  delay(60000);

  Serial.print("Uv index = ");
  Serial.println(voltage);
  Serial.println(sensorValue);
  Serial.println(UVIndex);
  Serial.println(Uv);

  delay(3000);
}
