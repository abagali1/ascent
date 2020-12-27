#include <string>

#include "../StateField.hpp"
#include "../debug_console.hpp"
#include "../TimedControlTask.hpp"
#include "../StateFieldRegistry.hpp"


int main(int argv, char* argc[]){
    StateFieldRegistry sfr;
    TimedControlTask ct(sfr, "test", 1*1e6);
    ReadableStateField<int> r("r");

    ct.execute_on_time();

    r.set_value(1);

    ct.add_readable_field(r);
    ReadableStateField<int>* rr = ct.find_readable_field<int>("r");
    debug::printf(debug::DEBUG, "%d\n", rr->get_value());
}

