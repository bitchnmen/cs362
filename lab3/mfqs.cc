
#include "sched.h"

int mfqs(){
    int queues = -1;
    int q = -1;
    cout << "\n\nSelected MFQS";
    cout << "\nEnter number of queues(1-5): ";
    cin >> queues;
    cout << "\n";
    
    cout << "\nEnter size of the time quantum: ";
    cin >> q;
    cout << "\n";
    
    if(queues < 1 && queues > 5){
        cout << "\nError: Invalid Number of Queues Input";
        exit(1);
    }

    if(q < 1){
        cout << "\nError: Invaild Time Quantum Input";
        exit(1);
    }
	
	//getProcesses();
	int numLines;
	
    Process* processes(getProcesses(&numLines));
	
	cout << "numLines: " << numLines << endl;
	
	print_in_file(processes, &numLines);
	
    
}
