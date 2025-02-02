#include "sched.h"

Process* getProcesses(int *numLines){

	int inputfilenum;
	string inputfilename;
	
	cout << "Choose a number for process input" << endl;
	cout << "1. testfile" << endl;
	cout << "2. testfileMEDIUM" << endl;
	cout << "3. testfileSEMILARGE" << endl;
	cout << "4. testfileLARGE" << endl;
	cout << "5. testfile1" << endl;
	cout << "6. testfile100" << endl;
	cout << "7. testfile1000" << endl;
	cout << "8. testfile10000" << endl;
	cout << "9. testfile100000" << endl;
	cin >> inputfilenum;
	cout << "\n";
	
	if (inputfilenum == 2) {
		inputfilename = "testfileMEDIUM";
	} else if (inputfilenum == 3) {
		inputfilename = "testfileSEMILARGE";
	} else if (inputfilenum == 4) {
		inputfilename = "testfileLARGE";
	} else if (inputfilenum == 5) {
		inputfilename = "testfile1";		
	} else if (inputfilenum == 6) {
		inputfilename = "testfile100";		
	} else if (inputfilenum == 7) {
		inputfilename = "testfile1000";		
	} else if (inputfilenum == 8) {
		inputfilename = "testfile10000";		
	} else if (inputfilenum == 9) {
		inputfilename = "testfile100000";		
	} else {
		inputfilename = "testfile";		

    }


	/* Counting the number of lines */
	*numLines = -1;
	ifstream in(inputfilename.c_str());
	std::string unused;
	while ( std::getline(in, unused) ) ++*numLines;
	
	cout << "Numlines: " << *numLines << endl;
	
	
    /* Creating a new array of Processes to store our Processes */
	Process* processes = new Process[*numLines];

//	print_in_file(processes, numLines);
//int a;
//	cin >> a;
	
	/* Opening a new file to create the Processes with */
	ifstream infile(inputfilename.c_str());
    string line;
	int count = 0;
	getline(infile,line); //first line has words, we don't want those

	/* looping through line by line and creating new processes, storing them in the array */
    while(getline(infile, line)) {
        istringstream iss(line);
        int a, b, c, d, e, f;
        if (!(iss >> a >> b >> c >> d >> e >> f)) {break;}
        
		//cout << "a: " << a << endl;
		//cout << "count: " << count << endl;
		
		if (a == count + 1 && b > 0 && c >= 0 && d > 0 && e > 0 && f >= 0) {
			processes[count].set_values(a, b, c, d, e, f);
			
			cout << "a: " << a << endl;
		}
		count++;
    }
	
    cout << "done inputing" << endl;
//	print_in_file(processes, numLines);
    return processes;
}

/* prints out the current file */
void print_in_file(Process* processes, int* numLines) {
	for(int i = 0; i < *numLines; i++) {
		processes[i].to_string();
	}
}
