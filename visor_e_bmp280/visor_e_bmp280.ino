// Programa : Estacao Meteorologica com Arduino

 
// Carrega bibliotecas graficas e sensores
#include <Adafruit_GFX.h>
#include <Adafruit_PCD8544.h>
#include <Adafruit_Sensor.h> //INCLUSÃO DE BIBLIOTECA
#include <Adafruit_BMP280.h> //INCLUSÃO DE BIBLIOTECA
 

#include <Wire.h>
#include <SPI.h>


// Pinagem ligacao display Nokia 5110
// pin 8 - Serial clock out (SCLK)
// pin 9 - Serial data out (DIN)
// pin 10 - Data/Command select (D/C)
// pin 11 - LCD chip select (CS/CE)
// pin 12 - LCD reset (RST)
 
// Inicializa o display nos pinos acima
Adafruit_PCD8544 display = Adafruit_PCD8544(8, 9, 10, 11, 12);
 

 Adafruit_BMP280 bmp; //OBJETO DO TIPO Adafruit_BMP280 (I2C)
 
void setup()   
{
  Serial.begin(115200);
 
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
  display.println("ALT");
  display.setCursor(50,14); 
  display.println("----"); 
  display.setCursor(75,14);
  display.println("");  
   
  // Retangulo pressao
  display.drawRoundRect(0,25, 84 ,23, 3, 2);
  // Texto inicial Pressao
  display.setCursor(22,28); 
  display.println("PRESSAO");
  display.setCursor(55,38);
  display.println("hPa");
  display.setCursor(11,38);
  display.println("------"); 
  display.display();
   
  delay(1000);
  // Inicializa o sensor BMP280
  if(!bmp.begin(0x76)){ //SE O SENSOR NÃO FOR INICIALIZADO NO ENDEREÇO I2C 0x76, FAZ
    Serial.println(F("Sensor BMP280 não foi identificado! Verifique as conexões.")); //IMPRIME O TEXTO NO MONITOR SERIAL
    while(1); //SEMPRE ENTRE NO LOOP
  }
}
 
 
void loop()
{
  // Leitura temperatura, umidade e pressao
 float t = bmp.readTemperature();
   int p = bmp.readPressure()/100.0;
 
  float atm = p / 101325; // "standard atmosphere"
  float a = bmp.readAltitude(101500)/1000.0;
 

   
  // Atualiza valor da temperatura
  display.fillRect(4,13, 25 , 10, 0);
  display.setCursor(4,14);
  display.println(t,1); 
   
  // Atualiza valor da umidade
  display.fillRect(50,13, 23 , 10, 0);
  display.setCursor(50,14);
  display.println(a,1); 
   
  // Atualiza valor da pressao
  display.fillRect(4, 37, 46 , 10, 0);
  display.setCursor(11,38);
  display.println(p,1); 
    
  display.display();
  // Aguarda 5 segundos para efetuar nova leitura
  delay(5000);
  
   //Logs na porta serial
   // Atualiza valor da temperatura
    Serial.println("IMET AGROTECH");
    
  Serial.print("Temperatura: ");
  Serial.println(t,1); 

   Serial.print("Altitude: ");
  Serial.println(a,1); 
  
    

  // Atualiza valor da Pressao
  Serial.print("Pressao: ");
Serial.println(p,1);

  // Atualiza valor da Pressao
  Serial.print("atm: ");
Serial.println(atm,1);

 Serial.print("Altitude real = ");
    Serial.print(bmp.readAltitude(101500));
    Serial.println(" metros");
    Serial.println();


  
    Serial.println("-----------------------------------"); //IMPRIME UMA LINHA NO MONITOR SERIAL
    delay(5000); //INTERVALO DE 5 SEGUNDOS
}
