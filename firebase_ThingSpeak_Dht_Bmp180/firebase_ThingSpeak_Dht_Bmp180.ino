/*Program: GemüseGarten WeatherStation
created by Paloma Passos
*/

//Include Libraries
#include <DHT.h>
#include <Adafruit_BMP085.h>
#include <Wire.h>
#include <SPI.h>
#include <ESP8266WiFi.h>
#include "secrets.h"
#include <SimpleTimer.h>
#include <FirebaseArduino.h>

DHT dht(D4, DHT22); // what digital pin the DHT22 is conected to

// Publish every 2 min
#define PUBLISH_INTERVAL 1000*60*2

const char* ssid = SECRET_SSID; // your network SSID (name)
const char* password = SECRET_PASS; // your network password

const char* FIREBASE_HOST = SECRET_HOST ;
const char* FIREBASE_AUTH = SECRET_AUTHF ;

//ThingSpeak Channel and ApiKey
String apiKey = SECRET_WRITE_APIKEY;
const char* server = "api.thingspeak.com";

WiFiClient client;

SimpleTimer timer;

Adafruit_BMP085 bmp180; // Initialize BMP180 sensor

bool publishNewState = true;

void publish() {
  publishNewState = true;
}

//Update every minute,  Thingspeak needs at least 20 seconds to update
const int UPDATE_INTERVAL_SECONDS = 60;


void setup()
{
  Serial.begin(115200);

  delay(1000);

  //Initiate WiFi
  WiFi.begin(ssid, password);


  //Wait for router connection
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println();
  Serial.print("connected: ");
  Serial.println(WiFi.localIP());

  Firebase.begin(FIREBASE_HOST, FIREBASE_AUTH);

  Wire.begin(2, 0);            // Pin configuration to BMP180 sensor. GPIO2(D4) to SDA(pin to data transfer), GPIO0(D3) to SCL(pin to timing)
  // Initialize BMP180 sensor

  if (!bmp180.begin())
  {
    Serial.println("BMP180 sensor not found!!");
    while (1) {}
  }

  // Initiate DHT22 sensor
  dht.begin();

  Serial.println("");
  Serial.print("Connected to network");
  Serial.println(ssid);
  Serial.print("IP: ");
  Serial.println(WiFi.localIP());
}


void loop()
{

  float h = dht.readHumidity();
  float t = dht.readTemperature();
  float hi = dht.computeHeatIndex(t, h, false);
  float p = bmp180.readPressure() / 100.0;

  // wait 5 seconds to new reading
  delay(5000);

  Firebase.pushFloat ("temperature", t);
  Firebase.pushFloat ("humidity", h);
  Firebase.pushFloat ("heat index", hi);
  Firebase.pushFloat ("pressure", p);

  //Initialize a TCP client to send data
  if (client.connect(server, 80)) {
    String postStr = apiKey;
    postStr += "&amp;field1=";
    postStr += String(t);
    postStr += "&amp;field2=";
    postStr += String(h);
    postStr += "&amp;field3=";
    postStr += String(hi);
    postStr += "&amp;field4=";
    postStr += String(p);

    postStr += "\r\n\r\n";

    client.print("POST /update HTTP/1.1\n");
    client.print("Host: api.thingspeak.com\n");
    client.print("Connection: close\n");
    client.print("X-THINGSPEAKAPIKEY: " + apiKey + "\n");
    client.print("Content-Type: application/x-www-form-urlencoded\n");
    client.print("Content-Length: ");
    client.print(postStr.length());
    client.print("\n\n");
    client.print(postStr);

    // Update temperature value
    Serial.println("GemüseGarten");

    Serial.print("Temperature: ");
    Serial.println(t, 1);

    // Update humidity value
    Serial.print("Humidity: ");
    Serial.println(h, 1);

    // Update heat index value
    Serial.print("Heat Index: ");
    Serial.println(hi, 1);

    // Update pressure value
    Serial.print("Pressure: ");
    Serial.println(p, 2);

    Serial.println("---------------------------------------");

    delay(20000);
  }

  client.stop();
}
