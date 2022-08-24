/*Program: GemüseGarten WeatherStation
   created by Paloma Passos
*/
//Include Libraries
#include <SPI.h>
#include <ESP8266WiFi.h>
#include "secrets.h"

String readString;

const char* ssid = SECRET_SSID; // your network SSID (name)
const char* password = SECRET_PASS; // your network password


int relay1 = 05; // Output Relay 1 GPI0 05 (D3)
int relay2 = 04;// Output Relay 2 GPI0 04 (D2)
boolean on = true;
boolean on_2 = true;

WiFiServer server(80);

void setup()
{
  Serial.begin(115200);
  delay(10);
  pinMode(relay1, OUTPUT);
  pinMode(relay2, OUTPUT);



  //turn off both relays
  digitalWrite(relay1, HIGH);
  digitalWrite(relay2, HIGH);

  Serial.print("Connected to network:");
  Serial.println(ssid);
  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("WiFi connected");
  server.begin();
  Serial.println("Server initiated");

  Serial.print("Use this URL:");
  Serial.print("http://");
  Serial.print(WiFi.localIP());
  Serial.println("/");

}


void loop()
{
  WiFiClient client = server.available();
  if (!client) {
    return;
  }
  Serial.println("New client");
  while (!client.available())
  {
    delay(1);
  }
  String requisition = client.readStringUntil('\r');
  Serial.println(requisition);
  client.flush();



  //Relay 2 Control
  Serial.println(requisition);
  //Turn on Relay 1
  if (requisition.indexOf("?on") > 0)
  {
    digitalWrite(relay1, LOW);
    Serial.println("Relay 1 Off");
    on = false;
  }
  else
  {
    //Desliga o Rele 1
    if (requisicao.indexOf("?desligar") > 0)
    {
      digitalWrite(relay1, HIGH);
      Serial.println("Rele 1 Ligado");
      on = true;
    }
  }

  //Relay 2 Control
  Serial.println(requisition);
  //Turn on Relay 2
  if (requisition.indexOf("?2_on") > 0)
  {
    digitalWrite(relay2, LOW);
    Serial.println("Relay 2 Off");
    on_2 = false;
  }
  else
  {
    //Turn Off Relay 2
    if (requisition.indexOf("?2_off") > 0)
    {
      digitalWrite(relay2, HIGH);
      Serial.println("Relay 2 On");
      on_2 = true;
    }
  }




  client.println("HTTP/1.1 200 OK");
  client.println("Content-Type: text/html");
  client.println("");
  client.println("<html>");
  client.println("<head>");
  client.println("<title>GemüseGarten</title>");
  client.println("<meta http-equiv='Content-Type' content='text/html; charset=ISO-8859-1'>");
  client.println("<meta http-equiv='Content-Type' content='text/html; charset=utf-8'>");
  client.println("<meta name='viewport' content='width=720, initial-scale=0.5' />");
  client.println("<style type=text/css>

                 root {
                 display: block;
               }

                 body {
                 margin: 0;
                 padding: 0;
               }

#wrapper {
                 padding-top: 40px;
                 position: relative;
                 width: 530px;
                 height: 600px;
                 margin-right: auto;
                 margin-top: 0;
                 margin-left: auto;
                 font-size: 30px;
                 color: black;
                 text-align: center;
                 font-family: arial;
               }

                 div.relay1_on {
                 position: absolute;
                 right: -110px;
                 top: 220px;
                 width: 300px;
                 height: 206px;
                 border: none;
                 margin:auto;
                 background: url("https://www.cleanpng.com/png-incandescent-light-bulb-electric-light-compact-flu-606738/")no-repeat left top;
}

div.relay1_off {
position: absolute;
right: -110px;
  top: 220px;
  width: 300px;
  height: 206px;
border: none;
background: url("https://www.cleanpng.com/png-incandescent-light-bulb-led-lamp-light-emitting-di-70077/") no - repeat left top;
}

div.rele2_off {
position: absolute;
right: -110px;
  top: 387px;
  width: 300px;
  height: 206px;
border: none;
background: url("https://www.cleanpng.com/png-incandescent-light-bulb-electric-light-compact-flu-606738/") no - repeat left top;
}

div.relay2_off{
position: absolute;
right: -110px;
  top: 387px;
  width: 300px;
  height: 206px;
border: none;
background: url("https://www.cleanpng.com/png-incandescent-light-bulb-led-lamp-light-emitting-di-70077/") no - repeat left top;
}

#div1 {
position: absolute;
right: 85px;
top: 195px;
border - radius: 25px;
border: 2px solid #000000;
width: 350px;
height: 150px;
}

#div2 {
position: absolute;
right: 85px;
top: 355px;
border - radius: 25px;
border: 2px solid #000000;
width: 350px;
height: 150px;
}

#button{
position: absolute;
right: 230px;
top: 250px;
width: 200px;
height: 256px;
}

