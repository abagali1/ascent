#include "UplinkConsumer.hpp"


UplinkConsumer::UplinkConsumer(StateFieldRegistry &registry, uint offset)
    : TimedControlTask(registry, "uplink_ct", offset)
{
    this->serial_in.begin(this->baud);

    this->mission_mode_f = this->find_writeable_field<unsigned char>("core.mission_mode");
    // this->servo_calib_p = this->find_writeable_field<int>("servo.calib_p");
    // this->servo_calib_y = this->find_writeable_field<int>("servo.calib_y");
}


void execute(){
}
