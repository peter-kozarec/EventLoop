#ifndef EVENTLOOP_UTILS_MUTEXLOCKER_HPP
#define EVENTLOOP_UTILS_MUTEXLOCKER_HPP

#include "mutex.hpp"


class CMutexLocker
{
    CMutex *mutex_;

    CMutexLocker(const CMutexLocker &);
    CMutexLocker &operator=(const CMutexLocker &);
public:
    explicit CMutexLocker(CMutex &mutex);
    ~CMutexLocker();

    void lock();
    void unlock();
};

#endif // EVENTLOOP_UTILS_MUTEXLOCKER_HPP
