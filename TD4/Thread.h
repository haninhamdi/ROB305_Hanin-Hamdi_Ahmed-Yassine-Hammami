#ifndef Thread_h_INCLUDED
#define Thread_h_INCLUDED

#include "PosixThread.h" 

class Thread : public PosixThread 
{
   private : 
     double startTime_ms_ ; 
     double stopTime_ms_ ;
     bool started_ ; 
     pthread_t posixId ;
     pthread_attr_t posixAttr ; 
   public :
     Thread() ; 
     ~Thread() ; 
     bool start() ; 
     double startTime_ms() ;
     double stopTime_ms() ;
     void stopTime() ; 
     double execTime_ms() ; 
     static void sleep_ms(double delay_ms) ; 
   protected :
     virtual void run() = 0 ;
   private :
       static void* call_run(void* v_thread) ;    
};

#endif 
