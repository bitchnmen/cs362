
#include "sched.h"

void print_stats(Process* processes, int* numLines){
    
    cout << "PID"<< "\t" << "Start Time" << "\t" << "End Time" << "\t" << "Level" << "\t" << "Burst" << "\t" << "Age" << endl;
    
    for(int i = 0; i < *numLines; i++) {
        cout << processes[i].get_p_id()<< "\t" << processes[i].get_start_time() << "\t\t"<< processes[i].get_end_time() << "\t\t" << processes[i].get_level() << "\t" << processes[i].get_burst() << "\t" << processes[i].get_burst() << endl;
    }
}
