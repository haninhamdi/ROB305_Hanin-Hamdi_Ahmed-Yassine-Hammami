#include "Calibrator.h"

using namespace std ; 

Calibrator::Calibrator(double samplingPeriod_ms, unsigned int nSamples) : nSamples_(nSamples)
/* nSamples must be pair */
{
    start(samplingPeriod_ms) ; 
    looper.runLoop() ;
    
    /****************************/
    /* Linear regression */ 
    unsigned int half_nSamples = (unsigned int) (nSamples_ / 2) ; 
    
    /* Compute the sum of the first half of the samples */ 
    unsigned int first_half_samples = 0 ; 
    for (unsigned int i =0; i < half_nSamples; i++)
    {
        first_half_samples += samples.at(i) ; 
    } 
    /* Compute the sum of the second half of the samples */ 
    unsigned int second_half_samples = 0 ; 
    for (unsigned int i = half_nSamples ; i < nSamples_; i++)
    {
        second_half_samples += samples.at(i) ; 
    } 

    /* Compute a and b as a mean between the first half and the second half of samples */ 
    double samplingPeriod_s = samplingPeriod_ms/1e3 ; 
    a = 4*(second_half_samples - first_half_samples) / (samplingPeriod_s*nSamples_*nSamples_) ; 
    b = (second_half_samples + first_half_samples - a*samplingPeriod_s*nSamples_*(nSamples_+1)/2) / nSamples_ ; 
}

unsigned int Calibrator::nLoops(double duration_ms)
{
    double n_loops = (double) (a*duration_ms/1e3 + b) ;
    return n_loops ;
}

void Calibrator::callback()
{
    samples.push_back(looper.getSample()) ;
    cout<< "Measure "<<samples.size()<<" : "<<samples.back()<<endl ; 
    
    if (samples.size() >= nSamples_)
    {
        looper.stopLoop() ; 
    }
}

double Calibrator::a_A()
{
  return a ;
}

double Calibrator::a_B()
{
  return b ; 
}
