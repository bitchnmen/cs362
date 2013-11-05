
#include "sched.h"

using namespace std;
int main(int argc, char *argv[]){
    
    string method = "";
    bool loop = false;

    do {
        loop = false;
        method = "";

        cout << "\nWhat scheduler would you like to use?";
        cout << "\n 1. MFQS";
        cout << "\n 2. RTS";
        cout << "\n 3. HS";
        cout << "\n 0. EXIT";
        cout << "\n\nSelect a number: ";
        cin >> method;
        cout << "\n";


        int result;
        if(method == "1"){
            
            result = mfqs();

        }else if(method == "2"){
                
            result = rts(); 

        }else if(method == "3"){

            result = hs();    

        }else if(method == "0"){
            cout << "\n\nSelected EXIT\n";
            exit(1);

        }else{
            cout << "\nError on menu selection.\n";
            loop = true;
        }

    } while (loop);   
}

