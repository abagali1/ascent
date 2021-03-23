#ifndef _TVC_HPP
#define _TVC_HPP_

#include <common/PID.hpp>
#include <common/TimedControlTask.hpp>

class TVC : public TimedControlTask {
    private:
        PID::PID yaw_controller;
        PID::PID pitch_controller;
        PID::PID position_controller;

        ReadableStateField<int> motor_speed;
        ReadableStateField<int> yaw_servo_angle;
        ReadableStateField<int> pitch_servo_angle;
    public:
        TVC(StateFieldRegistry&, uint);
        void execute(void) override;
};

#endif
