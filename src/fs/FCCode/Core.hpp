#ifndef _CORE_HPP
#define _CORE_HPP

#include <common/TimedControlTask.hpp>

#include <lin.hpp>

enum class mission_mode_t {
    boot,
    initialization,
    standby,
    calibration,
    ascent,
    descent,
    landed,
    emergency,
};

class Core: public TimedControlTask{
    public:
        Core(StateFieldRegistry&, uint);
        void execute(void) override;
    protected:
        void set_mode(mission_mode_t);
        
        void dispatch_initialization(void);
        void dispatch_standby(void);
        void dispatch_calibration(void);
        void dispatch_ascent(void);
        void dispatch_descent(void);
        void dispatch_landed(void);
        void dispatch_emergency(void);
    
    private:
        WriteableStateField<unsigned char> mission_mode_f;


        // Initialization Fields
        ReadableStateField<lin::Vector4d> init_quat_f;
        ReadableStateField<lin::Vector3f> acc_error_f;

        ReadableStateField<float> ground_level_f;
        ReadableStateField<bool> motor_on_f,
                                 servo_on_f;

        // Retrieved Fields
        ReadableStateField<unsigned char>* system_cal;
        ReadableStateField<unsigned char>* gyro_cal;
        ReadableStateField<unsigned char>* accel_cal;
        ReadableStateField<unsigned char>* mag_cal;


};

#endif
