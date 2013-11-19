
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
        
    //for(int i = 0; i < v.size(); i ++){
    //    swap(v[i], new queue(process));
    //}
	
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
                }
            }
            v.push_back(queue); 
            //queue<Process> temp;
            //temp = v[i];
            //Process pp = temp.front();
            cout << "\nqueue" << i << endl;
            //pp.to_string();
    }
    
	bool all_done;
    int clock = 0;
    while(true){
		
		all_done = true;
		for(int i = 99; i >= 0 && all_done; i--){
			queue<Process> queue = v[i];
			if(queue.front().get_p_id() != -1){
				all_done = false;
			}
		}
		if(clock == 10 || all_done){
			break;
		}
		
        bool doclock = true;
        cout << "Clock: " << clock << endl;
        cout << "done.size(): " << done.size() << endl;
        //hundred count thingy
        /*
        if (clock != 0 && clock % 100 == 0){
            //loop through user processes
            for(int i = 0; i < 50; i++){
                cout << "loop1" << endl;
                queue<Process> queue = v[i];
                for(int j = 0; j < queue.size(); j++){
                    cout << "loop2" << endl;
                    Process p = queue.front();
                    queue.pop(); 
                    if(p.get_increment() == p.get_priority_original()){
                         for(int m = 0; m < 10; m++){
                            cout << "loop3" << endl;
                            //user
                            if(p.get_priority() < 49){
                                p.set_priority(p.get_priority() + 1);
                            } 
                         }
                    }
                    v[p.get_priority()].push(p);
                }
            } 

        }
        */
        //boolean to start from the top if any priority was changed
        bool broke = false;
        //loop to go through each queue from the highest priority to the lowest to run processes
        for(int i = 99; i >= 0; i--){
            //cout << "loop4" << endl;
            //user
            queue<Process> queue = v[i];
            cout << "queue.size(): of v[" << i << "]: " << queue.size() << endl;
            //loo[ to go through each process in the queue
            for(int j = 0; j < queue.size(); j++){
                //cout << "loop5" << endl;
				bool pdone = false;
                Process p = queue.front();
				
				queue.pop();
				
				exit(0);
				
                if(p.get_p_id() != -1){     
                    
                    //loop to run the process for the length of the time quantum
                    for(int k = 0; k < q; k++){
                        //cout << "loop6" << endl;
                        //if the process is on the second to last burst and has io
                        if(p.get_burst() == 1 && p.get_io() > 0){
                           //do IO
                           int original_io = p.get_io();
                           //loop to decrement io
                           for(int m = 0; m < original_io; m++){
                               //cout << "loop7" << endl;
                               p.set_io(p.get_io() - 1);
                               clock++;
                           }
                           doclock = false;
                           //loop to adjust priority
                           if(p.get_priority() < 50){
								for(int m = 0; m < original_io; m++){
									//cout << "loop8" << endl;	
									//user
									if(p.get_priority() < 49){
										p.set_priority(p.get_priority() + 1);
									} 
									
								}
							}
							
							
							v[p.get_priority()].push(p);
						   
                           //break the loops and start from the top
                           broke = true;
                           cout << "BROKE" << endl;
                           break;
                        }else{
							cout << "Running process............" << endl;
                            //decrement burst
                            if(p.get_burst() > 0){
                                p.set_burst(p.get_burst() - 1);
                                clock++;
                                doclock = false;
                            }else{
                                pdone = true;
                                done.push_back(p);  
                            }
                        }
                        
                    }
                    
                    if(broke){
                        cout << "BROKE" << endl;
                        break;
                    }
                    //if process isnt finished at end of time quantum, decrease priority by time quantum
                    if(!pdone){
                        if(p.get_priority() < 50){
							//cout << "loop66" << endl;
							//check not to go lower than original and lower than 0
							if(p.get_priority()-q > p.get_priority_original() && p.get_priority()-q> 0){                            
								p.set_priority(p.get_priority() - q);
                            }
                        }
						
						cout << "HERE" << endl;
						v[p.get_priority()].push(p);
						broke = true;
						cout << "BROKE" << endl;
						break;
					}
                    
                }
            }
            if(broke){
                cout << "BROKE" << endl;
                break;
            }
        }
        if(doclock){
            clock++;
        }
    }
	
	cout << "\n\n\n-----------------"<< endl;

	for(int i = 0; i < v[82].size(); i++){
		Process p = v[82].front();
		p.to_string();
		v[82].pop();
	}
	
}

