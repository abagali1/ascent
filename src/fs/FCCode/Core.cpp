#include "Core.hpp"
#include "constants.hpp"

#include <cmath> 


Core::Core(StateFieldRegistry& registry, uint offset)
    :   TimedControlTask(registry, "core_ct", offset),
        mission_mode_f("core.mision_mode"),
        init_quat_f("core.init_quat"),
        acc_error_f("core.acc_error"),
        init_height_f("core.init_height"),
        init_readings_f("core.init_readings"),
        init_height_sums_f("core.init_height_sum"),
        init_quat_sum_f("core.init_quat_sum"),
        init_acc_error_sum_f("core.init_acc_error_sum")
{
    
    this->add_writeable_field(this->mission_mode_f);
    this->add_readable_field(this->init_quat_f);
    this->add_readable_field(this->acc_error_f);
    this->add_readable_field(this->init_readings_f);
    this->add_readable_field(this->init_height_sums_f);
    this->add_readable_field(this->init_height_f);

    this->system_cal = this->find_readable_field<unsigned char>("imu.system_cal");
    this->gyro_cal = this->find_readable_field<unsigned char>("imu.gyro_cal");
    this->accel_cal = this->find_readable_field<unsigned char>("imu.accel_cal");
    this->mag_cal = this->find_readable_field<unsigned char>("imu.mag_cal");
    this->control_cycle_count_f = this->find_readable_field<uint>("control_cycle_count");
    this->imu_functional_f = this->find_readable_field<bool>("imu.functional");
    this->altimeter_functional_f = this->find_readable_field<bool>("bmp.functional");
    this->altitude_f = this->find_readable_field<float>("bmp.altitude");
    this->imu_lin_acc_f = this->find_readable_field<lin::Vector3f>("imu.lin_accel");
    this->imu_quat_f = this->find_readable_field<lin::Vector4f>("imu.quat");

    this->mission_mode_f.set_value(static_cast<unsigned char>(ASCENT::HARDWARE_INIT));
    this->init_height_f.set_value(-1.0);
    this->init_quat_f.set_value({-1.0, -1.0, -1.0, -1.0});
    this->acc_error_f.set_value({-1.0, -1.0, -1.0});
};


void Core::execute() {
    switch (static_cast<ASCENT::mission_mode_t>(mission_mode_f.get_value())) {
    case ASCENT::HARDWARE_INIT:
        dispatch_hardware_init();
    case ASCENT::MANUAL_CAL:
        dispatch_manual_calibration();
    case ASCENT::AUTO_CAL:
        dispatch_automatic_calibration();
    case ASCENT::STANDBY:
        dispatch_standby();
    case ASCENT::ASCEND:
        dispatch_ascend();
    case ASCENT::DESCENT:
        dispatch_descent();
    case ASCENT::TOUCH_DOWN:
        dispatch_touch_down();
    case ASCENT::EMERGENCY:
        dispatch_emergency();
    default:
        break;
    }
}

void Core::dispatch_hardware_init() {
    mission_mode_f.set_value(static_cast<unsigned char>(ASCENT::HARDWARE_INIT));

    if (enter_emergency()) {
        dispatch_emergency();
    }

    if (control_cycle_count_f->get_value() >= MANAGER::init_cycles) {
        dispatch_manual_calibration();
    }
}

void Core::dispatch_manual_calibration() {
    mission_mode_f.set_value(static_cast<unsigned char>(ASCENT::MANUAL_CAL));

    bool uplink_says_to_go_to_automatic = true;
    if (uplink_says_to_go_to_automatic) {
        dispatch_automatic_calibration();
    }

}

void Core::dispatch_automatic_calibration() {
    mission_mode_f.set_value(static_cast<unsigned char>(ASCENT::AUTO_CAL));

    bool exit_condition = init_height_f.get_value() != -1.0; 
    exit_condition &= init_quat_f.get_value()(0) != -1.0 && init_quat_f.get_value()(1) != -1.0 && init_quat_f.get_value()(2) != -1.0 && init_quat_f.get_value()(3) != -1.0;
    exit_condition &= acc_error_f.get_value()(0) != -1.0 && acc_error_f.get_value()(1) != -1.0 && acc_error_f.get_value()(2) != -1.0;
    
    if (exit_condition) {
        dispatch_standby();
    }

    init_height_sums_f.set_value(init_height_sums_f.get_value() + altitude_f->get_value());
    init_quat_sum_f.set_value(init_quat_sum_f.get_value() + imu_quat_f->get_value());
    init_acc_error_sum_f.set_value(init_acc_error_sum_f.get_value() + imu_lin_acc_f->get_value());

    init_readings_f.set_value(init_readings_f.get_value() + 1);

    if (init_readings_f.get_value() >= MANAGER::init_readings) {
        init_height_f.set_value(init_height_sums_f.get_value() / init_readings_f.get_value());
        init_quat_f.set_value(init_quat_sum_f.get_value() / init_readings_f.get_value());
        acc_error_f.set_value(init_acc_error_sum_f.get_value() / init_readings_f.get_value());   
    }

}

void Core::dispatch_standby() {
    mission_mode_f.set_value(static_cast<unsigned char>(ASCENT::STANDBY));

    if (enter_emergency()) {
        dispatch_emergency();
    }

    bool uplink_says_to_go_ascent= true;
    if (uplink_says_to_go_ascent) {
        dispatch_ascend();
    }
}

void Core::dispatch_ascend() {
    mission_mode_f.set_value(static_cast<unsigned char>(ASCENT::ASCEND));

    if (enter_emergency()) {
        dispatch_emergency();
    }

    float current_height = 20; // retrieve from kalman estimation field

    if (std::abs(current_height - MANAGER::apogee) < MANAGER::apogee_error) {
        dispatch_descent();
    }
}

void Core::dispatch_descent() {
    mission_mode_f.set_value(static_cast<unsigned char>(ASCENT::DESCENT));

    if (enter_emergency()) {
        dispatch_emergency();
    }
    
    float current_height = 20; // retrieve from kalman estimation field

    if (std::abs(current_height) < MANAGER::touch_down_error) {
        dispatch_touch_down();
    }
}

void Core::dispatch_touch_down() {
    mission_mode_f.set_value(static_cast<unsigned char>(ASCENT::TOUCH_DOWN));
}

bool Core::enter_emergency() {
    bool uplink_says_to_abort = false;
    // bool hardware_failure = !imu_functional_f->get_value() || !altimeter_functional_f->get_value();
    bool lost_control = std::abs(0) > MANAGER::max_pitch || std::abs(0) > MANAGER::max_yaw;


    if (uplink_says_to_abort || lost_control) {
        return true;
    }

    return false;
}

void Core::dispatch_emergency() {
    mission_mode_f.set_value(static_cast<unsigned char>(ASCENT::EMERGENCY));
}
