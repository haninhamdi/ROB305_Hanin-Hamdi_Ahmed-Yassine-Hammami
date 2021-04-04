#ifndef PosixThread_h_INCLUDED
#define PosixThread_h_INCLUDED

#include <pthread.h>

class PosixThread
{
  public :
    class Exception ;
  private :
    pthread_t posixId ;
    pthread_attr_t posixAttr ;
  protected :
    bool isActive ;
  public :
    PosixThread() ;
    PosixThread(pthread_t posixId) ;
    ~PosixThread() ;
    void start(void* (*threadFunc) (void*), void* threadArg) ;
    void join() ;
    bool join(double timeout_ms) ;
    bool setScheduling(int schedPolicy , int priority) ;
    bool getScheduling(int* p_schedPolicy = nullptr , int* p_priority = nullptr) ;
};

class PosixThread::Exception
{
   public :
     char* throwException() ;
};


#endif
