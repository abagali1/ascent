#include "TimedControlTask.hpp"

system_time_t TimedControlTaskBase::current_cycle_start_time;
unsigned int TimedControlTaskBase::control_cycle_count = 0;