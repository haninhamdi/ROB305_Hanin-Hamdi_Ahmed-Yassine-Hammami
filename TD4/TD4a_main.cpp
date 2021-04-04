/******************************************************************
   RESPONSE to : TD4a  
   This script is used to test the classes Thread, PosixThread and
   IncrementorThread. We create 3 IncrementorThread whith 
   different priorities and which increment in parallel a commun 
   counter.   
*******************************************************************/

#include "IncrementorThread.cpp" 

using namespace std ;

struct Data {
   volatile bool stop ; 
   volatile unsigned int counter ;
   pthread_mutex_t mutex ;  
} ; 

int main(/*int argc, char* argv[]*/)
{
  cout<< "------------------------------------------------------------" <<endl ;
  cout<< "----------------------- ROB305 TD4A ------------------------" <<endl ; 
  cout<< "--------- Hanin Hamdi & Ahmed Yassine Hammami --------------" <<endl ;
  cout<< "------------------------------------------------------------" <<endl ;
  
  Data data = {false, 0} ; 
  pthread_mutex_init(&data.mutex, nullptr) ; 
  
  int schedPolicy = SCHED_RR ; 
  int priority_1 = 10 ; 
  int priority_2 = 15 ; 
  int priority_3 = 20 ; 
  
  bool test_active_1, test_active_2, test_active_3 ; 
  
  /* Create 3 identical objects incrementorThread */
  IncrementorThread incrementorThread_1(&(data.counter), &(data.stop)) ; 
  cout<<"----- First thread initiated ------"<< endl ; 
  IncrementorThread incrementorThread_2(&(data.counter), &(data.stop)) ;
  cout<<"----- Second thread initiated ------"<< endl ;
  IncrementorThread incrementorThread_3(&(data.counter), &(data.stop)) ;
  cout<<"----- Third thread initiated ------"<< endl ;
  
  /* Set the priority and the policy for the threads */
  test_active_1 = incrementorThread_1.setScheduling(schedPolicy , priority_1) ; 
  test_active_2 = incrementorThread_2.setScheduling(schedPolicy , priority_2) ; 
  test_active_3 = incrementorThread_3.setScheduling(schedPolicy , priority_3) ; 
  
  /* Test the outputs of setScheduling */ 
  cout<<"---- First thread isActive = "<< (bool) test_active_1 << endl ; 
  cout<<"---- Scond thread isActive = "<< (bool) test_active_2 << endl ; 
  cout<<"---- Third thread isActive = "<< (bool) test_active_3 << endl ; 
  
  /* Start the 3 threads */
  test_active_1 = incrementorThread_1.start() ;
  cout<<"----- First thread started -----"<< endl ; 
  test_active_2 = incrementorThread_2.start() ;
  cout<<"----- Second thread started ----"<< endl ;
  test_active_3 = incrementorThread_3.start() ;
  cout<<"----- Third thread started -----"<< endl ;
  
  for (char cmd = 'r' ; cmd != 's' ; cin >> cmd)
  {
     cout << "Type 's' to stop the threads " << flush ; 
  }
   
  data.stop = true ; 
  pthread_mutex_destroy(&data.mutex) ; 
  
  incrementorThread_1.join() ; 
  cout<<"---- First thread joined -----"<< endl ; 
  incrementorThread_2.join() ; 
  cout<<"---- Second thread joined ----"<< endl ; 
  incrementorThread_3.join() ; 
  cout<<"---- Third thread joined -----"<< endl ;
  
  /* Print the execution time for each thread */
  cout<<"---- Execution time of Thread 1 = "<<incrementorThread_1.execTime_ms()<<endl ; 
  cout<<"---- Execution time of Thread 2 = "<<incrementorThread_2.execTime_ms()<<endl ; 
  cout<<"---- Execution time of Thread 3 = "<<incrementorThread_3.execTime_ms()<<endl ; 
  
  /* Test if the priority is respected using the localCounter_ of each thread */
  cout<<"----------------- TEST PRIORITY ------------------------" << endl ;
  cout<<"---- Incrementations done by THREAD 1 = "<<incrementorThread_1.a_localCounter()<<endl ; 
  cout<<"---- Incrementations done by THREAD 2 = "<<incrementorThread_2.a_localCounter()<<endl ; 
  cout<<"---- Incrementations done by THREAD 3 = "<<incrementorThread_3.a_localCounter()<<endl ; 
  cout<<"---- Final value of the commun counter = "<<data.counter<<endl ; 
  
  return 0 ; 
}

