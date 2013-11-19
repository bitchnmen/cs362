CC = gcc
CFLAGS=-g 
LIBS=-lpthread 
FLIBS=-lfl

all:
	g++ -c -g sched.cc
	g++ -c -g input.cc
	g++ -c -g hs.cc
	g++ -c -g rts.cc
	g++ -c -g mfqs.cc
	g++ -c -g stats.cc
	g++ -c -g process.cc
	g++ -o sched sched.o input.o hs.o rts.o mfqs.o stats.o process.o
		
clean:
	rm -f *.o *.*~ run
	
