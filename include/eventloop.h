#ifndef EVENTLOOP_H
#define EVENTLOOP_H

#include "eventloop_export.h"
#include "event.h"


class EVENTLOOP_EXPORT CEventLoop
{
    struct CEventLoopImpl;
    CEventLoopImpl *impl_;

    CEventLoop( const CEventLoop &other );
    CEventLoop &operator=( const CEventLoop &other );
public:
    CEventLoop();
    ~CEventLoop();

    int process();
    bool post( IEvent *event );
    void stop();
};

#endif //EVENTLOOP_H