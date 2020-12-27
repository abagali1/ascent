#include "NanoRadio.hpp"


NanoRadio::NanoRadio(i2c_t3 Wire, uint8_t addr)
    :   I2CDevice("NanoRadio", Wire, addr, 32),
        Device("NanoRadio") {}

void NanoRadio::send_message(const std::string& msg){
    this->transmit(msg.c_str());
}

const std::string NanoRadio::read_message(){
    const char* buf;
    this->read_all(buf);
    return std::string(buf);
}

