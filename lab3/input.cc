#include "sched.h"

vector<Process> getProcesses(){
    vector<Process> processes;
    processes = fileIO();
    filterProcesses(processes);
    return processes;
}

vector<Process> fileIO() {
    vector<Process> processes;
    ifstream infile("testfile");
    string line;
    while(getline(infile, line)) {
        istringstream iss(line);
        int a, b, c, d, e, f;
        if (!(iss >> a >> b >> c >> d >> e >> f)) {break;}

        Process *p;
		p = new Process(a, b, c, d, e, f);
        processes.push_back(p);
    }

}

void filterProcesses(vector<Process>& processes) {

}
