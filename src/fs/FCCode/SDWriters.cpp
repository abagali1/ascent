#include "SDWriters.hpp"


SDWriter::SDWriter(StateFieldRegistry& registry, uint offset, const std::string& filename)
    :   TimedControlTask(registry, "sd_ct", offset),
        _filename(filename),
        functional_f("sd.functional"),
        write_success_f("sd.write_success")
{
    if(!SD.begin(this->sd_chip)){
        debug::println(debug::ERROR, "failed to initialize SD card");
        this->functional_f.set_value(false);
    }

    this->fout = SD.open(this->_filename.c_str(), FILE_WRITE);

    this->euler_f = this->find_readable_field<lin::Vector3f>("imu.euler_ang");
    this->lin_acc_f = this->find_readable_field<lin::Vector3f>("imu.lin_accel");
    this->angular_vel_f = this->find_readable_field<lin::Vector3f>("imu.ang_vel");

    // this->altitude_f = this->find_readable_field<float>("bmp.altitude");
}

void SDWriter::execute(){
    debug::printf(debug::LOG, "%lu\n", TimedControlTaskBase::current_cycle_start_time);
    this->fout.printf("%lu\n", TimedControlTaskBase::current_cycle_start_time);
    lin::Vector3f tmp = this->euler_f->get_value();
    debug::printf(debug::LOG, "%e %e %e\n", tmp(0), tmp(1), tmp(2));
    this->fout.printf("%e %e %e\n", tmp(0), tmp(1), tmp(2));

    tmp = this->lin_acc_f->get_value();
    this->fout.printf("%e %e %e\n", tmp(0), tmp(1), tmp(2));

    tmp = this->angular_vel_f->get_value();
    this->fout.printf("%e %e %e\n", tmp(0), tmp(1), tmp(2));

    // this->fout.printf("%e\n", this->altitude_f->get_value());
}

void SDWriter::close(){
    this->fout.close();
}
