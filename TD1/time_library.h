#ifndef time_library_h_INCLUDED 
#define time_library_h_INCLUDED 

#include <time.h> 

/*--------------------------------------------------------*/
/* Functions */

/* 1. Converts timespec into milliseconds */
double timespec_to_ms(const timespec& time_ts) ;   

/* 2. Converts milliseconds into timespec  */
timespec timespec_from_ms(double time_ms) ; 

/* 3. Determines the current time in timespec format */
timespec timespec_now() ;  
 
/* 4. Gives the negate value of a timespec */
timespec timespec_negate(const timespec& time_ts) ;

/* 5. Returns the sum of two timespects */
timespec timespec_add(const timespec& time1_ts, const timespec& time2_ts) ;

/* 6. Returns time2_ts - time2_ts */
timespec timespec_subtract(const timespec& time1_ts, const timespec& time2_ts) ;  //

/* 7. Make a delay of a given delay_ts (a timespec) */
timespec timespec_wait(const timespec& delay_ts) ;  //


/*--------------------------------------------------------*/
/* Operators */ 

/* 1. Gives the negation of time_ts */  
timespec operator- (const timespec& time_ts) ;

/* 2. Gives the sum of two timespect */
timespec operator+ (const timespec& time1_ts, const timespec& time2_ts) ; 

/* 3. Gives the subtruction between two timespec */ 
timespec operator- (const timespec& time1_ts, const timespec& time2_ts) ;  //

/* 4. Add a delay to a timespec */ 
timespec& operator+= (timespec& time_ts, const timespec& delay_ts) ; 

/* 5. Subtract a delay from a timespec */ 
timespec& operator-= (timespec& time_ts, const timespec& delay_ts) ; 

/* 6. Test whether two timespec are equal or not */ 
bool operator== (const timespec& time1_ts, const timespec& time2_ts) ;

/* 7. Test whether two timespec are different or not */ 
bool operator!= (const timespec& time1_ts, const timespec& time2_ts) ;

/* 8. Test whether time1_ts < time2 */
bool operator< (const timespec& time1_ts, const timespec& time2_ts) ;

/* 8. Test whether time1_ts > time2 */
bool operator> (const timespec& time1_ts, const timespec& time2_ts) ;

#endif 


