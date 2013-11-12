#include "sched.h"

Process::Process() {
	p_id = -1;
	burst = -1;
	arrival = -1;
	priority = -1;
	deadline = -1; 
	io = -1;
	level = 0;
	age = -1;
	start_time = -1;
	end_time = -1;
}

Process::Process (int p_ida, int bursta, int arrivala, int prioritya, int deadlinea, int ioa) {
    p_id = p_ida;
	burst = bursta;
	arrival = arrivala;
	priority = prioritya;
	deadline = deadlinea; 
	io = ioa;
	level = 1;
	start_time = -1;
	end_time = -1;
}

void Process::set_values(int p_ida, int bursta, int arrivala, int prioritya, int deadlinea, int ioa) {
	p_id = p_ida;
	burst = bursta;
	arrival = arrivala;
	priority = prioritya;
	deadline = deadlinea; 
	io = ioa;
}

void Process::to_string() {
	cout << this->p_id << " " << this->burst << " " << this->arrival << " " << this->priority << " " << this->deadline << " " << this->io << "\n" << endl;
}
