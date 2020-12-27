#ifndef _TIMED_CT_HPP
#define _TIMED_CT_HPP

#include "debug_console.hpp"
#include "ControlTask.hpp"
#include "StateFieldRegistry.hpp"

#ifdef DESKTOP
#include <chrono>
#include <thread>

typedef std::chrono::steady_clock::time_point system_time_t;
typedef std::chrono::steady_clock::duration system_duration_t;
#else
#include <Arduino.h>

typedef unsigned int system_time_t;
typedef unsigned int system_duration_t;
#endif


class TimedControlTaskBase{
    protected:
        static system_time_t current_cycle_start_time;
        static unsigned int control_cycle_count;
    public:
        static system_time_t get_current_system_time(){
            #ifdef DESKTOP
            return std::chrono::steady_clock::now();
            #else
            return micros();
            #endif
        }

        static unsigned int system_duration_to_microseconds(const system_duration_t& time){
            #ifdef DESKTOP
            return std::chrono::duration_cast<std::chrono::microseconds>(time).count();
            #else
            return time;
            #endif
        }

        static system_duration_t microseconds_to_duration(const unsigned int& time){
            #ifdef DESKTOP
            return std::chrono::duration_cast<std::chrono::microseconds>(std::chrono::microseconds(time));
            #else
            return time;
            #endif
        }

        static void sleep_for_duration(const unsigned int& time){
            const system_time_t start_time = get_current_system_time();
            while(system_duration_to_microseconds(get_current_system_time() - start_time) < time){
                #ifdef DESKTOP
                std::this_thread::sleep_for(std::chrono::microseconds(1));
                #else
                delayMicroseconds(1);
                #endif
            }
        }
};


class TimedControlTask: public ControlTask, public TimedControlTaskBase{
    private:
        const std::string& _name;
        const system_duration_t _offset;

        ReadableStateField<unsigned int> num_late_f;
        ReadableStateField<float> avg_wait_f;

    public:
        TimedControlTask(StateFieldRegistry& registry, const std::string& n, unsigned int offset)
            :   ControlTask(registry),
                _name(n),
                num_late_f("tct."+n+".num_late"),
                avg_wait_f("tct."+n+".avg_wait"),
                _offset(offset)
        {
            this->add_readable_field(this->num_late_f);
            this->add_readable_field(this->avg_wait_f);
        }

        void execute_on_time(){
            system_time_t execute_time = TimedControlTaskBase::current_cycle_start_time + this->_offset;
            this->sleep_until_time(execute_time);
            return this->execute();
        }

        void execute(){}

        void sleep_until_time(system_time_t time){
            const signed int dt = static_cast<signed int>(system_duration_to_microseconds(time - get_current_system_time()));
            unsigned int wait_time = dt;
            if (dt <= 0){
                this->num_late_f.set_value(this->num_late_f.get_value() + 1);
                wait_time = 0;
            }
            const float avg_wait = ((this->avg_wait_f.get_value() * this->control_cycle_count) + wait_time) / (this->control_cycle_count + 1);
            avg_wait_f.set_value(avg_wait);

            if(wait_time > 0)
                this->sleep_for_duration(wait_time);
            else
                return;
            
        }



};

#endif
