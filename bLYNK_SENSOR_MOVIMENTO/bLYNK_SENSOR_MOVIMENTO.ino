#include <ESP8266WiFi.h>
#include "secrets.h"
#define BLYNK_PRINT Serial    // Comment this out to disable prints and save space
#include <BlynkSimpleEsp8266.h>
BlynkTimer timer;


// You should get Auth Token in the Blynk App.
// Go to the Project Settings (nut icon).
char auth[] = SECRET_AUTH;

//Definir o SSID da rede WiFi
const char* ssid = SECRET_SSID;
//Definir a senha da rede WiFi
const char* password = SECRET_PASS;

//definição do pino de saída do sensor PIR 
#define PIN_SENSOR D1
//definição do pino de entrada do Buzzer
#define PIN_LED D7


void setup()
{
  Serial.begin(115200);
 
   
   pinMode(PIN_SENSOR, INPUT);
   pinMode(PIN_LED, OUTPUT);
   Blynk.begin(auth, ssid, password);
   timer.setInterval(1000L, getPirValue);
}
   

void loop()
{
  
  Blynk.run();
   timer.run();
}


void getPirValue(void)
{
 
  //faz a leitura do sensor de presença (retorna HIGH ou LOW)
  int sinal = digitalRead(PIN_SENSOR); 
 
  //HIGH : movimento detectado
  if(sinal == HIGH){
    digitalWrite(PIN_LED, HIGH);
    Blynk.notify("Alguém chegando na CHÁCARA");  
  }
  //LOW : nenhum movimento detectado
  else{
    //desativa o led
    digitalWrite(PIN_LED, LOW);
  }
 
}
