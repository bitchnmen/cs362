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

using namespace std;

/* Process class */
class Car {
    private:
        int id;
		int arrival;
		int direction;
    public:
		Car();
        Car(int, int, int);
		void set_values(int, int, int);
		int get_arrival() {return arrival;}
		int get_direction() {return direction;}
		int get_id() {return id;}
		void set_arrival(int _arrival) {arrival = _arrival;}
		void set_direction(int _direction) {direction = _direction;}
		void set_id(int _id) {id = _id;}
};

static void * approachintersection(void* arg);

double rndom();

void drive();

void quickSort(Car*, int, int);
