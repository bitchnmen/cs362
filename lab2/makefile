CC = gcc
CFLAGS=-g 
LIBS=-lpthread 
FLIBS=-lfl

all:
	flex lex.c
	gcc -g -c lex.yy.c myshell.c
	gcc -g -Wall -o myshell myshell.o lex.yy.o -lfl 
clean:
	rm -f *.o *.*~ run
	rm -f *.yy.c *.*~ run
	
