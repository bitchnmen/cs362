
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
                //cout << "Removing: " << k << endl;
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