#include "IMUMonitor.hpp"

IMUMonitor::IMUMonitor(StateFieldRegistry& registry, uint offset, uint id, int addr)
    :   TimedControlTask(registry, "imu_ct", offset),
        bno055(id, addr),
        functional_f("imu.functional"),
        system_cal_f("imu.system_cal"),
        gyro_cal_f("imu.gyro_cal"),
        accel_cal_f("imu.accel_cal"),
        mag_cal_f("imu.mag_cal"),
        euler_f("imu.euler_ang"),
        angular_vel_f("imu.ang_vel"),
        acc_grav_vec_f("imu.acc_grav_vec"),
        mag_field_f("imu.mag_field"),
        lin_accel_f("imu.lin_accel"),
        grav_vec_f("imu.grav_vec"),
        temp_f("imu.temp"),
        quat_f("imu.quat")
{
    this->add_readable_field(functional_f);

    this->add_readable_field(system_cal_f);
    this->add_readable_field(gyro_cal_f);
    this->add_readable_field(accel_cal_f);
    this->add_readable_field(mag_cal_f);
    
    this->add_readable_field(euler_f);
    this->add_readable_field(angular_vel_f);
    this->add_readable_field(acc_grav_vec_f);
    this->add_readable_field(mag_field_f);
    this->add_readable_field(lin_accel_f);
    this->add_readable_field(grav_vec_f);
    this->add_readable_field(temp_f);
    this->add_readable_field(quat_f);

    debug::println(debug::LOG, "IMU Sensor Test");
    if(!this->bno055.begin()){
        debug::println(debug::ERROR, "IMU Failed");
        this->functional_f.set_value(false);
    }else{
        this->functional_f.set_value(true);
    }

    this->bno055.setMode(Adafruit_BNO055::adafruit_bno055_opmode_t::OPERATION_MODE_NDOF);
    this->bno055.setAxisRemap(Adafruit_BNO055::adafruit_bno055_axis_remap_config_t::REMAP_CONFIG_P1);
    this->bno055.setAxisSign(Adafruit_BNO055::adafruit_bno055_axis_remap_sign_t::REMAP_SIGN_P1);
    this->bno055.setMode(Adafruit_BNO055::adafruit_bno055_opmode_t::OPERATION_MODE_NDOF);
    this->bno055.setExtCrystalUse(true);

    // Init with calibration data to enter into MM::Calibrate mode
    unsigned char sys_c, gyro_c, accel_c, mag_c;
    this->bno055.getCalibration(&sys_c, &gyro_c, &accel_c, &mag_c);
    this->system_cal_f.set_value(sys_c);
    this->gyro_cal_f.set_value(gyro_c);
    this->accel_cal_f.set_value(accel_c);
    this->mag_cal_f.set_value(mag_c);
}

void IMUMonitor::execute(){
    // Read calibration data
    unsigned char sys_c, gyro_c, accel_c, mag_c;

    this->bno055.getCalibration(&sys_c, &gyro_c, &accel_c, &mag_c);
    this->system_cal_f.set_value(sys_c);
    this->gyro_cal_f.set_value(gyro_c);
    this->accel_cal_f.set_value(accel_c);
    this->mag_cal_f.set_value(mag_c);


    sensors_event_t 
            lin_acc_v,
            acc_grav_v,
            grav_v,
            euler_ang_v,
            ang_vel_v,
            mag_v;
    
    int8_t temp;
    imu::Quaternion quat;

    // Read basic sensor values
    this->bno055.getEvent(&lin_acc_v, Adafruit_BNO055::VECTOR_LINEARACCEL);
    this->bno055.getEvent(&acc_grav_v, Adafruit_BNO055::VECTOR_ACCELEROMETER);
    this->bno055.getEvent(&grav_v, Adafruit_BNO055::VECTOR_GRAVITY);
    this->bno055.getEvent(&euler_ang_v, Adafruit_BNO055::VECTOR_EULER);
    this->bno055.getEvent(&ang_vel_v, Adafruit_BNO055::VECTOR_GYROSCOPE);
    this->bno055.getEvent(&mag_v, Adafruit_BNO055::VECTOR_MAGNETOMETER);
    temp = this->bno055.getTemp();
    quat = this->bno055.getQuat(); // Read Quaternion Orientation


    
    this->lin_accel_f.set_value({
        lin_acc_v.acceleration.x,
        lin_acc_v.acceleration.y,
        lin_acc_v.acceleration.z
    });

    this->acc_grav_vec_f.set_value({
        acc_grav_v.acceleration.x,
        acc_grav_v.acceleration.y,
        acc_grav_v.acceleration.z
    });

    this->grav_vec_f.set_value({
        grav_v.acceleration.x,
        grav_v.acceleration.y,
        grav_v.acceleration.z
    });

    this->euler_f.set_value({
        euler_ang_v.orientation.x,
        euler_ang_v.orientation.y,
        euler_ang_v.orientation.z
    });

    this->angular_vel_f.set_value({
        ang_vel_v.gyro.x,
        ang_vel_v.gyro.y,
        ang_vel_v.gyro.z
    });

    this->mag_field_f.set_value({
        mag_v.magnetic.x,
        mag_v.magnetic.y,
        mag_v.magnetic.z
    });

    this->temp_f.set_value(temp);

    this->quat_f.set_value({
        quat.w(),
        quat.x(),
        quat.y(),
        quat.z()
    });
}