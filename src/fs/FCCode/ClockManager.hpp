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
        ClockManager(StateFieldRegistry& registry, uint control_cycle_time)
            :   TimedControlTask(registry, "clockmanager_ct", 0),
                control_cycle_count_f("control_cycle_count", 0),
                control_cycle_total_time(control_cycle_time)

        {
            this->add_readable_field(this->control_cycle_count_f);
            this->initial_control_cycle_start_time = this->get_current_system_time();
        }

        void execute(){
            if(this->control_cycle_count_f.get_value() == 0){
                system_time_t start_time = TimedControlTaskBase::current_cycle_start_time + this->control_cycle_total_time;
                this->sleep_until_time(start_time);
            }
            TimedControlTaskBase::current_cycle_start_time = this->get_current_system_time();
            this->control_cycle_count_f.set_value(this->control_cycle_count_f.get_value() + 1);
        }
};

#endif
