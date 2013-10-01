/*
 * This code implements a simple shell program
 * It supports the internal shell command "exit", 
 * backgrounding processes with "&", input redirection
 * with "<" and output redirection with ">".
 * However, this is not complete.
 */
 
#include "myshell.h"

extern char **get_line();
    
/*
 * The main shell function
 */ 
main() {
  int i;
  char **args; 
  int result;
  int block;
  int output;
  int input;
  char *output_filename;
  char *input_filename;
  int append;
  // Set up the signal handler
  //sigset(SIGCHLD, SIG_IGN);
  //sigaction (SIGCHLD, NULL, NULL);
	signal(SIGINT, SIG_DFL);
	signal(SIGQUIT, SIG_DFL);
	signal(SIGTSTP, SIG_DFL);
	signal(SIGTTIN, SIG_DFL);
	signal(SIGTTOU, SIG_DFL);
	signal(SIGCHLD, SIG_DFL);

  // Loop forever
  while(1) {
    
    // Print out the prompt and get the input
    printf("->");
    args = get_line();
    
    // No input, continue
    if(args[0] == NULL)
      continue;

    // Check for internal shell commands, such as exit
    if(internal_command(args))
      continue;

    // Check for an ampersand
    block = (ampersand(args) == 0);
	
    // Check for redirected input
    input = redirect_input(args, &input_filename);

    switch(input) {
    case -1:
      printf("Syntax error!\n");
      continue;
      break;
    case 0:
      break;
    case 1:
      printf("Redirecting input from: %s\n", input_filename);
      break;
    }

    // Check for redirected output
    output = redirect_output(args, &output_filename, &append);

    switch(output) {
    case -1:
      printf("Syntax error!\n");
      continue;
      break;
    case 0:
      break;
    case 1:
      printf("Redirecting output to: %s\n", output_filename);
      break;
    }
	
	printf("\n\n");
	
	handle_symbols(args, block, input, input_filename, 
	       output, output_filename, append, 0);
	
  }
}

/*
 * Check for ampersand as the last argument
 */
int ampersand(char **args) {
  int i;

  for(i = 1; args[i] != NULL; i++) ;

  if(args[i-1][0] == '&') {
    free(args[i-1]);
    args[i-1] = NULL;
    return 1;
  } else {
    return 0;
  }
  
  return 0;
}

/* 
 * Check for internal commands
 * Returns true if there is more to do, false otherwise 
 */
int internal_command(char **args) {
  if(strcmp(args[0], "exit") == 0) {
    exit(0);
  }
  
  return 0;
}

/* 
 * Do the command
 */
int do_command(char **args, int block,
	       int input, char *input_filename,
	       int output, char *output_filename, int append, int subshell) {
  
	int result;
	int status;
	int child_id;
  
	//count # of pipes in args
	int pipes = 0;
	int i;
	for(i = 0; args[i] != NULL; i++){
		if(args[i][0] == '|' && args[i+1][0] != '|'){
			pipes++;
		}
	}
  
	// The number of commands to run
    const int commands = pipes + 1;
    int pipefds[2*pipes];

    for(i = 0; i < pipes; i++){
        if(pipe(pipefds + i*2) < 0) {
            perror("Couldn't Pipe");
            exit(EXIT_FAILURE);
        }
    }

    int j = 0;
    int k = 0;
    int s = 1;
    int place;
    int commandStarts[10];
    commandStarts[0] = 0;

    // This loop sets all of the pipes to NULL
    // And creates an array of where the next
    // Command starts

    while (args[k] != NULL){
        if(!strcmp(args[k], "|")){
            args[k] = NULL;
            commandStarts[s] = k+1;
            s++;
        }
        k++;
    }

    for (i = 0; i < commands; ++i) {
        // place is where in args the program should
        // start running when it gets to the execution
        // command
        place = commandStarts[i];

        child_id = fork();
		
		// Check for errors in fork()
		switch(child_id) {
			case EAGAIN:
			perror("Error EAGAIN: ");
			return 1;
		case ENOMEM:
			perror("Error ENOMEM: ");
			return 1;
		}
		
        if(child_id == 0) {
            
			/* Set the handling for job control signals back to the default.  */
			
			dup2 (0, STDIN_FILENO);
			dup2 (1, STDOUT_FILENO);	
			dup2 (2, STDERR_FILENO);
			
			
			// Set up redirection in the child process
			if(input)
			freopen(input_filename, "r", stdin);

			if(output){
				if(append == 0){      
					freopen(output_filename, "w", stdout);
				}else{
					freopen(output_filename, "a", stdout);
				}	
			}
			
			//if not last command
            if(i < pipes){
                if(dup2(pipefds[j + 1], 1) < 0){
                    perror("dup2");
                    exit(EXIT_FAILURE);
                }
            }

            //if not first command&& j!= 2*pipes
            if(j != 0 ){
                if(dup2(pipefds[j-2], 0) < 0){
                    perror("dup2");
                    exit(EXIT_FAILURE);
                }
            }

            int q;
            for(q = 0; q < 2*pipes; q++){
                    close(pipefds[q]);
            }

            // The commands are executed here
            //if (subshell == 0){
				if(execvp(args[place], args + place) < 0 ){
                    perror(*args);
                    exit(EXIT_FAILURE);
				}
			//}else{ //attempt at subshells that doesn't work************
			//	char **enter_sub = malloc(1);
			//	char **exit_sub = malloc(1);
			//	enter_sub[0] = "./myshell";
			//	exit_sub[0] = "exit";
			//	
			//	if(execvp(enter_sub[0], enter_sub + 0) < 0 ){
            //      perror(*enter_sub);
            //      exit(EXIT_FAILURE);
			//	}
			//	if(execvp(args[place], args + place) < 0 ){
            //      perror(*args);
            //      exit(EXIT_FAILURE);
			//	}
			//	if(execvp(exit_sub[0], exit_sub + 0) < 0 ){
            //      perror(*exit_sub);
            //      exit(EXIT_FAILURE);
			//	}
			//}
        }
        else if(child_id > 0){
            
			
			
        } else {
			perror("error");
            exit(EXIT_FAILURE);
		}
		
		if (block) {
			waitpid(-1, NULL, WNOHANG);
		} else {
			setpgid(child_id, 0);
		}
		
        j+=2;
    }

    for(i = 0; i < 2 * pipes; i++){
        close(pipefds[i]);
    }
	
	if(block) {
		for(i = 0; i < pipes + 1; i++){
			wait(&status);
		}
	}
    
	return status;
}

