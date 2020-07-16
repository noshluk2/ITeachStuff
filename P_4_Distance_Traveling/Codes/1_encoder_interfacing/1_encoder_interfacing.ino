/*
    We will calculate how encoders count 
    -   Also learn about 1 revolution ticks
*/


// motor pins
#define enc_L   5
#define enc_R   18
// Variables
int count_R    = 0;                         
int count_L    = 0;                    

void setup()
{   setup_pins();
  Serial.begin(115200);
} 
void loop(){}

// Encoders-Interrupt callback functions
void Update_encR(){
  Serial.println(count_R);
    count_R++;  
}

void Update_encL(){
    count_L++; 
}

void setup_pins(){
    // encoder pinout defination
    pinMode(enc_R,INPUT);
    pinMode(enc_L,INPUT);
    // Interrupt connection to gpio pins and defining interrupt case
    attachInterrupt(digitalPinToInterrupt(enc_R),Update_encR,CHANGE);
    attachInterrupt(digitalPinToInterrupt(enc_L),Update_encL,CHANGE);
}
