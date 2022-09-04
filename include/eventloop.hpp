#ifndef EVENTLOOP_HPP
#define EVENTLOOP_HPP

#include "eventloop_export.hpp"
#include "event.hpp"


class EVENTLOOP_EXPORT CEventLoop
{
    struct CEventLoopImpl;
    CEventLoopImpl *impl_;

    CEventLoop(const CEventLoop &other);
    CEventLoop &operator=(const CEventLoop &other);
public:
    CEventLoop();
    ~CEventLoop();

    void process();
    void post(IEvent *event);
    void stop();
};

#endif // EVENTLOOP_HPP