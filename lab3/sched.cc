
#include "prime.h"

using namespace std;
int main(int argc, char *argv[]){
    
    string method = argv[0];  //parse scheduling method
    int queues = -1;

    if(method == "mfqs"){

        // Collect the maximum
        cout << "\nEnter number of queues:";
        cin >> queues;
        cout << "\n";

    }else if(method == "rts"){

     
    }else if(method == "hs"){

    }
}

