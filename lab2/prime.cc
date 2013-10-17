
#include "prime.h"

using namespace std;
void sieve(int *isComposite, int maximum, int maxSqrt) {
    int m = isComposite[0];
    int currentPrime = m-1;

    //Loop through "maxSqrt" times through the array
    if(m <= maxSqrt){
           
        //Loop through the multiples of the number we're
        //looking at (m) and mark them as composite (1)
        for (int k = currentPrime * currentPrime; k <= maximum; k += currentPrime){
            if(isComposite[k+1] == 0){
                cout << "Removing: " << k << endl;
                isComposite[k+1] = 1;
            }
        }
    } 
}

void error(const char *msg){
    perror(msg);
    exit(1);
}

void writeFile(int *primeList, int max) {
    ofstream myfile;
    myfile.open("temp.txt");
    
    for (int i = 0; i < 10; i++) {
        if (primeList[i] != 1) {
            myfile << primeList[i];
        }
    }
    
    int count = 0;
	int j = max;
    while (count < 10) {
        if (primeList[j] != 1) {
            myfile << primeList[j];
            count++;
        }
		max--;
    }
    
    myfile.close();
}

//////////////////////////////////////////////////

/* bool sendAll(int socket, const void *data, ssize_t size) {
    ssize_t sent = 0;
    ssize_t just_sent;
    while (sent < size) {
        just_sent = send(socket, data, size - sent, 0);
        if (just_sent < 0) {
            return false;
        }
        sent += just_sent;
    }
    return true;
}

bool receiveAll(int socket, const void *data, ssize_t size) {
    ssize_t received = 0;
    ssize_t just_received;
    while (received < size) {
        just_received = recv(socket, data, size - received, 0);
        if (just_received < 0) {
            return false;
        }
        received += just_received;
    }
    return true;
} */