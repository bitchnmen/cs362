
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
	
	if (rtsOption == 1) {
		hardRTS(processes, &numLines);
	} else if (rtsOption == 2) {
		softRTS(processes, &numLines);
	} else {
		cout << "\nError on menu selection.\n";
		exit(1);
	}
}

void hardRTS(Process* processes, int* numLines) {
	print_in_file(processes, numLines);
	
	/*filter processes */
	for(int i = 0; i < *numLines; i++) {
		if (processes[i].get_deadline() < processes[i].get_burst() + processes[i].get_arrival()) {
			processes[i].set_p_id(-1);
		}
		processes[i].set_level(0);
	}
	process[0].set_level(1);
	
	int clock = 0;
    bool loop = true;
    while (loop){ 
        
		
		
		
		loop = false;
        for(int k = 0; k < *numLines; k++){
            if(processes[k].get_burst() > 0){
                loop = true;
                break;
            }
        }
        clock++;
    }
	
	
	
	
}

void softRTS(Process* processes, int* numLines) {
	print_in_file(processes, numLines);
	
	
	
}
