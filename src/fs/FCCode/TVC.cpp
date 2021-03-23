#include <cmath>
// #include <math.h>

#include "TVC.hpp"
#include "constants.hpp"

TVC::TVC(StateFieldRegistry &registry, uint offset) 
    :   TimedControlTask(registry, "tvc_ct", offset),
        yaw_controller(GNC::yaw_kP, GNC::yaw_kI, GNC::yaw_kD, 0, GNC::max_torque_force, GNC::min_torque_force, ASCENT::control_cycle_time_s),
        pitch_controller(GNC::pitch_kP, GNC::pitch_kI, GNC::pitch_kD, 0, GNC::max_torque_force, GNC::min_torque_force, ASCENT::control_cycle_time_s),
        position_controller(GNC::z_kP, GNC::z_kI, GNC::z_kD, 0, GNC::max_z_force, GNC::min_z_force, ASCENT::control_cycle_time_s),
        motor_speed("tvc.motor_speed"),
        yaw_servo_angle("tvc.yaw_angle"),
        pitch_servo_angle("tvc.pitch_angle")
{

}

void TVC::execute() {

    if (false) {
        // mission_mode != ascent / descent
        // set motor speed to zero!

        return;
    }

    // retrieve process values (yaw / pitch / height)
    // code to change hte position controllers setpoint (important !!!!)

    float yaw_output = yaw_controller.execute(0);  // force in the x direction 
    float pitch_output = pitch_controller.execute(0);  // force in the y direction 
    float pos_output = position_controller.execute(0); // force in the z direction

    // convert PID outputs into actuator commands + store in SFR

    float thrust =  sqrt( (yaw_output * yaw_output) + (pitch_output * pitch_output) + (pos_output * pos_output) );
    motor_speed.set_value((int) ((thrust / 2) - GNC::b) / GNC::m); 

    float pitch_thrust_angle = acos(pos_output / thrust);
    float yaw_thrust_angle = acos(pos_output / (thrust * sin(pitch_thrust_angle)));

    // convert pitch + yaw angles into servo angles
    yaw_servo_angle.set_value(0);
    pitch_servo_angle.set_value(0);

}   
