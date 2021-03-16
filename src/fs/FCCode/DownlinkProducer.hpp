#ifndef _DOWNLINK_HPP
#define _DOWNLINK_HPP

#include <iomanip>
#include <iostream>

#include <lin.hpp>

#include <common/TimedControlTask.hpp>

#include "constants.hpp"

class DownlinkProducer: public TimedControlTask {
    public:
        DownlinkProducer(StateFieldRegistry&, uint, uint);
        void execute(void) override;
    
    private:
        HardwareSerial serial_out = DEVICES::radio_out;
        ReadableStateField<uint> *control_cycle_f;
        WriteableStateField<unsigned char> *mission_mode_f;

        ReadableStateField<lin::Vector3f> *lin_accel_f;
        // ReadableStateField<lin::Vector4d> *world_quat_f;
        // ReadableStateField<lin::Vector3f> *world_euler_f;

        ReadableStateField<float> *altitude_f;

        // ReadableStateField<lin::Vector2f> *servo_orientation_f;

        /*
        ReadableStateField<double> *pid_pitch_out_f;
        ReadableStateField<double *pid_yaw_out_f;
        ReadableStateField<double> *pid_pos_out_f;
        */

       // ReadableStateField<float> *motor_throttle_f;




};

#endif