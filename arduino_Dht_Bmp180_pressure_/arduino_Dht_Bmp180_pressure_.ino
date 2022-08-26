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
// pin 8 - Serial clock out (SCLK)
// pin 9 - Serial data out (DIN)
// pin 10 - Data/Command select (D/C)
// pin 11 - LCD chip select (CS/CE)
// pin 12 - LCD reset (RST)

// Initiate display
Adafruit_PCD8544 display = Adafruit_PCD8544(8, 9, 10, 11, 12);

DHT dht(D1, DHT22); // what digital pin the DHT22 is conected to

Adafruit_BMP085 bmp180;


void setup()
{
  Serial.begin(9600); // open serial port, set the baud rate to 9600 bps

  // Initial display information
  display.begin();
  // Set display contrast
  display.setContrast(48);
  // Erase buffer and display
  display.clearDisplay();
  // Define size and text color
  display.setTextSize(1);
  display.setTextColor(BLACK);

  // Rect Temperature
  display.drawRoundRect(0, 0, 44, 24, 3, 2);
  // Initial text Temperature
  display.setCursor(11, 3); // Set cursor position
  display.println("Temp");
  display.setCursor(5, 14);
  display.println("----");
  display.setCursor(29, 14);
  display.drawCircle(31, 15, 1, 1);
  display.println(" C");

  // Rect Humidity
  display.drawRoundRect(45, 0, 39 , 24, 3, 2);
  // Initial text Humidity
  display.setCursor(52, 3);
  display.println("Humid");
  display.setCursor(50, 14);
  display.println("----");
  display.setCursor(75, 14);
  display.println("%");

  // Rect Heat Index
  display.drawRoundRect(0, 25, 44 , 23, 3, 2);
  // Initial text heat index
  display.setCursor(3, 28);
  display.println("H.Index");
  display.setCursor(5, 38);
  display.println("----");

  // Rect Pressure
  display.drawRoundRect(45, 25, 39 , 23, 3, 2);
  // Initial text Pressure
  display.setCursor(47, 27);
  display.println("Pressure");
  display.setCursor(50, 38);
  display.println("----");

  display.display();

  delay(1000);

  // Initialize BMP180 sensor
  if (!bmp180.begin())
  {
    Serial.println("Sensor BMP180 not found!!");
    while (1) {}
  }
  // Initialize DHT22 sensor
  dht.begin();
}


void loop()
{
  // Read Temperature, Humidity, Heat Index and Pressure
  float h = dht.readHumidity();
  float t = dht.readTemperature();
  float hi = dht.computeHeatIndex(t, h, false);
  float p = bmp180.readPressure() / 100.0;

  // Update temperature value
  display.fillRect(4, 13, 25 , 10, 0);
  display.setCursor(4, 14);
  display.println(t, 1);

  // Update humidity value
  display.fillRect(50, 13, 23 , 10, 0);
  display.setCursor(50, 14);
  display.println(h, 1);

  // Update heat index value
  display.fillRect(4, 37, 25 , 10, 0);
  display.setCursor(4, 38);
  display.println(hi, 1);

  // Update pressure value
  display.fillRect(50, 37, 23 , 10, 0);
  display.setCursor(50, 38);
  display.println(p, 1);

  display.display();
  // wait 5 seconds to new reading
  delay(1000);

  //Logs na porta serial
  // Update temperature value
  Serial.println("GemüseGarten");

  Serial.print("Temperature: ");
  Serial.println(t, 1);

  // Update humidity value
  Serial.print("Humidity: ");
  Serial.println(h, 1);

  //  Update heat index value
  Serial.print("Heat Index: ");
  Serial.println(hi, 1);

  //  Update pressure value
  Serial.print("Pressure: ");
  Serial.println(p, 1);

  Serial.println("---------------------------------------");

  // wait 5 seconds to new reading
  delay(5000);
}
