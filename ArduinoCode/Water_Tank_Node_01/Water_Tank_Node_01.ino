#include <RF24.h>
#include <RF24Network.h>
#include <SPI.h>
#include <Wire.h> 

#define SensorPin 0          //pH meter Analog output to Arduino Analog Input 0
int sensorPin = A1;          // Turbidity sensor connected to A1

RF24 radio(9, 10);               // nRF24L01 (CE,CSN)
RF24Network network(radio);      // Include the radio in the network
const uint16_t node2 = 02;   // Address of this node in Octal format ( 04,031, etc)
const uint16_t master = 00;    
char var[50]; 



unsigned long int avgValue;  //Store the average value of the sensor feedback
float b;
int buf[10],temp;



// Set the LCD address to 0x27 for a 16 chars and 2 line display


float volt;
float ntu;





float round_to_dp( float in_value, int decimal_place )
{
  float multiplier = powf( 10.0f, decimal_place );
  in_value = roundf( in_value * multiplier ) / multiplier;
  return in_value;
}


void setup()
{
 

    Serial.begin(9600);
    SPI.begin();
    radio.begin();
    network.begin(90, node2);  //(channel, node address)
    radio.setDataRate(RF24_2MBPS);
   
  
}
void loop ()
{


    network.update();


   ///////Ph sensor

   for(int i=0;i<10;i++)       //Get 10 sample value from the sensor for smooth the value
  { 
    buf[i]=analogRead(SensorPin);
    delay(10);
  }
  for(int i=0;i<9;i++)        //sort the analog from small to large
  {
    for(int j=i+1;j<10;j++)
    {
      if(buf[i]>buf[j])
      {
        temp=buf[i];
        buf[i]=buf[j];
        buf[j]=temp;
      }
    }
  }
  avgValue=0;
  for(int i=2;i<8;i++)                      //take the average value of 6 center sample
    avgValue+=buf[i];
  float phValue=(float)avgValue*5.0/1024/6; //convert the analog into millivolt
  phValue=3.5*phValue;                      //convert the millivolt into pH value
  //Serial.print("    pH:");  
  //Serial.print(phValue,2);
  //Serial.println(" ");
  

  ////////////////////////////////////////////////////

  //Turbidity

    volt = 0;
    for(int i=0; i<800; i++)
    {
        volt += ((float)analogRead(sensorPin)/1023)*5;
    }
    volt = volt/800;
    volt = round_to_dp(volt,1);
    if(volt < 2.5){
      ntu = 3000;
    }else{
      ntu = -1120.4*square(volt)+5742.3*volt-4353.8;
        
    }
   
    //Serial.print(volt);
    //Serial.print(" V  ");

    
    //Serial.print(ntu);
    //Serial.println(" NTU");
    //delay(10);

    ////////////////////////////////////////////
  

  String dbuff2="t";
  dbuff2+="Node_1";
  dbuff2+="u";
  dbuff2+=(String)phValue;
  dbuff2+="v";
  dbuff2+=(String)ntu;
  dbuff2+="w";
  //Serial.print(ntu);
 
  

  dbuff2.toCharArray(var, 50);
  
  RF24NetworkHeader header(master);     // (Address where the data is going)
  bool ok = network.write(header, &var, 
  sizeof(var)); // Send the data

  Serial.println(var);
  delay(1000);
  
}
