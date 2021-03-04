#ifndef _CORE_HPP
#define _CORE_HPP

#include <common/TimedControlTask.hpp>

#include <lin.hpp>

enum mission_mode_t {
    HARDWARE_INIT, // start imu + bn0 + motor
    MANUAL_CAL, // fix imu calibration if needed + realign servos
    AUTO_CAL, // find starting height + starting quat + acc error
    STANDBY, // wait for gs
    ASCEND, // go up
    DESCENT, // go down
    TOUCH_DOWN, // landed procedure
    EMERGENCY // turn everything off :(
};

class Core: public TimedControlTask{
    public:
        Core(StateFieldRegistry&, uint);
        void execute(void) override;
    protected:
        void set_mode(mission_mode_t);
        
        void dispatch_hardware_init(void);
        void dispatch_manual_calibration(void);
        void dispatch_automatic_calibration(void);
        void dispatch_standby(void);
        void dispatch_ascend(void);
        void dispatch_descent(void);
        void dispatch_touch_down(void);
        void dispatch_emergency(void);

        bool enter_emergency(void);
    
    private:
        WriteableStateField<unsigned char> mission_mode_f;


        // Initialization Fields
        ReadableStateField<lin::Vector4d> init_quat_f;
        ReadableStateField<lin::Vector3f> acc_error_f;
        ReadableStateField<float> init_height_f;

        ReadableStateField<uint> init_readings_f;

        ReadableStateField<float> init_height_sums_f;
        ReadableStateField<lin::Vector4f> init_quat_sum_f;
        ReadableStateField<lin::Vector3f> init_acc_error_sum_f;

        // Retrieved Fields
        ReadableStateField<unsigned char> 
                                *system_cal,
                                *gyro_cal,
                                *accel_cal,
                                *mag_cal;
        
        ReadableStateField<uint>
                                *control_cycle_count_f;
        
        ReadableStateField<float>
                                *altitude_f;

        ReadableStateField<bool>
                                *imu_functional_f,
                                *altimeter_functional_f;

        ReadableStateField<lin::Vector3f>
                                *imu_lin_acc_f;

        ReadableStateField<lin::Vector4f>
                                *imu_quat_f;

};

#endif
