#include <queue>
#include <mutex>
#include <condition_variable>
#include <atomic>

#include "eventloop.hpp"


struct CEventLoop::CEventLoopImpl
{
    std::condition_variable cv{};
    std::mutex event_queue_mutex{};
    std::queue<IEvent*> event_queue{};
    std::atomic_bool request_process_stop{};
};


CEventLoop::CEventLoop()
    : impl_(new CEventLoopImpl())
{
    impl_->request_process_stop.store(false, std::memory_order_relaxed);
}

CEventLoop::~CEventLoop()
{
    delete impl_;
}

void CEventLoop::process()
{
    std::mutex mtx;
    std::unique_lock<std::mutex> lock(mtx);

    while (!impl_->request_process_stop.load(std::memory_order_release))
    {
        IEvent *event = nullptr;

        impl_->event_queue_mutex.lock();
        if (!impl_->event_queue.empty())
            event = impl_->event_queue.front();
        impl_->event_queue_mutex.unlock();

        if (event)
        {
            event->process();
        }
        else
        {
            impl_->cv.wait(lock);
        }
    }
}

void CEventLoop::post(IEvent *event)
{
    impl_->event_queue_mutex.lock();
    {
        impl_->event_queue.push(event);
    }
    impl_->event_queue_mutex.unlock();

    impl_->cv.notify_one();
}

void CEventLoop::stop()
{
    impl_->request_process_stop.store(true, std::memory_order_relaxed);
    impl_->cv.notify_one();
}
