/***********************************************************
     Class used to assimilate the function of a chronometer
***********************************************************/

#ifndef Chrono_h_INCLUDED 
#define Chrono_h_INCLUDED 

#include <time.h> 

class Chrono 
{
    private :
       timespec startTime_ ; 
       timespec stopTime_ ;
    public :
       Chrono() ; 
       void stop() ; 
       void restart() ;
       bool isActive() const ; 
       double startTime() const ;
       double stopTime() const ; 
       double lap() const ;
};

#endif
