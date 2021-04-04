#ifndef Looper_h_INCLUDED
#define Looper_h_INCLUDED

#include <climits>

class Looper
{
    public :
       void runLoop(unsigned int nLoops = UINT_MAX) ;
       unsigned int getSample() ;
       void stopLoop() ;
       void s_doStop(bool stop) ; 
    private :
       bool doStop ;
       unsigned int iLoop ;
};

#endif
