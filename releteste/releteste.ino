#include <Wire.h>
#include <SPI.h>
#include <ESP8266WiFi.h>
#include "secrets.h"
#define BLYNK_PRINT Serial




// You should get Auth Token in the Blynk App.
// Go to the Project Settings (nut icon).
char auth[] = SECRET_AUTH;

//Nome da sua rede Wifi
const char* ssid = SECRET_SSID;

//Senha da rede
const char* password = SECRET_PASS;

 int pinLight = D2;
   
WiFiClient client;



void setup() {
  Serial.begin(115200); // inicializa a comunicação serial em 9600bps

  pinMode(pinLight, OUTPUT);
  digitalWrite(pinLight, LOW);
  

//Conectando a rede Wifi
  
  WiFi.begin(ssid, password);
  
  
  //Verificando se esta conectado,
  //caso contrario, espera um pouco e verifica de novo.
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
  }

  //Logs na porta serial
  Serial.println("");
  Serial.print("Conectado na rede ");
  Serial.println(ssid);
  Serial.print("IP: ");
  Serial.println(WiFi.localIP());
}
 Blynk.begin(auth, ssid, password);

void loop() {

digitalWrite(2,1);

  Blynk.run();

   Blynk.virtualWrite(V4, relays);
   

}
