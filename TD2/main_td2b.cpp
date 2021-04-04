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
  unsigned int nLoops;
  double counter;
  unsigned nTasks;
};


void incr(unsigned int nLoops, double* pCounter)
{
  for (unsigned int i=0; i<nLoops; i++) {
  *pCounter += 1.0;
  }
}

void* call_incr(void* v_data) {
  incrData* p_data = (incrData*) v_data;
  
  incr(p_data->nLoops, &p_data->counter);
  
  return 0;
}


int main(int argc, char* argv[])
{
 
if (argc > 4)
  {
    std::cerr << "Not expecting more than 3 arguments " << std::endl;
    return 1;
  }

struct incrData data;
data.nLoops = atoi(argv[1]);
data.counter = 0.0;
data.nTasks = atoi(argv[2]);

int schedPolicy = SCHED_OTHER;

if (argc > 3)
{
if (std::string(argv[3]) == "SCHED_RR") 
 {
     schedPolicy = SCHED_RR ;
 }

else if (std::string(argv[3]) == "SCHED_FIFO")
 {
     schedPolicy = SCHED_FIFO ;
 }

else 
{
  std::cout << "Unknown scheduling policy : " << argv[3] << std::endl;  
  return 1;
}
}

pthread_attr_t attr;
pthread_attr_init(&attr);
pthread_attr_setschedpolicy(&attr, schedPolicy);
struct sched_param schedParam;

if(schedPolicy == SCHED_OTHER) {
    schedParam.sched_priority = 0;
}
else {
    schedParam.sched_priority = 9;
}

pthread_attr_setschedparam(&attr,&schedParam);
  

struct timespec starttime, endtime, duration;
clock_gettime(CLOCK_REALTIME, &starttime);

pthread_t incrementThread[data.nTasks];
  
for (unsigned int k=0; k<data.nTasks; k++) {
    pthread_create(&incrementThread[k], &attr, call_incr, (void*) &data);
  }

clock_gettime(CLOCK_REALTIME, &endtime);

pthread_attr_destroy(&attr);
for (unsigned int j=0; j<data.nTasks; j++) pthread_join(incrementThread[j],nullptr);

duration.tv_sec = endtime.tv_sec - starttime.tv_sec;
if (endtime.tv_nsec < starttime.tv_nsec) 
{
    duration.tv_sec -= 1;
    endtime.tv_nsec += 1000000000;
}
duration.tv_nsec = endtime.tv_nsec - starttime.tv_nsec;


std::cout << "---------------------------------------------------------------" << std::endl;
std::cout << "-------------------------- ROB305 TD2B ------------------------" << std::endl;
std::cout << "------------- Hanine HAMDI & Ahmed Yasine HAMMAMI -------------" << std::endl;
std::cout << "---------------------------------------------------------------" << std::endl;
if (argc > 3) std::cout << "Scheduling type : " << argv[3] << std::endl;
else std::cout << "Scheduling policy : SCHED_OTHER" << std::endl;
std::cout << "Duration =" << duration.tv_sec << "," << duration.tv_nsec << std::endl;
std::cout << "nLoops =" << data.nLoops << std::endl;
std::cout << "counter =" << data.counter << std::endl;
return 0;
}