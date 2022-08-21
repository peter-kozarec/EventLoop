#ifndef EVENTLOOP_UTILS_MUTEXLOCKER_H
#define EVENTLOOP_UTILS_MUTEXLOCKER_H

#include "mutex.h"


class CMutexLocker
{
    CMutex *mutex_;

    CMutexLocker( const CMutexLocker & );
    CMutexLocker &operator=( const CMutexLocker & );
public:
    explicit CMutexLocker( CMutex &mutex );
    ~CMutexLocker();

    void lock();
    void unlock();
};

#endif // EVENTLOOP_UTILS_MUTEXLOCKER_H
