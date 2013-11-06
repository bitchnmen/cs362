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
		Process();
        Process(int, int, int, int, int, int);
		void set_values(int,int,int,int,int,int);
		int get_p_id();
		int get_burst();
		int get_arrival();
		int get_priority();
		int get_deadline();
		int get_io();
		void to_string();
};

int mfqs();
int rts();
int hs();

/* Input */
Process* getProcesses(int*);
void print_in_file(Process*, int*);

#endif
