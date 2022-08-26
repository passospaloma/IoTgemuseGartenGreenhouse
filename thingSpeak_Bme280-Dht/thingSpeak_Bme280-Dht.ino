/*Program: GemüseGarten WeatherStation
   created by Paloma Passos
*/

//Include Libraries

#include <Adafruit_Sensor.h>
#include <Adafruit_BMP280.h>
#include <DHT.h>
#include <ESP8266WiFi.h>
#include "secrets.h"
#include "ThingSpeak.h"

DHT dht(D5, DHT22); // what digital pin the DHT22 is conected to

// assign the ESP8266 pins to arduino pins
#define D1 5
#define D2 4
#define D4 2
#define D3 0

// assign the SPI bus to pins
#define BMP_SCK D1
#define BMP_MISO D4
#define BMP_MOSI D2
#define BMP_CS D3

Adafruit_BMP280 bme(BMP_CS, BMP_MOSI, BMP_MISO, BMP_SCK); // software SPI

#define SEALEVELPRESSURE_HPA (1013.25)

char ssid[] = SECRET_SSID;   // your network SSID (name)
char pass[] = SECRET_PASS;   // your network password

//ThingSpeak Channel and ApiKey
unsigned long myChannelNumber = SECRET_CH_ID;
const char * myWriteAPIKey = SECRET_WRITE_APIKEY;

WiFiClient  client;


void setup() {
  Serial.begin(115200);
  delay(100);

  WiFi.mode(WIFI_STA);

  // default settings
  bme.begin();
  if (!bme.begin()) {
    Serial.println("Could not find a valid BME280 sensor, check wiring!");
    while (1);
  }

  // Initiate DHT22 sensor
  dht.begin();

  // Initiate ThingSpeak
  ThingSpeak.begin(client);
}


void loop() {

  // Read Temperature, Humidity, Heat Index, Temperature from BME280 sensor, Pressure and Altitude
  int t = dht.readTemperature();
  int h = dht.readHumidity();
  int hi = dht.computeHeatIndex(t, h, false);
  int t1 = bme.readTemperature();
  int p =  bme.readPressure() / 100.0F;
  float a = bme.readAltitude(SEALEVELPRESSURE_HPA);

  // Update the 6 ThingSpeak fields with the new data
  ThingSpeak.setField(1, t);
  ThingSpeak.setField(2, h);
  ThingSpeak.setField(3, hi);
  ThingSpeak.setField(4, t1);
  ThingSpeak.setField(5, p);
  ThingSpeak.setField(6, a);

  // Write the fields that you've set all at once.
  ThingSpeak.writeFields(myChannelNumber, myWriteAPIKey);

  // Wait 60 seconds to update the channel again
  delay(60000);
}
