
 
#include <SPI.h>
#include <ESP8266WiFi.h>
#include <Wire.h>
#include "secrets.h"
#define BLYNK_PRINT Serial
#include <BlynkSimpleEsp8266.h>
#include <SimpleTimer.h>

String readString;


//Definir o SSID da rede WiFi
const char* ssid = SECRET_SSID;
//Definir a senha da rede WiFi
const char* password = SECRET_PASS;


// You should get Auth Token in the Blynk App.
// Go to the Project Settings (nut icon).
char auth[] = SECRET_AUTH;

 
 
 int pino_rele1 = 2;
 int pino_rele2 = 4;


boolean ligado = true;
boolean ligado_2 = true;

BLYNK_WRITE(V6) 
{
  if (param.asInt()) 
  {   
   digitalWrite(pino_rele1, LOw);       
  } 
  else 
  {
  digitalWrite(pino_rele1, LOW);    
  }
}

BLYNK_WRITE(V7) 
{
  if (param.asInt()) 
  {   
   digitalWrite(pino_rele2, HIGH);       
  } 
  else 
  {
  digitalWrite(pino_rele2, LOW);    
  }
}

BlynkTimer timerlerBlynk;

WiFiServer server(80);

WiFiClient client;

void setup()
{
  Serial.begin(115200);
  delay(10);
  pinMode(pino_rele1, OUTPUT);
  pinMode(pino_rele2, OUTPUT);
 
 Blynk.begin(auth, ssid, password);
  
  //Desliga os dois reles
  digitalWrite(pino_rele1, HIGH);
  digitalWrite(pino_rele2, HIGH);

   Serial.print("Conectando a rede:");
  Serial.println(ssid);
  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED){
    delay(500);
    Serial.print(".");
  }
  Serial.println("WiFi conectado");
  server.begin();
  Serial.println("Servidor Iniciado");

  Serial.print("Use esta URL:");
  Serial.print("http://");
  Serial.print(WiFi.localIP());
  Serial.println("/");

}
 
  

void loop()
{
  Blynk.run();
  
 WiFiClient cliente = server.available();
   if(!cliente){
    return;
  }
  Serial.println("Novo cliente");
    while (!cliente.available())
      {
        delay(1);
      }
        String requisicao = cliente.readStringUntil('\r');
  Serial.println(requisicao);
  cliente.flush();

   Blynk.virtualWrite(V6, pino_rele1);
  Blynk.virtualWrite(V7, pino_rele2);
  
          //Controle do rele1
          Serial.println(requisicao);
            //Liga o Rele 1
          if (requisicao.indexOf("?ligar") > 0)
          {
            digitalWrite(pino_rele1, LOW);
            Serial.println("Rele 1 Desligado");
            ligado = false;
          }
          else
          {
            //Desliga o Rele 1
            if (requisicao.indexOf("?desligar") > 0)
            {
              digitalWrite(pino_rele1, HIGH);
              Serial.println("Rele 1 Ligado");
              ligado = true;
            }
          }

           //Controle do rele2
          Serial.println(readString);
          //Liga o Rele 2
          if (requisicao.indexOf("?2_ligar") > 0)
          {
            digitalWrite(pino_rele2, LOW);
            Serial.println("Rele 2 Desligado");
            ligado_2 = false;
          }
          else
          {
            //Desliga o Rele 2
            if (requisicao.indexOf("?2_desligar") > 0)
            {
              digitalWrite(pino_rele2, HIGH);
              Serial.println("Rele 2 Ligado");
              ligado_2 = true;
            }
          }
          
 
       
 
         cliente.println("HTTP/1.1 200 OK");
          cliente.println("Content-Type: text/html");
          cliente.println("");
          cliente.println("<html>");
          cliente.println("<head>");
          cliente.println("<title>Paloma - Automacao Residencial</title>");
          cliente.println("<meta http-equiv='Content-Type' content='text/html; charset=ISO-8859-1'>");
          cliente.println("<meta name='viewport' content='width=720, initial-scale=0.5' />");
          cliente.println("<link rel='stylesheet' type='text/css' href='http://img.filipeflop.com/files/download/automacao/automacao_residencial.css' />");
          cliente.println("<script type='text/javascript' src='http://img.filipeflop.com/files/download/automacao/automacao_residencial.js'></script>");
          cliente.println("</head>");
          cliente.println("<body>");
         cliente.println("<div id='wrapper'><h2>PassosDewes Automacao Residencial</h2><br/>");
          cliente.println("<div id='div1'>Rele 1</div>");
          cliente.println("<div id='div2'>Rele 2</div>");
          cliente.print("<div id='rele'></div><div id='estado' style='visibility: hidden;'>");
          cliente.print(ligado);
          cliente.println("</div>");
          cliente.println("<div id='botao'></div>");
          cliente.println("<div id='botao_2'></div>");
          cliente.print("<div id='rele_2'></div><div id='estado_2' style='visibility: hidden;'>");
          cliente.print(ligado_2);
          cliente.println("</div>");
          cliente.println("</div>");
          cliente.println("<script>AlteraRele1()</script>");
          cliente.println("<script>AlteraRele2()</script>");
          cliente.println("</div>");
          cliente.println("</body>");
          cliente.println("</head>");
 
          delay(1);
                  }
      
