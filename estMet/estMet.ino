/*Program: GemüseGarten WeatherStation
   created by Paloma Passos
*/
//Include Libraries
#include <Adafruit_GFX.h>
#include <Adafruit_PCD8544.h>
#include <DHT.h>
#include <Adafruit_BMP085.h>
#include <Wire.h>
#include <SPI.h>

// Set pin to display Nokia 5110
// pin D5- Serial clock out (SCLK)
// pin D7 - Serial data out (DIN)
// pin D6 - Data/Command select (D/C)
// pin D1 - LCD chip select (CS/CE)
// pin D2 - LCD reset (RST)

 
 
// Initiate Nokia 5110 display
Adafruit_PCD8544 display = Adafruit_PCD8544(D5, D7, D6, D1, D2);

DHT dht(D3, DHT22); // what digital pin the DHT22 is conected to

 
void setup()   
{
  Serial.begin(115200);

  // Initial display information 
  display.begin();
  // Set display contrast
  display.setContrast(48);
 // Erase buffer and display
  display.clearDisplay();
 // Define text size and color
  display.setTextSize(1);
  display.setTextColor(BLACK);
   
  // Rect Temperature
  display.drawRoundRect(0,0, 44,24, 3, 2);
  // Initial Text Temperature
  display.setCursor(11,3);  // Seta a posição do cursor
  display.println("TEMP");  
  display.setCursor(5,14);
  display.println("----"); 
  display.setCursor(29,14);
  display.drawCircle(31, 15, 1,1);
  display.println(" C");
   
  // Rect Humidity
  display.drawRoundRect(45, 0, 39 , 24, 3, 2);
  //Initial Text Humidity
  display.setCursor(52,3);  
  display.println("HUMID");
  display.setCursor(50,14); 
  display.println("----"); 
  display.setCursor(75,14);
  display.println("%");  
   
 
  // Rect Pressure
  display.drawRoundRect(0, 25, 44 , 23, 3, 2);
  // Initial Text Heat Index
  display.setCursor(22,28); 
  display.println("H.INDEX");
  display.setCursor(55,38);
  display.println("hPa");
  display.setCursor(11,38);
  display.println("------"); 
  display.display();
   
  delay(1000);
  
  // Initiate DHT22 sensor
  dht.begin();
}
 
void loop()
{
  // Read temperature, humidity and pressure from sensor
  float h = dht.readHumidity();
  float t = dht.readTemperature();
   float hi = dht.computeHeatIndex(t, h, false);
 
  // Update temperature value
  display.fillRect(4,13, 25 , 10, 0);
  display.setCursor(4,14);
  display.println(t,1); 
   
  // Update  humidity value
  display.fillRect(50,13, 23 , 10, 0);
  display.setCursor(50,14);
  display.println(h,1); 

    //Update Heat Index value
  display.fillRect(4, 37, 25 , 10, 0);
  display.setCursor(4, 38);
  display.println(hi, 1);
     
  display.display();
  // Aguarda 5 segundos para efetuar nova leitura
  delay(5000);
}
