#include "conditionalvar.h"


void CConditionalVar::wait( CMutexLocker &lock )
{
    CMutexLocker locker( queue_mutex_ );
    lock.unlock();

    CMutex *mutex = new CMutex;
    lock_queue_.enqueue( mutex );

    mutex->lock();
    locker.unlock();
    mutex->lock();
    lock.lock();
}

void CConditionalVar::notify_one()
{
    CMutexLocker lock( queue_mutex_ );

    if ( CMutex *mutex = lock_queue_.dequeue() )
    {
        mutex->unlock();
        delete mutex;
    }
}

void CConditionalVar::notify_all()
{
    CMutexLocker lock( queue_mutex_ );

    while ( CMutex *mutex = lock_queue_.dequeue() )
    {
        mutex->unlock();
        delete mutex;
    }
}
