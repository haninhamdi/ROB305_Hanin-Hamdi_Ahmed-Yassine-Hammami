/******************************************************************
   RESPONSE to : TD1d (second part concerning the calibration)  
   This script is used to calibrate the function calculating 
   the number of loops done by the function incr during a given 
   duration. We suppose that this function is linear : 
               l(t) = a*t + b 
   So the aim of this script is to find a and b using Posix timers  
*******************************************************************/

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

void calib(double* pA, double* pB)
{
    volatile bool stop = false ; 
    volatile bool* pStop = &stop ; 
    unsigned int nLoops = UINT_MAX ; 
    unsigned int doneLoops_4 ;
    unsigned int doneLoops_6 ;
    double counter = 0.0 ; 
    double* pCounter = &counter ; 

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
   
    /* l(4) */ 
    itimerspec its ;
    its.it_value.tv_sec = 4.0 ;
    its.it_value.tv_nsec = 0.0 ;
    its.it_interval.tv_sec = 0.0 ;
    its.it_interval.tv_nsec = 0.0 ;
   
    timer_settime(tid, 0, &its, NULL);
    doneLoops_4 = incr(nLoops, pCounter, pStop) ;    

    /* l(6) */ 
    counter = 0.0 ; 
    stop = false ; 
    its.it_value.tv_sec = 6.0 ;
    its.it_value.tv_nsec = 0.0 ;
    its.it_interval.tv_sec = 0.0 ;
    its.it_interval.tv_nsec = 0.0 ;
   
    timer_settime(tid, 0, &its, NULL);
    doneLoops_6 = incr(nLoops, pCounter, pStop) ; 
   
    timer_delete(tid) ; 

    /* Calibration */
    double a = (doneLoops_6 - doneLoops_4) / 2.0 ; 
    *pA = a ; 
    *pB = doneLoops_4 - 4.0*a ;
  
}

int main()
{
    cout<< "------------------------------------------------------------" <<endl ;
    cout<< "-------------- ROB305 TD1D_bis : Calibration ---------------" <<endl ; 
    cout<< "--------- Hanin Hamdi & Ahmed Yassine Hammami --------------" <<endl ;
    cout<< "------------------------------------------------------------" <<endl ;
    
    
    double a, b ;
    double* pA = &a ; 
    double* pB = &b ; 
    
    /* Calibration using timers */
    calib(pA, pB) ; 
    cout<<"Calibration using timers : l(t) = "<<a<<"*t + "<<b<<"   ( t(s) )"<<endl ; 
    
    /* Test of the calibration using CLOCK_REALTIME */ 
    struct timespec debut, fin, duration ; 
    double duration_s_1, duration_s_2 ; 
    bool stop = false ; 
    double counter = 0.0 ; 
    double* pCounter = &counter ;
 
    clock_gettime(CLOCK_REALTIME, &debut) ;
    incr(10000, pCounter, &stop) ; 
    clock_gettime(CLOCK_REALTIME, &fin) ;
    duration = fin - debut ; 
    duration_s_1 = timespec_to_ms(duration)/1e3 ; 

    counter = 0.0 ; 
    clock_gettime(CLOCK_REALTIME, &debut) ;
    incr(100000, pCounter, &stop) ; 
    clock_gettime(CLOCK_REALTIME, &fin) ;
    duration = fin - debut ; 
    duration_s_2 = timespec_to_ms(duration)/1e3 ;
    
    a = (100000 - 10000)/(duration_s_2 - duration_s_1) ;
    b = 10000 - duration_s_1*a ; 
    cout<<"Calibration using clock_gettime : l(t) = "<<a<<"*t + "<<b<<"   ( t(s) )   "<<endl ; 
    
    /* a is roughly the same in the two calibrations, however b differs a lot -> necessity to improve calib() */ 
    
    return 0 ; 
    
}
