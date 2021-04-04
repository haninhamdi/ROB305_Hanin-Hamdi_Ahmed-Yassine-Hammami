#include "Timer.h" 
#include "/home/hani.hamdi/ROB305/TD1/time_library.cpp"

using namespace std ; 

Timer::Timer() 
{
    /* Contructor used to create the timer and to assign its action and event */
    sa.sa_flags = SA_SIGINFO ;
    sa.sa_sigaction = call_callback;
    
    sigemptyset(&sa.sa_mask);
    sigaction(SIGRTMIN, &sa, NULL) ; 
    
    sev.sigev_notify = SIGEV_SIGNAL ; 
    sev.sigev_signo = SIGRTMIN ;
    sev.sigev_value.sival_ptr = this;
    
    timer_create(CLOCK_REALTIME, &sev, &tid) ; 
    cout<<"timer created"<<endl ; 
}

Timer::~Timer() 
{
    /* Destructor used to delete the timer automatically */ 
    timer_delete(tid) ; 
    cout<<"timer deleted "<<endl ; 
}

void Timer::start(double duration_ms)
{  
    /* Start the timer : assign its it_value, NB : it's not periodic so its.it_value = 0 */ 
    timespec duration_ts = timespec_from_ms(duration_ms) ;
    itimerspec its ;
    its.it_value = duration_ts ;
    its.it_interval.tv_sec = 0 ;
    its.it_interval.tv_nsec = 0 ;
   
    timer_settime(tid, 0, &its, NULL);
    cout<<"timer started "<<endl ; 
}

void Timer::stop()
{
    /* Stop the timer */ 
    itimerspec its ;
    its.it_value.tv_sec = 0 ;
    its.it_value.tv_nsec = 0 ;
    its.it_interval = its.it_value ; 
   
    timer_settime(tid, 0, &its, NULL);
    cout<<"timer stopped"<<endl ; 
}


void Timer::call_callback(int, siginfo_t* si, void*) 
{
    /* Call the callback implemented by daughter classes */
    Timer* pTimer = static_cast <Timer*>(si->si_value.sival_ptr) ;
    pTimer->callback() ;
}
