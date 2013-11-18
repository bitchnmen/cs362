#include "sched.h"

Process* getProcesses(int *numLines){

	/* Counting the number of lines */
	*numLines = -1;
	ifstream in("testfileSEMILARGE");
	std::string unused;
	while ( std::getline(in, unused) ) ++*numLines;
	
	cout << "Numlines: " << *numLines << endl;
	int a;
	cin >> a;
	
    /* Creating a new array of Processes to store our Processes */
	Process* processes = new Process[*numLines];
	
	/* Opening a new file to create the Processes with */
	ifstream infile("testfileSEMILARGE");
    string line;
	int count = 0;
	getline(infile,line); //first line has words, we don't want those

	/* looping through line by line and creating new processes, storing them in the array */
    while(getline(infile, line)) {
        stringstream ss(line);
        int a, b, c, d, e, f;
        if (!(ss >> a >> b >> c >> d >> e >> f)) {break;}
        
		//cout << "a: " << a << endl;
		//cout << "count: " << count << endl;
		
		if (a == count + 1 && b > 0 && c >= 0 && d > 0 && e > 0 && f >= 0) {
			processes[count].set_values(a, b, c, d, e, f);
			
		} else {
			--*numLines;
		}
		count++;
    }
	
    cout << "done inputing" << endl;
	print_in_file(processes, numLines);
    return processes;
}

/* prints out the current file */
void print_in_file(Process* processes, int* numLines) {
	for(int i = 0; i < *numLines; i++) {
		processes[i].to_string();
	}
}
