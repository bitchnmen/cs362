#define PRIME_H

#include <iostream>
#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h> 
#include <pthread.h>
#include <fstream>
#include <sstream>
#include <vector>
#include <math.h>
#include <map>
#include <queue>
#include <time.h>
#include <unistd.h>
#include <stdint.h>
#include <signal.h>

using namespace std;


static void * approachintersection(void* arg);

double rndom();


void generate_cars();

void increment_clock();

//Thread Class
class Thread{
  private:
    pthread_t  m_tid;
    int        m_running;
    int        m_detached;
  public:
    
    Thread();
    virtual ~Thread();
    
    int start();
    int join();
    int detach();
    pthread_t self();
    
    virtual void* run() = 0;
    
  };

//Car class
class Car : public Thread{
  private:
	int id;
	int direction;
    bool running;
     
  public:
    void* run();

	int get_direction();
	int get_id();
	void set_direction(int);
    void set_id(int);
    void set_running(bool);
    void drive();
    

};


