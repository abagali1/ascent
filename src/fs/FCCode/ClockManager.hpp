#ifndef _CLOCK_MANAGER_HPP
#define _CLOCK_MANAGER_HPP

#include <common/TimedControlTask.hpp>
#include <common/StateFieldRegistry.hpp>

class ClockManager: public TimedControlTask{
    private:
        ReadableStateField<uint> control_cycle_count_f;
        system_time_t initial_control_cycle_start_time;
        uint control_cycle_total_time;
    public:
        ClockManager(StateFieldRegistry&, uint);
        void execute(void);
};

#endif
