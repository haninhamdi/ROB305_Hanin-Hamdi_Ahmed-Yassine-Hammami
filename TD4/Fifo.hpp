#ifndef Fifo_HPP
#define Fifo_HPP

#include <deque>
#include <exception>
#include "Mutex.h"

#include <iostream>
#include <mutex>
#include <condition_variable>
#include <thread>
#include "Mutex.h"
#include <deque>
#include <exception>

template <typename T>
class Fifo {
private :
  std::deque<T> elements; 
  

public:
    Mutex m_mutex;
    // exception class for pop(timeout_ms) with empty queue
    class ReadEmptyQueue : public std::exception {
      public:
        virtual const char* what() const throw() {
            return "read empty queue";
        }
    };

    // number of elements
    typename std::deque<T>::size_type size() const {
        return elements.size();
    }

    // is queue empty?
    bool empty() const {
        return elements.empty();
    }

    // insert element into the queue
    void push(const T& elem) {
        Mutex::Monitor monitor(m_mutex);

        monitor.wait();
        m_mutex.unlock();
        elements.push_back(elem);

        m_mutex.lock();
        monitor.notify();
   }

  // remove next element from the queue and return its value
    T pop() {
    
        Mutex::Monitor monitor(m_mutex);
        monitor.wait();
        m_mutex.unlock();
        T elem(elements.front());
        elements.pop_front();
      
        m_mutex.lock();
        monitor.notify();
        return elem;
  }

  T pop(double timeout_ms) {
    
        Mutex::Monitor monitor(m_mutex);
        monitor.wait(timeout_ms);
        m_mutex.unlock();

        if (elements.empty()) {
            throw ReadEmptyQueue();
        }
        T elem(elements.front());
        elements.pop_front();
        m_mutex.lock();
        monitor.notifyAll();
        return elem;
  }
};

#endif /* Fifo_HPP */