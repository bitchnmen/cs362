CC = gcc
CFLAGS=-g 
LIBS=-lpthread 
FLIBS=-lfl

all:
	g++ -c -g traffic.cc
	g++ -o traffic traffic.o -lm -lpthread

clean:
	rm -f *.o *.*~ run
	
