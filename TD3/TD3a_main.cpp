/***************************************************************
   RESPONSE to : TD3a 
   The aim of this script is to test the class Chrono ; We will
   wait for a certain duration given from the shell.
***************************************************************/

#include "Chrono.cpp"
#include <iostream> 
#include <cstdlib>
#include <unistd.h>

using namespace std ; 

int main(int argc, char* argv[])
{
    cout<< "------------------------------------------------------------" <<endl ;
    cout<< "----------------------- ROB305 TD3A ------------------------" <<endl ; 
    cout<< "--------- Hanin Hamdi & Ahmed Yassine Hammami --------------" <<endl ;
    cout<< "------------------------------------------------------------" <<endl ;
    
    
    /* We will verify wether the chrono duration is aqual to the waiting time */
    unsigned int waitTime_s ;
    if (argc > 1)
    {
         waitTime_s = stoi(argv[1], nullptr) ;
    }
    
    cout<< "waiting for  " << waitTime_s << "  seconds   "<<endl ; 
    
    /* Create a chrono */
    Chrono chrono ; 
    sleep(waitTime_s) ;
    chrono.stop() ; 
    cout << "Done! Chrono time =  " << chrono.lap() << "  millisecondes " << endl ; 
    return 0 ; 
}
