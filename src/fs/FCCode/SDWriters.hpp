#ifndef _SD_WRITER_HPP
#define _SD_WRITER_HPP

#include <SD.h>
#include <lin.hpp>

#include <string>

#include <common/TimedControlTask.hpp>

class SDWriter: public TimedControlTask {
    public:
        SDWriter(StateFieldRegistry&, uint, std::string&);
        void execute(void) override;
    private:
        const std::string& _filename;
        File fout;

        ReadableStateField<bool> functional_f;
        ReadableStateField<bool> write_success_f;

        static constexpr int sd_chip = BUILTIN_SDCARD;

        // Retrieved Fields
        ReadableStateField<lin::Vector3f>
                                *euler_f,
                                *lin_acc_f,
                                *angular_vel_f;

        ReadableStateField<float> *altitude_f;
};

#endif
