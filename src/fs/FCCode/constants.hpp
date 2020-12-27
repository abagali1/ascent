#ifndef _CONSTANTS_HPP
#define _CONSTANTS_HPP

// BEST IF ALL OF THESE ARE constexpr

namespace ASCENT{
    // Global Constants, MCL Loop timing etc.
    constexpr uint control_cycle_time_s = 0.1;
    constexpr uint control_cycle_time_ms = control_cycle_time_s * 1000;
    constexpr uint control_cycle_time_us = control_cycle_time_ms * 1000;
    constexpr uint control_cycle_time = control_cycle_time_us;
}

namespace DEVICES{
    // Hardware pinouts, Serial monitor vs XBee Serial, Motor pins, etc.
    // Maybe sub namespace for Motors
    constexpr uint bno055_offset = 1;
    constexpr int bno055_id = 55;
    constexpr int bno055_address = 0x28;
}

namespace MANAGER{
    // State transition thresholds, dangerous acceleration, dangerous height, etc.
}

#endif
