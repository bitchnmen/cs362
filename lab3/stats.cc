
#include "sched.h"

void print_stats(Process* processes, int* numLines){
    
    cout << "PID"<< "\t" << "Start Time" << "\t" << "End Time" << "\t" << "Level" << "\t" << "Burst" << "\t" << "Age"<< "\t" << "Arrival" << "\t" << "Deadline" << "\t" << endl;
    
    for(int i = 0; i < *numLines; i++) {
        cout << processes[i].get_p_id()<< "\t" << processes[i].get_start_time() << "\t\t"<< processes[i].get_end_time() << "\t\t" << processes[i].get_level() << "\t" << processes[i].get_burst() << "\t" << processes[i].get_burst() << "\t" << processes[i].get_arrival() << "\t"<< processes[i].get_deadline() << endl;
    }
}

void print_stats_rts(Process* processes, int* numLines){
    
    cout << "PID"<< "\t" 
		<< "Start Time" << "\t" 
		<< "End Time" << "\t" 
		<< "WT" << "\t\t" 
		<< "TT" << endl;
    
	double avgwait = 0;
	double avgturn = 0;
	double numschd = 0;
	
	
    for(int i = 0; i < *numLines; i++) {
        cout << processes[i].get_p_id()<< "\t" 
			<< processes[i].get_start_time() << "\t\t"
			<< processes[i].get_end_time() << "\t\t"
			<< processes[i].get_end_time() - processes[i].get_arrival() - processes[i].get_burst_original() + 1 << "\t\t" 
			<< processes[i].get_end_time() - processes[i].get_arrival() << endl;
			
		if (processes[i].get_p_id() != -1) {
            numschd++;
		    avgwait += processes[i].get_end_time() - processes[i].get_arrival() - processes[i].get_burst_original() + 1;
		    avgturn += processes[i].get_end_time() - processes[i].get_arrival();
        }
    }
    
//    double await = (doub

    avgwait = double(avgwait / numschd);
    avgturn = double(avgturn / numschd);
      	
	cout << "\nAvg Wait\tAvg Turnaround\t# Processes Sched" << endl;
	cout << avgwait << "\t\t" << avgturn << "\t\t" << numschd << endl;
	
	
}

