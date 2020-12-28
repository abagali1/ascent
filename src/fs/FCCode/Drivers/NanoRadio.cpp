#include "NanoRadio.hpp"


NanoRadio::NanoRadio(i2c_t3 Wire, uint8_t addr)
    :   I2CDevice("NanoRadio", Wire, addr, 32),
        Device("NanoRadio")
{
    this->setup();
}

void NanoRadio::send_message(const std::string& msg){
    this->transmit(msg.c_str());
}

const std::string NanoRadio::read_message(){
    char buf[this->max_bytes];
    this->read_all(buf);
    return std::string(buf, this->max_bytes);
}

