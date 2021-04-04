#ifndef Semaphore_h_INCLUDED 
#define Semaphore_h_INCLUDED 

#include <time.h> 
#include <pthread.h>
#include "Mutex.h"

class Semaphore
{
    public :
       Semaphore() ;
       Semaphore(unsigned int initCount,unsigned int maxCount) ; 
       ~Semaphore() ; 
       void take();
       bool take(double timeout_ms);
       void give();
       int getCounter();

    private :
        unsigned int counter_ ;
        unsigned int maxCount_ ;
        Mutex mutex_ ;

};

#endif 