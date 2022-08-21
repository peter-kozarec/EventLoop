#ifndef EVENTLOOP_UTILS_MUTEX_H
#define EVENTLOOP_UTILS_MUTEX_H

#if  defined(WIN32)
#include <Windows.h>
#define TARG_PLATFORM_WINDOWS
#elif defined(__unix)
#include <unistd.h>
#define TARG_PLATFORM_LINUX
#else
// Fail if this is a system you have not compensated for:
#error "Unknown System Type"
#endif

const int MUTEX_LOCKED = 1;
const int MUTEX_UNLOCKED = 0;

class CMutex
{
    volatile unsigned long long interlock_;

    CMutex( const CMutex & );
    CMutex &operator=( const CMutex & );
public:
    CMutex();
    ~CMutex();

    void lock();
    void unlock();
};

#endif // EVENTLOOP_UTILS_MUTEX_H