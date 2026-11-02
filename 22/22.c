#define _GNU_SOURCE
#include <errno.h>
#include <fcntl.h>
#include <stdio.h>
#include <string.h>
#include <sys/select.h>
#include <sys/stat.h>
#include <unistd.h>

int main()
{
    if (mkfifo("fifo22", 0660) == -1 && errno != EEXIST) {
        perror("mkfifo");
        return 1;
    }
   
    int fd = open("fifo22", O_RDWR | O_NONBLOCK);
    
    fd_set readable;
    FD_ZERO(&readable);
    FD_SET(fd, &readable);

    struct timeval timeout = {10, 0};
    printf("Waiting for data in FIFO for 10 seconds...\n");
    fflush(stdout);

    int ready = select(fd + 1, &readable, NULL, NULL, &timeout);

    if (ready == 0) {
        puts("No FIFO data arrived within 10 seconds");
    } 
    else{

        char buffer[256];
        ssize_t count = read(fd, buffer, sizeof(buffer) - 1);
        if (count > 0) {
            buffer[count] = '\0';
            printf("Received: %s\n", buffer);
        }
    }

    close(fd);
    return 0;
}

/*
nilkanth@zuxxy: gcc 22.c && ./a.out 
Waiting for data in FIFO for 10 seconds...
Received: Hello from writer process!


write.c or printf "hello from writer\n" > fifo22 
will write in this fifo22
*/
