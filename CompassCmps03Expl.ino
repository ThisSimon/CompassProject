/*
CMPS03 with arduino I2C example

This will display a value of 0 - 359 for a full rotation of the compass.

The SDA line is on analog pin 4 of the arduino and is connected to pin 3 of the CMPS03.
The SCL line is on analog pin 5 of the arduino and is conected to pin 2 of the CMPS03.
Both SDA and SCL are also connected to the +5v via a couple of 1k8 resistors.
A switch to callibrate the CMPS03 can be connected between pin 6 of the CMPS03 and the ground.
The LEDs are on digital pis 3 and 4.
*/

#include <Wire.h>

#define ADDRESS 0x60 //defines address of compass

const int west=3;
const int east=4;

void setup(){
  pinMode(west, OUTPUT);
  pinMode(east, OUTPUT);
  digitalWrite(west, LOW);
  digitalWrite(east,LOW);
  delay(100);
  
  Wire.begin(); //conects I2C
  //Serial.begin(9600);
 // Serial.println("insetup");
  delay(2000);
}

void loop(){
  byte highByte;
  byte lowByte;
  
   Wire.beginTransmission(ADDRESS); //starts communication with cmps03
   Wire.write(2);                   //Sends the register we wish to read
   Wire.endTransmission();

   Wire.requestFrom(ADDRESS, 2);    //requests high byte
   while(Wire.available() < 2);     //while there is a byte to receive
   highByte = Wire.read();          //reads the byte as an integer
   lowByte = Wire.read();
   int bearing = ((highByte<<8)+lowByte)/10; 
   
  // Serial.println(bearing);
   if (bearing >5 && bearing <175){
    digitalWrite(west, LOW);
    digitalWrite(east, HIGH);
   }
   else if  (bearing >185 && bearing <355){
    digitalWrite(west, HIGH);
    digitalWrite(east, LOW);
   }
   else if  (bearing >=175 && bearing <=185){
    digitalWrite(west, HIGH);
    digitalWrite(east, HIGH);
   }
   else
   {
    digitalWrite(west, LOW);
    digitalWrite(east, LOW);
   }
   delay(200);
}
