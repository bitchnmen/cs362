CC = gcc
CFLAGS=-g 
LIBS=-lpthread 
FLIBS=-lfl

all:
	g++ -c -g traffic.cc
	g++ -c -g car.cc
	g++ -o traffic traffic.o car.o -lm -lpthread

clean:
	rm -f *.o *.*~ run
	
