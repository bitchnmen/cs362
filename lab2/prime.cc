
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
	
	printWholeArray(data, 100);
	
	for(int i = 0; i < max+1; i++){
		int *tempArray = new int[1];
		
		tempArray[0] = data[i]; 
		
		//cout << "Sending: " << tempArray[0] << endl;
		if((send(socket_connection_fd, tempArray, sizeof(int), 0)) == -1) {
			perror("send()");
			break;
		}
		free(tempArray);
	}
	return data[0];
}

int recvAll(int socket_connection_fd, int *data, int max){

	for(int i = 0; i < max+1; i++){
		int *tempArray = new int[1];
		
		if((recv(socket_connection_fd, tempArray, sizeof(int), 0)) == -1) {
			perror("recv()");
			break;
		}
		
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
	
    while (count < 10) {
		cout << "j = " << j << endl;
        if (primeList[j+1] == 0) {
            fprintf (myfile, "%d\n",j);
            count++;
        }
        j--;
    }
    fclose(myfile);
}

void printWholeArray(int *list, int max) {
    for (int i = 0; i < max; i++) {
        if(list[i+1] == 0){
            printf ("%d,",i);
        }
    }
	printf ("\n\n");
}