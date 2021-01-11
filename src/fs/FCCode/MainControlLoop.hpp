#ifndef _MCL_HPP
#define _MCL_HPP

#include "ClockManager.hpp"
#include "IMUMonitor.hpp"
#include "BMPMonitor.hpp"

class MainControlLoop: public ControlTask{
    protected:
        ClockManager clock_manager;
        IMUMonitor imu_monitor;
        BMPMonitor bmp_monitor;
    public:
        MainControlLoop(StateFieldRegistry&);
        void execute(void);
};

#endif
