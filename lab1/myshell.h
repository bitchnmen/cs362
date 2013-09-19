#ifndef MYSHELL_H
#define MYSHELL_H

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <errno.h>
#include <signal.h>
#include <stdbool.h>

/* myshell.c methods */

void sig_handler(int);

int ampersand(char**);

int internal_command(char**);

int do_command(char**, int, int, char*, int, char*, bool);

int redirect_input(char**, char**);

int redirect_output(char**, char**);

int append_output(char**, char**);


/* lex.c methods */
char **get_line();

#endif
