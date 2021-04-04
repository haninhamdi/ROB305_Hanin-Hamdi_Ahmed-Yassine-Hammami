#include "CpuLoop.h"

using namespace std ; 

CpuLoop::CpuLoop(Calibrator& calibrator) : calibrator_(calibrator) 
{
}
void CpuLoop::runTime(double duration_ms)
{

  unsigned int nLoops = calibrator_.a_A()*duration_ms/1e3 + calibrator_.a_B() ;
  cout<<"nLoops " <<nLoops<<endl ; 
  runLoop(nLoops) ; 
}
