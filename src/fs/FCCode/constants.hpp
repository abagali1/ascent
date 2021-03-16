#ifndef _CONSTANTS_HPP
#define _CONSTANTS_HPP

// BEST IF ALL OF THESE ARE constexpr

namespace ASCENT {
    // Global Constants, MCL Loop timing etc.
    constexpr uint control_cycle_time_s = 0.1;
    constexpr uint control_cycle_time_ms = control_cycle_time_s * 1000;
    constexpr uint control_cycle_time_us = control_cycle_time_ms * 1000;
    constexpr uint control_cycle_time = control_cycle_time_us;
}

namespace DEVICES {
    // Hardware pinouts, Serial monitor vs XBee Serial, Motor pins, etc.
    // Maybe sub namespace for Motors
    constexpr uint bno055_offset = 1;
    constexpr uint8_t bno055_id = 55;
    constexpr uint8_t bno055_address = 0x28;

    constexpr uint bmp388_offset = 2;
    constexpr uint8_t bmp388_address = 0x77;

    constexpr uint sd_offset = 3;

    constexpr uint dl_offset = 4;
    
    const HardwareSerial radio_out = Serial4;
    constexpr uint radio_max_buf = 32;

    constexpr uint8_t nano_address = 0x60; // Must be synchronized on the nano
}

namespace MANAGER {
    // State transition thresholds, dangerous acceleration, dangerous height, etc.
    constexpr int init_cycles = 20;

    constexpr int init_readings = 30;

    constexpr float apogee = 10;
    constexpr float apogee_error = 10;
    constexpr float touch_down_error = 10;

    constexpr float max_pitch = 15;
    constexpr float max_yaw = 15;
}

#endif
