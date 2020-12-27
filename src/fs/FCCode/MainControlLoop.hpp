#ifndef _MCL_HPP
#define _MCL_HPP

#include <common/ControlTask.hpp>
#include <common/StateFieldRegistry.hpp>

#include "ClockManager.hpp"

class MainControlLoop: public ControlTask{
    protected:
        ClockManager clock_manager;
    public:
        MainControlLoop(StateFieldRegistry&);
        void execute(void);
};

#endif
