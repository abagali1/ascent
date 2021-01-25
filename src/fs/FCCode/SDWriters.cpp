#include "SDWriters.hpp"


SDWriter::SDWriter(StateFieldRegistry& registry, uint offset, std::string& filename)
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
}


void SDWriter::execute(){
    
}