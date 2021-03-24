#include "UplinkConsumer.hpp"


UplinkConsumer::UplinkConsumer(StateFieldRegistry &registry, uint offset)
    : TimedControlTask(registry, "uplink_ct", offset)
{
    this->serial_in.begin(this->baud);

    this->mission_mode_f = this->find_writeable_field<unsigned char>("core.mission_mode");
    // this->servo_calib_p = this->find_writeable_field<int>("servo.calib_p");
    // this->servo_calib_y = this->find_writeable_field<int>("servo.calib_y");
}

void UplinkConsumer::execute(void){
    std::istringstream recv(this->serial_in.readStringUntil('\n').c_str());
    std::string s;
    std::string msg[3];
    int i = 0;
    while(std::getline(recv, s, ';')){
        msg[i] = s;
        i++;
    }
}
