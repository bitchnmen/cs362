
#include "sched.h"

int rts(){
	int rtsOption;
    cout << "\n\nSelected RTS";
    cout << "\nChoose scheduling option hard/soft:";
    cout << "\n 1. Hard";
    cout << "\n 2. Soft";
    cout << "\n";
	cin >> rtsOption;
	cout << "\n";
	
	int numLines;
	Process* processes(getProcesses(&numLines));
	
	if (rtsOption == 1 || rtsOption == 2) {
		bool hard = (rtsOption == 1);
		runRTS(processes, &numLines, hard);
	} else {
		cout << "\nError on menu selection.\n";
		exit(1);
	}
}

void runRTS(Process* processes, int* numLines, bool hard) {
	//print_in_file(processes, numLines);
	
	// if hard rts, filter processes. look processes that can't complete
	if (hard) {
		for(int i = 0; i < *numLines; i++) {
			if (processes[i].get_deadline() < processes[i].get_burst() + processes[i].get_arrival()) {
				processes[i].set_p_id(-1);
			}
			processes[i].set_level(0);
		}
	}
	
	int lowest_deadline_process;
	int clock = 0;
    int low_deadline = 0;
    bool loop = true;
    while (loop){ 
	
		cout << "CLOCK = " << clock << endl;
	
        for(int i = 0; i < *numLines; i++) {
        
			if (processes[i].get_burst() != 0 && processes[i].get_p_id() != -1) {
				//if hard rts, check for expired deadlines
				if (hard) {
					if (processes[i].get_deadline() < processes[i].get_burst() + clock) {
						processes[i].set_p_id(-1);
					}
				}
		
				if (processes[i].get_arrival() >= clock) {
					int curr_deadline = processes[i].get_deadline();
                    
					if (low_deadline == 0 || low_deadline > curr_deadline) {
						low_deadline = curr_deadline;
						lowest_deadline_process = i;
						
					/* tiebreaker | add more later if needed*/
					} else if (low_deadline == curr_deadline) {          
						if (processes[lowest_deadline_process].get_p_id() > processes[i].get_p_id()) {
							lowest_deadline_process = i;
						}
					}
				}
			}
			processes[i].to_string();
        }
		if (clock == 10) {exit(1);}
		
        int current_burst = processes[lowest_deadline_process].get_burst();
        processes[lowest_deadline_process].set_burst(current_burst-1);
		
		
		if (processes[lowest_deadline_process].get_start_time() == -1) {
			processes[lowest_deadline_process].set_start_time(clock);
		}	
			
		if (processes[lowest_deadline_process].get_burst() == 0 && processes[lowest_deadline_process].get_end_time() == -1) {
			processes[lowest_deadline_process].set_end_time(clock);
			low_deadline = 0;
		}

		loop = false;
		for(int k = 0; k < *numLines; k++){
			if(processes[k].get_burst() > 0){
				loop = true;
				break;
			}
		}
		//print_stats_rts(processes, numLines);

		
		clock++;
    }
	
	//print_stats_rts(processes, numLines);
	
}

void sort_rts(Process* processes, int* numLines){
    int max_arrival = 0;
	Process* processesNEW = new Process[*numLines];
    
    for(int i = 0; i < *numLines; i++){
        if (processes[i].get_arrival() > max_arrival){
            max_arrival = processes[i].get_arrival();
        }
    }
    int count = 0;
    for(int i = 0; i <= max_arrival; i++){
        for(int j = 0; j < *numLines; j++){
            if (processes[j].get_arrival() == i){
                processesNEW[count] = processes[j];
                count++;
            }
        }
    }
    
    cout << "Processes:" << endl;
	print_in_file(processes, numLines);
    cout << "ProcessesNEW:" << endl;
	print_in_file(processesNEW, numLines);
    
    processes = processesNEW;

}


