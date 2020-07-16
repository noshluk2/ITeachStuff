/*
  Robot will go straight through encoders inputs
  and proportional controller

*/ 
// encoder and motor pins
#define enc_L   5
#define enc_R   18
#define motorLa 26
#define motorLb 25
#define motorRa 32
#define motorRb 33
#define Rpwm 4
#define Lpwm 16

// PWM and encoders Variables
const int channel_R   = 0;
const int channel_L   = 1; 
const int freq        = 5000;
const int res         = 8;
int rightMotorSpeed   = 0; 
int leftMotorSpeed    = 0;
int base_right_speed   = 200; 
int base_left_speed    = 200;
int count_R           = 0;                         
int count_L           = 0;  

// Controller Variables
float Kp              = 1.3;        // Proportional Controller
int error;
int16_t output;

void setup()
{ 
  Serial.begin(115200);
  setup_all_pins();
  start_moving();
} 


void loop(){  
    Proportional_controller();                      // start processing the controller
    changeMotorSpeed();                             // update the motors      
  
}
void Proportional_controller() {
  error =  count_L - count_R;
  output = Kp * (error); 
}

void changeMotorSpeed() {

    rightMotorSpeed = base_right_speed + output  ;
    leftMotorSpeed  = base_left_speed  - output;
    
    rightMotorSpeed = constrain(rightMotorSpeed, 90, 170);  
    leftMotorSpeed  = constrain(leftMotorSpeed, 90, 170);
  
//    Serial.print(output);Serial.print(" | ");Serial.print(error);Serial.print(" // ");//Serial.print(leftMotorSpeed);Serial.print("/");Serial.println(rightMotorSpeed);
//    Serial.print(count_L);Serial.print("|| ");Serial.println(count_R);
    ledcWrite(channel_R, rightMotorSpeed);  
    ledcWrite(channel_L, leftMotorSpeed);

}

// Encoders-Interrupt callback functions
void Update_encR(){
    count_R++; 
}

void Update_encL(){
    count_L++; 
}

// all motor setup is done in one function call

void setup_all_pins(){
    // encoder pinout defination
    pinMode(enc_R,INPUT);
    pinMode(enc_L,INPUT);
    // Interrupt connection to gpio pins and defining interrupt case
    attachInterrupt(digitalPinToInterrupt(enc_R),Update_encR,RISING);
    attachInterrupt(digitalPinToInterrupt(enc_L),Update_encL,RISING);   
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


void start_moving(){
  digitalWrite(motorLa,HIGH);                             // Forward direction configuration
  digitalWrite(motorRa,HIGH);
  digitalWrite(motorLb,LOW);
  digitalWrite(motorRb,LOW);
  ledcWrite(channel_R , base_right_speed);                // giving each motor 0 dutycycle value
  ledcWrite(channel_L , base_left_speed); 
}
