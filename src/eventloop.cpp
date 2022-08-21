#include "eventloop.h"
#include "utils/ptrqueue.h"
#include "utils/mutex.h"
#include "utils/mutexlocker.h"
#include "utils/conditionalvar.h"


struct CEventLoop::CEventLoopImpl
{
    CConditionalVar cv;
    CPtrQueue< IEvent > event_queue;
    CMutex stop_mutex;
    bool request_process_stop;

    CEventLoopImpl() :
            request_process_stop( false )
    {
    }

    bool event_or_stop();
};

bool CEventLoop::CEventLoopImpl::event_or_stop()
{
    return request_process_stop || !event_queue.is_empty();
}


CEventLoop::CEventLoop()
{
    impl_ = new CEventLoopImpl();
}

CEventLoop::~CEventLoop()
{
    delete impl_;
}

int CEventLoop::process()
{
    CMutex cv_mutex;
    CMutexLocker lock( cv_mutex );

    while ( !impl_->request_process_stop )
    {
        if ( impl_->event_queue.is_empty() )
        {
            impl_->cv.wait( lock, impl_, &CEventLoopImpl::event_or_stop );
        }

        if ( IEvent *event = impl_->event_queue.dequeue() )
        {
            event->process();
        }
    }

    return 0;
}

bool CEventLoop::post( IEvent *event )
{
    if ( impl_->event_queue.enqueue( event ) )
    {
        impl_->cv.notify_one();
        return true;
    }
    return false;
}

void CEventLoop::stop()
{
    CMutexLocker lock( impl_->stop_mutex );
    impl_->request_process_stop = true;
    impl_->cv.notify_one();
}
