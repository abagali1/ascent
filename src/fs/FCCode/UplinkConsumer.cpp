#include "UplinkConsumer.hpp"


UplinkConsumer::UplinkConsumer(StateFieldRegistry &registry, uint offset)
    : TimedControlTask(registry, "uplink_ct", offset)
{
    this->serial_in.begin(this->baud);

    this->mission_mode_f = this->find_writeable_field<unsigned char>("core.mission_mode");
    // this->servo_calib_p = this->find_writeable_field<int>("servo.calib_p");
    // this->servo_calib_y = this->find_writeable_field<int>("servo.calib_y");
}

void UplinkConsumer::invalid_message(){
    this-serial_in.println(-1);
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
    if(i != 3){
        return invalid_message();
    }

    if(msg[0] == "CORE"){
        if(msg[1] == "MODE"){
            if(msg[2] == "EMERGENCY"){
                this->mission_mode_f->set_value((ASCENT::EMERGENCY));
            }else if(msg[2] == "ASCEND"){
                this->mission_mode_f->set_value((ASCENT::ASCEND));
            }else{
                return invalid_message();
            }
        }else{
            return invalid_message();
        }
    }else if(msg[0] == "SERVO"){
        if(msg[1] == "CALIBRATE"){
            if(msg[2] == "P+"){
                // set pitch +
            }else if(msg[2] == "P-"){
                // set pitch -
            }else if(msg[2] == "Y+"){
                // set yaw +
            }else if(msg[2] == "Y-"){
                // set yaw -
            }else{
                return invalid_message();
            }
        }else{
            return invalid_message();
        }
    }else{
        return invalid_message();
    }
}
