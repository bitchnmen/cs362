#include "traffic.h"

pthread_mutex_t intersection_mutex;

int main(int argc, char *argv[]){
    int NUMCARS = -1;
    cout << "\nSelect number of cars: ";
    cin >> NUMCARS;
    
    if(NUMCARS < 1){
        cout << "\n\n Please select a valid amount of cars. \n\n";
        exit(1);
    }

    int index, tid;
    int carids[NUMCARS];
    pthread_t carthreads[NUMCARS];
    
    /* Start up a thread for each car*/ 
    for(index = 0; index <NUMCARS; index++){
        carids[index] = index;
        tid = pthread_create(&carthreads[index], NULL, approachintersection,  (void*)&carids[index]);
    }

    /* Wait for every car thread to finish */
    for(index = 0; index <NUMCARS; index++){
        pthread_join(carthreads[index], NULL);
    }
    printf("Done\n");
    return 1;
}
static void * approachintersection(void* arg){
	unsigned int * carnumberptr;
	unsigned int carnumber;
	double temp = rndom();
    int cardirection;
    if(temp >= .75){
         cardirection = 1;
    }else if(temp >= .50){
         cardirection = 2;
    }else if(temp >= .25){
         cardirection = 3;
    }else{
         cardirection = 4;
    }

    carnumberptr = (unsigned int*) arg;
	carnumber = (unsigned int) *carnumberptr;

    pthread_mutex_lock(&intersection_mutex);
    switch(cardirection){
        case 1:
            printf("Car %d, Moving North-South\n", carnumber);
            break;
        case 2:
            printf("Car %d, Moving South-North\n", carnumber);
            break;
        case 3:
            printf("Car %d, Moving East-West\n", carnumber);
            break;
        case 4:
            printf("Car %d, Moving West-East\n", carnumber);
            break;
    }

    drive();

    pthread_mutex_unlock(&intersection_mutex);
}

/* Returns a random number from 0 to 1 */ 
double rndom() { 
    const long A = 48271; 
    const long M = 2147483647; 
    const long Q = M/A; 
    const long R = M%A; 
     
    static long state = 1; 
    long t = A * (state % Q) - R * (state / Q); 

    if (t > 0) 
      state = t;
    else 
      state = t + M;
    return ((double) state/M); 
} 

void drive(){
    usleep(1000 * 1000);
}

