
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
    
    //for(int i = 0; i < numLines; i++){
    //    v.push_back(queue<Process*>());
    // }
    
    for(int i =0; i < 100; i++){
            queue<Process> q;
            Process null = Process(-1,-1,-1,-1,-1,-1);
            q.push(null); 
            bool popped = false;
            for(int j = 0; j < numLines; j++){
                
                if(processes[j].get_priority() == i){
                    Process p = processes[j];
                    if(!popped){
                        q.pop();
                        popped = true;
                    }
                    q.push(p);
                    p = q.front();
                }
            }
            v.push_back(q); 
             
            queue<Process> temp = v[i];
            Process pp = temp.front();
            cout << "\nqueue" << i << endl;
            pp.to_string();
    }
   
    cout << "__________________________" << endl;

    Process p = v[66].front();
    p.to_string();

    int clock = 0;
    while(true){
         

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

