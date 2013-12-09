#include "traffic.h"

pthread_mutex_t intersection_semaphore;
int clock_;
int currCarId;
int numCarsPerTick;
int maxNumClockTicks;
vector< vector< Car* > > queueList;

int main(int argc, char *argv[]){
    cout << "\nSelect max number of cars to create per clocktick: ";
    cin >> numCarsPerTick;
   
    cout << "\nSelect max number of clockticks in which you can make cars: ";
    cin >> maxNumClockTicks;
    

    
    if(numCarsPerTick < 1){
        cout << "\n\n Please select a valid amount of cars per clocktick. \n\n";
        exit(1);
    }

    if(maxNumClockTicks < 1){
        cout << "\n\n Please select a valid maximum clockticks. \n\n";
        exit(1);
    }

	//Creates a new ArrayList, fills it with 4 linked lists, trims it to the appropriate size
	for (int i = 0; i < 4; i++) {
        vector< Car* > t;
		queueList.push_back(t);
	}
	
	// Create new cars, add cars to queue; This starts the entire process. 
	// In order to see the program run, there must be cars generated.
	generate_cars();


    while(true);	
	printf("\n\nDone\n");
}

void generate_cars(){
   
    // Printout showing the current car allocation
    printf("\nClock: %d", clock_);
    for (int i = 0; i < 4; i++) {
        vector< Car* > temp = queueList[i];
        printf("\nStreet %d: ", i);
        for(int j = 0; j < temp.size(); j++){
            if(temp[j]->get_id() != -1){
                printf( "Car %d, ", temp[j]->get_id());         
            }
        }
    }
    
    // Every time cars are generated, a random number of cars (to a point) are created and added to a random street
    if (clock_ < maxNumClockTicks) {
        double temp = rndom();
        int carsPerClockTick = ((int)(temp * 10));
        for (int i = 0; i < carsPerClockTick; i++) {
            temp = rndom();
            int direction = ((int)(temp * 4)); 
            
            //Cars are created, added, and then the thread starts.
            Car* ct = new Car();
            ct->set_id(++currCarId);
            ct->set_direction(direction);
            queueList[direction].push_back(ct);
            ct->start();
        }
    }
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

void drive(){
	clock_++;
	generate_cars();
}


static void* runThread(void* arg){
    
    return ((Thread*)arg)->run();
}

Thread::Thread() : m_tid(0), m_running(0), m_detached(0){}

Thread::~Thread()
{
    if (m_running == 1 && m_detached == 0) {
        pthread_detach(m_tid);
    }
    if (m_running == 1) {
        pthread_cancel(m_tid);
    }
}

int Thread::start()
{
    int result = pthread_create(&m_tid, NULL, runThread, this);
    if (result == 0) {
        m_running = 1;
    }
    return result;
}

int Thread::join()
{
    int result = -1;
    if (m_running == 1) {
        result = pthread_join(m_tid, NULL);
        if (result == 0) {
            m_detached = 0;
        }
    }
    return result;
}

int Thread::detach()
{
    int result = -1;
    if (m_running == 1 && m_detached == 0) {
        result = pthread_detach(m_tid);
        if (result == 0) {
            m_detached = 1;
        }
    }
    return result;
}

pthread_t Thread::self() {
    return m_tid;
}

int Car::get_id() {
    return id;
}

int Car::get_direction() {
    return direction;
}

void Car::set_id(int id_) {
    id = id_;
}

void Car::set_direction(int direction_) {
    direction = direction_;
}

void* Car::run() {
    pthread_mutex_lock(&intersection_semaphore);
    drive();
    pthread_mutex_unlock(&intersection_semaphore);
    vector< Car* > v = queueList[direction];	
    bool exit = false;
    for(int i = 0; i < v.size() && !exit; i++ ){
        if (v[i]->get_id() == id){
            exit = true;
            //v.erase(v.begin() + i);
            //printf("\nErased Car %d\n", id);
            printf("\nErased From %d\n", direction);
            v[i]->set_id(-1);
        }
    }
}


