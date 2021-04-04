/*********************************************
    Abstract class Timer : constructs, starts
    and stops Posix timers 
*********************************************/

#ifndef Timer_h_INCLUDED 
#define Timer_h_INCLUDED 

#include <time.h> 
#include <signal.h> 

class Timer
{
    public :
       Timer() ; 
       ~Timer() ; 
       void start(double duration_ms) ;
       void stop() ; 
    protected :
       virtual void callback() = 0 ;
    private :
       static void call_callback(int, siginfo_t* sig, void*) ;   
    protected :
    timer_t tid ;  
    private : 
       struct sigaction sa ; 
       struct sigevent sev ; 
};

#endif 
