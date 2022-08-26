// Programa : Estacao Meteorologica com Arduino

 
// Carrega bibliotecas graficas e sensores

#include <DHT.h>

#include <Wire.h>
#include <SPI.h>
#include <Adafruit_Sensor.h>
#include <Adafruit_BMP280.h>

#define BMP_SCK 13
#define BMP_MISO 12
#define BMP_MOSI 11 
#define BMP_CS 10


#define DHTPIN 4     // what digital pin the DHT22 is conected to
#define DHTTYPE DHT22   // there are multiple kinds of DHT sensors

DHT dht(DHTPIN, DHTTYPE); 

 
 Adafruit_BMP280 bme; // I2C

void setup()   
{
  Serial.begin(115200);
  // Informacoes iniciais no display
 
   
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
  float p = bmp180.readPressure()/100.0;
  float t2 = bme.readTemperature();
  float p2 = bme.readPressure()/100.0;
  float a = bme.readAltitude(1013.25);

   
    // Atualiza valor da temperatura
  Serial.print("Temperatura: ");
  Serial.println(t,1); 
   
  // Atualiza valor da umidade
 Serial.print("Umidade: ");
  Serial.println(h,1);

    // Atualiza valor da sensacao termica
 Serial.print("Sensação Térmica: ");
  Serial.println(st,1);
   
 
 // Atualiza valor da pressao
 Serial.print("Pressao: ");
 Serial.println(p,2);
  
  Serial.print("Temperature = ");
  Serial.println(t2,1);
    
  Serial.print("Pressure = ");
  Serial.println(" Pa");

  Serial.print("Approx altitude = ");
  Serial.print(bme.readAltitude(1013.25)); // this should be adjusted to your local forcase
  Serial.println(" m");
    
   
  
 
  // Aguarda 5 segundos para efetuar nova leitura
  delay(5000);
}
