// Programa : Estacao Meteorologica com Arduino

 
// Carrega bibliotecas graficas e sensores

#include <DHT.h>
#include <ESP8266WiFi.h>
#include "secrets.h"
#include <BlynkSimpleEsp8266.h>
BlynkTimer timer;

DHT dht(D1, DHT22);
 
// You should get Auth Token in the Blynk App.
// Go to the Project Settings (nut icon).
char auth[] = SECRET_AUTH;
 

//Definir o SSID da rede WiFi
const char* ssid = SECRET_SSID;
//Definir a senha da rede WiFi
const char* password = SECRET_PASS;

void enviaDados(){
  
  
int AirValue = 845; //you need to replace this value with Value_1
int WaterValue = 403; //you need to replace this value with Value_2
int intervals = (AirValue - WaterValue)/3;
int soil = 0;
String us = "0";

 soil = analogRead(A0); //put Sensor insert into soil
if(soil > WaterValue && soil < (WaterValue + intervals))
{
 us = "MOLHADO";
}
else if(soil > (WaterValue + intervals) && soil< (AirValue - intervals))
{
 us ="ÚMIDO";
}
else if(soil < AirValue && soil > (AirValue - intervals))
{
 us = "SECO";
} 

if(us == "MOLHADO"){
  Blynk.notify("SOLO BEM MOLHADO!!!");
  
  }

  int h = dht.readHumidity();
  float t = dht.readTemperature();
  int st = dht.computeHeatIndex(t, h, false);

  
  if (isnan(t) || isnan(h)|| isnan(st)) {
    Serial.println("Falha ao ler dados do sensor!");
    return;
  }
 
  Blynk.virtualWrite(V0, t);
  Blynk.virtualWrite(V1,h);
  Blynk.virtualWrite(V2, st);
  Blynk.virtualWrite(V8, us);

 

}
 
void setup()   
{
  Serial.begin(115200);
   
   // Inicializa o DHT22
  dht.begin();
    
   Blynk.begin(auth, ssid, password);
  
  timer.setInterval(1000L, enviaDados);
 
}
 
 
void loop()
{
  Blynk.run();
  timer.run();
}
