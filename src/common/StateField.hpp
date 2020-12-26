#ifndef _STATE_FIELD_HPP
#define _STATE_FIELD_HPP

#include <string>

class StateFieldBase{
    public:
        virtual const std::string& get_name() const = 0;
        virtual const bool is_readable() const = 0;
        virtual const bool is_writeable() const = 0;
        virtual ~StateFieldBase() = default;
};

template<typename T>
class StateField : public virtual StateFieldBase {
    protected:
        const std::string name;
        T value;
        bool ground_readable;
        bool ground_writeable;

    public:
        StateField(const std::string& n, const bool gr, const bool gw)
            : name(n),
              ground_readable(gr),
              ground_writeable(gw) {};

        const std::string& get_name() const { return this->name; }

        const bool is_readable() const { return this->ground_readable; }

        const bool is_writeable() const { return this->ground_writeable; }

        const T get_value() const { return this->value; }

        void set_value(T value) { this->value = value; }
};

#include "StateFieldTypes.inl"

#endif