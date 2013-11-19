#include "sched.h"

Process::Process() {
	p_id = -1;
	burst = -1;
	burst_original = -1;
	arrival = -1;
	priority = -1;
	priority_original = -1;
	deadline = -1; 
	io = -1;
	level = 0;
	age = -1;
	start_time = -1;
    end_time = -1;
	increment = burst;
}

Process::Process (int p_ida, int bursta, int arrivala, int prioritya, int deadlinea, int ioa) {
    p_id = p_ida;
	burst = bursta;
	burst_original = bursta;
	arrival = arrivala;
	priority = prioritya;
	priority_original = priority;
	deadline = deadlinea; 
	io = ioa;
	level = 1;
	start_time = -1;
	end_time = -1;
	increment = burst;
}

void Process::set_values(int p_ida, int bursta, int arrivala, int prioritya, int deadlinea, int ioa) {
	p_id = p_ida;
	burst = bursta;
	burst_original = bursta;
	arrival = arrivala;
	priority = prioritya;
	priority_original = priority;
	deadline = deadlinea; 
	io = ioa;
	increment = burst;
}

void Process::to_string() {
	cout << "PID\tBURST\tARRIVAL\tPRIOR\tDEAD\tIO" << endl;
	cout << this->p_id << "\t" << this->burst << "\t" << this->arrival << "\t" << this->priority << "\t" << this->deadline << "\t" << this->io << "\n" << endl;
}

bool Process::is_done() {
    return (this->burst == 0);
}
