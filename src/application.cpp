#include "application.hpp"
#include "eventloop.hpp"


struct CApplication::CApplicationImpl
{
    int argc;
    char **argv;
    CEventLoop event_loop_;

    CApplicationImpl(int argc, char **argv) :
        argc(argc),
        argv(argv) {}
};


CApplication::CApplication(int argc, char **argv)
{
    static CApplicationImpl app(argc, argv);
    application_ = &app;
}

void CApplication::run()
{
    application_->event_loop_.process();
}

void CApplication::stop()
{
    application_->event_loop_.stop();
}
