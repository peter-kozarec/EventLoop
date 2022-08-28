#include "eventloop.hpp"
#include "event.hpp"
#include <chrono>
#include <thread>


CEventLoop eventLoop;

class CustomEvent : public IEvent
{
public:
    void process();
};

void CustomEvent::process()
{
    eventLoop.stop();
}

void run()
{
    std::this_thread::sleep_for(std::chrono::milliseconds(10000));
    eventLoop.post(new CustomEvent);
}

int main(int argc, char **argv)
{
    std::thread thread(&run);
    const int result = eventLoop.process();
    thread.join();
    return result;
}