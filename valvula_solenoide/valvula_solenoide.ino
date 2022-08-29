/*Program: GemüseGarten WeatherStation
   created by Paloma Passos
*/

//Include Libraries
#define pinDigital 13
#define pinAnalog 0
#define pinRelay      7

float AnalogOutput = 0;
float voltage = 0;
int LeituraSensor = 0;

// the setup routine runs once when you press reset:
void setup() {
  pinMode(pinDigital, INPUT);  
  pinMode(pinRelay, OUTPUT);  
  Serial.begin(9600);
}

// the loop routine runs over and over again forever:
void loop() {
  
  AnalogOutput = analogRead(pinAnalog);
  LeituraSensor = digitalRead(pinDigital);
  float voltage = AnalogOutput * (5.0 / 1023.0);
  Serial.println("Sainda analog");
  Serial.println(voltage);
  Serial.println("Sainda digital");
  Serial.println(LeituraSensor);
  
  if(LeituraSensor == HIGH)
    digitalWrite(pinRelay,LOW);
  else
    digitalWrite(pinRelay,HIGH);
    
    
  delay(2000);

}
