#include "mutexlocker.h"

CMutexLocker::CMutexLocker( CMutex &mutex )
{
    mutex_ = &mutex;
    mutex_->lock();
}

CMutexLocker::~CMutexLocker()
{
    mutex_->unlock();
}

void CMutexLocker::lock()
{
    mutex_->lock();
}

void CMutexLocker::unlock()
{
    mutex_->unlock();
}
