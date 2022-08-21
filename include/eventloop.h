#ifndef EVENTLOOP_H
#define EVENTLOOP_H

#include "eventloop_export.h"


class EVENTLOOP_EXPORT CEventLoop final
{
public:
    CEventLoop();
    CEventLoop(const CEventLoop &other);
    CEventLoop(CEventLoop &&other) noexcept;
    CEventLoop &operator=(const CEventLoop &other);
    CEventLoop &operator=(CEventLoop &&other) noexcept;
    ~CEventLoop();

    int process();
};

#endif //EVENTLOOP_H