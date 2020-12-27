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

const char* SEVERITY_STRING[3] = {"DEBUG:", "LOG:", "ERROR:"};

void printf(SEVERITY s, const char* format, ...){
    char buf[100];
    va_list args;
    va_start(args, format);
    vsnprintf(buf, sizeof(buf), format, args);
    #ifdef DESKTOP
        std::cout << SEVERITY_STRING[s] << buf << std::endl;
    #else
        Serial.println(buf);
    #endif
    va_end(args);
}

void println(SEVERITY s, const char* msg){
    #ifdef DESKTOP
        std::cout << SEVERITY_STRING[s] << msg << std::endl;
    #else
        Serial.println(msg);
    #endif
}
} // namespace debug

#endif
