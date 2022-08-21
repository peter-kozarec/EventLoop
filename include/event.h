#ifndef EVENTLOOP_EVENT_H
#define EVENTLOOP_EVENT_H

#include "eventloop_export.h"


class EVENTLOOP_EXPORT IEvent
{
public:
    virtual ~IEvent() {}

    virtual void process() = 0;
};

#endif // EVENTLOOP_EVENT_H