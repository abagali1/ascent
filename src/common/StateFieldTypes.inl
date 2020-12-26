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
            : StateField<T>(name, true, false) {};
};

template<class T>
class WriteableStateField: public WriteableStateFieldBase, public StateField<T>{
    public:
        WriteableStateField(const std::string& name)
            :  StateField<T>(name, true, true) {};
};

#endif