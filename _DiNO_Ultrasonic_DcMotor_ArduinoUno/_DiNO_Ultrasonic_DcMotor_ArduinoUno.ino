/*Program: Creation of "DiNO"
 * created by Paloma Passos
 */

int const trigPin = 10; //set trigPin
int const echoPin = 9; //set EchoPin

int relay1 = 2; //set relay 1 
int relay2 = 3; //set relay 2

const int triggerType = LOW;// your relay type

int relayOFF, relayON; // relay ON and OFF values for LOW and HIGH Trigger relays


void setup() {

  pinMode(trigPin, OUTPUT); // trig pin will have pulses output
  pinMode(echoPin, INPUT); // echo pin should be input to get pulse width

  pinMode(relay1, OUTPUT);// set pin as output for relay 1
  pinMode(relay2, OUTPUT);// set pin as output for relay 2

   if(triggerType ==LOW){
     relayON = LOW;
     relayOFF = HIGH;
     digitalWrite(relay1, relayOFF); //keep both relay OFF so motor is stopped
     digitalWrite(relay2, relayOFF); //keep both relay OFF so motor is stopped
   }else{
     relayON = HIGH;
     relayOFF = LOW; 
     digitalWrite(relay1, relayOFF); //keep both relay OFF so motor is stopped
     digitalWrite(relay2, relayOFF); //keep both relay OFF so motor is stopped
   }
}

void loop() {
  
// Duration will be the input pulse width and distance will be the distance to the obstacle in centimeters
int duration, distance;

// Output pulse with 1ms width on trigPin
digitalWrite(trigPin, HIGH);
delay(1);
digitalWrite(trigPin, LOW);

// Measure the pulse input in echo pin
duration = pulseIn(echoPin, HIGH);

// Distance is half the duration devided by 29.1 (from datasheet)
distance = (duration/2) / 29.1;

// if distance less than 0.15 meter and more than 0 (0 or less means over range)
if (distance <= 15 && distance >= 0) {
   
// Rotate in CW direction
  motorCW();
  delay(245); // wait for 1/4 seconds

// Rotate in CCW direction
  motorCCW(); 
  delay(245); // wait for 1/4 seconds


  motorStop();
  delay(2000); //wait for 2 seconds
 }         
}


// controls the relay so the motor rotates in CCW
void motorCCW()
{
  digitalWrite(relay1, relayON); // turn relay 1 ON
  digitalWrite(relay2, relayOFF); // turn relay 2 OFF  
}


// controls the relay so the motor rotates in CW
void motorCW()
{
  digitalWrite(relay1, relayOFF); // turn relay 1 OFF
  digitalWrite(relay2, relayON); // turn relay 2 ON 
}

// controls the relay so the motor is stopped
void motorStop()
{
  digitalWrite(relay1, relayOFF); // turn relay 1 OFF
  digitalWrite(relay2, relayOFF); // turn relay 2 OFf 
} 
