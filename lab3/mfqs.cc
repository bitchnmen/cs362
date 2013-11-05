
#include "sched.h"

using namespace std;

int mfqs(){
    int queues = -1;
    cout << "\n\nSelected MFQS";
    cout << "\nEnter number of queues(1-5): ";
    cin >> queues;
    cout << "\n";
    
    if(queues < 1 && queues > 5){
        cout << "\nError on menu selection.";
        exit(1);
    }
}
