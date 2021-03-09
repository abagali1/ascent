#include "DownlinkProducer.hpp"

DownlinkProducer::DownlinkProducer(StateFieldRegistry &registry, uint baud, uint offset)
    :   TimedControlTask(registry, "downlink_ct", offset)
{
    this->serial_out.begin(baud);
    this->control_cycle_f = this->find_readable_field<uint>("control_cycle_count");
    this->mission_mode_f = this->find_writeable_field<unsigned char>("core.mission_mode");

    this->altitude_f = this->find_readable_field<float>("bmp.altitude");

}


void DownlinkProducer::execute(){
    char buf[DEVICES::radio_max_buf];

    snprintf(buf, DEVICES::radio_max_buf, "%03lu");
}
