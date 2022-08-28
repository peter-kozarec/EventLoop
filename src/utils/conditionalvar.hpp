#ifndef EVENTLOOP_UTILS_CONDITIONALVAR_HPP
#define EVENTLOOP_UTILS_CONDITIONALVAR_HPP

#include "mutex.hpp"
#include "mutexlocker.hpp"
#include "ptrqueue.hpp"


class CConditionalVar
{
    CPtrQueue<CMutex> lock_queue_;
    CMutex queue_mutex_;

    CConditionalVar(const CConditionalVar &);
    CConditionalVar &operator=(const CConditionalVar &);
public:
    CConditionalVar() = default;
    ~CConditionalVar() = default;

    template<typename FunctionPtr>
    void wait(CMutexLocker &lock, FunctionPtr fct);
    template<typename ObjectPtr, typename FunctionPtr>
    void wait(CMutexLocker &lock, ObjectPtr obj, FunctionPtr fct);
    void wait(CMutexLocker &lock);

    void notify_one();
    void notify_all();
};

template<typename FunctionPtr>
void CConditionalVar::wait(CMutexLocker &lock, FunctionPtr fct)
{
    while (!(*fct)())
    {
        wait(lock);
    }
}

template<typename ObjectPtr, typename FunctionPtr>
void CConditionalVar::wait(CMutexLocker &lock, ObjectPtr obj, FunctionPtr fct)
{
    while (!(*obj.*fct)())
    {
        wait(lock);
    }
}

#endif // EVENTLOOP_UTILS_CONDITIONALVAR_HPP