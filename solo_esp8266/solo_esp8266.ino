/*Program: GemüseGarten WeatherStation
   created by Paloma Passos
*/

//Include Libraries
void setup() {
 Serial.begin(115200); // open serial port, set the baud rate as 9600 bps
}
void loop() {
 int val;
 val = analogRead(A0); //connect sensor to Analog 0
 Serial.print("umidade do solo:");
 Serial.println(val); //print the value to serial port
 delay(500);
} 
