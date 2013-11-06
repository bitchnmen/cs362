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

/* Process class */
class Process {
    private:
		int p_id;
		int burst;
		int arrival;
		int priority;
		int deadline;
		int io;
    public:
		int get_p_id();
		int get_burst();
		int get_arrival();
		int get_priority();
		int get_deadline();
		int get_io();		
};

int mfqs();
int rts();
int hs();

/* Input */
vector<Process> fileIO();
void filterProcesses(vector<Process>);
vector<Process> getProcesses();

#endif