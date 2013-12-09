README
----------------------------------------------------------------------------------

AUTHORS
----------------------------------------------------------------------------------
Ben Singer and Mitchell Sheaffer

DESCRIPTION
----------------------------------------------------------------------------------
	This directory contains code for our Traffic implementation. Our code is complete,
and all of the functionality contained in the write up. It functions well, but slowly,
especially in large sets. We have tested the code rigorously, and it appears to function
well under the majority of tests.

	In both Java and C++, traffic arrives at every single clock tick, as opposed to
all at once. Both implementations follow the same pattern.

	The "Traffic - Java Files" is different in that it contains code for two Java 
implementations. Traffic1.java and Traffic1.jar contains coad that runs as stated in class, 
office hours, and in the write up. Traffic arrives, processes are started, and then the
code goes through and handles which one will be chosen next.

Traffic2.java and .jar feature a slightly different implementation, where the processes
are left up to themselves to decide which process should go to through the intersection
next. It is significantly faster, but does not fulfill the requirements of the assignment
completely.

TO RUN
----------------------------------------------------------------------------------
C++ code is compiled first by typing make. To run, enter "traffic" and then follow the
instructions.

The Java code was compressed into an executable jar, and can be run with the command 
"java -jar Traffic1.jar".


REFERENCED CODE
----------------------------------------------------------------------------------
Java style threads were created using code referenced from the following site

https://github.com/vichargrave/threads

We used some of the code line for line, however ended up modifying the code in 
order to make it functional within our implementation of the algorithm.