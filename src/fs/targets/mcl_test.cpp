#include <fs/FCCode/MainControlLoop.hpp>
#include <common/StateFieldRegistry.hpp>

#include <core_pins.h>
#include <wiring.h>

void setup(){
    Serial.begin(9600);
    delay(2000);
    StateFieldRegistry sfr;
    MainControlLoop mcl(sfr);

    debug::println(debug::DEBUG, "start");
    for(int i=0;;i++)
        mcl.execute();
    mcl.finish();
    debug::println(debug::DEBUG, "fin");
}

void loop(){}
