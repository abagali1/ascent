#ifndef _I2C_DEVICE_HPP
#define _I2C_DEVICE_HPP

#include <i2c_t3.h>

#include "Device.hpp"

class I2CDevice: public virtual Device{
    protected:
        i2c_t3 Wire;
        uint8_t address;
        uint8_t max_bytes;

    public:
        I2CDevice(const std::string&, i2c_t3, uint8_t, uint8_t);
        void setup() override;
        void reset() override;

        void _request_from(uint8_t);
        
        void read_all(const char*);
        void transmit(const char*);
};

#endif