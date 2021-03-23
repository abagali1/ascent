#ifndef _MCL_HPP
#define _MCL_HPP

#include "ClockManager.hpp"
#include "IMUMonitor.hpp"
#include "BMPMonitor.hpp"
#include "DownlinkProducer.hpp"
#include "SDWriters.hpp"

class MainControlLoop: public ControlTask{
    protected:
        ClockManager clock_manager;
        IMUMonitor imu_monitor;
        // BMPMonitor bmp_monitor;
        DownlinkProducer downlink_producer;
        // SDWriter sd_writer;
    public:
        MainControlLoop(StateFieldRegistry&);
        void execute(void) override;
};

#endif
