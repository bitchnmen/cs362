
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
	
	
	
}

void softRTS(Process* processes, int* numLines) {
	print_in_file(processes, numLines);
	
	
	
}
