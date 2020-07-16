
/*
    last code
    Variables Update

*/ 

//Wifi Udp setup
#include <WiFi.h>
#include <WiFiUdp.h>

const char*  ssid = "LuqmanZGeh";
const char*  password = "qwertyuiop";
unsigned int localPort = 9999;
WiFiUDP udp;
IPAddress Server(192, 168, 43, 225);
IPAddress Client(192, 168, 43, 20);
IPAddress Subnet(255, 255, 255, 0);

// encoder and motor pins
#define enc_L   5
#define enc_R   18
#define motorLa 26
#define motorLb 25
#define motorRa 32
#define motorRb 33
#define Rpwm 4
#define Lpwm 16


// Variables
const int freq        = 5000;
const int res         = 8;
int count_R              = 0;                          //For Encoders
int count_L              = 0;                    
const int channel_R      = 0;                          //PWM setup
const int channel_L      = 1;   
int Right_motor_speed    = 130;                        // Motor Base speeds
int Left_motor_speed     = 130;
float Kp                 = 2.1;                        // Proportional Controller
int error;
int16_t output;

char packetBuffer[255];                                 //UDP variables



void setup()
{ 
  Serial.begin(115200);
  setup_all_pins();

  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {          // Exit only when connected
    delay(500);
    Serial.print(".");}
  WiFi.mode(WIFI_STA);                             // ESP-32 as client
  WiFi.config(Client, Server, Subnet);
  
  Serial.print("\nConnected to ");Serial.println(ssid);
  Serial.print("IP address: ");Serial.println(WiFi.localIP());
  delay(3000);
  udp.begin(localPort);                            // Begin the udp communication
} 


void loop()
{   
    if(udp.parsePacket() ){                         // If we recieve any packet
      parseUdpMessage();

    }else{
    Proportional_controller();                      // start processing the controller
    changeMotorSpeed();                             // update the motors
    }             
  
}

// here we recieve the upd message and process is 
void parseUdpMessage() 
    {
    udp.read(packetBuffer, 255);
    delay(2000);
    if(packetBuffer[0]=='s'){
      stop_robot();
    }else{
       // complexity                                                 kp , 130, 255, 400
    char * strtokIndx;
    strtokIndx = strtok(packetBuffer,",");
    Kp = atof(strtokIndx); 
    strtokIndx = strtok(NULL, ",");
    Right_motor_speed = atoi(strtokIndx);
    strtokIndx = strtok(NULL, ",");
    Left_motor_speed= atoi(strtokIndx);
    Serial.print("Kp =");Serial.print(Kp);
  ////////
  
    Serial.print("  Motor Speeds :");Serial.print(Left_motor_speed);Serial.print(" // ");Serial.println(Right_motor_speed);
    delay (3000);
    start_moving();                                // enable the motors
    reset_();
    }

}

void reset_(){                       // previous Kp values residue must not interfere with new one
  error=0;
  count_R=0;
  count_L=0;
}

void Proportional_controller() {
  error =  count_L - count_R;
  output = Kp * (error); 
}

void changeMotorSpeed() {

int rightMotorSpeed = Right_motor_speed + output  ;
int leftMotorSpeed  = Left_motor_speed  - output;
    rightMotorSpeed = constrain(rightMotorSpeed, 120, 255);  
    leftMotorSpeed  = constrain(leftMotorSpeed, 120, 255);
  
    Serial.print(output);Serial.print("/");Serial.print(error);Serial.print(" // ");Serial.print(leftMotorSpeed);Serial.print("/");Serial.println(rightMotorSpeed);
  
    // ledcWrite(channel_R, rightMotorSpeed);  
    // ledcWrite(channel_L, leftMotorSpeed);

}

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

void stop_robot(){
  Serial.print("Stopping RObot");
    digitalWrite(motorLa,LOW);                            
  digitalWrite(motorRa,LOW);
}
void start_moving(){
  digitalWrite(motorLa,HIGH);                             // Forward direction configuration
  digitalWrite(motorRa,HIGH);
  digitalWrite(motorLb,LOW);
  digitalWrite(motorRb,LOW);
  // ledcWrite(channel_R , base_right_speed);                // giving each motor 0 dutycycle value
  // ledcWrite(channel_L , base_left_speed); 
}
