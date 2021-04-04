/***************************************************************
   RESPONSE to : TD1a 
   This script is used to test the functions implemented in 
   time_library.cpp
***************************************************************/

#include "time_library.cpp" 
#include <iostream> 
#include <unistd.h>

using namespace std ; 

int main(int ,char* argv[])
{
    cout<< "------------------------------------------------------------" <<endl ;
    cout<< "------------------- ROB305 TD1A ----------------------------" <<endl ; 
    cout<< "--------- Hanin Hamdi & Ahmed Yassine Hammami --------------" <<endl ;
    cout<< "------------------------------------------------------------" <<endl ;
     
    double delay_ms, delay_ms_test, debut_ms, debut_ms_test, fin_ms, debut_ms_negate; 
    struct timespec debut_ts, fin_ts, duration_ts, real_time_duration_ts ,debut_ts_negate; 
    bool test ; 
    
    delay_ms = stoi(argv[1], nullptr, 10) ;
    /* Test timespec_to_ms and timespec_from_ms --> done with succes */  
    duration_ts = timespec_from_ms(delay_ms) ;
    delay_ms_test = timespec_to_ms(duration_ts) ;
    cout<<"Given delay_ms = "<<delay_ms<<" ms"<<endl; 
    cout<<"timespec_from_ms :" <<"Seconds = "<< duration_ts.tv_sec << "nanosecons = " << duration_ts.tv_nsec << endl ; 
    cout<<"timespec_to_ms : "<<"delay_ms_test = "<<delay_ms_test<<endl; 
    if (delay_ms == delay_ms_test)
        cout<<"test correct"<<endl;
    else 
        cout<<"test failed"<<endl;
    cout<<"  "<<endl ;

    /* Test of timespec_now(), operator- and timespec_wait --> done with success but nanosleep is not very precise */ 
    cout<<"TEST : timespec_now(), operator- and timespec_wait(..)"<<endl; 
    debut_ts = timespec_now() ; 
    timespec_wait(duration_ts) ; 
    fin_ts = timespec_now() ; 
    real_time_duration_ts = fin_ts - debut_ts ; 
    delay_ms_test = timespec_to_ms(real_time_duration_ts) ; 
    cout<<"real_time_duration_ts :"<<"Seconds = "<<real_time_duration_ts.tv_sec<<"Nanoseconds = "<<real_time_duration_ts.tv_nsec<< endl ; 
    cout<<"Given delay_ms = "<<delay_ms<<" ms"<<endl; 
    cout<<"delay_ms_test = "<<delay_ms_test<<endl;
    if (delay_ms == delay_ms_test)    // Here the test is expected to fail because nanoslepp is not very precise 
        cout<<"test correct"<<endl;
    else 
        cout<<"test failed"<<endl;
    cout<<"  "<<endl ;

    /* Test of operators */
    /* operator+ */
    cout<<"TEST : operator+"<<endl ; 
    debut_ms = timespec_to_ms(debut_ts) ; 
    fin_ts = debut_ts + duration_ts ;
    fin_ms = timespec_to_ms(fin_ts) ; 
    delay_ms_test = fin_ms - debut_ms ; 
    cout<<"delay_ms_test = " <<delay_ms_test<<" given delay_ms = "<< delay_ms <<endl ; 
    if (delay_ms == delay_ms_test)
        cout<<"test correct"<<endl;
    else 
        cout<<"test failed"<<endl;
    cout<<"  "<<endl ;
    
    /* operator- */
    cout<<"TEST : operator-"<<endl ; 
    debut_ts = fin_ts - duration_ts ;
    debut_ms = timespec_to_ms(debut_ts) ; 
    delay_ms_test = fin_ms - debut_ms ; 
    cout<<"delay_ms_test = " <<delay_ms_test<<" given delay_ms = "<< delay_ms <<endl ; 
    if (delay_ms == delay_ms_test)
        cout<<"test correct"<<endl;
    else 
        cout<<"test failed"<<endl;
    cout<<"  "<<endl ;

    /* Operator negation */ 
    cout<<"TEST : operator negation "<<endl ; 
    debut_ts_negate = -debut_ts ; 
    debut_ms_negate = timespec_to_ms(debut_ts_negate) ; 
    cout<<"debut_ms = " << debut_ms <<" debut_ms_negate = " << debut_ms_negate << endl ;
    if (debut_ms + debut_ms_negate == 0.0)
        cout<<"test correct"<<endl;
    else 
        cout<<"test failed"<<endl;
    cout<<"  "<<endl ;

    /* Operator += */ 
    cout<<"TEST : operator+= "<<endl ;
    debut_ts += duration_ts ; // it has to be equal to fin_ts 
    debut_ms_test = timespec_to_ms(debut_ts) ; 
    cout<<"right fin_ms = " <<fin_ms << " calculated fin_ms += "<<debut_ms_test << endl ;
    if (fin_ms == debut_ms_test)
        cout<<"test correct"<<endl;
    else 
        cout<<"test failed"<<endl;
    cout<<"  "<<endl ;
    
    /* Operator -= */ 
    cout<<"TEST : operator-= "<<endl ;
    fin_ts -= duration_ts ; // it has to be equal to fin_ts 
    fin_ms = timespec_to_ms(fin_ts) ; 
    cout<<"right debut_ms = " <<debut_ms << " calculated debut_ms -= "<<fin_ms << endl ;
    if (debut_ms == fin_ms)
        cout<<"test correct"<<endl;
    else 
        cout<<"test failed"<<endl;
    cout<<"  "<<endl ;
    
    /* Operator == */ 
    cout<<"TEST : operator == "<<endl ;
    debut_ts = fin_ts - duration_ts ; 
    test = debut_ts == fin_ts ; 
    if (test == true )
         cout<<"test1 failed"<<endl ;
    else 
         cout<<"test1 correct"<<endl ; 
    test = debut_ts == debut_ts ; 
    if (test == false )
         cout<<"test2 failed"<<endl ;
    else 
         cout<<"test2 correct"<<endl ; 
    cout<<"  "<<endl ;
    
    /* Operator != */ 
    cout<<"TEST : operator != "<<endl ;
    test = debut_ts != fin_ts ; 
    if (test == false )
         cout<<"test1 failed"<<endl ;
    else 
         cout<<"test1 correct"<<endl ; 
    test = debut_ts != debut_ts ; 
    if (test == true )
         cout<<"test2 failed"<<endl ;
    else 
         cout<<"test2 correct"<<endl ; 
    cout<<"  "<<endl ;
         
    /* Operator > */ 
    cout<<"TEST : operator > "<<endl ;
    test = debut_ts > fin_ts ; 
    if (test == true )
         cout<<"test1 failed"<<endl ;
    else 
         cout<<"test1 correct"<<endl ; 
    test = fin_ts > debut_ts ; 
    if (test == false )
         cout<<"test2 failed"<<endl ;
    else 
         cout<<"test2 correct"<<endl ;
    cout<<"  "<<endl ; 
        
    /* Operator < */ 
    cout<<"TEST : operator > "<<endl ;
    test = debut_ts < fin_ts ; 
    if (test ==false )
         cout<<"test1 failed"<<endl ;
    else 
         cout<<"test1 correct"<<endl ; 
    test = fin_ts < debut_ts ; 
    if (test == true )
         cout<<"test2 failed"<<endl ;
    else 
         cout<<"test2 correct"<<endl ;
    cout<<"  "<<endl ;
    
    
    return 0 ; 

}
