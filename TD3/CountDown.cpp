#include "CountDown.h" 
#include "PeriodicTimer.cpp" 

using namespace std ; 

CountDown::CountDown(unsigned int n_count) : PeriodicTimer(), counter_(n_count) 
{ 
   /* Constructor for countDown */ 
}

void CountDown::s_counter(unsigned int n_count)
{
    /* Setter of the private parameter n_count */
    counter_ = n_count ;
}

unsigned int CountDown::a_counter()
{
    /* Accessor to the parameter counter_ */ 
    return counter_ ;
}


void CountDown::callback()
{ 
    /* Implementation of the virtual method of the class Timer : decrement the parameter counter_ */
    cout<<"counter = "<< a_counter()<< endl ; 
    counter_ -= 1 ; 
}
