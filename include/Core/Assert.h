#pragma once

#if defined(_WIN32)
#define ASSERT(x) if(!(x)) __debugbreak();
#elif defined(__unix__)
#define ASSERT(x) if(!(x)) __builtin_trap();
#endif