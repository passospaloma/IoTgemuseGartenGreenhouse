/*Program: GemüseGarten WeatherStation
   created by Paloma Passos
*/

//Include Libraries
void setup() {
  Serial.begin(115200); // open serial port, set the baud rate as 9600 bps
}
void loop() {
  int val;
  int val1;
  
  val = analogRead(0); //connect sensor to Analog 0
  val1 = analogRead(1); //connect sensor to Analog 0
  Serial.print("Sensor1: ");
  Serial.println(val); //print the value to serial port
  Serial.print("Sensor2: ") ;
  Serial.println(val1); //print the value to serial port
  
  delay(5000);
}
