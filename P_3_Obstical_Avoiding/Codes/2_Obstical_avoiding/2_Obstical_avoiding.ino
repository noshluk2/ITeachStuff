/*

  Robot is going to detect obsticles and tell us 
  - Stop right there
  - Distance in between
  - Take Left Turn

*/

// Assigning names to esp Pins 
#define motorLa 26
#define motorLb 25
#define motorRa 32
#define motorRb 33

const int trigger_Pin = 14;
const int echo_Pin = 27;
long duration;
int distance;

void setup(){ 
  Serial.begin(115200);
  setup_all_pinouts(); 
  forward(); // boht important 
}

void loop(){
digitalWrite(trigger_Pin, LOW);
delayMicroseconds(2);
digitalWrite(trigger_Pin, HIGH);
delayMicroseconds(10);
digitalWrite(trigger_Pin, LOW);
duration = pulseIn(echo_Pin, HIGH);
distance= duration*0.034/2;

Serial.println(distance);
// code to make robot take turn when obstical is infront of it
  if(distance<20){
    stop_();
    delay(1000);
    left_turn();
    delay(400);
    stop_();
    delay(1000);
    forward();
  }

  }
void forward(){
  Serial.println("Moveing Forward");
  digitalWrite(motorLa,HIGH);
  digitalWrite(motorRa,HIGH);
  digitalWrite(motorLb,LOW);
  digitalWrite(motorRb,LOW);
}
void left_turn(){
  Serial.println("Turning Left");
  digitalWrite(motorLa,LOW);
  digitalWrite(motorRa,HIGH);
  digitalWrite(motorLb,LOW);
  digitalWrite(motorRb,LOW);
}
void stop_(){
  Serial.println("Stop");
  digitalWrite(motorLa,LOW);
  digitalWrite(motorRa,LOW);
  digitalWrite(motorLb,LOW);
  digitalWrite(motorRb,LOW);
}

void setup_all_pinouts(){
  pinMode(trigger_Pin, OUTPUT); 
  pinMode(echo_Pin, INPUT);
  pinMode(motorLa, OUTPUT);
  pinMode(motorLb, OUTPUT);
  pinMode(motorRa, OUTPUT);
  pinMode(motorRb, OUTPUT);
}
