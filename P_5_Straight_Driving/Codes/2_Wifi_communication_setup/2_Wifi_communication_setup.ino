
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

char packetBuffer[255];                                 //UDP variables



void setup()
{ 
  Serial.begin(115200);

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
      parseUdpMessage(); }   
  
}

// here we recieve the upd message and process is 
void parseUdpMessage() 
    {
    udp.read(packetBuffer, 255);
    Serial.println(packetBuffer[0]);


}
