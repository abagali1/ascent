#include "NanoRadio.hpp"


NanoRadio::NanoRadio(i2c_t3 Wire, uint8_t addr, uint pin)
    :   Device("NanoRadio"),
        I2CDevice("NanoRadio", Wire, addr, 32),
        reset_pin(pin)
{
    this->setup();
    pinMode(this->reset_pin, OUTPUT);
    digitalWrite(this->reset_pin, HIGH);
}

void NanoRadio::send_message(const std::string& msg){
    this->transmit(msg.c_str());
}

const std::string NanoRadio::read_message(){
    char buf[this->max_bytes];
    this->read_all(buf);
    return std::string(buf, this->max_bytes);
}

void NanoRadio::reset(){
    digitalWrite(this->reset_pin, LOW);
    this->Wire.resetBus();
}

