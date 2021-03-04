#include "BMPMonitor.hpp"

BMPMonitor::BMPMonitor(StateFieldRegistry& registry, uint offset, uint addr)
    :   TimedControlTask(registry, "bmp_ct", offset),
        functional_f("bmp.functional"),
        read_success_f("bmp.read_success"),
        temp_f("bmp.temp"),
        pressure_f("bmp.pressure"),
        altitude_f("bmp.altitude"),
        distance_f("bmp.distance")
{

    add_readable_field(this->functional_f);
    add_readable_field(this->temp_f);
    add_readable_field(this->pressure_f);
    add_readable_field(this->altitude_f);

    this->init_height_f = this->find_readable_field<float>("core.init_height");

    bool functional = true;

    if(!this->bmp.begin_I2C(addr)){
        debug::println(debug::ERROR, "bmp failed to initialize");
        functional = false;
    }

    if(!this->bmp.setTemperatureOversampling(this->temp_oversampling)){
        debug::println(debug::ERROR, "bmp failed to set temp oversampling");
        functional = false;
    }

    if(!this->bmp.setPressureOversampling(this->pressure_oversampling)){
        debug::println(debug::ERROR, "bmp failed to set pressure oversampling");
        functional = false;
    }

    if(!this->bmp.setOutputDataRate(this->odr)){
        debug::println(debug::ERROR, "bmp failed to set odr");
        functional = false;
    }

    if(!this->bmp.setIIRFilterCoeff(this->iir)){
        debug::println(debug::ERROR, "bmp failed to set iir");
        functional = false;
    }

    functional_f.set_value(functional);
    this->bmp.readAltitude(this->sealevel_hpa);
}


void BMPMonitor::execute(){
    if(!this->bmp.performReading()){
        debug::println(debug::ERROR, "failed to perform bmp read");
        this->read_success_f.set_value(false);
        return;
    }

    this->temp_f.set_value(this->bmp.temperature);
    this->pressure_f.set_value(this->bmp.pressure / 100.0f);
    this->altitude_f.set_value(this->bmp.readAltitude(this->sealevel_hpa));

    if (this->init_height_f->get_value() != -1) {
        this->distance_f.set_value(altitude_f.get_value() - init_height_f->get_value());
    } else {
        this->distance_f.set_value(0);
    }

}

