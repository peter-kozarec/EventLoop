#include <gtest/gtest.h>
#include <thread>
#include "eventloop.hpp"
#include "stopevent.hpp"


TEST(CEventLoop, stop)
{
    using namespace std::chrono_literals;

    CEventLoop event_loop;
    CStopEvent stop_event(event_loop);

    auto lambda = [&stop_event, &event_loop]()
    {
        std::this_thread::sleep_for(2000ms);
        event_loop.post(&stop_event);
    };

    std::thread t1(lambda);
    auto processing_result = event_loop.process() == 0;
    t1.join();

    EXPECT_TRUE(processing_result);
}