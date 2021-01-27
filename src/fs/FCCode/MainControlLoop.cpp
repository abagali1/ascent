#include "MainControlLoop.hpp"
#include "constants.hpp"

MainControlLoop::MainControlLoop(StateFieldRegistry& registry)
    :   ControlTask(registry),
        clock_manager(registry, ASCENT::control_cycle_time),
        imu_monitor(registry, DEVICES::bno055_offset, DEVICES::bno055_id, DEVICES::bno055_address),
        // bmp_monitor(registry, DEVICES::bmp388_offset, DEVICES::bmp388_address)
        sd_writer(registry, DEVICES::sd_offset, "dataaaaa.txt")
    {
    }

void MainControlLoop::execute(){
    
    { // READ TASKS
        this->clock_manager.execute_on_time();
        this->imu_monitor.execute_on_time();
        // this->bmp_monitor.execute_on_time();
    }

    { // CONTROL TASKS

    }

    { // ACTUATE TASKS
        this->sd_writer.execute_on_time();
    }
}


void MainControlLoop::finish(){
    this->sd_writer.close();
}
