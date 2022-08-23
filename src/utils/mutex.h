#ifndef EVENTLOOP_UTILS_MUTEX_H
#define EVENTLOOP_UTILS_MUTEX_H

#if  defined(WIN32)
#include <Windows.h>
#else
// Fail if this is a system you have not compensated for:
#error "Unknown System Type"
#endif


class CMutex
{
    HANDLE handle_;

    CMutex( const CMutex & );
    CMutex &operator=( const CMutex & );
public:
    CMutex();
    ~CMutex();

    void lock();
    void unlock();
};

#endif // EVENTLOOP_UTILS_MUTEX_H