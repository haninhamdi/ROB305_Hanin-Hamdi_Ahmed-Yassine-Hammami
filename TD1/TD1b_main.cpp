/***************************************************************
   RESPONSE to : TD1b 
   The aim of this script is to create a software device which 
   increments and prints on the screen a counter incremented 
   with 1 with a frequency = 2 Hz. So, we implements a periodic
   timer with a duration = 0.5 s 
***************************************************************/

#include <time.h>
#include <signal.h> 
#include <iostream>

using namespace std ; 

/* The handler of the timer */
void myHandler(int /*sig*/, siginfo_t* si, void* )   
{
    int* p_counter = (int*) si-> si_value.sival_ptr ;
    *p_counter += 1 ;
    cout << *p_counter << endl ;
}


int main()
{

   cout<< "------------------------------------------------------------" <<endl ;
   cout<< "------------------- ROB305 TD1B ----------------------------" <<endl ; 
   cout<< "--------- Hanin Hamdi & Ahmed Yassine Hammami --------------" <<endl ;
   cout<< "------------------------------------------------------------" <<endl ;
    
   /* Create a counter to be incremented while the execution of the timer callback */
   volatile int counter = 0 ;
   
   /* Create the timer */
   struct sigaction sa ;
   sa.sa_flags = SA_SIGINFO;
   sa.sa_sigaction = myHandler ;
   sigemptyset(&sa.sa_mask);
   sigaction(SIGRTMIN,&sa, NULL) ;
   
   struct sigevent sev ;
   sev.sigev_notify = SIGEV_SIGNAL ;
   sev.sigev_signo = SIGRTMIN ; 
   sev.sigev_value.sival_ptr = (void*) &counter /*data*/;
   
   timer_t tid ; 
   timer_create(CLOCK_REALTIME, &sev, &tid);
   
   itimerspec its ;
   its.it_value.tv_sec = 0 ;
   its.it_value.tv_nsec = 500000000 ;
   its.it_interval = its.it_value ;
   
   /* Start the timer */
   timer_settime(tid, 0, &its, NULL);
   
   while(counter < 15)
   { 
       /* just wait */ 
   }
   
   /* Destroy the timer before leaving */
   timer_delete(tid) ;
   
   return 0 ;
}
