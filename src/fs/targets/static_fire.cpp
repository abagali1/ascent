#include <Arduino.h>
#include <Servo.h>
#include "SoftwareSerial.h"

#define STOP 999
#define PERIOD 46
#define ESC_PIN 9
#define NEWLINE 13
#define MIN_THROTTLE 1000
#define MAX_THROTTLE 2000

String buf;
bool exited = false;

Servo servo;
SoftwareSerial XBee(2, 3);

void setup()
{
    servo.attach(ESC_PIN,1000,2000);
    servo.writeMicroseconds(0);
    delay(2000);

    XBee.begin(9600);
    XBee.write("teensy started\n");
    Serial.begin(15200);
    Serial.println("teensy started");
}

void loop()
{
    if(!exited){
        while (XBee.available() > 0) {
            byte inByte = XBee.read(); // reads into ascii decimal
            if(inByte != NEWLINE && inByte != PERIOD && (inByte > 57 || inByte < 48)){ // not a number
                buf = "";
                continue;
            }
            buf += (char)inByte; // converts to ascii char
            if(inByte == NEWLINE){
                float throttle = buf.toFloat();
                if(throttle == 999){ // abort/stop 
                    servo.writeMicroseconds(MIN_THROTTLE);
                    XBee.write("exited\n");
                    exited = true;
                    return;
                }
                servo.writeMicroseconds(throttle); // write value
                XBee.write(String("wrote: " + String(throttle) + "\n").c_str());
                buf = "";
                Serial.println(throttle);
            }
        }
        delay(100);
    }
}