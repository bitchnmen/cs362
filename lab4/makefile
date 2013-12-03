CC = gcc
CFLAGS=-g 
LIBS=-lpthread 
FLIBS=-lfl

all:
	g++ -c traffic.cc 
	g++ -o traffic traffic.o -lm -lpthread

clean:
	rm -f *.o *.*~ run
	
