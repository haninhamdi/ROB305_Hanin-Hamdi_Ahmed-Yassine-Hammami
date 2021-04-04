/******************************************************************
   RESPONSE to : TD1e (second part concerning the calibration)  
   This script is used to calibrate the function calculating 
   the number of loops done by the function incr during a given 
   duration. We suppose that this function is linear : 
               l(t) = a*t + b 
   So the aim of this script is to find a and b using Posix timers 
   We give in this script an improvement of the method used in 
   TD1d_bis : we do the calibration using more than 2 samples.   
*******************************************************************/

#include <time.h>
#include <signal.h> 
#include <iostream>
#include <climits>
#include <vector>
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

void calib(double* pA, double* pB, unsigned int nSamples, double samplingPeriod_ms)
{
    volatile bool stop ; 
    volatile bool* pStop = &stop ; 
    unsigned int nLoops = UINT_MAX ; 
    unsigned int doneLoops ;
    double counter ; 
    double* pCounter = &counter ; 
    vector<unsigned int> samples ; 
    double a, b ; 

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
    timespec time_ts ; 
    /* Determine the nSamples */
    for (unsigned int i = 1 ; i < nSamples + 1 ; i++)
    {
        counter = 0.0 ; 
        stop = false ; 
        
        time_ts = timespec_from_ms((double) i*samplingPeriod_ms) ; 
        its.it_value = time_ts ; 
        its.it_interval.tv_sec = 0.0 ;
        its.it_interval.tv_nsec = 0.0 ;
        
        timer_settime(tid, 0, &its, NULL);
        doneLoops = incr(nLoops, pCounter, pStop) ;  
        samples.push_back(doneLoops) ; 
    }
    
    /* Calibration */
    /****************************/
    /* Linear regression */ 
    unsigned int half_nSamples = (unsigned int) (nSamples / 2) ; 
    
    /* Compute the sum of the first half of the samples */ 
    unsigned int first_half_samples = 0 ; 
    for (unsigned int i =0; i < half_nSamples; i++)
    {
        first_half_samples += samples.at(i) ; 
    } 
    /* Compute the sum of the second half of the samples */ 
    unsigned int second_half_samples = 0 ; 
    for (unsigned int i = half_nSamples ; i < nSamples; i++)
    {
        second_half_samples += samples.at(i) ; 
    } 

    /* Compute a and b as a mean between the first half and the second half of samples */ 
    double samplingPeriod_s = samplingPeriod_ms/1e3 ; 
    a = 4*(second_half_samples - first_half_samples) / (samplingPeriod_s*nSamples*nSamples) ; 
    b = (second_half_samples + first_half_samples - a*samplingPeriod_s*nSamples*(nSamples+1)/2) / nSamples ; 
    *pA = a ; 
    *pB = b ;
}

int main(int argc, char* argv[])
{
    cout<< "------------------------------------------------------------" <<endl ;
    cout<< "------  ROB305 TD1e : Calibration with more samples --------" <<endl ; 
    cout<< "--------- Hanin Hamdi & Ahmed Yassine Hammami --------------" <<endl ;
    cout<< "------------------------------------------------------------" <<endl ;
    
    
    double a, b ;
    double* pA = &a ; 
    double* pB = &b ; 
    unsigned int nSamples ; 
    double samplingPeriod_ms ; 
    
    /* Read the initialization of the number of samples and the samplingPeriod_ms from the shell */ 
    if (argc > 2)
    {
        nSamples = stoi(argv[1], nullptr, 10) ; 
        samplingPeriod_ms = stoi(argv[2], nullptr, 10) ; 
    }
    
    /* Calibration using timers */
    calib(pA, pB, nSamples, samplingPeriod_ms) ; 
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
