#ifndef CpuLoop_h_INCLUDED
#define CpuLoop_h_INCLUDED

#include "Looper.h" 
#include "Calibrator.cpp" 

class CpuLoop : public Looper
{
    public :
       CpuLoop(Calibrator& calibrator) ;
       void runTime(double duration_ms) ;
    private :
       Calibrator& calibrator_ ;
};

#endif
