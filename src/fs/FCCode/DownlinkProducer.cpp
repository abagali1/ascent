#include "DownlinkProducer.hpp"

DownlinkProducer::DownlinkProducer(StateFieldRegistry &registry, uint offset)
    :   TimedControlTask(registry, "downlink_ct", offset)
{
    this->serial_out.begin(this->baud);
    this->control_cycle_f = this->find_readable_field<uint>("control_cycle_count");
    this->mission_mode_f = this->find_writeable_field<unsigned char>("core.mission_mode");

    this->lin_accel_f = this->find_readable_field<lin::Vector3f>("imu.lin_accel");
    this->altitude_f = this->find_readable_field<float>("bmp.altitude");

}


void DownlinkProducer::execute(){
    lin::Vector3f linaccel = this->lin_accel_f->get_value();
    // lin::Vector3f euler = this->world_euler_f->get_value();
    // lin::Vector4d quat = this->world_quat_f->get_value();
    // lin::Vector2f servo = this->servo_orientation_f->get_value();

    std::ostringstream msg_stream;
    msg_stream << std::fixed << std::setprecision(4);
    msg_stream << this->control_cycle_f->get_value() << ";";
    msg_stream << static_cast<uint>(this->mission_mode_f->get_value()) << ";";
    msg_stream << linaccel(0) << ";" << linaccel(1) << ";" << linaccel(2) << ";";
    // msg_stream << euler(0) << ";" << euler(1) << ";" << euler(2) << ";";
    msg_stream << this->altitude_f->get_value() << ";";
    // msg_stream << quat(0) << ";" << quat(1) << ";" << quat(2) << ";" << quat(3) << ";";

    // msg_stream << this->pid_pitch_out_f->get_value() << ";";
    // msg_stream << this->pid_yaw_out_f->get_value() << ";";
    // msg_stream << this->pid_pos_out_f->get_value() << ";";

    // msg_stream << servo(0) << ";" << servo(1) << ";";
    // msg_stream << this->motor_throttle_f->get_value() << ";";

    msg_stream << ";";

    const std::string final_msg = msg_stream.str();
    for(int i=0;i<final_msg.length(); i++)
        this->serial_out.print(final_msg.substr(i, DEVICES::RADIO_OUT::max_buf).c_str());
}
