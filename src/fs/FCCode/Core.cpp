#include "Core.hpp"
#include "constants.hpp"

#include <cmath> 


Core::Core(StateFieldRegistry& registry, uint offset)
    :   TimedControlTask(registry, "core_ct", offset),
        mission_mode_f("core.mision_mode"),
        init_quat_f("core.init_quat"),
        acc_error_f("core.acc_error"),
        ground_level_f("core.ground_level")
{
    
    this->add_writeable_field(this->mission_mode_f);
    this->add_readable_field(this->init_quat_f);
    this->add_readable_field(this->acc_error_f);
    this->add_readable_field(this->ground_level_f);

    this->system_cal = this->find_readable_field<unsigned char>("imu.system_cal");
    this->gyro_cal = this->find_readable_field<unsigned char>("imu.gyro_cal");
    this->accel_cal = this->find_readable_field<unsigned char>("imu.accel_cal");
    this->mag_cal = this->find_readable_field<unsigned char>("imu.mag_cal");
    this->control_cycle_count_f = this->find_readable_field<uint>("control_cycle_count");
    this->imu_functional_f = this->find_readable_field<bool>("imu.functional");
    this->altimeter_functional_f = this-> find_readable_field<bool>("bmp.functional");
    
};


void Core::execute() {
    switch (static_cast<mission_mode_t>(mission_mode_f.get_value())) {
    case HARDWARE_INIT:
        dispatch_hardware_init();
    case MANUAL_CAL:
        dispatch_manual_calibration();
    case AUTO_CAL:
        dispatch_automatic_calibration();
    case STANDBY:
        dispatch_standby();
    case ASCEND:
        dispatch_ascend();
    case DESCENT:
        dispatch_descent();
    case TOUCH_DOWN:
        dispatch_touch_down();
    case EMERGENCY:
        dispatch_emergency();
    default:
        break;
    }
}

void Core::dispatch_hardware_init() {
    mission_mode_f.set_value(static_cast<unsigned char>(HARDWARE_INIT));

    if (enter_emergency()) {
        dispatch_emergency();
    }

    uint period = 10;
    uint init_period = 20; 

    if (control_cycle_count_f->get_value() * period > init_period) {
        dispatch_manual_calibration();
    }
}

void Core::dispatch_manual_calibration() {
    mission_mode_f.set_value(static_cast<unsigned char>(MANUAL_CAL));

    if (enter_emergency()) {
        dispatch_emergency();
    }

    bool uplink_says_to_go_to_automatic = true;
    if (uplink_says_to_go_to_automatic) {
        dispatch_automatic_calibration();
    }

}

void Core::dispatch_automatic_calibration() {
    mission_mode_f.set_value(static_cast<unsigned char>(AUTO_CAL));

    if (enter_emergency()) {
        dispatch_emergency();
    }

    bool cond = true;  // when initial height, acceleration error, and starting quaternion fields have been filled

    if (cond) {
        dispatch_standby();
    }
}

void Core::dispatch_standby() {
    mission_mode_f.set_value(static_cast<unsigned char>(STANDBY));

    if (enter_emergency()) {
        dispatch_emergency();
    }

    bool uplink_says_to_go_ascent= true;
    if (uplink_says_to_go_ascent) {
        dispatch_ascend();
    }
}

void Core::dispatch_ascend() {
    mission_mode_f.set_value(static_cast<unsigned char>(ASCEND));

    if (enter_emergency()) {
        dispatch_emergency();
    }

    float current_height = 20; // retrieve from kalman estimation field

    if (std::abs(current_height - MANAGER::apogee) < MANAGER::apogee_error) {
        dispatch_descent();
    }
}

void Core::dispatch_descent() {
    mission_mode_f.set_value(static_cast<unsigned char>(DESCENT));

    if (enter_emergency()) {
        dispatch_emergency();
    }
    
    float current_height = 20; // retrieve from kalman estimation field

    if (std::abs(current_height) < MANAGER::touch_down_error) {
        dispatch_touch_down();
    }
}

void Core::dispatch_touch_down() {
    mission_mode_f.set_value(static_cast<unsigned char>(TOUCH_DOWN));
}

bool Core::enter_emergency() {
    bool uplink_says_to_abort = false;
    bool hardware_failure = !imu_functional_f->get_value() || !altimeter_functional_f->get_value();
    bool lost_control = std::abs(0) > MANAGER::max_pitch || std::abs(0) > MANAGER::max_yaw;


    if (uplink_says_to_abort || hardware_failure || lost_control) {
        return true;
    }

    return false;
}

void Core::dispatch_emergency() {
    mission_mode_f.set_value(static_cast<unsigned char>(EMERGENCY));
}
