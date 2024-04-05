#include <RF24.h>
#include <RF24Network.h>
#include <SPI.h>
RF24 radio(9, 10);               // nRF24L01 (CE,CSN)
RF24Network network(radio);      // Include the radio in the network
const uint16_t node1 = 01;   // Address of this node in Octal format ( 04,031, etc)
const uint16_t master = 00;    
unsigned long var;
String test[] = "Hello";

void setup(){ 
  
  Serial.begin(9600);
  SPI.begin();
  radio.begin();
  network.begin(108, node1);  //(channel, node address)
}
 
void loop(){
  network.update();
 

  var = 123;
  RF24NetworkHeader header(master);     // (Address where the data is going)
  bool ok = network.write(header, &var, sizeof(var)); // Send the data
  Serial.print(ok);
  

}
 

 
