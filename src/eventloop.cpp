#include "eventloop.h"


CEventLoop::CEventLoop()
{
}

CEventLoop::CEventLoop(const CEventLoop &other)
{
}

CEventLoop::CEventLoop(CEventLoop &&other) noexcept
{
}

CEventLoop &CEventLoop::operator=(const CEventLoop &other)
{
    return *this;
}

CEventLoop &CEventLoop::operator=(CEventLoop &&other) noexcept
{
    return *this;
}

CEventLoop::~CEventLoop()
{
}

int CEventLoop::process()
{
    return 0;
}
