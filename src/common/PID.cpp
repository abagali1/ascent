#include "PID.hpp"

#include <algorithm>
#include <cstdint>

PID::PID(float kp, float ki, float kd, float sp, float upper_limit, float lower_limit, float period) 
    :   kP(kp),
        kI(ki),
        kD(kd),
        set_point(sp),
        upper(upper_limit),
        lower(lower_limit),
        dt(period)
{
    this->error_sum = 0;
    this->previous_error = 0;
    this->clamp = false;
}

float PID::execute(float process_value) {

    float error = set_point - process_value;
    float integral = 0.5 * (error + previous_error) * dt;
    float derivative = (error - previous_error) / dt;

    if (clamp) {
        integral = 0;
    }

    float output = kP * error + kI * integral + kD * derivative;
    
    if (!clamp) {
        error_sum += error;
    }
    previous_error = error;

    float saturated_output = output;

    if (output >= upper) {
        saturated_output = upper;
    }

    if (output <= lower) {
        saturated_output = lower;
    }

    if (saturated_output != output && integral * error > 0) {
        clamp = true;
    } else {
        clamp = false;
    }

    return saturated_output;

}