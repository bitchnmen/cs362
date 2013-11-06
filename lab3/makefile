CC = gcc
CFLAGS=-g 
LIBS=-lpthread 
FLIBS=-lfl

all:
	g++ -c sched.cc
	g++ -c input.cc
	g++ -c hs.cc
	g++ -c rts.cc
	g++ -c mfqs.cc
	g++ -c stats.cc
	g++ -c process.cc
	g++ -o sched sched.o input.o hs.o rts.o mfqs.o stats.o process.o
		
clean:
	rm -f *.o *.*~ run
	
