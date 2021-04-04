#include <iostream>
#include <sstream>
#include <string>
#include <cstring>
#include <cstdlib>
#include <time.h>
#include <pthread.h>
#include "time_library.h"
#include <vector>

struct incrData {

  // protected mode 
  bool protected_test = false;
  unsigned int nLoops;
  double counter;
  unsigned nTasks;
  pthread_mutex_t *mutex ;
};


void incr(unsigned int nLoops, double* pCounter)
{
  for (unsigned int i=0; i<nLoops; i++) {
  *pCounter += 1.0;
  }
}

void* call_incr(void* v_data) {
  incrData* p_data = (incrData*) v_data;
  if (p_data->protected_test == false)
  {
      incr(p_data->nLoops, &p_data->counter);
  }
  else if (p_data->protected_test == true)
  {
      pthread_mutex_lock(p_data->mutex);
      incr(p_data->nLoops, &p_data->counter);
      pthread_mutex_unlock(p_data->mutex);
  }
  
  
  return 0;
}

pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;

int main(int argc, char* argv[])
{


struct incrData data;

if (argc > 3)
  {
    if (std::string(argv[3]) == "true") data.protected_test = true;
    else if (std::string(argv[3]) == "false") data.protected_test = false ;
    else 
    {
        std::cout << "Unknown boolean input : " << argv[3] << std::endl;  
        return 1 ;
    }
  }

if (argc > 4)
  {
    std::cerr << "Not expecting more than 3 arguments " << std::endl;
    return 1;
  }

  data.nLoops = atoi(argv[1]);
  data.counter = 0.0;
  data.nTasks = atoi(argv[2]);
  data.mutex = &mutex;

  

  struct timespec starttime, endtime, duration;

  clock_gettime(CLOCK_REALTIME, &starttime);

  pthread_t incrementThread[data.nTasks];
  //std::vector<pthread_t> incrementThread(nTasks);
 
  for (unsigned int k=0; k<data.nTasks; k++) {
    pthread_create(&incrementThread[k], nullptr, call_incr, (void*) &data);
  }
  pthread_mutex_destroy(&mutex);

  clock_gettime(CLOCK_REALTIME, &endtime);

  for (unsigned int j=0; j<data.nTasks; j++) pthread_join(incrementThread[j],nullptr);

  duration.tv_sec = endtime.tv_sec - starttime.tv_sec;
  if (endtime.tv_nsec < starttime.tv_nsec) {
duration.tv_sec -= 1;
endtime.tv_nsec += 1000000000;
}
duration.tv_nsec = endtime.tv_nsec - starttime.tv_nsec;
std::cout << "---------------------------------------------------------------" << std::endl;
std::cout << "-------------------------- ROB305 TD2C ------------------------" << std::endl;
std::cout << "------------- Hanine HAMDI & Ahmed Yasine HAMMAMI -------------" << std::endl;
if(data.protected_test==0) 
{
    std::cout << "------------------------- Normal Mode -------------------------" << std::endl;
}
else 
{
    std::cout << "------------------- Mutex Protected Mode ----------------------" << std::endl;
}
std::cout << "---------------------------------------------------------------" << std::endl;
std::cout << "duration =" << duration.tv_sec << "," << duration.tv_nsec << std::endl;
std::cout << "nLoops =" << data.nLoops << std::endl;
std::cout << "counter =" << data.counter << std::endl;
return 0;
}