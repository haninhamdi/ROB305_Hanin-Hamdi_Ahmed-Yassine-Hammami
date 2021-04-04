#include <iostream>
#include <sstream>
#include <string>
#include <cstring>
#include <cstdlib>
#include <time.h>
#include "time_library.h"
#include "Mutex.h"
#include <vector>
#include "Semaphore.h"

int main(int argc, char* argv[])
{
unsigned int counter = 20;
int nCons = 10 ;
int nProd = 10 ;
Semaphore producer(counter, 100);
Semaphore consumer(counter,100);

for (int i = 0 ; i < nProd;i++)  producer.give();
int prod_counter = producer.getCounter();

for (int i = 0 ; i < nCons;i++) consumer.take();
int cons_counter = consumer.getCounter();

std::cout << "---------------------------------------------------------------" << std::endl;
std::cout << "-------------------------- ROB305 TD4C ------------------------" << std::endl;
std::cout << "------------- Hanine HAMDI & Ahmed Yasine HAMMAMI -------------" << std::endl;
std::cout << "---------------------------------------------------------------" << std::endl;
std::cout << "Consumer counter : " << cons_counter << std::endl;
std::cout << "Producer counter : " << prod_counter << std::endl;

return 0;
}