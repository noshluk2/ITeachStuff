/*
We are going to take a look on 
- Userfullness of Serial Monitor
- Setup our Bluetooth Communication

*/ 

#include "BluetoothSerial.h" // library
char command; // global declaration
BluetoothSerial SerialBT;

void setup() {
  Serial.begin(115200); //serial monitor init
  SerialBT.begin(" Bluetooth Avaible for communication ");
}

void loop() {
  if (SerialBT.available()) {
      command=SerialBT.read();
       Serial.print("What i recieved :");
    Serial.println(command); 
  }

  }
