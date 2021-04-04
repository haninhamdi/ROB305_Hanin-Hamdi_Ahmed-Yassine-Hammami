/***************************************************************
   RESPONSE to : TD3c
   The aim of this script is to run a loop during a given time.
   So we have to convert the duration in milleseconds into
   equivalent number of loops using a calibrator of an object
   looper which runs a loops nLoops times. 
***************************************************************/

#include <iostream>
#include <time.h> 
#include "CpuLoop.cpp" 
#include "/home/hani.hamdi/ROB305/TD1/time_library.h"


int main(int argc, char* argv[])
{
   cout<< "------------------------------------------------------------" <<endl ;
   cout<< "----------------------- ROB305 TD3C ------------------------" <<endl ; 
   cout<< "--------- Hanin Hamdi & Ahmed Yassine Hammami --------------" <<endl ;
   cout<< "------------------------------------------------------------" <<endl ;
    
    
  double duration_ms, duration_ms_test ;
  double samplingPeriod_ms ;
  unsigned int nSamples ;
  struct timespec debut, fin, duration ; 

  /* Read the parameters from the shell */ 
  if (argc > 3)
  {
    duration_ms = stoi(argv[1], nullptr, 10) ;
    samplingPeriod_ms = stoi(argv[2], nullptr, 10) ;
    nSamples = strtoul(argv[3], nullptr, 10) ;
  }
  
  /* Compute an appropriate calibration */ 
  Calibrator calibrator(samplingPeriod_ms,nSamples) ;
  Calibrator &calibrator_ref = calibrator ; 
  CpuLoop cpuLoop(calibrator_ref) ;

  /* Run the looper for the given duration_ms : the conversion from 
     duration to nLoops done internally.
  */ 
  cpuLoop.s_doStop(false) ; 
  
  /* Use CLOCK_REALTIME to test the accuracy of the code */ 
  clock_gettime(CLOCK_REALTIME, &debut) ;
  cpuLoop.runTime(duration_ms) ;
  clock_gettime(CLOCK_REALTIME, &fin) ;
  
  duration = fin - debut ; 
  duration_ms_test = timespec_to_ms(duration) ; 
  cout<<"TEST of the calibration : RealTime Duration = "<<duration_ms_test<<endl ; 
  return 0 ;
}
