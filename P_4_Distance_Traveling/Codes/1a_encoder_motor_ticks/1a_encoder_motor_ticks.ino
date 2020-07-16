/*

    Code to measures ticks of one revolution
    through motor actuation .

*/

// encoder pins
#define enc_L   5
#define enc_R   18
// motor pins
#define motorRa 26
#define motorRb 25
#define motorLa 32
#define motorLb 33
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
unsigned int one_rev_ticks = 200 ;


void setup()
{   
    Serial.begin(115200);
    setup_all_pins();
    start();
} 
void loop(){}

// Encoders-Interrupt callback functions
void Update_encR(){
    count_R++;
    
    if(one_rev_ticks <=count_R++ ){
        stop_();
    }  
}

void Update_encL(){
    count_L++; 
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

void stop_(){
  Serial.println(count_R);
  ledcWrite(channel_R , 0);                            
  ledcWrite(channel_L , 0);  
}

void start(){
  digitalWrite(motorLa,HIGH);
  digitalWrite(motorRa,HIGH);
  digitalWrite(motorLb,LOW);
  digitalWrite(motorRb,LOW);
  ledcWrite(channel_R , 230);                            
  ledcWrite(channel_L , 230);
}
