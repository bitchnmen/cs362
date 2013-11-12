
#include "sched.h"

int mfqs(){
    int queues = -1;
    int q = -1;
    int maxage = -1;

    cout << "\n\nSelected MFQS";
    cout << "\nEnter number of queues(1-5): ";
    cin >> queues;
    cout << "\n";
    
    cout << "\nEnter size of the Time Quantum: ";
    cin >> q;
    cout << "\n";
    
    cout << "\nEnter the Maximum Age Time: ";
    cin >> maxage;
    cout << "\n";

    if(queues < 1 && queues > 5){
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
	
	cout << "numLines: " << numLines << endl;
	
	print_in_file(processes, &numLines);
    
    int *start_times = new int[numLines];
    int *end_times = new int[numLines];

    //initialize arrays
    for(int i = 0; i < numLines; i++){
        start_times[i] = -1;
        end_times[i] = -1;
    }


    int clock = 0;
    
    while (loop){ 
        for (int i = 0; i < numLines; i++){
            //check for arrival
            if(processes[i].get_arrival() >= clock){
                //check if there is anything left to process
                if(processes[i].get_burst() > 0){
                    //add start to array if not started yet
                    if(start_times[i] == -1){
                        start_times[i] = clock;  
                    }
                    //execute for length of time quantum
                    for(int j = 0; j < q; j++) {
                        processes[i].set_burst(processes[i].get_burst() - 1);
                        clock++;
                    }
                    //if processing is not done
                    if(processes[i].get_burst() > 0){
                        //adjust level of queue
                        //if process is on the last queue and has run for >= to the maxage 
                        if((processes[i].get_level() == (queues-1)) && (processes[i].get_age() >= maxage)){
                            //move up a level
                            processes[i].set_level(processes[i].get_level() - 1);
                        }else{
                            //otherwise, move down a level
                            processes[i].set_level(processes[i].get_level() + 1);
                        } 
                    
                    } else {
                        if(end_times[i] == -1){
                            end_times[i] = clock;  
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
        clock++;
	    print_stats(processes, start_times, end_times, &numLines);
    }

    cout << "FINISHED" << endl;
	print_in_file(processes, &numLines);
	print_stats(processes, start_times, end_times, &numLines);

}
