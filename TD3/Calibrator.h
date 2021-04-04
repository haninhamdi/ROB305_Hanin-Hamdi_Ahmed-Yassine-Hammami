#ifndef Calibrator_h_INCLUDED
#define Calibrator_h_INCLUDED

#include <vector> 
#include "PeriodicTimer.cpp"
#include "Looper.cpp" 

using namespace std ;

class Calibrator : public PeriodicTimer
{
     private :
        double a ;
        double b ;
        vector<unsigned int> samples ;
        Looper looper ;
        unsigned int nSamples_ ; 
     public :
        Calibrator(double samplingPeriod_ms, unsigned int nSamples) ;
        unsigned int nLoops(double duration_ms) ;
        double a_A() ; // Accessor to private parameter a
        double a_B() ; // Accessor to private parameter b 
     protected :
        virtual void callback()  ;
};

#endif
