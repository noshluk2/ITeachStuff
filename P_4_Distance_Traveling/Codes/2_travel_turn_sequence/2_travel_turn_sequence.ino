/* 
Robot will travel 100 cm
it will take a turn of 180 degrees ( U-TURN)
then it will move 100 cm

*/ 



// encoder pins
#define enc_L   5
#define enc_R   18
// motor pins
#define motorLa 26
#define motorLb 25
#define motorRa 32
#define motorRb 33
#define Rpwm 4
#define Lpwm 16

// PWM Variables
const int channel_R = 0;
const int channel_L = 1; 
const int freq = 5000;
const int res = 8;
//Encoder variables
int count_R    = 0;                         
int count_L    = 0;                    
short ticks_req = 0;
unsigned int one_rev_ticks = 480 ;// its an average the encoders are not very accurate so error will be produced.
short one_rev_dist = 20.7 ;               
unsigned int ticks_for_360 = 1840 ; //  calculated through th formula with ticks 480 per revolution
bool car_moving;                         

void setup() {
  Serial.begin(115200);                           
  setup_all_pins();
  Serial.println("GET READY ");
  delay(2000);
  travel_turn_sequence();
}

void loop() {}

void travel_turn_sequence(){
  distance_to_travel(100);
  Serial.println("COMPLETED !!! Went 100cm forward");
  delay(3000);
  degrees_to_turn(180);
  Serial.println("COMPLETED !!!  180 Degree Turn");
  delay(3000);
  distance_to_travel(100);
  Serial.println("COMPLETED !!! 100cm forward");

}


void distance_to_travel(int centimeters){
  short rev_req = centimeters / one_rev_dist;       // this will produced revolution required for required distance to travel
  ticks_req = rev_req * one_rev_ticks ;             // this will produced ticks motor should do to complete required distance
  start();count_R=0;                                          //Enable motors
  while(car_moving){
    Serial.println(count_R);
    if(count_R>=ticks_req + 20){
      stop_();
      }
    }
  }

void degrees_to_turn(int degree){
    ticks_req = (degree * ticks_for_360)/360 ;
    start();count_R=0;
    digitalWrite(motorLa,LOW); // only using right turns 
    while(car_moving){
      Serial.println(count_R);
      if(count_R>=ticks_req){
        stop_();          
        }
      }
  }

void setup_all_pins(){
    // encoder pinout defination
    pinMode(enc_R,INPUT);
    pinMode(enc_L,INPUT);
    // Interrupt connection to gpio pins and defining interrupt case
    attachInterrupt(digitalPinToInterrupt(enc_R),Update_encR,CHANGE);
    attachInterrupt(digitalPinToInterrupt(enc_L),Update_encL,CHANGE);   
    // Motor Pins defination 
    pinMode(motorLa, OUTPUT);
    pinMode(motorLb, OUTPUT);
    pinMode(motorRa, OUTPUT);
    pinMode(motorRb, OUTPUT);
    ledcSetup(channel_R ,freq , res);
    ledcSetup(channel_L ,freq , res);
    ledcAttachPin(Rpwm,channel_R);
    ledcAttachPin(Lpwm,channel_L);

}
// Encoders-Interrupt callback functions
void Update_encR(){
    count_R++; 
}

void Update_encL(){
    count_L++; 
}

void stop_(){
  car_moving=false;
  ledcWrite(channel_R , 0);                            
  ledcWrite(channel_L , 0);  

}

void start(){
  
  digitalWrite(motorLa,HIGH);
  digitalWrite(motorRa,HIGH);
  digitalWrite(motorLb,LOW);
  digitalWrite(motorRb,LOW);
  ledcWrite(channel_R , 230);                            
  ledcWrite(channel_L , 232);
  car_moving=true;
}
