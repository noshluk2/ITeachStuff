/*
  Lets control our robot over bluetooth
- Through any app on smart phone

*/ 

#include "BluetoothSerial.h"
#define motorRa 26
#define motorRb 25
#define motorLa 32
#define motorLb 33

char command;
BluetoothSerial SerialBT;

void setup() {
  Serial.begin(115200);
  setup_motors_direction();
  SerialBT.begin("Car Availble to drive ");
}

void loop() {

  if (SerialBT.available()) {
      command=SerialBT.read();
    
  }

  switch (command) {
    case 'f':
    Serial.println("Going Forward");
      forward();
      break;

    case 'b':
    Serial.println("Going Reverse");
      reverse();
      break;

    case 'r':
    Serial.println("Turning Right");
      right();
      break;
    case 'l':

    Serial.println("Turning Left");
      left();
      break;
      
    case 's':
    Serial.println("STOPPING");
      stopp();
      break;
}
  
  }

void stopp(){
  digitalWrite(motorLa,LOW);
  digitalWrite(motorRa,LOW);
  digitalWrite(motorLb,LOW);
  digitalWrite(motorRb,LOW);
}

void reverse(){
  digitalWrite(motorLa,LOW);
  digitalWrite(motorRa,LOW);
  digitalWrite(motorLb,HIGH);
  digitalWrite(motorRb,HIGH);
}
void forward(){
  digitalWrite(motorLa,HIGH);
  digitalWrite(motorRa,HIGH);
  digitalWrite(motorLb,LOW);
  digitalWrite(motorRb,LOW);
}

void left(){
  digitalWrite(motorLa,LOW);
  digitalWrite(motorRa,HIGH);
  digitalWrite(motorLb,LOW);
  digitalWrite(motorRb,LOW);
}
void right(){
  digitalWrite(motorLa,HIGH);
  digitalWrite(motorRa,LOW);
  digitalWrite(motorLb,LOW);
  digitalWrite(motorRb,LOW);
}

void setup_motors_direction(){
  pinMode(motorLa, OUTPUT);
  pinMode(motorLb, OUTPUT);
  pinMode(motorRa, OUTPUT);
  pinMode(motorRb, OUTPUT);
}
