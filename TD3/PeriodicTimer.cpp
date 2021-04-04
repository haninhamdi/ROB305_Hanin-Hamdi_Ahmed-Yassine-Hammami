#include "PeriodicTimer.h" 
#include "Timer.cpp"

using namespace std ; 

void PeriodicTimer::start(double duration_ms) 
{
    /* Start the periodic timer, NB: Here you have to assign an its.it_interval != 0 */ 
    timespec duration_ts = timespec_from_ms(duration_ms) ;
    itimerspec its ;
    its.it_value = duration_ts ;
    its.it_interval = duration_ts ;
    
    timer_settime(tid, 0, &its, NULL);
    cout<<"periodic timer started "<<endl ; 
}
