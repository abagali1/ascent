#ifndef _STATE_FIELD_TYPES_INL
#define _STATE_FIELD_TYPES_INL

#include <string>

#include "StateField.hpp"

// TODO: ADD ROBUST SERIALIZATION

class ReadableStateFieldBase: public virtual StateFieldBase{};
class WriteableStateFieldBase: public virtual StateFieldBase{};

template<class T>
class ReadableStateField: public ReadableStateFieldBase, public StateField<T>{
    public:
        ReadableStateField(const std::string& name)
            :   StateField<T>(name, true, false) {};
        ReadableStateField(const std::string& name, T value)
            :   StateField<T>(name, true, false)
        {
            this->value = value;
        }
};

template<class T>
class WriteableStateField: public WriteableStateFieldBase, public StateField<T>{
    public:
        WriteableStateField(const std::string& name)
            :  StateField<T>(name, true, true) {};
        WriteableStateField(const std::string& name, T value)
            :   StateField<T>(name, true, true)
        {
            this->value = value;
        }
};

#endif