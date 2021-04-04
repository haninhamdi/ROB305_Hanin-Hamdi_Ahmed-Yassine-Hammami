#include <time.h> 
#include <iostream>
#include "time_library.h" 

using namespace std ;

/*--------------------------------------------------------*/
/* Functions */

double timespec_to_ms(const timespec& time_ts)   // tested 
{
    double time_ms ;
    time_ms = time_ts.tv_sec*1e3 + (double) time_ts.tv_nsec/(1e6) ; 
    return time_ms ; 
}

timespec timespec_from_ms(double time_ms)       // tested 
{
    struct timespec time_ts ;
    time_ts.tv_sec = (double) time_ms/1e3 ; 
    time_ts.tv_nsec = (time_ms - (double) time_ts.tv_sec*1e3)*1e6 ; 
    if (time_ts.tv_nsec < 0) 
    { 
        time_ts.tv_sec -= 1 ;
        time_ts.tv_nsec += 1e9 ;
    }
    return time_ts ; 
}

timespec timespec_now()                       // tested 
{
    struct timespec time_now ;
    clock_gettime(CLOCK_REALTIME, &time_now) ;
    return time_now ;   
}

timespec timespec_negate(const timespec& time_ts) // tested 
{
    struct timespec time_ts_negate ; 
    if (time_ts.tv_nsec == 0 ) 
    {
        time_ts_negate.tv_sec = - time_ts.tv_sec ; 
        time_ts_negate.tv_nsec = 0 ; 
    }
    else 
    {
        time_ts_negate.tv_sec = - time_ts.tv_sec - 1; 
        time_ts_negate.tv_nsec = - time_ts.tv_nsec + 1e9 ; 
    }
    return time_ts_negate ;
}

timespec timespec_add(const timespec& time1_ts, const timespec& time2_ts)  // tested within the operator+
{
    struct timespec time_ts_sum ; 
    time_ts_sum.tv_sec = time1_ts.tv_sec + time2_ts.tv_sec ;
    time_ts_sum.tv_nsec = time1_ts.tv_nsec + time2_ts.tv_nsec ;
    if ( time_ts_sum.tv_nsec >= 1e9)
    {
        time_ts_sum.tv_nsec -= 1e9 ;
        time_ts_sum.tv_sec  += 1 ;
    }
    return time_ts_sum ;
}

timespec timespec_subtract(const timespec& time1_ts, const timespec& time2_ts) // Here we do always time2_ts - time1_ts  
   // tested within the operator- 
{
    struct timespec time_ts_diff ;
    time_ts_diff.tv_sec = time2_ts.tv_sec - time1_ts.tv_sec ;
    time_ts_diff.tv_nsec = time2_ts.tv_nsec - time1_ts.tv_nsec ;
    if (time_ts_diff.tv_nsec < 0 )
    {
         time_ts_diff.tv_sec -= 1 ;
         time_ts_diff.tv_nsec += 1e9 ;
    }
    return time_ts_diff ;
}

timespec timespec_wait(const timespec& delay_ts)  // tested 
{
    struct timespec rem ;
    int sleep_return = nanosleep(&delay_ts, &rem) ;
    cout<<"Sleep counter = "<<sleep_return<<endl;
    
    return rem ;   /* = NULL if sleep_return == 0 and the remaining duration otherwise */ 
}


/*--------------------------------------------------------*/
/* Operators */

timespec operator- (const timespec& time_ts)   // tested 
{
    return timespec_negate(time_ts) ;  
}

timespec operator+ (const timespec& time1_ts, const timespec& time2_ts)  // tested 
{
    return timespec_add(time1_ts, time2_ts) ; 
}

timespec operator- (const timespec& time1_ts, const timespec& time2_ts)  // tested 
{
    return timespec_subtract(time2_ts, time1_ts) ; 
}

timespec& operator+= (timespec& time_ts, const timespec& delay_ts)      // tested 
{
    time_ts = timespec_add(time_ts, delay_ts) ;
    return time_ts ; 
}

timespec& operator-= (timespec& time_ts, const timespec& delay_ts)     // tested 
{
    time_ts = timespec_subtract(delay_ts, time_ts) ;
    return time_ts ; 
}

bool operator== (const timespec& time1_ts, const timespec& time2_ts)   // tested 
{
    if ((time1_ts.tv_sec == time2_ts.tv_sec) and (time1_ts.tv_nsec == time2_ts.tv_nsec))
         return true ; 
    else 
         return false ; 
}

bool operator!= (const timespec& time1_ts, const timespec& time2_ts)    // tested 
{
    return not(time1_ts == time2_ts) ; 
}

bool operator< (const timespec& time1_ts, const timespec& time2_ts)    // tested 
{
    if (time1_ts.tv_sec < time2_ts.tv_sec)
          return true ; 
    else if ((time1_ts.tv_sec == time2_ts.tv_sec) and (time1_ts.tv_nsec < time2_ts.tv_nsec))
          return true ; 
    else 
          return false ; 
}

bool operator> (const timespec& time1_ts, const timespec& time2_ts)   // tested 
{
    if (time1_ts == time2_ts) 
          return false ;
    else 
          return not(time1_ts < time2_ts) ; 
}



 
