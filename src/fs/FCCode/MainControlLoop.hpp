#ifndef _MCL_HPP
#define _MCL_HPP

#include "ClockManager.hpp"
#include "IMUMonitor.hpp"

class MainControlLoop: public ControlTask{
    protected:
        ClockManager clock_manager;
        IMUMonitor imu_monitor;
    public:
        MainControlLoop(StateFieldRegistry&);
        void execute(void);
};

#endif
