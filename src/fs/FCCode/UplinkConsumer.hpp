#ifndef _UPLINK_CONSUMER_HPP
#define _UPLINK_CONSUMER_HPP

#include <sstream>

#include <common/TimedControlTask.hpp>

#include "constants.hpp"

class UplinkConsumer: public TimedControlTask{
    public:
        UplinkConsumer(StateFieldRegistry&, uint);
        void execute(void) override;

    private:
        HardwareSerial serial_in = DEVICES::RADIO_OUT::serial;
        unsigned int baud = DEVICES::RADIO_OUT::baud;

        WriteableStateField<unsigned char> *mission_mode_f;
        // WriteableStateField<int> *servo_calib_p;
        // WriteableStateField<int> *servo_calib_y;
};

#endif
