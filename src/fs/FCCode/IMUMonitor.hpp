#ifndef _IMU_MONITOR_HPP
#define _IMU_MONITOR_HPP

#include <i2c_t3.h>
#include <Adafruit_Sensor.h>
#include <Adafruit_BNO055.h>

#include <lin/core.hpp>

#include <common/TimedControlTask.hpp>

class IMUMonitor: public TimedControlTask{
    private:
        Adafruit_BNO055 bno055;
        ReadableStateField<bool> functional_f;

        ReadableStateField<unsigned char>
                        system_cal_f,
                        gyro_cal_f,
                        accel_cal_f,
                        mag_cal_f;
                        
        ReadableStateField<lin::Vector3f>
                        euler_f,
                        angular_vel_f,
                        acc_grav_vec_f,
                        mag_field_f,
                        lin_accel_f,
                        grav_vec_f;

        ReadableStateField<int8_t> temp_f;

        ReadableStateField<lin::Vector4f> quat_f;
    public:
        IMUMonitor(StateFieldRegistry&, uint, uint, int);
        void execute(void) override;
};

#endif
