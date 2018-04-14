#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
 

#define fullName "Marlon Johnson"
#define BUFFER_SIZE 27

int main(int argc, char *argv[]) {

    char buffer[BUFFER_SIZE+1];
    // creates null terminator: takes care of any extra char printed to the screen
    buffer[BUFFER_SIZE] = '\0';

    char file[100];
    char file2[100];
    
    printf("\nWelcome to the File Copy Program by %s\n", fullName);

    printf("\nEnter the name of the file to copy from: ");
    scanf("%s", file);

    // file 1 {Checks for permissions}
    int readIn = open(file, O_RDONLY);

    if ( readIn < 0) {
        printf("\nError: file isn't in the directory\n");
        return 1;
    }

    printf("\nEnter the name of the file to copy to:  ");
    scanf("%s", file2);

    // file 2 {Reads and Writes; also checks for file exists}
    int readOut = open(file2, O_RDWR | O_CREAT | O_EXCL, S_IRUSR | S_IWUSR );

    if ( readOut < 0 ) {
        printf("\nThe File already already exist create a new one\n");
        return 1;
    }    

    int bytes_read = -1;
    int bytes_written = 0;
    int grab_rest_of_bytes = 0;

    // to read | write bytes 
    while( bytes_read != 0) {

        bytes_read = (int) read(readIn, buffer, 1);
        
        bytes_written = (int) write(readOut, buffer, bytes_read);

        ++grab_rest_of_bytes;
    }

    printf("\nFile copied Successful, %d bytes copied\n", grab_rest_of_bytes-1); // reads n-1 bytes 

    if (close(readIn) < 0) {
        printf("Issue closing file");
        return 1;
    }

    if (close(readOut) < 0) {
        printf("Issue closing file");
        return 1;
    }

    close(readIn);

    close(readOut);
    
    return 0;

}