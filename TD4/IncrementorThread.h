#ifndef IncrementorThread_h_INCLUDED
#define IncrementorThread_h_INCLUDED

#include "Thread.h" 

class IncrementorThread : public Thread 
{
  private : 
    volatile unsigned int* counter_ ; 
    unsigned int localCounter_ ; 
    volatile bool* pStop_ ; 
  private :
    void run() override ; 
  public :
    IncrementorThread(volatile unsigned int* counter, volatile bool* pStop) ; 
    unsigned int a_localCounter() ; 
    
};
#endif 
