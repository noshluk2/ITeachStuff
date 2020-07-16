/*
  Robot will slow down as it approches obsticals 
*/

// Assigning names to esp Pins 
#define motorRa 26
#define motorRb 25
#define motorLa 32
#define motorLb 33

#define Rpwm 4
#define Lpwm 16

// ultra sonic sensor global variables
const int trigger_Pin = 14;
const int echo_Pin = 27;
long duration;
int distance;

//Motor Pwm global Variables
const int channel_R = 0;
const int channel_L = 1;
const int freq = 5000;
const int res = 8;

void setup(){ 
  setup_all_pinouts(); 
  start_moving();
  Serial.begin(115200);
}

void loop(){
  digitalWrite(trigger_Pin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigger_Pin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigger_Pin, LOW);
  duration = pulseIn(echo_Pin, HIGH);
  distance= duration*0.034/2;
  //Proportional - controller
  ledcWrite(channel_R , 3*distance);                         
  ledcWrite(channel_L , 3*distance);
  Serial.println(distance);

// 20  --> 60
// 10 ->> 30
//100 -->> 300
// 90 -->> 180


  }



void stop_(){
  Serial.println("STOPING");
  digitalWrite(motorLa,LOW);
  digitalWrite(motorRa,LOW);
  digitalWrite(motorLb,LOW);
  digitalWrite(motorRb,LOW);

}

void  start_moving(){
  digitalWrite(motorLa,HIGH);
  digitalWrite(motorRa,HIGH);
  digitalWrite(motorLb,LOW);
  digitalWrite(motorRb,LOW);
  ledcWrite(channel_R , 150);                            
  ledcWrite(channel_L , 150);
}


void setup_all_pinouts(){
  pinMode(trigger_Pin, OUTPUT); 
  pinMode(echo_Pin, INPUT);
  // motor pwm signal setup
  pinMode(motorLa, OUTPUT);
  pinMode(motorLb, OUTPUT);
  pinMode(motorRa, OUTPUT);
  pinMode(motorRb, OUTPUT);
  ledcSetup(channel_R ,freq , res);
  ledcSetup(channel_L ,freq , res);
  ledcAttachPin(Rpwm,channel_R);
  ledcAttachPin(Lpwm,channel_L);
}
