#ifndef _CT_HPP
#define _CT_HPP

#include <string>
#include <cassert>

#include "StateField.hpp"
#include "debug_console.hpp"
#include "StateFieldRegistry.hpp"


class ControlTask{
    private:
        StateFieldRegistry& _registry;
    
    protected:
        virtual void execute() = 0;

    public:
        ControlTask(StateFieldRegistry& r): _registry(r) {};
        virtual ~ControlTask() = default;

        void field_exists(StateFieldBase* s, const std::string& type, const std::string& name){
            if(!s){
                #ifndef FLIGHT
                debug::printf(debug::ERROR, "%s state field %s is not in registry", type.c_str(), name.c_str());
                #endif
                assert(false);
            }
        }

        void field_added(const bool added, const std::string& type, const std::string& name){
            if(!added){
                #ifndef FLIGHT
                debug::printf(debug::ERROR, "%s state field %s is already in registry", type.c_str(), name.c_str());
                #endif
                assert(false);
            }
        }

        template<class T>
        void add_readable_field(ReadableStateField<T>& field){
            bool added = this->_registry.add_readable_field(static_cast<ReadableStateFieldBase*>(&field));
            field_added(added, "readable", field.get_name());
        }

        template<class T>
        void add_writeable_field(WriteableStateField<T>& field){
            bool added = this->_registry.add_writeable_field(static_cast<WriteableStateFieldBase*>(&field));
            field_added(added, "writeable", field.get_name());
        }

        template<class T>
        ReadableStateField<T>* find_readable_field(const std::string& name){
            auto ptr = this->_registry.find_readable_field(name);
            field_exists(ptr, "readable", name);
            return static_cast<ReadableStateField<T>*>(ptr);
        }

        template<class T>
        WriteableStateField<T>* find_writeable_field(const char* name){
            auto ptr = this->_registry.find_writeable_field(name);
            field_exists(ptr, "writeable", name);
            return static_cast<WriteableStateField<T>*>(ptr);
        }

};

#endif
