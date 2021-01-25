#include <fs/FCCode/MainControlLoop.hpp>
#include <common/StateFieldRegistry.hpp>

#include <core_pins.h>
#include <wiring.h>

void setup(){
    StateFieldRegistry sfr;
    MainControlLoop mcl(sfr);

    mcl.execute();
}

void loop(){}
