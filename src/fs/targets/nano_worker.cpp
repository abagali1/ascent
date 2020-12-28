#include <Wire.h>

#define SLAVE_ADDRESS 0x60 // Must be synchronized with Teensy constants

const char x[15] = "hello world";

void setup(){
  Wire.begin(SLAVE_ADDRESS);
  Wire.onReceive(receiveEvent);
  Wire.onRequest(requestEvent);
  Serial.begin(9600);
}

void loop()
{
  delay(100);
}

void requestEvent() 
{
  Serial.print("Request from Master. Sending: ");
  Serial.println(x);
  Wire.write(x, 15);
}

void receiveEvent(int bytes){
  Serial.print("Got ");
  Serial.println(bytes);
  char buf[bytes];
  if(Wire.available() != 0)
  {
    for(int i = 0; i< bytes; i++)
    {
      buf[i] = (char)Wire.read();
    }
  Serial.println(buf);
  }
}