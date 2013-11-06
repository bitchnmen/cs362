#include "sched.h"
Process::Process (int p_ida, int bursta, int arrivala, int prioritya, int deadlinea, int ioa) {
    p_id = p_ida;
	burst = bursta;
	arrival = arrivala;
	priority = prioritya;
	deadline = deadlinea; 
	io = ioa;
}
