
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
    /*
    // initialize the vector of vectors   
    vector<Process> **map;
    map = new vector<Process>*[100]; 
    for(int i =0; i < 100; i++){
        //map.push_back(new vector<Process>);
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
                //v.push_back(processes[j]);
                cout << processes[j].get_priority() << endl;
            } 
            cout << "\n--DONE--\n\n" << endl;
    } */

    vector< queue<Process> > v;
    vector<Process> done;

    //for(int i = 0; i < numLines; i++){
    //    v.push_back(queue<Process*>());
    // }
    
    for(int i = 0; i < 100; i++){
            queue<Process> queue;
            Process null = Process(-1,-1,-1,-1,-1,-1);
            queue.push(null); 
            bool popped = false;
            for(int j = 0; j < numLines; j++){
                
                if(processes[j].get_priority() == i){
                    Process p = processes[j];
                    if(!popped){
                        queue.pop();
                        popped = true;
                    }
                    queue.push(p);
                    p = queue.front();
                }
            }
            v.push_back(queue); 
            /* 
            queue<Process> temp;
            temp = v[i];
            Process pp = temp.front();
            cout << "\nqueue" << i << endl;
            pp.to_string();
            */
    }
   

    int clock = 0;
    while(true){
        //hundred count thingy


        //boolean to start from the top if any priority was changed
        bool broke = false;
        //loop to go through each queue from the highest priority to the lowest to run processes
        for(int i = 99; i <= 0; i++){
            queue<Process> queue = v[i];
            //loo[ to go through each process in the queue
            for(int j = 0; j = queue.size(); j++){
                Process p = queue.front(); 
                queue.pop();
                //loop to run the process for the length of the time quantum
                for(int k = 0; k < q; k++){
                    //if the process is on the second to last burst and has io
                    if(k == p.get_burst_original() - 1 && p.get_io() > 0){
                       //do IO
                       int original_io = p.get_io();
                       //loop to decrement io
                       for(int m = 0; m < p.get_io(); m++){
                           p.set_io(p.get_io() - 1);
                           clock++;
                       }
                       //loop to adjust priority
                       for(int m = 0; m < original_io; m++){
                            if(p.get_priority() < 50){
                                if(p.get_priority() < 49){
                                    p.set_priority(p.get_priority() + 1);
                                } 
                            }else{
                                if(p.get_priority() > 49 && p.get_priority() < 98){
                                    p.set_priority(p.get_priority() + 1);
                                } 

                            }
                       }
                       //break the loops and start from the top
                       broke = true;
                       break;
                    }else{
                        //decrement burst
                        if(p.get_burst() > 0){
                            p.set_burst(p.get_burst() - 1);
                            clock++;

                            
                        }else{
                            done.push_back(p);  
                        }
                    }
                    if(broke){
                        break;
                    }
                }
                
                if(broke){
                    break;
                }else{
                    //if process isnt finished at end of time quantum, decrease priority by time quantum
                    for(int k = 0; k < q; k++){
                        //////////////////////////////////////////////////////////check not to go lower than original
                        if(p.get_priority() < 50){
                            if(p.get_priority() < 49){
                                p.set_priority(p.get_priority() - 1);
                            }
                        }else{
                            if(p.get_priority() > 49 && p.get_priority() < 98){
                                p.set_priority(p.get_priority() - 1);
                            } 

                        }
                    }
                    broke = true;
                    break;
                }
            }
            if(broke){
                break;
            }
        }
             

    }
    
    /*
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
    */

}

