#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>
#include <RF24Network.h>
RF24 radio(9, 10); // CE, CSN
const uint16_t this_node = 01;   // Address of this node in Octal format ( 04,031, etc)
const uint16_t node01 = 00;
RF24Network network(radio);   

void setup() {
  Serial.begin(9600);  
  radio.begin();
 // radio.openWritingPipe(address);//
  radio.setDataRate(RF24_2MBPS);
  radio.setPALevel(RF24_PA_MIN);
  //radio.stopListening();//
  network.begin(90, this_node);
}
void loop() 
{
    network.update();
    char txt[32]="";
    while ( network.available() )
   {
    Serial.println("Inside Loop");
    delay(20);
 
    RF24NetworkHeader header2;
    network.read(header2,&txt,sizeof(txt));
    Serial.println("Received");
    Serial.println(txt);
   }
    delay(20);
    const char data[]= {"PrahsantRanpura"};
    RF24NetworkHeader header2(node01);
    network.write(header2,&data,sizeof(data));
    Serial.println("transmitted");

}
   

  
