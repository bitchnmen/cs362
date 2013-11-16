
#include "sched.h"

void print_stats(Process* processes, int* start_times, int* end_times, int* numLines){
    
    cout << "PID"<< "\t" << "Start Time" << "\t" << "End Time" << "\t" << "Level" << "\t" << "Burst" << "\t" << "Age" << endl;
    
    for(int i = 0; i < *numLines; i++) {
        cout << processes[i].get_p_id()<< "\t" << start_times[i] << "\t\t"<< end_times[i] << "\t\t" << processes[i].get_level() << "\t" << processes[i].get_burst() << "\t" << processes[i].get_burst() << endl;
    }
}

void print_stats_rts(Process* processes, int* numLines){
    
    cout << "PID"<< "\t" 
		<< "Start Time" << "\t" 
		<< "End Time" << "\t" 
		<< "WT" << "\t" 
		<< "TT" << "\t" 
		<< "# Scheduled" << endl;
    
	int avgwait = 0;
	int avgturn = 0;
	int numschd = 0;
	
	
    for(int i = 0; i < *numLines; i++) {
        cout << processes[i].get_p_id()<< "\t" 
			<< processes[i].get_start_time() << "\t\t"
			<< processes[i].get_end_time() - processes[i].get_arrival() - processes[i].get_burst()<< "\t\t" 
			<< processes[i].get_end_time() - processes[i].get_arrival() << "\t" 
			<< processes[i].get_burst() << "\t" 
			<< processes[i].get_burst() << endl;
			
		avgwait += processes[i].get_end_time() - processes[i].get_arrival() - processes[i].get_burst();
		avgturn += processes[i].get_end_time() - processes[i].get_arrival();
		if (processes[i].get_p_id() != -1) {numschd++;}
    }
	
	cout << "\nAvg Wait\tAvg Turnaround\t# Processes Sched" << endl;
	cout << avgwait << "\t\t" << avgturn << "\t\t" << numschd << endl;
	
	
}

