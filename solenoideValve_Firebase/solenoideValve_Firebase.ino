/*Program: GemüseGarten WeatherStation
   created by Paloma Passos
*/

//Include Libraries
#include <ESP8266WiFi.h>
#include <FirebaseArduino.h>
#include <Ticker.h>
#include <secrets.h>

#define VALV_PIN D3

const char* ssid = SECRET_SSID; // your network SSID (name)
const char* password = SECRET_PASS; // your network password

const char* FIREBASE_HOST = SECRET_HOST ;
const char* FIREBASE_AUTH = SECRET_AUTHF ;

// Publique a cada 3 min
#define PUBLISH_INTERVAL 1000*60*3

Ticker ticker;
bool publishNewState = true;

void publish() {
  publishNewState = true;
}


void setupPins() {

  pinMode(VALV_PIN, OUTPUT);
  digitalWrite(VALV_PIN, LOW);
}

void setupWifi() {
  
  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
  Serial.print("connecting");
  while (WiFi.status() != WL_CONNECTED) {
    Serial.print(".");
    delay(500);
  }
  Serial.println();
  Serial.print("connected: ");
  Serial.println(WiFi.localIP());
}

void setupFirebase() {
  Firebase.begin(FIREBASE_HOST, FIREBASE_AUTH);
  Firebase.setBool("valv", false);

}


void setup() {
  Serial.begin(115200);

  setupPins();
  setupWifi();

  setupFirebase();

  // Ticker register to publish time to time
  ticker.attach_ms(PUBLISH_INTERVAL, publish);
}


void loop() {

  // To just publish in a certain time
  if (publishNewState) {
    Serial.println("Publish new State");


    // Verifies lamp value in firebase
    bool valvValue = Firebase.getBool("valv");
    digitalWrite(VALV_PIN, valvValue ? HIGH : LOW);

    delay(200);
  }
