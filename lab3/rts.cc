
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
	
		cout << " in rts" << endl;

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
		}
	}
	
	int lowest_deadline_process;
	int clock = 0;
	bool run = true;
    while (run){ 
//	    cout << "_____________" << endl;
//	    cout << "Clock: " << clock << endl;
//		cout << "_____________" << endl;
        int to_process = -1;
        for(int i = 0; i < *numLines; i++){
            if(hard){
//				cout << "burst: " << processes[i].get_burst() << endl;
//				cout << "deadline: " << processes[i].get_deadline() << endl;

                if(clock + processes[i].get_burst() <= processes[i].get_deadline()){
					
//					processes[i].to_string();
					
                    if((processes[i].get_p_id() != -1) && (processes[i].get_arrival() <= clock) && (processes[i].get_burst() > 0)){
//                        cout << "in if statement" << endl;
                        if((to_process == -1) || (processes[i].get_deadline() < processes[to_process].get_deadline())){
                            to_process = i; 
                        }else if(processes[i].get_deadline() == processes[to_process].get_deadline()){
                            if(processes[i].get_arrival() < processes[to_process].get_arrival()){
                                to_process = i;  
                            }else if(processes[i].get_arrival() == processes[to_process].get_arrival()){
                                if(processes[i].get_p_id() < processes[to_process].get_p_id()){
                                    to_process = i;  
                                } 
                            }         
                        }
                    }    

                }else{
					cout << "1 .setting to -1" << endl;
                    processes[i].set_p_id(-1);
                }
            }else{
                if((processes[i].get_p_id() != -1) && (processes[i].get_arrival() <= clock) && (processes[i].get_burst() > 0)){
//                    cout << "in if statement" << endl;
                    if((to_process == -1) || (processes[i].get_deadline() < processes[to_process].get_deadline())){
                        to_process = i; 
                    }
                }
            }
            //cout << "To Process: " << to_process << endl;
        }

        
       //print_stats_rts(processes, numLines);
	   
		run = false;
		for (int j = 0; j < *numLines; j++) {
			if (processes[j].get_p_id() != -1 && processes[j].get_burst() > 0) {
				run = true;
			}
		}
		/*if(to_process == -1){
            cout << "All processes done." << endl;
            break;
        }*/
        

        if(processes[to_process].get_start_time() == -1){
            processes[to_process].set_start_time(clock);        
        }
        
        processes[to_process].set_burst(processes[to_process].get_burst() - 1);
        
        if(processes[to_process].get_burst() == 0 && processes[to_process].get_end_time() == -1){
            processes[to_process].set_end_time(clock);        
        }
        clock++;
        int b;
        //cin >> b;

    }	
    print_stats_full(processes, numLines);
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


