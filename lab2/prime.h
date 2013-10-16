#ifndef PRIME_H
#define PRIME_H

#include <errno.h>
#include <iostream>
#include <fstream>
#include <signal.h>
#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h> 
#include <sys/socket.h>
#include <netinet/in.h>
#include <cmath>
#include <pthread.h>
#include <netdb.h>

/* client.cc */

/* server.cc */

/* prime.cc */
void sieve(int*, int, int);

void error(const char*);

#endif
