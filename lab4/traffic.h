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

using namespace std;


static void * approachintersection(void* arg);

static void gostraight(int cardirection, unsigned int carnumber);

int rndom();


