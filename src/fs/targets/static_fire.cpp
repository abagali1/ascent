#include <Arduino.h>
#include "SoftwareSerial.h"
#define NEWLINE 13
#define STOP 999
SoftwareSerial XBee(2, 3);
String buf;
bool exited = false;
void setup()
{
  XBee.begin(9600);
  Serial.begin(15200);
  Serial.println("teensy started");
}

void loop()
{
  if(!exited){
    while (XBee.available() > 0) {
      byte inByte = XBee.read(); // reads into ascii decimal
      if(inByte != NEWLINE && (inByte > 57 || inByte < 48)){ // not a number
        buf = "";
        continue;
      }
      buf += (char)inByte; // converts to ascii char
      if(inByte == NEWLINE){
        float throttle = buf.toFloat();
        if(throttle == 999){
          XBee.write("exited\n");
          exited = true;
          return;
        }
        XBee.write(String("wrote: " + String(throttle) + "\n").c_str());
        buf = "";
        Serial.println(throttle);
      }
    }
    delay(500);
  }
}