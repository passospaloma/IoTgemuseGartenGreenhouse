
#include <ESP8266WiFi.h>
#include "secrets.h"

const char* ssid = SECRET_SSID;
const char* password = SECRET_PASS;
int ledPin = 13;
WiFiServer server(80);

void setup() {
  Serial.begin(115200);
  delay(10);
  pinMode(ledPin, OUTPUT);
  digitalWrite(ledPin, LOW);
  Serial.print("Connected to network:");
  Serial.println(ssid);
  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("WiFi connected");
  server.begin();
  Serial.println("Server intiated");

  Serial.print("Use this URL:");
  Serial.print("http://");
  Serial.print(WiFi.localIP());
  Serial.println("/");

}

void loop() {
  WiFiClient clients = server.available();
  if (!clients) {
    return;
  }
  Serial.println("New client");
  while (!clients.available()) {
    delay(1);
  }
  String requisition = clients.readStringUntil('\r');
  Serial.println(requisition);
  clients.flush();

  int status = LOW;
  if ( requisition.indexOf("/LED=ON") != -1) {
    status = HIGH;
  }
  if (requisition.indexOf("/LED=OFF") != -1) {
    status = LOW;
  }
  Serial.print("status:");
  Serial.println(status);
  digitalWrite(ledPin, status);

  clients.println("HTTP/1.1 200 OK");
  clients.println("Content-Type:text/html");
  clients.println("");
  clients.println("<!DOCTYPE HTML>");
  clients.println("<html>");

  clients.println("<br><br>");
  clients.println("<a href=\"/LED=ON\"\"><button> Turn On Relay</button></a>");
  clients.println("<a href=\"/LED=OFF\"\"><button> Turn Off Relay </button></a><br/>");
  clients.println("</html>");
  delay(1);
}
