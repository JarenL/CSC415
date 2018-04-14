/****************************************************************
 * Name        : Marlon Johnson                                 *
 * Class       : CSC 415                                        *
 * Date  	   : 3/4/18                                         *
 * Description :  Writting a simple bash shell program          *
 * 	        	  that will execute simple commands. The main   *
 *                goal of the assignment is working with        *
 *                fork, pipes and exec system calls.            *
 ****************************************************************/

#include <string.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

#define BUFFERSIZE 256
#define PROMPT "myShell >> "
#define PROMPTSIZE sizeof(PROMPT)
#define ARGVMAX 64
#define PIPECNTMAX 10 // only we need one pipe but if more we can create more
#define READ 0 // stdin for pipe
#define WRITE 1 // stdout for pipe
// #define READ1 2
// #define WRITE 3

int main(int argc, char** argv) {

    char buf[BUFFERSIZE];
    char *token;
    char *myargv[ARGVMAX];
    char *argvpipe[ARGVMAX];
    char *directory;
    int myargc;
    pid_t childPid; 
    pid_t pipeChild;   
    // int fd; // creating the pipes

    // pipe(fd); // fd[0] -> reading fd[1] -> writing fd[2] -> append -> fd[3] -> f[4]

    while (1) {
        int k = 0;
        int fd, byte_length;
        // int fd1[2];

        

        printf("%s", PROMPT);
		// myargv[BUFFERSIZE + 1] = (char**) malloc(sizeof(int*)*256);        
        // fflush(stdout); // just to know that I'm writing to the file
        // gets(buf);
        memset(buf, '\0', BUFFERSIZE);
        for (int i=0; i < ARGVMAX; i++) {
            myargv[i] = NULL;
        }
        if (fgets(buf, BUFFERSIZE, stdin) == NULL) {  // Ctrl + D
            break;
        } 
        // printf("$PATH %s", buf); // I guess for testing purposes 

        token = strtok(buf, " \t\n"); // tokenize the arguments
        if (token == NULL) {
            continue;
        } 
        
        if (strcmp(buf, "exit") == 0 ) {
            return 0;
        }
        // token = strtok(buf, " \n"); // tokenize the arguments
        while ( token != NULL ) {
            myargv[k] = token;
            // token = strtok(NULL, " ");
            // k++;
            token = strtok(NULL, " \n");
            k++; // go to next element
            
        }
        // begins the processID
        int fd1[2];
        childPid = fork();
        // pipeChild = fork();
        pipe(fd1);

        // tried to do the piping process 

        // child process 1
        // if ( pipeChild  > 0) {
        //     dup2(fd1[READ], READ);
        //     close(fd1[WRITE]);

        //     execvp(argvpipe[0], argvpipe);
        //     perror("execvp failed");

        // } else if ( (pipeChild == fork()) == 0) {
        //     dup2(fd1[WRITE], WRITE);

        //     close(fd1[READ]);
        //     execvp(argvpipe[0], argvpipe);
        // } else {
        //     waitpid(pipeChild, NULL, 0);
        // }


        if ( childPid < 0 ) {
            
            perror("failed to fork");
            exit(1);
        } else if ( childPid > 0 ) { // Parent Process
            // close(fd1[READ]); // closing the first file descriptor
            // dup2(fd1[WRITE], 1); // copying fd[write] 
            // close(fd1[WRITE]); // end file descriptor;

            // if (execlp(myargv[1], myargv[1], NULL) == -1) {
            //     perror("error execlp");
            // }  
            // Background Processing 
            if(strcmp(myargv[k-1], "&") == 0) {
                printf("Background process detected don't wait\n");
            }

            int status, pid;
            pid = wait(&status);
            printf("pid %d exit status %d\n", pid, status);
            // return 0;    
            sleep(1); // to givd more time for the child
            // wait(NULL);
        }

        else if ( childPid == 0 ) {

            // close(pipe[0]); // file 1 
            // int fd;
            // int in, out, append, change_directory = 1;
            if ( k > 2 ) {

                // if (in) {

                    // if ((fd[0] = open(myargv[k-2], O_RDONLY, 0)) < 0) {
                    //     perror("fd[0]->");
                    //     exit(0);
                    // }b

                if (strcmp(myargv[k-2], "<") == 0) { 

                    fd = open(myargv[k-1], O_RDONLY, 0);
                    dup2(fd, 0);
                // in = 0;
                    close(fd); 
                    
                }

                    // in = 1; // return successful if completed
            
                // }

                // if (out) {
                if (strcmp(myargv[k-2], ">") == 0) {

                    fd= open(myargv[k-1], O_CREAT | O_TRUNC | O_WRONLY, 0600);
                    dup2(fd, STDOUT_FILENO);
                    close(fd);
                }

                    // out = 1; // returns succesful if completed
                // }
                    // execvp(myargv[0], myargv);

                // if (append) {
                if (strcmp(myargv[k-2], ">>") == 0) {

                    fd = open(myargv[k-1], O_RDWR | O_CREAT| O_APPEND, 0644);
                    dup2(fd, STDOUT_FILENO);
                    close(fd);
                    
                }

                // if (strcmp(myargv[k-2], "|") == 0) {
                //     int write_passed = 
                //     fd = open(myargv[k-1], )
                // }


            }

            // piping process ending 

            // closing the pipes in the childer header

            // close(fd1[WRITE]);
            // dup2(fd1[READ], 0);
            // close(fd1[READ]); // closing the read descriptor
            // execute the reading command
            // if (execlp(argv[2], argv[2], NULL) ==  -1) { // Execute the reader passed arg 
            //     perror("connect");
            // }
            

            // pwd

            if (strcmp("pwd", myargv[0]) == 0) {
                char pwd[BUFFERSIZE];
                if (getcwd(pwd, BUFFERSIZE) != NULL) {
                    printf("%s\n", pwd);
                } else {
                    printf("pwd failed");
                }
                continue;
            }


                        // Cd 
            if (strcmp(myargv[0], "cd") == 0) {
                char *directory = myargv[1];
                int expected;
                expected = chdir(directory);
                if (expected == -1) {
                    perror("Directory failed");
                }
            } 
                // printf("\n");

                if (k > 1 && strcmp(myargv[k-1], "&") == 0) {
                    myargv[k-1] = NULL;
                } else if (k >2 && strcmp(myargv[k-2], "<") == 0) {
                    // Delete last two arguments for < case
                    myargv[k-2] = NULL;
                    myargv[k-1] = NULL;
                } else if (k > 2 && strcmp(myargv[k-2], ">") == 0) {
                    // Delete last two arguments for > case
                    myargv[k-2] = NULL;
                    myargv[k-1] = NULL;
                } else if (k > 2 && strcmp(myargv[k-2], ">>") == 0){
                    myargv[k-2] = NULL;
                    myargv[k-1] = NULL;
                } else if (k > 2 && strcmp(myargv[k-2], "|") == 0) {
                    myargv[k-2] = NULL;
                    myargv[k-1] = NULL;
                }

                execvp(myargv[0], myargv);
                // perror("execvp");
                // _exit(1);

                // if (strcmp(myargv[k-2], "exit")) {
                //     break;
                // }

            // if (execvp(buf, myargv) == -1) {
            //     perror(buf);
            //     return -1;
            // }
        }

    }

	return 1;

}
