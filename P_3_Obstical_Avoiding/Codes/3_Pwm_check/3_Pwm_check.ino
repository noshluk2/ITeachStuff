/*
  Tyres will rotate in increasing and then decreasing order
  to check pwm signals

*/

// Assigning names to esp Pins 
#define motorRa 26
#define motorRb 25
#define motorLa 32
#define motorLb 33

// PWM for 2 motor
#define Rpwm 4
#define Lpwm 16


//Motor Pwm global Variables
const int channel_R = 0;
const int channel_L = 1;
const int freq = 5000;
const int res = 8;

void setup(){ 
  setup_all_pinouts();
  setup_direction(); 
  Serial.begin(115200);
}

void loop(){
    for (int inc=0 ;inc<=255;inc=inc+15){

      ledcWrite(channel_R , inc);               
      ledcWrite(channel_L , inc);
      Serial.print("Increasing PWM Value = ");
      Serial.println(inc);
      delay(500); 
    }

  for (int dec=255;dec>=0;dec=dec-15){
    ledcWrite(channel_R , dec);               
    ledcWrite(channel_L , dec);
    Serial.print("Decreasing PWM Value = ");
    Serial.println(dec); 
    delay(500);  }

  }
  
void setup_direction(){
  digitalWrite(motorLa,HIGH);
  digitalWrite(motorRa,HIGH);
  digitalWrite(motorLb,LOW);
  digitalWrite(motorRb,LOW);

}
void setup_all_pinouts(){
  
  pinMode(motorLa, OUTPUT);
  pinMode(motorLb, OUTPUT);
  pinMode(motorRa, OUTPUT);
  pinMode(motorRb, OUTPUT);
  
  ledcSetup(channel_R ,freq , res);
  ledcSetup(channel_L ,freq , res);

  ledcAttachPin(Rpwm,channel_R);
  ledcAttachPin(Lpwm,channel_L);
}
