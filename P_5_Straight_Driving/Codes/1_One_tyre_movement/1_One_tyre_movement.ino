/* 
Only Single Tyre movement

- Robot will move in Forward direction for 1.5 second
- It will stop for 2 seconds
- Then it will move in Reverse Direction  for 1.5 seconds
- Rest and then repeat

*/


// Assigning names to  Pins connected with ESP32

#define motorRa 32
#define motorRb 33

void setup(){ 
  // defining pins working type
  
  pinMode(motorRa, OUTPUT);
  pinMode(motorRb, OUTPUT);
}

void loop(){
  
  // forward
  digitalWrite(motorRa,HIGH);
  digitalWrite(motorRb,LOW);
  delay (1500);
  
  //Stopping 
  digitalWrite(motorRa,LOW);
  digitalWrite(motorRb,LOW);
  delay(2000);
  
  // Reverse
  digitalWrite(motorRa,LOW);
  digitalWrite(motorRb,HIGH);
  delay (1500);
  
  // Again Stopping 
  digitalWrite(motorRa,LOW);
  digitalWrite(motorRb,LOW);
  delay(2000);
  }
