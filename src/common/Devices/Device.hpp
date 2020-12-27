#ifndef _DEVICE_HPP
#define _DEVICE_HPP

#include <string>

class Device{
    protected:
        const std::string& name;
    public:
        Device(const std::string& n): name(n) {};
        virtual void setup() = 0;
        virtual void reset() = 0;
        virtual ~Device() = default;
};

#endif
