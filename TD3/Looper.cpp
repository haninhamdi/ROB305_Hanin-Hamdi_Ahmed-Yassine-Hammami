#include "Looper.h"
#include <limits>

void Looper::runLoop(unsigned int nLoops)
{
    iLoop = 0 ;
    
    while (iLoop < nLoops and not(doStop) )
    {
       iLoop += 1 ;
    }
}

unsigned int Looper::getSample()
{
    return iLoop ;
}

void Looper::stopLoop()
{
    doStop = true ;
}

void Looper::s_doStop(bool stop)
{
   doStop = stop ; 
}
