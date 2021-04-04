/***************************************************************
   RESPONSE to : TD3b 
   The aim of this script is to create a countdown which 
   decrements an unsigned int until zero with a given frequency
   Please enter while execution the initial counter_ and the 
   frequency in Hz. 
***************************************************************/

#include <time.h>
#include <signal.h> 
#include <iostream>
#include "CountDown.cpp"   

using namespace std ; 

int main(int argc, char* argv[])
{

    cout<< "------------------------------------------------------------" <<endl ;
    cout<< "----------------------- ROB305 TD3B ------------------------" <<endl ; 
    cout<< "--------- Hanin Hamdi & Ahmed Yassine Hammami --------------" <<endl ;
    cout<< "------------------------------------------------------------" <<endl ;
    
    
    unsigned int n_counter ; 
    double duration_ms ; 
    double frequency ; 
    
    /* Read the initialization of the counter and the frequency from the shell */ 
    if (argc > 2)
    {
        n_counter = stoi(argv[1], nullptr, 10) ; 
        frequency = stoi(argv[2], nullptr, 10) ; 
    }
    /* Calculate the duration of the timer in milliseconds*/ 
    duration_ms = 1e3/frequency ; 
    
    /* Create a countdown*/ 
    CountDown countdown(n_counter) ; 
    
    /* Start the countdown*/ 
    countdown.start(duration_ms) ;  
    
    /* Wait until countdown.counter_ becomes 0 */
    while (countdown.a_counter() + 1 != 0)
    {
        // wait
    }
    return 0 ; 
}
