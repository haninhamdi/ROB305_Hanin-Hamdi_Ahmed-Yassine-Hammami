
#include "Mutex.h" 
#include "time_library.cpp"
#include <time.h> 
#include <pthread.h>
////////////////////////////////////////////////////////////////
////////////// Declaration of TimeoutException class ///////////
////////////////////////////////////////////////////////////////
using namespace std ; 
char* Mutex::Monitor::TimeoutException::throwException()
{
  throw "Timeout error" ;
}
////////////////////////////////////////////////////////////////
//////////////// Declaration of Monitor class //////////////////
////////////////////////////////////////////////////////////////

Mutex::Monitor::Monitor(Mutex &m) : mutex_(m)
{
}
void Mutex::Monitor::wait()
{
    printf("Waiting on condition variable cond\n");
    pthread_cond_wait(&mutex_.posixCondId,&mutex_.posixId); 
}
bool Mutex::Monitor::wait(double timeout_ms)
{
    const timespec wait = timespec_from_ms(timeout_ms);
    int x = pthread_cond_timedwait(&mutex_.posixCondId,&mutex_.posixId,&wait);
    return x == 0 ;
}
void Mutex::Monitor::notify()
{
    pthread_cond_signal(&mutex_.posixCondId);
}
void Mutex::Monitor::notifyAll()
{
    pthread_cond_broadcast(&mutex_.posixCondId);
}
////////////////////////////////////////////////////////////////
///////////////// Declaration of Lock class ////////////////////
////////////////////////////////////////////////////////////////
Mutex::Lock::Lock(Mutex &m) : Monitor(m)
{
    
    pthread_mutex_lock(&mutex_.posixId);
}

Mutex::Lock::Lock(Mutex &m, double timeout_ms) : Monitor(m)
{   
    int ret ;
    const timespec wait = timespec_from_ms(timeout_ms);
    ret=pthread_mutex_timedlock(&mutex_.posixId, &wait);

    if(ret!=0) throw TimeoutException();
}

Mutex::Lock::~Lock()
{

}
////////////////////////////////////////////////////////////////
//////////////// Declaration of TryLock class //////////////////
////////////////////////////////////////////////////////////////
Mutex::TryLock::TryLock(Mutex &m) : Mutex::Monitor(m)
{
    int x =pthread_mutex_trylock(&mutex_.posixId);

    if(x!=0) throw TimeoutException();
}

Mutex::TryLock::~TryLock()
{
}
////////////////////////////////////////////////////////////////
///////////////// Declaration of Mutex class ///////////////////
////////////////////////////////////////////////////////////////
Mutex::Mutex() 
{
    posixId = PTHREAD_RECURSIVE_MUTEX_INITIALIZER_NP;
    posixCondId =  PTHREAD_COND_INITIALIZER;
    pthread_mutexattr_t attr;
    pthread_mutexattr_init(&attr);
    pthread_mutexattr_settype(&attr, PTHREAD_MUTEX_RECURSIVE);
    pthread_mutex_init(&posixId, &attr);
    pthread_mutexattr_destroy(&attr);
}

Mutex::~Mutex() 
{
    pthread_mutex_destroy(&posixId);
}

bool Mutex::lock(){
  try
   {
    Mutex::Lock lock_(*this);
   }
   catch(Mutex::Monitor::TimeoutException e)
   {
       cerr << "ERREUR : " << e.throwException() << endl;
       return false ;
   }
return true ;
}

bool Mutex::lock(double timeout_ms){
  try
   {
    Mutex::Lock lock_(*this, timeout_ms);
   }
   catch(Mutex::Monitor::TimeoutException e)
   {
       cerr << "ERREUR : " << e.throwException() << endl;
       return false ;
   }
return true ;
}

bool Mutex::trylock(){
  try
   {
    
    Mutex::TryLock trylock_(*this);
   }
   catch(Mutex::Monitor::TimeoutException e)
   {
       cerr << "ERREUR : " << e.throwException() << endl;
       return false ;
   }
return true ;
}

bool Mutex::unlock()
{
    int x = pthread_mutex_unlock(&this->posixId);

    if(x!=0) return false ;
    else return true ;
}




