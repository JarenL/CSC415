
#include <stdio.h>
#include <string.h>
#include <unistd.h>

#define NAME "Marlon Johnson"

int main ( char** argv, int* argc) 
{
    char msg[256];
    int bytes_formatted = -1;
    int bytes_printed = -1;
    bytes_formatted = sprintf(msg, "CSC 415, This program is written by %s\n", NAME);
        
    if (bytes_formatted < 0) {
        perror("error running sprintf..");
    }
    
    bytes_printed = write(STDOUT_FILENO, msg, bytes_formatted);

    if (bytes_printed < 0 ) {
        perror("Error printing to FD...");
    }

    
    return 0;

}
