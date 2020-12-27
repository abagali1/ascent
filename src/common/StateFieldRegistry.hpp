#ifndef _STATE_FIELD_REGISTRY_HPP
#define _STATE_FIELD_REGISTRY_HPP

#include <string>
#include <vector>

#include "StateField.hpp"

// TODO: ADD EVENTS AND FAULTS

class StateFieldRegistry{
    private:
        std::vector<ReadableStateFieldBase*> readable_fields;
        std::vector<WriteableStateFieldBase*> writeable_fields;

        // ACCESSOR METHODS
        ReadableStateFieldBase* find_readable_field(const std::string&) const;
        WriteableStateFieldBase* find_writeable_field(const std::string&) const;

        // SETTER METHODS
        bool add_readable_field(ReadableStateFieldBase*);
        bool add_writeable_field(WriteableStateFieldBase*);

        friend class ControlTask;

    public:
        StateFieldRegistry() = default;
};

#endif
