#include <stdio.h>
#include <unistd.h>

int main(void)
{
    int channel[2];

    char message[] = "Data sent through a pipe";
    char received[128];
    
    pipe(channel);

    write(channel[1], message, sizeof(message) - 1);
    close(channel[1]);

    ssize_t length = read(channel[0], received, sizeof(received) );
    if (length == -1) {
        perror("read");
        return 1;
    }

    received[length] = '\0';
    printf("Read from pipe: %s\n", received);
    close(channel[0]);
    return 0;
}

/*
nilkanth@zuxxy: gcc 14.c && ./a.out 
Read from pipe: Data sent through a pipe
*/