/*
 * Check for input redirection
 */
int redirect_input(char **args, char **input_filename) {
  int i;
  int j;

  for(i = 0; args[i] != NULL; i++) {

    // Look for the <
    if(args[i][0] == '<') {
      free(args[i]);

      // Read the filename
      if(args[i+1] != NULL) {
	*input_filename = args[i+1];
      } else {
	return -1;
      }

      // Adjust the rest of the arguments in the array
      for(j = i; args[j-1] != NULL; j++) {
	args[j] = args[j+2];
      }

      return 1;
    }
  }

  return 0;
}

/*
 * Check for output redirection
 */
int redirect_output(char **args, char **output_filename, int *append) {
	int i;
	int j;
	*append = 0;

	for(i = 0; args[i] != NULL; i++) {
		// Look for the >
		if(args[i][0] == '>' && args[i+1][0] != '>'){
			free(args[i]);
			// Get the filename 
			if(args[i+1] != NULL) {
				*output_filename = args[i+1];
			} else {
				return -1;
			}
			// Adjust the rest of the arguments in the array
			for(j = i; args[j-1] != NULL; j++) {
				args[j] = args[j+2];
			}
			return 1;
		} else if (args[i][0] == '>' && args[i+1][0] == '>'){
			*append = 1;
			free(args[i]);
			free(args[i+1]);	
			// Get the filename 
			if(args[i+2] != NULL) {
				*output_filename = args[i+2];
			} else {
				return -1;
			}
			// Adjust the rest of the arguments in the array
			for(j = i; args[j-1] != NULL; j++) {
				args[j] = args[j+3];
			}
			return 1;
		}
	} 
  return 0;
}

/*
 * Method to handle symbols listed in the write up.
 */
int handle_symbols(char **args, int block,
	       int input, char *input_filename,
	       int output, char *output_filename, int append, int pipes) {
	
	int skip_next = 0;
	int subshell = 0;
	int i;
	int return_code;
	int n = 0;
	int z = 0;
	
	//Baller way of setting up an empty array because I don't really know c.
	//(Hopefully this wont have memory leaks although my brain says it will.)
	char *new_args[20];
	for(i = 0; i < sizeof(args); i++){
		new_args[i] = NULL;
	}
	clear_array(new_args);

	//loop for each case
	for(i = 0; args[i] != NULL; i++){
		if(args[i][0] == '('){ //Case: "("
			clear_array(new_args);
			n = 0;
			subshell = 1;
			
		}else if(args[i][0] == ')'){ //Case: ")"
			if(skip_next == 0 && new_args[0] != NULL){
				do_command(new_args, block, input, input_filename, 
							output, output_filename, append, subshell);
			}else{
				skip_next = 0;
			}
			clear_array(new_args);
			n = 0;
			subshell = 0;
			
		}else if(args[i][0] == ';'){ //Case: ";"
			if(skip_next == 0 && new_args[0] != NULL){
				do_command(new_args, block, input, input_filename, 
							output, output_filename, append, subshell);
			}else{
				skip_next = 0;
			}
			clear_array(new_args);
			n = 0;

		}else if(args[i][0] == '&' && args[i+1][0] == '&'){ //Case: "&&"
            if(skip_next == 0 && new_args[0] != NULL){
				return_code = do_command(new_args, block, input, input_filename, 
							output, output_filename, append, subshell);
			}else{
				skip_next = 0;
			}
			clear_array(new_args);
			n = 0;
			i = i + 1;
			if (return_code != 0) {
				skip_next = 1;
			}else{
				skip_next = 0;
			}
			
		}else if(args[i][0] == '|' && args[i+1][0] == '|'){ //Case: "||"
			if(skip_next == 0 && new_args[0] != NULL){
				return_code = do_command(new_args, 1, input, input_filename, 
							output, output_filename, append, subshell);
			}else{
				skip_next = 0;
			}
			clear_array(new_args);
			n = 0;
			i = i + 1;
            if (return_code != 0) {
				skip_next = 0;
			}else{
				skip_next = 1;
			}

		}else{ //Case: "Not a symbol. Add to temp array."
			new_args[n] = args[i];
			n = n + 1;
             
            if (args[i+1] == NULL){ //end of full command. execute last part if present.
				if(skip_next == 0 && new_args[0] != NULL){
					do_command(new_args, block, input, input_filename, 
							output, output_filename, append, subshell);
				}
			}
		}
	}
}

/*
 * Method to clear the passed in array.
 */
clear_array(char **new_args){
	int i;
	for(i = 0; new_args[i] != NULL; i++){
		new_args[i] = NULL;
	}	
}

/*
 * Method to print the passed in array.
 */
print_array(char **args){
    //printf("\n***************************\n");
	//int z;
    //for(z = 0; args[z] != NULL; z++){
	//    printf("\narg is %s\n", args[z]);
	//}
	//printf("\n***************************\n\n");
}


