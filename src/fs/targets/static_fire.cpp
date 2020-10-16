#include <Arduino.h>
#include <Servo.h>
#include "SoftwareSerial.h"

#define STOP 999
#define ESC_PIN 9
#define PERIOD 46
#define NEWLINE 13
#define MIN_THROTTLE 1000
#define MAX_THROTTLE 2000

String buf;
bool exited = false;

Servo servo;
SoftwareSerial XBee(2, 3);

void arm(){
    servo.writeMicroseconds(0);
    delay(3000);
    servo.writeMicroseconds(MAX_THROTTLE);
    delay(3000);
    servo.writeMicroseconds(MIN_THROTTLE);
    delay(5000);
}

void setup()
{
    servo.attach(ESC_PIN);
    delay(1000);
    arm();

    XBee.begin(9600);
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
                servo.writeMicroseconds((throttle/100.0 * MIN_THROTTLE)+MIN_THROTTLE); // write value
                XBee.write(String("wrote: " + String((throttle/100.0 * MIN_THROTTLE)+MIN_THROTTLE) + "\n").c_str());
                buf = "";
                Serial.println(throttle);
            }
        }
        delay(500);
    }
}