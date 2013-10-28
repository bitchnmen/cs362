
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

int sendAll(int socket_connection_fd, int *data, int max){
	//loop through array
	for(int i = 0; i < max+1; i++){
		//create a temp array to store single int
		int *tempArray = new int[1];
		tempArray[0] = data[i]; 
		//send individual int
		if((send(socket_connection_fd, tempArray, sizeof(int), 0)) == -1) {
			error("sendAll()");
			break;
		}
		//free the temp array from memory
		free(tempArray);
	}
	return data[0];
}

int recvAll(int socket_connection_fd, int *data, int max){
	//loop through array
	for(int i = 0; i < max+1; i++){
		//create a temp array to store single int
		int *tempArray = new int[1];
		//send individual int
		if((recv(socket_connection_fd, tempArray, sizeof(int), 0)) == -1) {
			error("recvAll()");
			break;
		}
		//free the temp array from memory
		data[i] = tempArray[0];
		free(tempArray);
	}
	
	return data[0];
}

void error(const char *msg){
    perror(msg);
    exit(1);
}

void writeFile(int *primeList, int max) {
    FILE * myfile;
    myfile = fopen("temp.txt", "w+");
    
    int count = 0;
    int i = 2;
    //write first 10 primes to file
    while (count < 10) {
        if (primeList[i+1] == 0) {
            fprintf (myfile, "%d\n",i);
            count++;
        }
        i++;
    }
    
        fprintf (myfile, "\n");
        
    count = 0;
	int j = max-1;
	//write last 10 primes to file
    while (count < 10) {
        if (primeList[j+1] == 0) {
            fprintf (myfile, "%d\n",j);
            count++;
        }
        j--;
    }
    fclose(myfile);
}

void printWholeArray(int *list, int max) {
    //loop through array and print out primes
	for (int i = 0; i < max; i++) {
        if(list[i+1] == 0){
            printf ("%d,",i);
        }
    }
	printf ("\n\n");
}