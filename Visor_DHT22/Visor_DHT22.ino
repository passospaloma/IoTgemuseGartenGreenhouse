// Programa : Estacao Meteorologica com Arduino

 
// Carrega bibliotecas graficas e sensores
#include <Adafruit_GFX.h>
#include <Adafruit_PCD8544.h>
#include <DHT.h>
#include <Wire.h>
#include <SPI.h>
 


DHT dht(8, DHT22);



// Pinagem ligacao display Nokia 5110
// pin D5- Serial clock out (SCLK)
// pin D4 - Serial data out (DIN)
// pin D5 - Data/Command select (D/C)
// pin D7 - LCD chip select (CS/CE)
// pin D6 - LCD reset (RST)
 
// Inicializa o display nos pinos acima
Adafruit_PCD8544 display = Adafruit_PCD8544(D4, D3, D2, D1, D0);


 
void setup()   
{
  Serial.begin(115200);

  // Informacoes iniciais no display
  display.begin();
    
  // Ajusta o contraste do display
  display.setContrast(100);
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
  display.drawRoundRect(0,25,84 ,23, 3, 2);
  // Texto inicial sensacao termica
  display.setCursor(5,28); 
  display.println("SENSACAO TERM");
    display.setCursor(54,38);
   display.drawCircle(50, 39, 1,1);
   display.println("C");
 
   
     display.display();
   
  delay(1000);
 
  // Inicializa o DHT22
  dht.begin();
 
 
}
 
 
void loop()
{
  
 int h = dht.readHumidity();
  float t = dht.readTemperature();
  int st = dht.computeHeatIndex(t, h, false);
 
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
  display.setCursor(35,38);
  display.println(st,1);

     display.display();
    // Aguarda 5 segundos para efetuar nova leitura
  delay(5000);
  
     //Logs na porta serial
   // Atualiza valor da temperatura
    Serial.println("imet agrotech");
    
  Serial.print("Temperatura: ");
  Serial.println(t,1); 
   
  // Atualiza valor da umidade
 Serial.print("Umidade: ");
  Serial.println(h,1); 

  // Atualiza valor da sensacao termica
 Serial.print("Sensacao Termica: ");
 Serial.println(st,1);



Serial.println("---------------------------------------");

delay(30000);
    
  }
  
