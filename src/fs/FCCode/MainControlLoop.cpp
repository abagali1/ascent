#include "MainControlLoop.hpp"
#include "constants.hpp"

MainControlLoop::MainControlLoop(StateFieldRegistry& registry)
    :   ControlTask(registry),
        clock_manager(registry, ASCENT::control_cycle_time),
        imu_monitor(registry, DEVICES::bno055_offset, DEVICES::bno055_id, DEVICES::bno055_address),
        bmp_monitor(registry, DEVICES::bmp388_offset, DEVICES::bmp388_address)
    {
    }

void MainControlLoop::execute(){
    
    { // READ TASKS
        this->clock_manager.execute_on_time();
        this->imu_monitor.execute_on_time();
        this->bmp_monitor.execute_on_time();
    }

    { // CONTROL TASKS

    }

    { // ACTUATE TASKS

    }
}
