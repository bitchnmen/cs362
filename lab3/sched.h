#ifndef SCHED_H
#define SCHED_H

#include <iostream>
#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h> 
#include <pthread.h>
#include <fstream>
#include <sstream>
#include <vector>

using namespace std;

int mfqs();
int rts();
int hs();

/* Process class */
class Process {
    int p_id, burst, arrival, priority, deadline, io;
    public:
		Process(int, int, int, int, int, int);
		int get_p_id();
		int get_burst();
		int get_arrival();
		int get_priority();
		int get_deadline();
		int get_io();		
};

/* Input */
vector<Process> fileIO();
void filterProcesses(vector<Process>);

#endif