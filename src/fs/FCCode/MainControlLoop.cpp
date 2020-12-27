#include "MainControlLoop.hpp"
#include "constants.hpp"

MainControlLoop::MainControlLoop(StateFieldRegistry& registry)
    : ControlTask(registry) {
        delay(1000);
    }

void MainControlLoop::execute(){
    debug::println(debug::DEBUG, "execute");
}
