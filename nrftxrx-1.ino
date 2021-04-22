#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>
#include <RF24Network.h>
#include  <LiquidCrystal.h>

LiquidCrystal lcd(2,3,4,5,6,8);

RF24 radio(9,10); // CE, CSN
const uint16_t this_node = 01;   // Address of this node in Octal format ( 04,031, etc)
const uint16_t node01 = 00;
RF24Network network(radio);   

void setup() {
  Serial.begin(9600);  
  radio.begin();
  lcd.begin(16,2);
  lcd.setCursor(0,0);
 // radio.openWritingPipe(address);//
  radio.setDataRate(RF24_2MBPS);
  radio.setPALevel(RF24_PA_MIN);
  //radio.stopListening();//
  network.begin(90, this_node);
}
void loop() 
{
    network.update();
    const char txt[32]="";
    while ( network.available() )
   {
    lcd.print("In");
 
    RF24NetworkHeader header2;
    network.read(header2,&txt,sizeof(txt));
//  
    lcd.print(txt);
    Serial.println(txt);
    delay(2000);
   }
    delay(30);
    const char data[]= {"PrahsantRanpura"};
    RF24NetworkHeader header2(node01);
    network.write(header2,&data,sizeof(data));
//    lcd.print("transmitted");
    delay(1000);
    lcd.clear();

}
