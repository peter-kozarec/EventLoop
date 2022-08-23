#include "mutex.h"


CMutex::CMutex()
{
    handle_ = ::CreateEvent( NULL, FALSE, FALSE, NULL );
    ::SetEvent( handle_ );
}

CMutex::~CMutex()
{
    ::ResetEvent( handle_ );
    ::CloseHandle( handle_ );
}

void CMutex::lock()
{
    ::WaitForSingleObject( handle_, INFINITE );
}

void CMutex::unlock()
{
    ::SetEvent( handle_ );
}
