#include "Thread.h" 
#include <time.h>
#include "PosixThread.cpp"

using namespace std ; 

Thread::Thread() : PosixThread()
{
   cout<<"----Init thread -----"<<endl ; 
   started_ = false ; 
}

Thread::~Thread() 
{
}

bool Thread::start() 
{
  if (not(started_))
  {
     cout<<"---Starting Thread ---"<<endl ; 
     /* Set startTime to current time */ 
     timespec startTime_ts = timespec_now(); 
     startTime_ms_ = timespec_to_ms(startTime_ts) ; 
     started_ = true ; 
  
     cout<<"Waiting ..."<<endl ; 
     PosixThread::start(call_run, (void*) this) ; 
     cout<<"----Thread started ----"<<endl ; 
     return true ;  
  }
  else 
  {
     cout<<"Thread already started"<<endl ; 
     return false ; 
  }
}

double Thread::startTime_ms()
{
  return startTime_ms_ ; 
}

double Thread::stopTime_ms()
{
  return stopTime_ms_ ; 
}

void Thread::stopTime() 
{
  timespec stopTime_ts ;
  stopTime_ts = timespec_now(); 
  stopTime_ms_ = timespec_to_ms(stopTime_ts) ; 
}

double Thread::execTime_ms()
{
  return stopTime_ms_ - startTime_ms_ ; 
}

void Thread::sleep_ms(double delay_ms)
{
  timespec delay_ts = timespec_from_ms(delay_ms) ;
  cout<<"----Start sleep for : "<<delay_ms<<"  ms---"<<endl ; 
  timespec_wait(delay_ts) ; 
  cout<<"----Finished sleep for : "<<delay_ms<<"  ms---"<<endl ; 
}

void* Thread::call_run(void* v_thread)
{ 
   Thread* pThread = (Thread*) v_thread ;
   pThread->run() ;
   return v_thread ; 
}

