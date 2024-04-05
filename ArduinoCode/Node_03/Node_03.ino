#include <RF24.h>
#include <RF24Network.h>
#include <SPI.h>
RF24 radio(9, 10);               // nRF24L01 (CE,CSN)
RF24Network network(radio);      // Include the radio in the network
const uint16_t node3 = 03;   // Address of this node in Octal format ( 04,031, etc)

const uint16_t master = 00;    
char var[50]; 


volatile int flow_frequency; // Measures flow sensor pulses
float l_hour; // Calculated litres/hour
float flowsensor = 2; // Sensor Input
unsigned long currentTime;
unsigned long cloopTime;
 float total_litres = 0;

 
void flow () // Interrupt function
{
   flow_frequency++;
}
void setup()
{
   pinMode(flowsensor, INPUT);
   digitalWrite(flowsensor, HIGH); // Optional Internal Pull-Up
   Serial.begin(9600);
   attachInterrupt(0, flow, RISING); // Setup Interrupt
   sei(); // Enable interrupts
   currentTime = millis();
   cloopTime = currentTime;


    Serial.begin(9600);
   SPI.begin();
   radio.begin();
   network.begin(90, node3);  //(channel, node address)
   radio.setDataRate(RF24_2MBPS);
  
}
void loop ()
{
   currentTime = millis();
   // Every second, calculate and print litres/hour
   if(currentTime >= (cloopTime + 1000))
   {
      cloopTime = currentTime; // Updates cloopTime
      // Pulse frequency (Hz) = 7.5Q, Q is flow rate in L/min.
      l_hour = (flow_frequency * 60 / 7.5); // (Pulse frequency x 60 min) / 7.5Q = flowrate in L/hour
      flow_frequency = 0; // Reset Counter
      Serial.print(l_hour,  DEC); // Print litres/hour
      Serial.println(" L/hour");
      total_litres = total_litres +  l_hour / 3600;
      Serial.println(total_litres, 2);
   }

    network.update();
   /* String dbuff2="Node_1 ";
    dbuff2+=(String)l_hour;
    dbuff2=" ";
    dbuff2+=(String)total_litres; 
    

  dbuff2.toCharArray(var, 50); */

  String dbuff2="t";
  dbuff2+="Node_3";
  dbuff2+="u";
  dbuff2+=(String)l_hour;
  dbuff2+="v";
  dbuff2+=(String)total_litres;
  dbuff2+="w";
 
 
  

 dbuff2.toCharArray(var, 50);
  
  RF24NetworkHeader header(master);     // (Address where the data is going)
  bool ok = network.write(header, &var, sizeof(var)); // Send the data

  Serial.print(var);
  delay(1500);
  
}
