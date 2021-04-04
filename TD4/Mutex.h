#ifndef Mutex_h_INCLUDED 
#define Mutex_h_INCLUDED 

#include <time.h> 
#include <pthread.h>
////////////////////////////////////////////////////////////////
//////////////// Declaration of Mutex class ////////////////////
////////////////////////////////////////////////////////////////
class Mutex
{
    public :
       Mutex() ; 
       ~Mutex() ; 
       class Monitor ;
       class Lock;
       class TryLock;
    public :
       pthread_mutex_t posixId ;
       pthread_cond_t posixCondId;
       bool lock();
       bool lock(double timeout_ms);
       bool trylock();
       bool unlock();
};

////////////////////////////////////////////////////////////////
//////////////// Declaration of Monitor class //////////////////
////////////////////////////////////////////////////////////////
class Mutex::Monitor
{
    public :
      class TimeoutException;
      void wait();
      bool wait(double timeout_ms);
      void notify();
      void notifyAll();
    public:
      Monitor(Mutex& m); 
      Mutex& mutex_ ; 
};
////////////////////////////////////////////////////////////////
////////////// Declaration of TimeoutException class ///////////
////////////////////////////////////////////////////////////////
class Mutex::Monitor::TimeoutException
{
   public :
     char* throwException() ;
}; 
////////////////////////////////////////////////////////////////
///////////////// Declaration of Lock class ////////////////////
////////////////////////////////////////////////////////////////
class Mutex::Lock : Mutex::Monitor 
{
    public :
        Lock(Mutex &m);
        Lock(Mutex &m, double timeout_ms) ;
       ~Lock();   
};

////////////////////////////////////////////////////////////////
//////////////// Declaration of TryLock class //////////////////
////////////////////////////////////////////////////////////////
class Mutex::TryLock : public Mutex::Monitor
{
    public :
       TryLock( Mutex &m) ;
       ~TryLock();
     
};

#endif 
