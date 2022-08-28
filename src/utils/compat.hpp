#ifndef EVENTLOOP_COMPAT_HPP
#define EVENTLOOP_COMPAT_HPP

#if defined(_WIN32) || defined(_WIN64) || (defined(__CYGWIN__) && !defined(_WIN32))
#include "windows.h"
/*
#elif defined(__ANDROID__)
    #define PLATFORM_NAME "android"
#elif defined(__linux__)
    #define PLATFORM_NAME "linux"
#elif defined(__unix__) || !defined(__APPLE__) && defined(__MACH__)
    #include <sys/param.h>
    #if defined(BSD)
        #define PLATFORM_NAME "bsd"
    #endif
#elif defined(__hpux)
    #define PLATFORM_NAME "hp-ux"
#elif defined(_AIX)
    #define PLATFORM_NAME "aix"
#elif defined(__APPLE__) && defined(__MACH__)
    #include <TargetConditionals.h>
    #if TARGET_IPHONE_SIMULATOR == 1
        #define PLATFORM_NAME "ios"
    #elif TARGET_OS_IPHONE == 1
        #define PLATFORM_NAME "ios"
    #elif TARGET_OS_MAC == 1
        #define PLATFORM_NAME "osx"
    #endif
#elif defined(__sun) && defined(__SVR4)
    #define PLATFORM_NAME "solaris"
*/
#else
    #error "Unknown os"
#endif

#if defined(__x64)
using tsize = unsigned long long;
#elif defined(__x86)
using tsize = unsigned int;
#else
#error "Unknown architecture"
#endif

#endif // EVENTLOOP_COMPAT_HPP
