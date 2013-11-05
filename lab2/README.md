README
----------------------------------------------------------------------------------

AUTHORS
----------------------------------------------------------------------------------
Ben Singer and Mitchell Sheaffer

DESCRIPTION
----------------------------------------------------------------------------------
	This directory contains code for our C shell implementation. Our code is 
almost complete, containing the majority of the functionality listed in the 
document write up. It is fully functional when communicating between multiple
thingies, but only compiles on Shiva. We were unable to complete the Shiva testing
because it was slow/unaccessible for the majority of the time we were coding.

	In the file named prime.cc, we have two commented out methods called recvAll
and sendAll that use a different method of sending parts of our data array over the
TCP socket. The method we chose to submit was to send and receive each int in our
data array one at a time over the TCP socket. We recognize that this method may be
slower, however we were having problems with the commented out methods.

TO RUN
----------------------------------------------------------------------------------
Our code is run by first compiling with the command “make”, or the command "make
shiva" on Shiva.

The compiled files can also be removed with the command “make clean”. 

After the files are compiled, the program can be run with the commands
“server <port number>” and "client <hostname> <port number>". 

If you are running on shiva, you must run the commands
“serverS <port number>” and "clientS <hostname> <port number>".



REFERENCED CODE
----------------------------------------------------------------------------------
For the basic socket connection portion of our code we referenced code that was
found on Stack Overflow and Linuxhowtos.org at the following urls: 

http://stackoverflow.com/questions/13114458/almost-finished-c-prime-number-sieve-over-sockets

http://www.linuxhowtos.org/C_C++/socket.htm


We used some of the code line for line, however ended up modifying the code in 
order to make it functional within our implementation of the algorithm.