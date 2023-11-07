#pragma once

#include <iostream>
#include <source_location>

#if defined(_WIN32)
#define ASSERT(x) if(!(x)){\
     std::cout << "At " << std::source_location::current().file_name() << ":" << std::source_location::current().line() << "." << std::endl;\
     __debugbreak();\
    }
#elif defined(__unix__)
#define ASSERT(x) if(!(x)) __builtin_trap();
#endif