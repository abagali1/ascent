#include "StateFieldRegistry.hpp"

ReadableStateFieldBase* StateFieldRegistry::find_readable_field(const std::string& name) const{
    for(ReadableStateFieldBase* r: this->readable_fields){
        if(r->get_name() == name)
            return r;
    }
    return nullptr;
}

WriteableStateFieldBase* StateFieldRegistry::find_writeable_field(const std::string& name) const{
    for(WriteableStateFieldBase* w: this->writeable_fields){
        if(w->get_name() == name)
            return w;
    }
    return nullptr;
}

bool StateFieldRegistry::add_readable_field(ReadableStateFieldBase* field){
    if(find_readable_field(field->get_name()))
        return false;
    this->readable_fields.push_back(field);
    return true;
}

bool StateFieldRegistry::add_writeable_field(WriteableStateFieldBase* field){
    if(find_writeable_field(field->get_name()))
        return false;
    this->writeable_fields.push_back(field);
    return true;
}
