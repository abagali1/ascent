#include "MainControlLoop.hpp"
#include "constants.hpp"

MainControlLoop::MainControlLoop(StateFieldRegistry& registry)
    :   ControlTask(registry),
        clock_manager(registry, ASCENT::control_cycle_time)
    {
    }

void MainControlLoop::execute(){
    
    { // READ TASKS
        this->clock_manager.execute_on_time();
    }

    { // CONTROL TASKS

    }

    { // ACTUATE TASKS

    }
}