.button {
-moz - box - shadow: inset 0px 1px 0px 0px #ffffff;
- webkit - box - shadow: inset 0px 1px 0px 0px #ffffff;
box - shadow: inset 0px 0px 0px 0px #ffffff;
background: -webkit - gradient( linear, left top, left bottom, color - stop(0.1, #16ADFF), color-stop(1, #26A8FF) );
background: -moz - linear - gradient( center top, #16ADFF 5%, #26A8FF 100% );
filter: progid: DXImageTransform.Microsoft.gradient(startColorstr = '#16ADFF', endColorstr = '#26A8FF');
background - color: #ededed;
  -moz - border - radius: 6px;
  -webkit - border - radius: 6px;
  border - radius: 6px;
  border: 1px solid #dcdcdc;
display: inline - block;
color: #ffffff;
font - family: arial;
  font - size: 28px;
font - weight: bold;
  padding: 10px 40px;
text - decoration: none;
  text - shadow: 0px 0px 0px #ffffff;
  width: 100px;
text - align: center;
}

} .button: active {
position: relative;
  top: 1px;
}

#button_2{
position: absolute;
right: 230px;
top: 417px;
width: 200px;
height: 256px;
}

.button_2 {
-moz - box - shadow: inset 0px 1px 0px 0px #ffffff;
- webkit - box - shadow: inset 0px 1px 0px 0px #ffffff;
box - shadow: inset 0px 0px 0px 0px #ffffff;
background: -webkit - gradient( linear, left top, left bottom, color - stop(0.1, #16ADFF), color-stop(1, #26A8FF) );
background: -moz - linear - gradient( center top, #16ADFF 5%, #26A8FF 100% );
filter: progid: DXImageTransform.Microsoft.gradient(startColorstr = '#16ADFF', endColorstr = '#26A8FF');
background - color: #ededed;
  -moz - border - radius: 6px;
  -webkit - border - radius: 6px;
  border - radius: 6px;
  border: 1px solid #dcdcdc;
display: inline - block;
color: #ffffff;
font - family: arial;
  font - size: 28px;
font - weight: bold;
  padding: 10px 40px;
text - decoration: none;
  text - shadow: 0px 0px 0px #ffffff;
  width: 100px;
text - align: center;
}

} .button_2: active {
position: relative;
  top: 1px;
}


< / style > ")
client.println(" < / head > ");
client.println("<body>");
client.println("<div id = 'wrapper'><h4>GemúseGarten < / h4 > < br / > ");
                          client.println("<div id = 'div1'>Lamp < / div > ");
                              client.println("<div id = 'div2'>Lamp2 < / div > ");
                                  client.print("<div id = 'relay'> < / div > <div id = 'state' style = 'visibility: hidden;'>");
                                      client.print(on);
                                      client.println(" < / div > ");
                                      client.println("<div id = 'button'> < / div > ");
                                          client.println("<div id = 'button_2'> < / div > ");
                                              client.print("<div id = 'relay_2'> < / div > <div id = 'state_2' style = 'visibility: hidden;'>");
                                                  client.print(on_2);
                                                  client.println(" < / div > ");
                                                  client.println(" < / div > ");
                                                  client.println("<script>ChangeRelay1() < / script > ");
                                                  client.println("<script>ChangeRelay2() < / script > ");
                                                  client.println(" < / div > ");
                                                  client.println("<script>
function ChengeRelay1() {
  var state = document.getElementById("state").innerHTML;
  if (state == = "0") {
    document.getElementById("state").innerHTML = "1";
    document.getElementById("relay").innerHTML = "<div class = 'relay1_on'> < / div > ";
    document.getElementById("button").innerHTML = "<a href = '/?turnoff' class = 'button'>Turn Off < / a > ";
  } else {
    document.getElementById("state").innerHTML = "0";
    document.getElementById("relay").innerHTML = "<div class = 'relay1_off'> < / div > ";
    document.getElementById("button").innerHTML = "<a href = '/?turnon' class = 'button'>Turn On < / a > ";
  }
}

function ChangeRelay2() {
  var state_2 = document.getElementById("state_2").innerHTML;
  if (state_2 == = "0") {
    document.getElementById("state_2").innerHTML = "1";
    document.getElementById("relay_2").innerHTML = "<div class = 'relay2_on'> < / div > ";
    document.getElementById("button_2").innerHTML = "<a href = '/?2_turnoff' class = 'button_2'>Turn Off < / a > ";
  } else {
    document.getElementById("state_2").innerHTML = "0";
    document.getElementById("relay_2").innerHTML = "<div class = 'relay2_off'> < / div > ";
    document.getElementById("button_2").innerHTML = "<a href = '/?2_turnon' class = 'button_2'>Turn On < / a > ";
  }
}
< / script > ");

client.println(" < / body > ");
client.println(" < / html > ");
delay(1);
}
