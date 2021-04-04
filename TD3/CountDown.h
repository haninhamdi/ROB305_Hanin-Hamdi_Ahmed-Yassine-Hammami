/********************************************
    Class CountDown doughter of the class
    PeriodicTimer : it's a PeriodicTimer
    which increments periodically an 
    unsigned int counter_ until it becomes 0 
    CountDown overrides the virtual method
    of the class Timer : callback() 
*********************************************/

#ifndef CountDown_h_INCLUDED 
#define CountDown_h_INCLUDED 

#include "PeriodicTimer.h" 

class CountDown : public PeriodicTimer 
{
     public :
       CountDown(unsigned int n_count) ;
       void s_counter(unsigned int n_count) ; 
       unsigned int a_counter() ; 
     private :
       void callback() override ;  
     private :
       unsigned int counter_ ;
};


#endif 
