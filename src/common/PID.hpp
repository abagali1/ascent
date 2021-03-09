#ifndef _PID_HPP
#define _PID_HPP

class PID {
    private:
        float kP;
        float kI;
        float kD;
        float set_point;
        float upper;
        float lower;
        float dt;

        float error_sum;
        float previous_error;
        bool clamp;

    public:
        PID(float, float, float, float, float, float, float);
        float execute(float);
};

#endif

