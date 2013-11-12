
#include "sched.h"

void print_stats(Process* processes, int* start_times, int* end_times, int* numLines){
    
    cout << "PID"<< "\t" << "Start Time" << "\t" << "End Time" << "\t" << "Level" << "\t" << "Burst" << endl;
    
    for(int i = 0; i < *numLines; i++) {
        cout << processes[i].get_p_id()<< "\t" << start_times[i] << "\t\t"<< end_times[i] << "\t\t" << processes[i].get_level() << "\t" << processes[i].get_burst() << endl;
    }
}

