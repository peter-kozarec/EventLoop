#ifndef EVENT_LOOP_UNIT_TEST_STOP_EVENT
#define EVENT_LOOP_UNIT_TEST_STOP_EVENT

#include "eventloop.hpp"
#include "event.hpp"


class CStopEvent : public IEvent
{
    CEventLoop *event_loop_;
public:
    CStopEvent(CEventLoop &event_loop) : event_loop_(&event_loop) {}
    ~CStopEvent() override = default;

    void process() override;
};

inline void CStopEvent::process()
{
    event_loop_->stop();
}

#endif // EVENT_LOOP_UNIT_TEST_STOP_EVENT