#include "traffic.h"

pthread_mutex_t intersection_mutex;

int main(int argc, char *argv[]){
    int NUMCARS = -1;
    int MAXARRIVE = -1;
    cout << "\nSelect number of cars: ";
    cin >> NUMCARS;
   
    cout << "\nSelect max arrival time: ";
    cin >> MAXARRIVE;
    

    
    if(NUMCARS < 1){
        cout << "\n\n Please select a valid amount of cars. \n\n";
        exit(1);
    }

    if(MAXARRIVE < 1){
        cout << "\n\n Please select a valid maximum arrival time. \n\n";
        exit(1);
    }

   /*
    int index, tid;
    int carids[NUMCARS];
    pthread_t carthreads[NUMCARS];
   
      
    
    // Start up a thread for each car
    for(index = 0; index <NUMCARS; index++){
        carids[index] = index;
        tid = pthread_create(&carthreads[index], NULL, approachintersection,  (void*)&carids[index]);
    }

    // Wait for every car thread to finish
    for(index = 0; index <NUMCARS; index++){
        pthread_join(carthreads[index], NULL);
    }
   */

    queue< Car > n;
    queue< Car > s;
    queue< Car > e;
    queue< Car > w;
    Car[] = Car[NUMCARS];

    for(int i = 0; i < NUMCARS; i++){
        double temp = rndom();
        int cardirection = ((int)(temp * 4)) + 1;

       
        
        temp = rndom();
        int cararrival = ((int)(temp * MAXARRIVE)) + 1;

        Car c = Car(i + 1, cardirection, cararrival);
           
        if(cardirection = 1){
            n.push(c);
        }else if(cardirection = 2){
            s.push(c);
        }else if(cardirection = 3){
            e.push(c);
        }else{
            w.push(c);
        }

                 
    }

    
    
    int clock = 1;
    while(true){
        
        pthread_t carthreads[4];
        if(n.front().get_arrival() <= clock){
            pthread_create(&carthreads[0], NULL, approachintersection,  (void*)n.front().get_id());
        }
        if(n.front().get_arrival() <= clock){
            pthread_create(&carthreads[1], NULL, approachintersection,  (void*)s.front().get_id());
        }
        if(n.front().get_arrival() <= clock){
            pthread_create(&carthreads[2], NULL, approachintersection,  (void*)e.front().get_id());
        }
        if(n.front().get_arrival() <= clock){
            pthread_create(&carthreads[3], NULL, approachintersection,  (void*)w.front().get_id());
        }
        

    }
    
    printf("Done\n");
    return 1;
}

static void * approachintersection(void* arg){

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

    pthread_mutex_unlock(&intersection_mutex);
}

//Returns a random number from 0 to 1
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

int drive(int clock){
    //usleep(1000 * 1000);
    return clock++;
}

void quickSort(Car* arr, int left, int right) {
    int i = left, j = right;
    Car tmp;
    Car pivot = arr[(left + right) / 2];

    /* partition */
    while (i <= j) {
        cout << "arr[i] = " << arr[i].get_arrival() << endl;
        cout << "arr[j] = " << arr[j].get_arrival() << endl;
        cout << "pivot = " << pivot.get_arrival() << endl;

        while (arr[i].get_arrival() < pivot.get_arrival()){
            cout << "stuck i loop" << endl;
            i++;
        }
        while (arr[j].get_arrival() > pivot.get_arrival()){
            cout << "stuck in j loop" << endl;
            j--;
        }
        if (i<= j) {
            cout << "switching and incrementing" << endl;
            tmp = arr[i];
            arr[i] = arr[j];
            arr[j] = tmp;
            i++;
            j--;
        }
    };


