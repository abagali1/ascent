#include <Arduino.h>
#include <i2c_t3.h>

void setup()
{
    Wire1.begin(); // join i2c bus (address optional for master)
}

byte x = 0;

void loop()
{
    Wire1.beginTransmission(4); // transmit to device #4
    Wire1.write("x is ");        // sends five bytes
    Wire1.write(x);              // sends one byte  
    Wire1.endTransmission();    // stop transmitting

    x++;
    delay(500);
}
