#include "mutex.h"


CMutex::CMutex()
{
    interlock_ = MUTEX_UNLOCKED;
}

CMutex::~CMutex()
{
    interlock_ = MUTEX_UNLOCKED;
}

void CMutex::lock()
{
#ifdef TARG_PLATFORM_WINDOWS
    while ( interlock_ == MUTEX_LOCKED ||
            InterlockedCompareExchange( &interlock_, 1, 0 ) == 1 )
    {
    }
#endif
#ifdef TARG_PLATFORM_LINUX
    while(interlock_ == MUTEX_LOCKED ||
          __sync_lock_test_and_set(&interlock_, 1) == 1)
    {}
#endif
}

void CMutex::unlock()
{
    interlock_ = MUTEX_UNLOCKED;
}
