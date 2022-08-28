#include "eventloop.hpp"
#include "utils/ptrqueue.hpp"
#include "utils/mutex.hpp"
#include "utils/mutexlocker.hpp"
#include "utils/conditionalvar.hpp"


struct CEventLoop::CEventLoopImpl
{
    CConditionalVar cv;
    CMutex event_queue_mutex;
    CPtrQueue<IEvent> event_queue;
    CMutex stop_mutex;
    bool request_process_stop{false};

    CEventLoopImpl() = default;

    bool event_or_stop();
};

bool CEventLoop::CEventLoopImpl::event_or_stop()
{
    event_queue_mutex.lock();
    const auto is_queue_empty = event_queue.is_empty();
    event_queue_mutex.unlock();

    CMutexLocker lock(stop_mutex);
    return request_process_stop || !is_queue_empty;
}

CEventLoop::CEventLoop() : impl_(new CEventLoopImpl())
{
}

CEventLoop::~CEventLoop()
{
    delete impl_;
}

int CEventLoop::process()
{
    CMutex cv_mutex;
    CMutexLocker lock(cv_mutex);
    while (!impl_->request_process_stop)
    {
        impl_->event_queue_mutex.lock();
        const auto is_queue_empty = impl_->event_queue.is_empty();
        impl_->event_queue_mutex.unlock();

        if (is_queue_empty)
        {
            impl_->cv.wait(lock, impl_, &CEventLoopImpl::event_or_stop);
        }

        impl_->event_queue_mutex.lock();
        auto *const event = impl_->event_queue.dequeue();
        impl_->event_queue_mutex.unlock();

        if (event)
        {
            event->process();
        }
    }
    return 0;
}

bool CEventLoop::post(IEvent *event)
{
    impl_->event_queue_mutex.lock();
    const auto post_result = impl_->event_queue.enqueue(event);
    impl_->event_queue_mutex.unlock();

    if (post_result)
    {
        impl_->cv.notify_one();
        return true;
    }
    return false;
}

void CEventLoop::stop()
{
    CMutexLocker lock(impl_->stop_mutex);
    impl_->request_process_stop = true;
    impl_->cv.notify_one();
}
