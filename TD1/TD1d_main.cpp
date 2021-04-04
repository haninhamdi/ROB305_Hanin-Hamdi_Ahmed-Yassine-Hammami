/***************************************************************
   RESPONSE to : TD1d (first part before calibration)  
   This script is used to increment a double until the 
   expiration of a timer with a duration given from the shell.  
***************************************************************/

#include <time.h>
#include <signal.h> 
#include <iostream>
#include <climits>
#include "time_library.cpp" 

using namespace std ;

unsigned int incr(unsigned int nLoops, double* pCounter, volatile bool* pStop)
{
    unsigned int iLoop = 0 ; 
    unsigned int doneLoops = 0 ; 

    while (iLoop < nLoops and not(*pStop))
    {
        *pCounter += 1.0 ;
        iLoop += 1 ; 
        doneLoops += 1 ;  
    }
    return doneLoops ; 
}

void myHandler(int /*sig*/, siginfo_t* si, void* )
   {
       int* pStop = (int*) si-> si_value.sival_ptr ;
       *pStop = true ; 
   }


int main(int , char* argv[])
{
    cout<< "------------------------------------------------------------" <<endl ;
    cout<< "------------------- ROB305 TD1D ----------------------------" <<endl ; 
    cout<< "--------- Hanin Hamdi & Ahmed Yassine Hammami --------------" <<endl ;
    cout<< "------------------------------------------------------------" <<endl ;
    
    volatile bool stop = false ; 
    volatile bool* pStop = &stop ; 
    unsigned int nLoops = UINT_MAX ; 
    unsigned int doneLoops ;
    double counter = 0.0 ; 
    double* pCounter = &counter ; 
    
    /* The duration of the timer in melliseconds is given as parameter to the main while execution */ 
    double duration_ms = stoi(argv[1], nullptr, 10) ;
    timespec duration_ts ; 

    /* Action of the timer */ 
    struct sigaction sa ;
    sa.sa_flags = SA_SIGINFO;
    sa.sa_sigaction = myHandler ;
    sigemptyset(&sa.sa_mask);
    sigaction(SIGRTMIN,&sa, NULL) ;
   
    /* Event of the timer */
    struct sigevent sev ;
    sev.sigev_notify = SIGEV_SIGNAL ;
    sev.sigev_signo = SIGRTMIN ; 
    sev.sigev_value.sival_ptr = (void*) pStop /*data*/;
   
    /* Creation of the timer */ 
    timer_t tid ; 
    timer_create(CLOCK_REALTIME, &sev, &tid);
   
    itimerspec its ;
    duration_ts = timespec_from_ms(duration_ms) ; 
    its.it_value = duration_ts ;
    its.it_interval.tv_sec = 0 ;
    its.it_interval.tv_sec = 0 ;
   
    timer_settime(tid, 0, &its, NULL);
    doneLoops = incr(nLoops, pCounter, pStop) ; 
    
    /* Print the done loops */ 
    cout<<"Done Loops = "<<doneLoops<<endl ; 
   
    timer_delete(tid) ;    

    return 0 ; 
    
}
