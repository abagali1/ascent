#ifndef _NANO_HPP
#define _NANO_HPP

#include <string>

#include <common/Devices/I2CDevice.hpp>

class NanoRadio: public I2CDevice{
    public:
        NanoRadio(i2c_t3, uint8_t);
        const std::string read_message();
        void send_message(const std::string&);
};

#endif
