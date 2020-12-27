#include "MainControlLoop.hpp"
#include "constants.hpp"

MainControlLoop::MainControlLoop(StateFieldRegistry& registry)
    : ControlTask(registry) {}

void execute(){
    debug::println(debug::DEBUG, "mcl execute");
}
