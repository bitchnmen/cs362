CC = gcc
CFLAGS=-g 
LIBS=-lpthread 
FLIBS=-lfl

all:
	g++ -c server.cc
	g++ -c client.cc
	g++ -c prime.cc
	g++ -o server server.o
	g++ -o client client.o	
clean:
	rm -f *.o *.*~ run
	
