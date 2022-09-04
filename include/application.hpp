#ifndef EVENTLOOP_APPLICATION_HPP
#define EVENTLOOP_APPLICATION_HPP

#include "eventloop_export.hpp"


class EVENTLOOP_EXPORT CApplication
{
    struct CApplicationImpl;
    static inline CApplicationImpl *application_ = nullptr;

    CApplication(const CApplication&);
    CApplication& operator=(const CApplication&);
public:
    CApplication(int argc, char **argv);
    ~CApplication() = default;

    static void run();
    static void stop();
};

#endif // EVENTLOOP_APPLICATION_HPP
