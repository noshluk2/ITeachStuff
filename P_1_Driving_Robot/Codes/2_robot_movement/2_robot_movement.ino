/* 
Complete Robot Movement

- Robot will move in Forward direction for 3 seconds
- It will stop for 1 second
- Then it will move in Reverse Direction for 2 seconds
- Stop for 1 second
- Repeat from start

*/


// Assigning names to  Pins connected with ESP32

#define motorRa 32
#define motorRb 33

#define motorLa 25
#define motorLb 26

void setup(){ 
  // defining pins working type
  pinMode(motorRa, OUTPUT);
  pinMode(motorRb, OUTPUT);

  pinMode(motorLa, OUTPUT);
  pinMode(motorLb, OUTPUT);
}

void loop(){
  forward();
  delay(3000);

  stop_();
  delay(1000);
  
  reverse();
  delay(2000);

  stop_();
  delay(1000);

}
 

  void forward(){
    // forward
    digitalWrite(motorRa,HIGH);
    digitalWrite(motorRb,LOW);
    digitalWrite(motorLa,HIGH);
    digitalWrite(motorLb,LOW);
  }

  void reverse(){
  // Reverse
    digitalWrite(motorRa,LOW);
    digitalWrite(motorRb,HIGH);
    digitalWrite(motorLa,LOW);
    digitalWrite(motorLb,HIGH);
  }

  void stop_(){
 // Again Stopping 
  digitalWrite(motorRa,LOW);
  digitalWrite(motorRb,LOW);
  digitalWrite(motorLa,LOW);
  digitalWrite(motorLb,LOW);
  
  }
