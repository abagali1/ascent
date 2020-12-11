#pragma once

#include <string>

class StateFieldBase{
    public:
        virtual ~StateFieldBase(){};
};

template<typename T>
class StateField : public virtual StateFieldBase {
    protected:
        std::string name;
        T value;
        bool ground_readable;
        bool ground_writeable;

    public:
        StateField(const std::string name, const bool gr, const bool gw)
            : StateFieldBase(),
              name(name),
              value(),
              ground_readable(gr),
              ground_writeable(gw) {};
        
        const std::string get_name() const { return this->name; }

        const bool is_readable() const { return this->ground_readable; }

        const bool is_writeable() const { return this->ground_writeable; }

        const T get_value() const { return this->value; }

        void set_value(T value) { this->value = value; }

        void operator = (const T &value){ this->value = *value; }
};
