#include <string>

#include "../StateField.hpp"
#include "../debug_console.hpp"
#include "../TimedControlTask.hpp"
#include "../StateFieldRegistry.hpp"


int main(int argv, char* argc[]){
    StateFieldRegistry sfr;
    TimedControlTask ct(sfr, "test", 1);
}

