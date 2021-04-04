#include "Chrono.h" 
#include "/home/hani.hamdi/ROB305/TD1/time_library.cpp"

Chrono::Chrono()
{
    restart();
}

void Chrono::stop()
{
    stopTime_ = timespec_now() ;
}

void Chrono::restart()
{
    startTime_ = timespec_now() ;
    startTime_ = timespec_now() ;
}

bool Chrono::isActive() const 
{
    return startTime_ == stopTime_ ;
}

double Chrono::startTime() const 
{
    return timespec_to_ms(startTime_) ;
}

double Chrono::stopTime() const 
{
    return timespec_to_ms(stopTime_) ;
}

double Chrono::lap() const
{
    timespec duration_ts ;   
    if (isActive())
    {
        duration_ts = timespec_now() - startTime_ ;
    }
    else 
    {
        duration_ts = stopTime_ - startTime_ ;
    }
    return timespec_to_ms(duration_ts) ;
}
