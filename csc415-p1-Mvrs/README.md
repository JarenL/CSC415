# csc415-p1

This program makes use of sprintf which takes in a int value and writes that size of *this* creating a buffer then stores the contents in a character array. 
I believe it doesn't use STDOUT. The use of write is just a system call that we use to buffer the file in sizeof bytes. 

```c

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

```



This program was build with the use of the <b>MAKE</b> utility which helps automates the procress of before the code becomes executable
```
make hello_world
```   

After the use of make I built the program using this call
```
 ./hello_world
```
