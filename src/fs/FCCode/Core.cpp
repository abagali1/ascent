#include "Core.hpp"


Core::Core(StateFieldRegistry& registry, uint offset)
    :   TimedControlTask(registry, "core_ct", offset),
        mission_mode_f("core.mision_mode"),
        init_quat_f("core.init_quat"),
        acc_error_f("core.acc_error"),
        ground_level_f("core.ground_level"),
        motor_on_f("core.motor_on"),
        servo_on_f("core.servo_on")
{
    
    this->add_writeable_field(this->mission_mode_f);

    this->add_readable_field(this->init_quat_f);
    this->add_readable_field(this->acc_error_f);
    this->add_readable_field(this->ground_level_f);
    this->add_readable_field(this->motor_on_f);
    this->add_readable_field(this->servo_on_f);

    this->system_cal = this->find_readable_field<unsigned char>("imu.system_cal");
    this->gyro_cal = this->find_readable_field<unsigned char>("imu.gyro_cal");
    this->accel_cal = this->find_readable_field<unsigned char>("imu.accel_cal");
    this->mag_cal = this->find_readable_field<unsigned char>("imu.mag_cal");

};
