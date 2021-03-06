/*

Interface Testing of Ultrasonic sensor
-  Will measure Distance and check its accuracy

*/

// Assigning names to esp Pins 
const int trigger_Pin = 14;
const int echo_Pin = 27;
//Some Global Variables
long duration;
int distance;

void setup(){ 
  setup_all_pinouts(); 
  Serial.begin(115200);
}

void loop(){
  // Signal stop
  digitalWrite(trigger_Pin, LOW);
  delayMicroseconds(2);
  //Signal start
  digitalWrite(trigger_Pin, HIGH);
  delayMicroseconds(10);

  digitalWrite(trigger_Pin, LOW);
  
  duration = pulseIn(echo_Pin, HIGH);
  distance= duration*0.034/2;

  Serial.print("Current Distance = ");
  delay(500);
  Serial.println(distance);

  }

void setup_all_pinouts(){
  pinMode(trigger_Pin, OUTPUT); 
  pinMode(echo_Pin, INPUT);
}
