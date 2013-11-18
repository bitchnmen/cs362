
#include "sched.h"

int mfqs(){
    int queues = -1;
    int q = -1;
    int maxage = -1;

    cout << "\n\nSelected MFQS";
    cout << "\nEnter number of queues(2-5): ";
    cin >> queues;
    cout << "\n";
    
    cout << "\nEnter size of the Time Quantum: ";
    cin >> q;
    cout << "\n";
    
    cout << "\nEnter the Maximum Age Time: ";
    cin >> maxage;
    cout << "\n";

    if(queues < 2 && queues > 5){
        cout << "\nError: Invalid Number of Queues Input";
        exit(1);
    }

    if(q < 1){
        cout << "\nError: Invaild Time Quantum Input";
        exit(1);
    }
    
    if(maxage < 1){
        cout << "\nError: Invaild Maximum Age Input";
        exit(1);
	}

	//getProcesses();
	int numLines;
	bool loop = true;
    Process* processes(getProcesses(&numLines));
    
    cout << "Started sorting" << endl;
    sort_mfqs(processes, &numLines);	

	cout << "numLines: " << numLines << endl;
    	
	//print_in_file(processes, &numLines);
    
    //int *start_times = new int[numLines];
    //int *end_times = new int[numLines];

    //initialize arrays
    //for(int i = 0; i < numLines; i++){
    //    start_times[i] = -1;
    //    end_times[i] = -1;
    //}


    int clock = 0;
    
	//print_stats(processes, start_times, end_times, &numLines);
    
    while (loop){ 
        //cout << "\n__________________________________________________________" << endl;
        for (int i = numLines-1; i >= 0; i--){
            //cout << "Clock: " << clock << endl;
            //print_stats(processes, &numLines);
            //check for arrival
            if(processes[i].get_arrival() <= clock){
                //check if there is anything left to process
                if(processes[i].get_burst() > 0){
                    //add start to array if not started yet
                    if(processes[i].get_start_time() == -1){
                        processes[i].set_start_time(clock);  
                    }
                    //execute for length of time quantum
                    if(!(processes[i].get_level() > (queues-1))){
                        for(int j = 0; j < (pow(2,processes[i].get_level())*q); j++) {

                            processes[i].set_burst(processes[i].get_burst() - 1);
                            clock++;
                            //cout << "Clock: " << clock << endl;
                            
                            //age all processes in last queue  
                            for(int m = 0; m < numLines; m++){
                                //if processing is not done
                                if(processes[m].get_burst() > 0){
                                    //adjust level of queue
                                    //if process is on the last queue and has run 
                                    //      for >= to the maxage 
                                    int before =  processes[m].get_level();
                                    if((processes[m].get_level() == (queues-1))){
                                        //cout << "in the last queue" << endl;
                                        if(processes[m].get_age() >= maxage){
                                            //move up a level
                                            //cout << "moving up" << endl;
                                            processes[m].set_level(processes[m].get_level() - 1);
                                            processes[m].set_age(0);
                                        }else{
                                            //cout << "not moving up" << endl;
                                            processes[m].set_age(processes[m].get_age()+1);
                                        }
                                        
                                    }else{
                                        //otherwise, move down a level
                                        //cout << "moving down" << endl;
                                        processes[m].set_level(processes[m].get_level() + 1);
                                    } 
                                    int after =  processes[m].get_level();
                                    //cout << "before: " << before << " - after: " << after << endl;
                                } else {
                                    //otherwise mark its done
                                    if(processes[m].get_end_time() == -1){
                                       processes[m].set_end_time(clock);  
                                    }
                                }
                            }
                            if(processes[i].get_burst() == 0){
                                break;
                            }
                        }
                    } else {
                        while(true) {
                            processes[i].set_burst(processes[i].get_burst() - 1);
                            clock++;
                            //cout << "Clock: " << clock << endl;
                            
                            //age all processes in last queue  
                            for(int m = 0; m < numLines; m++){
                                //if processing is not done
                                if(processes[m].get_burst() > 0){
                                    //adjust level of queue
                                    //if process is on the last queue and has run for >= to the maxage 
                                    int before =  processes[m].get_level();
                                    if((processes[m].get_level() == (queues-1))){
                                        //cout << "in the last queue" << endl;
                                        if(processes[m].get_age() >= maxage){
                                            //move up a level
                                            //cout << "moving up" << endl;
                                            processes[m].set_level(processes[m].get_level() - 1);
                                            processes[m].set_age(0);
                                        }else{
                                            //cout << "not moving up" << endl;
                                            processes[m].set_age(processes[m].get_age()+1);
                                        }
                                        
                                    }else{
                                        //otherwise, move down a level
                                        //cout << "moving down" << endl;
                                        processes[m].set_level(processes[m].get_level() + 1);
                                    } 
                                    int after =  processes[m].get_level();
                                    //cout << "before: " << before << " - after: " << after << endl;
                                } else {
                                    //otherwise mark its done
                                    if(processes[m].get_end_time() == -1){
                                       processes[m].set_end_time(clock);  
                                    }
                                }
                            }

                            if(processes[i].get_burst() == 0){
                                break;
                            }
                        }
                    }

                }
            }  
        }

        
        
        loop = false;
        for(int k = 0; k < numLines; k++){
            if(processes[k].get_burst() > 0){
                loop = true;
                break;
            }
        }
    }

    cout << "FINISHED" << endl;
	//print_in_file(processes, &numLines);
	print_stats_full(processes, &numLines);

}


void sort_mfqs(Process* processes, int* numLines){
    int max_arrival = 0;
	Process* processesNEW = new Process[*numLines];
    
    for(int i = 0; i < *numLines; i++){
        if (processes[i].get_arrival() > max_arrival){
            max_arrival = processes[i].get_arrival();
        }
    }
    int count = 0;
    for(int i = 0; i <= max_arrival; i++){
        for(int j = 0; j < *numLines; j++){
            if (processes[j].get_arrival() == i){
                processesNEW[count] = processes[j];
                count++;
            }
        }
    }
    
    //cout << "Processes:" << endl;
	//print_in_file(processes, numLines);
    //cout << "ProcessesNEW:" << endl;
	//print_in_file(processesNEW, numLines);
    
    processes = processesNEW;

}




