#include "PosixThread.h"
#include "/home/hani.hamdi/ROB305/TD1/time_library.cpp"

using namespace std ; 
char* PosixThread::Exception::throwException()
{
  throw "Posix Thread doesn't exit" ;
}

PosixThread::PosixThread()
{
  isActive = false ;
  pthread_attr_init(&posixAttr) ;
}

PosixThread::PosixThread(pthread_t posixId) 
{
  this->posixId = posixId ;
  isActive = true ;
}

PosixThread::~PosixThread()
{
  pthread_attr_destroy(&posixAttr) ;
  cout<<"---PosixThread destroyed----"<<endl ; 
}

void PosixThread::start(void* (*threadFunc) (void*), void* threadArg)
{
  if (not(isActive))
  {
    pthread_create(&posixId, &posixAttr, threadFunc, threadArg) ;
    isActive = true ;
  }
}

void PosixThread::join()
{
  pthread_join(posixId, nullptr) ; 
}

bool PosixThread::join(double timeout_ms)
{
  timespec timeout_ts = timespec_from_ms(timeout_ms) ;
  int error = pthread_timedjoin_np(posixId, nullptr, &timeout_ts) ; 
  if (error == 0) /* thread finished before the timeout*/
    return true ;
  else
    return false ;
}

bool PosixThread::setScheduling(int schedPolicy , int priority)
{
  pthread_attr_setinheritsched(&posixAttr, PTHREAD_EXPLICIT_SCHED) ;

  sched_param schedParams ;
  schedParams.sched_priority = priority ;
  if (isActive) /* Active thread */
  {
    pthread_setschedparam(posixId, schedPolicy, &schedParams) ;
    return true ;
  }
  else /* Non active thread */
  {
    pthread_attr_setschedpolicy(&posixAttr, schedPolicy) ;
    pthread_attr_setschedparam(&posixAttr, &schedParams) ;
    return false ;
  }
}

bool PosixThread::getScheduling(int* p_schedPolicy , int* p_priority )
{
  int error ;
  sched_param schedParams ;
  schedParams.sched_priority = *p_priority ;
  if (isActive)
  {
    error = pthread_getschedparam(posixId, p_schedPolicy, &schedParams) ;
    cout<<"--- Return of pthread_getschedparam : "<<error<<endl ; 
    return true ;
  }
  else
  {
    error = pthread_attr_getschedparam(&posixAttr, &schedParams) ;
    cout<<"--- Return of pthread__attr_getschedparam : "<<error<<endl ; 
    error = pthread_attr_getschedpolicy(&posixAttr, p_schedPolicy) ;
    cout<<"--- Return of pthread__attr_getschedpolicy : "<<error<<endl ; 
    return false ;
  }
}

