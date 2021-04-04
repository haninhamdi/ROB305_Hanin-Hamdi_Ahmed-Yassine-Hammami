#include <iostream>
#include <mutex>
#include <condition_variable>
#include <thread>
#include "Mutex.h"
#include <deque>
#include <exception>
#include "Fifo.hpp"

class Producer {
public:
  Producer(Fifo<int>& bq, int id):m_bq(bq), m_id(id) {
  }
  
  void operator()() {
    for (int i = 0; i < 9; i++) {
      m_bq.push(i);
    }
  }
private:
  Fifo<int> &m_bq;
  int m_id;
};

class Consumer {
public:
  Consumer(Fifo <int>& bq, int id):m_bq(bq), m_id(id) {
  }

  void operator()() {
    std::cout << "Reading from queue: \n";
    for (int i = 0; i < 10; i++) {
      int value;
      value = m_bq.pop();
      std::cout << "int Value : "<< value << " \n";
    }
    std::cout << std::endl;
  }
private:
  Fifo<int> &m_bq;
  int m_id;
};

int main() {
    Fifo <int>q;

    std::cout << "---------------------------------------------------------------" << std::endl;
    std::cout << "-------------------------- ROB305 TD4D ------------------------" << std::endl;
    std::cout << "------------- Hanine HAMDI & Ahmed Yasine HAMMAMI -------------" << std::endl;
    std::cout << "---------------------------------------------------------------" << std::endl;
  
    std::thread producerThread (Producer(q, 0));
    std::thread consumerThread (Consumer(q, 1));
    
    pthread_mutex_destroy(&q.m_mutex.posixId) ;
    producerThread.join();
    consumerThread.join();
    
}