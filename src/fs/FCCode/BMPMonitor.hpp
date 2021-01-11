#ifndef _BMP_MONITOR_HPP
#define _BMP_MONITOR_HPP

#include <i2c_t3.h>
#include <Adafruit_Sensor.h>
#include <Adafruit_BMP3XX.h>

#include <lin/core.hpp>

#include <common/TimedControlTask.hpp>


class BMPMonitor: public TimedControlTask{
    private:
        Adafruit_BMP3XX bmp;
        ReadableStateField<bool> 
                        functional_f,
                        read_success_f;

        ReadableStateField<float> 
                        temp_f,
                        pressure_f,
                        altitude_f;

        static constexpr uint8_t temp_oversampling = BMP3_OVERSAMPLING_2X;
        static constexpr uint8_t pressure_oversampling = BMP3_OVERSAMPLING_8X;
        static constexpr uint8_t odr = BMP3_ODR_50_HZ;
        static constexpr uint8_t iir = BMP3_IIR_FILTER_COEFF_3;

    public:
        static constexpr float sealevel_hpa = 1013.25;
        BMPMonitor(StateFieldRegistry&, uint, uint);
        void execute(void);
};


#endif