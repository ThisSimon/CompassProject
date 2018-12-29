/*
@Author Simon Remington

*/

/*
CMPS03 with arduino I2C example
understanding the compass: https://www.robot-electronics.co.uk/htm/cmps3tech.htm
helpfull for wiring: https://www.noisebridge.net/wiki/Compass
helpfull for i2c bus: https://robot-electronics.co.uk/i2c-tutorial
This will display a value of 0 - 359 for a full rotation of the compass.

The SDA line is on analog pin 4 of the arduino and is connected to pin 3 of the CMPS03.
The SCL line is on analog pin 5 of the arduino and is conected to pin 2 of the CMPS03.
Both SDA and SCL are also connected to the +5v via a couple of 1k8 resistors.
A switch to callibrate the CMPS03 can be connected between pin 6 of the CMPS03 and the ground.
The LEDs are on digital pin 3 and 4.
A button is in pin 2
*/

#include <Wire.h>

#define ADDRESS 0x60 //defines address of compass

const int west=3;
const int east=4;
const int btnPin=2;
int myTimer=20;

void setup(){
  pinMode(west, OUTPUT);
  pinMode(east, OUTPUT);
  pinMode(btnPin, INPUT);
  
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
  //if(btnPin){
  if(digitalRead(btnPin)){  //if button pressed
    myTimer=20;
  }
  while(myTimer > 0) {
   Wire.beginTransmission(ADDRESS); //starts communication with cmps03
   Wire.write(2);                   //Sends the register we wish to read
   Wire.endTransmission();

   Wire.requestFrom(ADDRESS, 2);    //requests high byte
   while(Wire.available() < 2);     //while there is a byte to receive
   highByte = Wire.read();          //reads the byte as an integer
   lowByte = Wire.read();
   int bearing = ((highByte<<8)+lowByte)/10; 
   
  // Serial.println(bearing);
   if (bearing >10 && bearing <175){
    digitalWrite(west, LOW);
    digitalWrite(east, HIGH);
   }
   else if  (bearing >185 && bearing <350){
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
   delay(500);
    digitalWrite(west, LOW);
    digitalWrite(east, LOW);
   delay(500);
   myTimer--;
  }
}
