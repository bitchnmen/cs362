README
----------------------------------------------------------------------------------

AUTHORS
----------------------------------------------------------------------------------
Ben Singer and Mitchell Sheaffer

DESCRIPTION
----------------------------------------------------------------------------------
	This directory contains code for our C shell implementation. Our code is 
partially complete, containing the majority of the functionality listed in the 
document write up. The standard commands (#1-6), piping, and background processes 
work correctly and emulates the functionality in bash. 

The demo utilities have also been implemented correctly with the exception of 
parenthesis. With this utility we have somewhat functional code, however we 
commented it out to ensure our shell functions correctly.

The Flex scanner is used for parsing commands, and it works flawlessly with the 
exception of minor memory leaks. In fact, our code is relatively free of memory 
leaks. There are a number of areas where there are blocks that are still reachable, 
however investigation into the issue has shown that these “still reachable” blocks 
pose no threat to the system and aren’t considered true memory leaks by Valgrind. 

TO RUN
----------------------------------------------------------------------------------
Our code is run by first compiling with the command “make”. The compiled files can 
also be removed with the command “make clean”. After the files are compiled, the 
shell can be accessed with the command “./myshell”.

REFERENCED CODE
----------------------------------------------------------------------------------
For the piping portion of our code we referenced code that was found on Stack
Overflow at the following url: 
http://stackoverflow.com/questions/12679075/almost-perfect-c-shell-piping
We used some of the code line for line, however ended up modifying the code in 
order to make it functional within our do_command method.