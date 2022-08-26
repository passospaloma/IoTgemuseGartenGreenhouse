// Programa : Estacao Meteorologica com Arduino

 
// Carrega bibliotecas graficas e sensores
#include <Adafruit_GFX.h>
#include<Adafruit_PCD8544.h>
#include <DHT.h>
#include <Adafruit_BMP085.h>
#include <Adafruit_Sensor.h>
#include <Adafruit_BMP280.h>
#include <Wire.h>
#include <SPI.h>
#define DHTPIN 1    // what digital pin the DHT22 is conected to
#define DHTTYPE DHT22   // there are multiple kinds of DHT sensors
 
// Pinagem ligacao display Nokia 5110
// pin 12 - Serial clock out (SCLK)
// pin 13 - Serial data out (DIN)
// pin 14 - Data/Command select (D/C)
// pin 15 - LCD chip select (CS/CE)
// pin 16- LCD reset (RST)
 
// Inicializa o display nos pinos acima
Adafruit_PCD8544 display = Adafruit_PCD8544(16, 15, 14, 13, 12);
 

DHT dht(DHTPIN, DHTTYPE); 
 
#define BMP_SCK 13
#define BMP_MISO 12
#define BMP_MOSI 11 
#define BMP_CS 10

Adafruit_BMP280 bme; // I2C


void setup()   
{
  Serial.begin(9600);
  
  // Informacoes iniciais no display
  display.begin();
  // Ajusta o contraste do display
  display.setContrast(48);
  // Apaga o buffer e o display
  display.clearDisplay();
  // Define tamanho do texto e cor
  display.setTextSize(1);
  display.setTextColor(BLACK);
   
  // Retangulo temperatura
  display.drawRoundRect(0,0, 44,24, 3, 2);
  // Texto inicial temperatura
  display.setCursor(11,3);  // Seta a posição do cursor
  display.println("TEMP");  
  display.setCursor(5,14);
  display.println("----"); 
  display.setCursor(29,14);
  display.drawCircle(31, 15, 1,1);
  display.println(" C");
   
  // Retangulo umidade
  display.drawRoundRect(45,0, 39 ,24, 3, 2);
  // Texto inicial Umidade
  display.setCursor(52,3);  
  display.println("UMID");
  display.setCursor(50,14); 
  display.println("----"); 
  display.setCursor(75,14);
  display.println("%");

 // Retangulo Sensacao termica
  display.drawRoundRect(0,25,44 ,23, 3, 2);
  // Texto inicial sensacao termica
  display.setCursor(3,28); 
  display.println("S.TERM");
  display.setCursor(5,38);
  display.println("----");
   display.setCursor(35,38);
   display.drawCircle(31, 38, 1,1);
   display.println("C");

  // Retangulo umidade do solo
  display.drawRoundRect(45,25,39 ,23, 3, 2);
  // Texto inicial pressao
  display.setCursor(47,27); 
  display.println("PRESS");
  display.setCursor(50,38);
  display.println("----");
  

  display.display();
   
  delay(1000);
  Serial.println(F("BMP280 test"));
  
  if (!bme.begin(0x76)) {  
    Serial.println("Could not find a valid BMP280 sensor, check wiring!");
    while (1);
  }

  
 
  // Inicializa o DHT22
  dht.begin();
}
 
void loop()
{
  // Leitura temperatura, umidade e pressao
  float h = dht.readHumidity();
  float t = dht.readTemperature();
  float st = dht.computeHeatIndex(t, h, false);
 float p =  bme.readPressure()/100.0;
 
  
   
  // Atualiza valor da temperatura
  display.fillRect(4,13, 25 , 10, 0);
  display.setCursor(4,14);
  display.println(t,1); 
   
  // Atualiza valor da umidade
  display.fillRect(50,13, 23 , 10, 0);
  display.setCursor(50,14);
  display.println(h,1); 

  // Atualiza valor da sensacao termica
  display.fillRect(4, 37, 25 , 10, 0);
  display.setCursor(4,38);
  display.println(st,1);

   // Atualiza valor da sensacao termica
  display.fillRect(50, 37, 23 , 10, 0);
  display.setCursor(50,38);
  display.println(p,2);

  display.display();
  // Aguarda 5 segundos para efetuar nova leitura
  delay(5000);
}
