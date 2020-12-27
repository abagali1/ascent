#ifndef _MCL_HPP
#define _MCL_HPP


#include <common/ControlTask.hpp>
#include <common/StateFieldRegistry.hpp>

class MainControlLoop: public ControlTask{
    protected:
        // CTs go here
    public:
        MainControlLoop(StateFieldRegistry& registry);
        void execute() override;
};

#endif
