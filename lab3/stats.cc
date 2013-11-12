
#include "sched.h"

void print_stats(Process* processes, int* start_times, int* end_times, int* numLines){
    
    cout << "PID"<< "\t" << "Start Time" << "\t" << "End Time" << "\t" << endl;
    
    for(int i = 0; i < *numLines; i++) {
        cout << processes[i].get_p_id()<< "\t\t" << start_times[i] << "\t\t"<< end_times[i] << endl;
    }
}

