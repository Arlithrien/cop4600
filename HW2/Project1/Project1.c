#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <stdlib.h>
#include <string.h>



#define MAX_LINE		80 /* The maximum length command */

char* hist[10][MAX_LINE];
int history_wait[10];
int buffer = 0;
void init_history(void);
void free_history(void);
void print_history(void);
char** history_computation(char** args,int *needWait);

int main(void)
{
	char *args[MAX_LINE/2 + 1];	/* command line arguments */
    int should_run = 1;      /* flag to determine when to exit program */
	
	
		
    init_history();
    while (should_run){   
        printf("osh>");
        fflush(stdout);

        pid_t pid;

        char cmd_line[MAX_LINE+1];
        char *sptr = cmd_line;
        int isAmp=0;
        
        }
       
        
        int need_to_wait = 1;
        if(strlen(args[isAmp-1])==1 && args[isAmp-1][0]=='&') {
            need_to_wait = 0;
            free(args[isAmp-1]);
            args[isAmp-1]=NULL;
        } else {
            args[isAmp]=NULL;
        }
        if(strcmp(args[0],"exit")==0){
            free_history();
            return 0;
        }
        //History Computation
        if(strcmp(args[0],"history")==0) {
            print_history();
            continue;
        }
     
        pid = fork();
    
         
        /**
         * After reading user input, the steps are:
         * (1) fork a child process using fork()
         * (2) the child process will invoke execvp()
         * (3) if command included &, parent will invoke wait()
         */
    
    
	return 0;
}





        }