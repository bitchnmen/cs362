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
    Car *cars = new Car[NUMCARS];
    
    for(int i = 0; i < NUMCARS; i++){
        double temp = rndom();
        int cardirection = ((int)(temp * 4)) + 1;
       
        double temp2 = rndom();
        int cararrival = ((int)(temp2 * MAXARRIVE)) + 1;

        Car c = Car();
        c.set_id(i+1);
        c.set_arrival(cararrival);
        c.set_direction(cardirection);
           
        cars[i] = c;
    }

    quickSort(cars, 0, NUMCARS-1);

    for(int i = 0; i < NUMCARS; i++){
        cout << "ID: " << cars[i].get_id() << ", Arrival: " << cars[i].get_arrival() << ", Direction: " << cars[i].get_direction() << endl;      
        int cardirection = cars[i].get_direction();
        if(cardirection == 1){
            n.push(cars[i]);
        }else if(cardirection == 2){
            s.push(cars[i]);
        }else if(cardirection == 3){
            e.push(cars[i]);
        }else{
            w.push(cars[i]);
        }
    }
   
    cout << "\nn size: " << n.size() << endl;
    cout << "\ns size: " << s.size() << endl;
    cout << "\ne size: " << e.size() << endl;
    cout << "\nw size: " << w.size() << endl;
         
    int clock = 0;
    while(n.size() > 0 || s.size() > 0 || e.size() > 0 || w.size() > 0){
        int tempclock = clock;

        pthread_t carthreads[4];
        
        bool nn = false;
        bool ss = false;
        bool ee = false;
        bool ww = false;

        if(n.front().get_arrival() <= clock && n.front().get_id() > 0){
        cout << "\nClock: " << clock << endl; 
            pthread_create(&carthreads[0], NULL, approachintersection,  (void*)n.front().get_direction());
            clock++;
            printf("Car %d, Moving North-South\n", n.front().get_id());
            n.pop();
            nn = true;
        }
        if(s.front().get_arrival() <= clock && s.front().get_id() > 0){
        cout << "\nClock: " << clock << endl; 
            pthread_create(&carthreads[1], NULL, approachintersection,  (void*)s.front().get_direction());
            clock++;
            printf("Car %d, Moving South-North\n", s.front().get_id());
            s.pop();
            ss = true;
        }
        if(e.front().get_arrival() <= clock && e.front().get_id() > 0){
        cout << "\nClock: " << clock << endl; 
            pthread_create(&carthreads[2], NULL, approachintersection,  (void*)e.front().get_direction());
            clock++;
            printf("Car %d, Moving East-West\n", e.front().get_id());
            e.pop();
            ee = true;
        }
        if(w.front().get_arrival() <= clock && w.front().get_id() > 0){
        cout << "\nClock: " << clock << endl; 
            pthread_create(&carthreads[3], NULL, approachintersection,  (void*)w.front().get_direction());
            clock++;
            printf("Car %d, Moving West-East\n", w.front().get_id());
            w.pop();
            ww = true;
        }
        if(clock == tempclock){
        cout << "\nClock: " << clock << endl; 
            clock++;
            printf("No cars drove through the intersection.\n");
        }
        
        // Wait for every car thread to finish
        if(nn == true){
            pthread_join(carthreads[0], NULL);
        }
        if(ss == true){
            pthread_join(carthreads[1], NULL);
        }
        if(ee == true){
            pthread_join(carthreads[2], NULL);
        }
        if(ww == true){
            pthread_join(carthreads[3], NULL);
        }


    }
    
    printf("Done\n");
    return 1;
}

static void * approachintersection(void* arg){
    pthread_mutex_lock(&intersection_mutex);
    pthread_mutex_unlock(&intersection_mutex);
}

//Returns a random number from 0 to 1
double rndom() { 
    const long A = 48271; 
    const long M = 2147483647; 
    const long Q = M/A; 
    const long R = M%A; 
     
    srand (time(NULL));
    static long state = rand(); 
    long t = A * (state % Q) - R * (state / Q); 

    if (t > 0) 
      state = t;
    else 
      state = t + M;
    return ((double) state/M); 
} 

void drive(int clock){
    clock++;
}

void quickSort(Car* arr, int left, int right) {
    int i = left, j = right;
    Car tmp;
    Car pivot = arr[(left + right) / 2];

    // partition
    while (i <= j) {
        while (arr[i].get_arrival() < pivot.get_arrival()){
            i++;
        }
        while (arr[j].get_arrival() > pivot.get_arrival()){
            j--;
        }
        if (i<= j) {
            tmp = arr[i];
            arr[i] = arr[j];
            arr[j] = tmp;
            i++;
            j--;
        }
    };
    
    // recursion
    if (left < j)
        quickSort(arr, left, j);
    if (i < right)
        quickSort(arr, i, right);
}

