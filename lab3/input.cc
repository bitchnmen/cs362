#include "sched.h"

Process* getProcesses(int *numLines){

	/* Counting the number of lines */
	*numLines = -1;
	ifstream in("testfile");
	std::string unused;
	while ( std::getline(in, unused) ) ++*numLines;
	
    /* Creating a new array of Processes to store our Processes */
	Process* processes = new Process[*numLines];
	
	/* Opening a new file to create the Processes with */
	ifstream infile("testfile");
    string line;
	int count = 0;
	getline(infile,line); //first line has words, we don't want those

	/* looping through line by line and creating new processes, storing them in the array */
    while(getline(infile, line)) {
        stringstream ss(line);
        int a, b, c, d, e, f;
        if (!(ss >> a >> b >> c >> d >> e >> f)) {break;}
        processes[count].set_values(a, b, c, d, e, f);
        count++;
    }

    /* filter the array here, remove bad timings */
	/* :) */
	
    return processes;
}

/* prints out the current file */
void print_in_file(Process* processes, int* numLines) {
	for(int i = 0; i < *numLines; i++) {
		processes[i].to_string();
	}
}