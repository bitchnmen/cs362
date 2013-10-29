CC = gcc
CFLAGS=-g 
LIBS=-lpthread 
FLIBS=-lfl

all:
	g++ -c server.cc
	g++ -c client.cc
	g++ -c prime.cc
	g++ -o server server.o prime.o
	g++ -o client client.o prime.o
	
shiva:
	g++ -c server.cc
	g++ -c client.cc
	g++ -c prime.cc
	g++ -o serverS server.o prime.o -lsocket -lnsl  
	g++ -o clientS client.o prime.o -lsocket -lnsl
		
clean:
	rm -f *.o *.*~ run
	rm temp.txt
	
