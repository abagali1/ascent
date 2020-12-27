#ifndef _TIMED_CT_HPP
#define _TIMED_CT_HPP

#include "debug_console.hpp"
#include "ControlTask.hpp"
#include "StateFieldRegistry.hpp"

class TimedControlTask: public ControlTask{
    public:
        TimedControlTask(StateFieldRegistry& r): ControlTask(r) {};
        void execute(){
            debug::println(debug::DEBUG, "execute");
        }
};

#endif
