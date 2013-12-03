#include "traffic.h"


int main(int argc, char *argv[]){
	street[4]; 
	Q[4] ; //each queue for each street 
	empty // intersection is empty (Boolean) 
 
	// car arrives at street[i] 
	arrival(int i) { 
		if (empty) { 
			empty =false; 
			drive(i); 
		} else { 
			Q[i]++; 
			// wait for someone to signal that it is street[i]’s 
			turn to go 
			drive[i]; 
		} 
	} //arrival(i)
	
	// departure of car from intersection 
	departure (int i) { 
		// one car departs
		// pick the next intersection for next car to go 
		// if no cars are in queues, empty = true 
		
	}

/* Returns a random number from 0 to 1 */ 
double rndom() { 
    const long A = 48271; 
    const long M = 2147483647; 
    const long Q = M/A; 
    const long R = M%A; 
    static long state = 1; 
    long t = A * (state % Q) - R * (state / Q); 

    if (t > 0) { 
        state = t;
    } else { 
        state = t + M;
        return ((double) state/M); 
    }
}
