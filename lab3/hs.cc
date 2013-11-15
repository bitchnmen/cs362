
#include "sched.h"

int hs(){
    int q = -1; 

    cout << "\n\nSelected HS";
    
    cout << "\nEnter size of the Time Quantum: ";
    cin >> q;
    cout << "\n";
    
    if(q < 1){
        cout << "\nError: Invaild Time Quantum Input";
        exit(1);
    }

    int numLines;
    bool loop = true;
    // get processes
    Process* processes(getProcesses(&numLines));
    
    // initialize the vector of vectors   
    vector<Process> **map;
    map = new vector<Process>*[100]; 
    for(int i =0; i < 100; i++){
        map.push_back(new vector<Process>);
    }
    
    // add proccesses to map to start
    for(int i =0; i < numLines; i++){
        cout << &map[i] << endl;
        vector<Process> v = *map[processes[i].get_priority()];
        Process p = processes[i];
        v.push_back(p);
    }
    
    for(int i =0; i < 100; i++){
            vector<Process> v = *map[i];
            
            cout << i << ": " << endl;
            cout << "v.size =" << v.size() << endl;   
           
            for(int j = 0; j < v.size(); j++){
                //Process p = processes[j];
                //p.to_string();
                cout << "p.id = " << processes[j].get_p_id() << endl;
                v.push_back(processes[j]);
                cout << processes[j].get_priority() << endl;
            } 
            cout << "\n--DONE--\n\n" << endl;
    } 
    
    
   /*  
    sort_hs(processes, &numLines);

    for(int i = 0; i < numLines; i++){

        if(processes[i].get_priority() >= 0 && processes[i].get_priority() < 50 ){
        //low band (user)
            if(start_times[i] == -1 && processes[i].get_burst() > 0){
            // not done so demote 
            }else{
            // boost

            }

        }else if(processes[i].get_priority() >=50 && processes[i].get_priority() < 100 ){
        //high band (kernel)
            if(start_times[i] == -1 && processes[i].get_burst() > 0){
            // not done so demote 
            }
        }
    }




}

void sort_hs(Process* processes, int* numLines){
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
    
    cout << "Processes:" << endl;
	print_in_file(processes, numLines);
    cout << "ProcessesNEW:" << endl;
	print_in_file(processesNEW, numLines);
    
    processes = processesNEW;

*/
}
