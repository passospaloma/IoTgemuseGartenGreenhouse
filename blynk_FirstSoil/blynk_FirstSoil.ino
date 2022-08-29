/*Program: GemüseGarten WeatherStation
   created by Paloma Passos
*/

//Include Libraries

#include <ESP8266WiFi.h>
#include "secrets.h"
#include <BlynkSimpleEsp8266.h>
BlynkTimer timer;

// You should get Auth Token in the Blynk App.
// Go to the Project Settings (nut icon).
char auth[] = SECRET_AUTH;
 

//Definir o SSID da rede WiFi
const char* ssid = SECRET_SSID;
//Definir a senha da rede WiFi
const char* password = SECRET_PASS;

void enviaDados(){
  
  
int AirValue = 835; //you need to replace this value with Value_1
int WaterValue = 469; //you need to replace this value with Value_2
int intervals = (AirValue - WaterValue)/3;
int soil = 0;
String us = "0";

 soil = analogRead(A0); //put Sensor insert into soil
if(soil > WaterValue && soil < (WaterValue + intervals))
{
 us = "WET SOIL";
}
else if(soil > (WaterValue + intervals) && soil< (AirValue - intervals))
{
 us ="HUMID SOIL";
}
else if(soil < AirValue && soil > (AirValue - intervals))
{
 us = "DRY SOIL";
} 

if(us == "WET"){
  Blynk.notify("WELL DONE!! THE SOIL IS WET!!!");
  
  }
  if(us == "DRY"){
  Blynk.notify("I NEED WATER!!!");
  
  }
    Blynk.virtualWrite(V8, us);
     Blynk.virtualWrite(V9, soil);
    
}
 
void setup()   
{
  Serial.begin(115200);
   
     
   Blynk.begin(auth, ssid, password);
  
  timer.setInterval(1000L, enviaDados);
 
}
 
 
void loop()
{

  Blynk.run();
  timer.run();
}
