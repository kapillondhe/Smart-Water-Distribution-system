
#include <RF24Network.h>
#include <RF24.h>
#include <SPI.h>


RF24 radio(9,10);               // nRF24L01 (CE,CSN)
RF24Network network(radio);      // Include the radio in the network
const uint16_t Master = 00;   // Address of this node in Octal format ( 04,031, etc)
const uint16_t node01 = 01;      // Address of the other node in Octal format

char incomingData[50];

void setup() {
  SPI.begin();
  Serial.begin(9600);
  radio.begin();
  network.begin(90, Master);  //(channel, node address)
 // radio.setDataRate(RF24_2MBPS);
  
}

void loop() {
  network.update();
  //===== Receiving =====//
  while ( network.available() ) {     // Is there any incoming data?
    RF24NetworkHeader header;
    
    network.read(header, &incomingData, sizeof(incomingData)); // Read the incoming data
  
    Serial.println(incomingData); 
  }
  
  
  

}
