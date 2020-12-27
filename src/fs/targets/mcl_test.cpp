#include <fs/FCCode/MainControlLoop.hpp>
#include <common/StateFieldRegistry.hpp>

#include <Arduino.h>

void setup(){
    StateFieldRegistry sfr;
    MainControlLoop mcl(sfr);

    mcl.execute();

}

void loop(){}