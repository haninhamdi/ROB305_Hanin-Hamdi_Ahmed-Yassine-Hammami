#include <time.h> 
#include <pthread.h>
#include <climits> 
#include "Mutex.h"
#include "Semaphore.h"


Semaphore::Semaphore()
{
    counter_ = 0 ;
    maxCount_ = UINT_MAX;
    mutex_ = Mutex();
}

Semaphore::~Semaphore()
{

}
Semaphore::Semaphore(unsigned int initCount = 0 ,unsigned int maxCount = UINT_MAX) 
{
    counter_ = initCount ;
    maxCount_ = maxCount;
    mutex_ =Mutex();
}
void Semaphore::take()
{   
    
    Mutex::Monitor monitor(mutex_);
    
    mutex_.lock();
    if(counter_ == 0){
        monitor.wait();
    }
    counter_--;
    mutex_.unlock();   
}

int Semaphore::getCounter()
{
    return counter_;
}
bool Semaphore::take(double timeout_ms)
{   
    bool state = true ;
    Mutex::Monitor monitor(mutex_);
    
    mutex_.lock();
    while(counter_ == 0){
        state = monitor.wait(timeout_ms);
    }
    counter_--;
    mutex_.unlock();
    return state ;  
}

void Semaphore::give()
{   
    
    Mutex::Monitor monitor(mutex_);
    
    mutex_.lock();
    if(counter_!= maxCount_) counter_++;
    mutex_.unlock();
    if(counter_== 0)  monitor.notify();
}