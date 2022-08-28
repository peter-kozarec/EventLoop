#ifndef EVENTLOOP_EVENT_HPP
#define EVENTLOOP_EVENT_HPP

#include "eventloop_export.hpp"


class EVENTLOOP_EXPORT IEvent
{
public:
    virtual ~IEvent() = default;

    virtual void process() = 0;
};

#endif // EVENTLOOP_EVENT_HPP