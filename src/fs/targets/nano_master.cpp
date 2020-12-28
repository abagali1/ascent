#include <Arduino.h>

#include <fs/FCCode/Drivers/NanoRadio.hpp>

NanoRadio r(Wire, 0x60, 20);

void setup()
{   
    Serial.begin(9600);
    delay(5000);
    Serial.println("begin");
}


void loop()
{
    Serial.println("Receiving");
    Serial.println(r.read_message().c_str());

    r.send_message("hello duino");
    delay(1000);
}
