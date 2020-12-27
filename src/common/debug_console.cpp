#ifndef _DEBUG_CONSOLE_HPP
#define _DEBUG_CONSOLE_HPP

#include <cstdarg>
#include <string>

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

    std::string sbuf(SEVERITY_STRING[s]);
    sbuf.append(buf);
    
    #ifdef DESKTOP
        std::cout << sbuf;
    #else
        Serial.print(sbuf.c_str());
    #endif
    va_end(args);
}

void println(SEVERITY s, const char* msg){
    std::string buf(SEVERITY_STRING[s]);
    buf.append(msg);
    #ifdef DESKTOP
        std::cout << buf << std::endl;
    #else
        Serial.println(buf.c_str());
    #endif
}
} // namespace debug

#endif
