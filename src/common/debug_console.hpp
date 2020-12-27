#ifndef _DEBUG_CONSOLE_HPP
#define _DEBUG_CONSOLE_HPP

#include <cstdarg>

#ifdef DESKTOP
#include <iostream>
#else
#include <Arduino.h>
#endif

//TODO: ADD LOGGING OF STATE FIELDS

namespace debug{
enum SEVERITY{
    DEBUG,
    LOG,
    ERROR
};


void printf(SEVERITY s, const char* format, ...);
void println(SEVERITY s, const char* msg);

} // namespace debug

#endif
