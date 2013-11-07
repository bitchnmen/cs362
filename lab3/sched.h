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
		int age;
		int level;
    public:
		Process();
        Process(int, int, int, int, int, int);
		void set_values(int,int,int,int,int,int);
		int get_p_id() {return p_id;}
		int get_burst() {return burst;}
		int get_arrival() {return arrival;}
		int get_priority() {return priority;}
		int get_deadline() {return deadline;}
		int get_io() {return io;}
		int get_level() {return level;}
		int get_age() {return age;}
		void set_burst(int _burst) {burst = _burst;}
		void set_priority(int _priority) {priority = _priority;}
		void set_age(int _age) {age = _age;}
		void set_level(int _level) {level = _level;}
		void to_string();
};

int mfqs();
int rts();
int hs();

/* Input */
Process* getProcesses(int*);
void print_in_file(Process*, int*);

#endif
