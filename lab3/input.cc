#include "sched.h"


vector<int[]> getProcesses(){
    vector<int[]> processes;
    processes = fileIO();
    filterProcesses(processes);
    return processes;
}

vector<int[]> fileIO() {
    vector<int[]> processes;
    ifstream infile("testfile");
    string line;
    while(getline(infile, line)) {
        istringstream iss(line);
        int a, b, c, d, e, f;
        if (!(iss >> a >> b >> c >> d >> e >> f)) {break;}

        int[] params = {a, b, c, d, e, f};
        process.push_back(params);
    }

}

void filterProcesses(vector<int[]> processes) {


}
