/***************************************************************
   RESPONSE to : TD1c 
   The aim of this script is to create a looper wich increments 
   a double intialized with 0.0 with nLoops times. We also 
   calculate the real time duration of the looper.  
***************************************************************/

#include <time.h>
#include <signal.h> 
#include <iostream>
#include "time_library.cpp" 

using namespace std ; 

void incr(unsigned int nLoops, double* pCounter)
{
    for (unsigned int i = 0; i < nLoops; i++)
    {
        *pCounter += 1.0 ; 
    }
}

int main(int , char* argv[])
{
    
    cout<< "------------------------------------------------------------" <<endl ;
    cout<< "------------------- ROB305 TD1C ----------------------------" <<endl ; 
    cout<< "--------- Hanin Hamdi & Ahmed Yassine Hammami --------------" <<endl ;
    cout<< "------------------------------------------------------------" <<endl ;
    
    unsigned int nLoops = stoul(argv[1], nullptr, 10) ;
    double counter = 0.0 ; 
    double* pCounter = &counter ;
    struct timespec debut, fin, duration ; 
    double duration_s ; 
    
    clock_gettime(CLOCK_REALTIME, &debut) ;
    incr(nLoops, pCounter) ; 
    clock_gettime(CLOCK_REALTIME, &fin) ;
    
    duration = fin - debut ; 
    duration_s = timespec_to_ms(duration)/1e3 ; 
    cout<<"Final value of the counter = "<<*pCounter<<endl ;
    cout<<"Duration of the function incr = "<<duration_s<<" seconds"<<endl ;  

    return 0 ;
}
