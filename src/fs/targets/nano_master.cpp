#include <Arduino.h>

void setup()
{   
    Serial.begin(9600);
    Serial4.begin(9600);
    delay(5000);
    Serial.println("begin");
    Serial4.println("hello");
}


void loop()
{   
    String in = Serial.readStringUntil('\n');
    if(in)
        Serial4.println(in);
    delay(1000);
}
