#include "IncrementorThread.h" 
#include "Thread.cpp" 

using namespace std ; 


IncrementorThread::IncrementorThread(volatile unsigned int* counter, volatile bool* pStop)
{
   this->counter_ = counter ; 
   this->pStop_ = pStop ; 
   localCounter_ = 0 ; 
}
unsigned int IncrementorThread::a_localCounter()
{
   return localCounter_ ; 
}

void IncrementorThread::run()
{
   while (not(*pStop_))
   {
      *counter_ += 1 ; 
      localCounter_ += 1 ; 
   }
   this->stopTime() ; 
}
