#include "I2CDevice.hpp"

I2CDevice::I2CDevice(const std::string& n, i2c_t3 theWire, uint8_t addr, uint8_t mb)
    :   Device(n),
        Wire(theWire),
        address(addr),
        max_bytes(mb) {}

void I2CDevice::setup(){
    this->Wire.begin();
}

void I2CDevice::reset(){
    this->Wire.resetBus();
}

void I2CDevice::_request_from(uint8_t bytes){
    this->Wire.requestFrom(this->address, bytes);
}

void I2CDevice::read_all(const char* out){
    this->_request_from(this->max_bytes);
    uint8_t bytes = this->Wire.available();
    char buf[bytes];

    for(int i=0;i<bytes;i++){
        buf[i] = this->Wire.read();
    }
    out = buf;
}

void I2CDevice::transmit(const char* msg){
    this->Wire.beginTransmission(this->address);
    this->Wire.write(msg);
    this->Wire.endTransmission();
}
