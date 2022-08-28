#ifndef EVENTLOOP_UTILS_MUTEX_HPP
#define EVENTLOOP_UTILS_MUTEX_HPP

#include "compat.hpp"


class CMutex
{
    HANDLE handle_;

    CMutex(const CMutex &);
    CMutex &operator=(const CMutex &);
public:
    CMutex();
    ~CMutex();

    void lock();
    void unlock();
};

#endif // EVENTLOOP_UTILS_MUTEX_HPP